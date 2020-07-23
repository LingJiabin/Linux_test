/*SMIME格式的PKCS7 验证签名
    使用参数：
        签名文件    sign_test
        证书文件    my.pem

    命令形式：
    openssl smime -verity -in sign_test -CAfile my.pem -signer my.pem    
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<openssl/err.h>
#include<openssl/pkcs7.h>
#include<openssl/pem.h>
#include<openssl/evp.h>
#include <openssl/x509_vfy.h>

#define SIGN_FILE ("sign_test")
#define CAfile ("my.pem")

int main(){

    int flags = PKCS7_DETACHED;
    flags &= ~PKCS7_DETACHED;

    BIO* in_data = BIO_new(BIO_s_file());
    BIO* out_data = BIO_new(BIO_s_file());
    BIO* indata = NULL;
    BIO_read_filename(in_data, SIGN_FILE);
    BIO_set_fp(out_data, stdout, BIO_NOCLOSE);
    PKCS7 *pk7 = SMIME_read_PKCS7(in_data, &indata);

    if(pk7==NULL){
        printf("pk7 NULL\n");
    }

    X509_STORE *store = X509_STORE_new();
    X509_LOOKUP *lookup;

    if(store==NULL){
        printf("store NULL\n");
    }

    lookup = X509_STORE_add_lookup(store, X509_LOOKUP_file());
    //X509_STORE_set_verify_cb(store, NULL);

    if((X509_LOOKUP_load_file(lookup, CAfile, X509_FILETYPE_PEM))==0){
        printf("lookup_load_file\n");
    }

    if((PKCS7_verify(pk7, NULL, store, indata, out_data, flags))){
        printf("success end\n");

      
        BIO_free(in_data);
        BIO_free(out_data);
        BIO_free(indata);
        PKCS7_free(pk7);
        X509_STORE_free(store);
        X509_LOOKUP_free(lookup);
        
    }
    else{
        printf("failure end\n");

        BIO_free(in_data);
        BIO_free(out_data);
        BIO_free(indata);
        PKCS7_free(pk7);
        X509_STORE_free(store);
        X509_LOOKUP_free(lookup);

    }


    

    return 1;
}
