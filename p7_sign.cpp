
/*SMIME格式的PKCS7 签名
    使用参数：
        签名文件：test
        密钥：  private.key
        证书:   my.pem

    命令形式： 
    openssl smime -sign -in test -inkey private.key -signer my.pem
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<openssl/err.h>
#include<openssl/pkcs7.h>
#include<openssl/pem.h>
#include<openssl/evp.h>


#define PRIVATE_KEY ("private.key")
#define PUBLIC_KEY ("public.key")
#define SIGNCERT ("my.pem")
#define DATA ("test")
#define OUT ("sign_test")



int main(int argc, char **argv){

    PKCS7 *pk7;
    X509 *cert1 = NULL; 
    FILE *cert = fopen(SIGNCERT,"r");
    FILE *key = fopen(PRIVATE_KEY, "r");
    FILE *sign_in = fopen(DATA, "rb");
    FILE *sign_out = fopen("sign_test","w+");

    int flags = PKCS7_DETACHED;
    flags |= PKCS7_TEXT;
    flags |= PKCS7_STREAM;
    flags |= PKCS7_PARTIAL;

    char buff[200];
    if(PEM_read_X509(cert, &cert1, NULL, NULL)==NULL){
        printf("Read x509 failure\n");
        return 0;
    }

    BIO* bio_data = BIO_new(BIO_s_file());
    BIO* bio_out = BIO_new(BIO_s_file());
    //BIO_read_filename(bio_data, DATA);
    BIO_set_fp(bio_data, sign_in, BIO_NOCLOSE);
    BIO_set_fp(bio_out, sign_out, BIO_NOCLOSE);
    
    /*
    int format = FORMAT_SMIME;
    BIO* bio_data = BIO_new_file(DATA, "r");
    BIO* bio_out = BIO_new_file(OUT, "w");
    */

    EVP_PKEY *a_key=NULL;
    a_key = PEM_read_PrivateKey(key, NULL, NULL, NULL);
    //d2i_PrivateKey_fp(key, &a_key);


    pk7 = PKCS7_sign(NULL, NULL, NULL, bio_data, flags);

    if(pk7==NULL){
        printf("pk7 NULL\n");
    }

    if(cert1==NULL){
        printf("cert1 NULL\n");
    }
     if(a_key==NULL){
        printf("a_key NULL\n");
    }

    if((PKCS7_sign_add_signer(pk7, cert1, a_key, NULL, flags))==NULL){
        printf("P_S_a_s failure\n");
    }

    

    if((SMIME_write_PKCS7(bio_out, pk7, bio_data, flags))==NULL){
        printf("s_w_p failure\n");
    }

    if(pk7==NULL){
        printf("pk7 failure\n");

        fclose(cert);
        fclose(key);
        fclose(sign_out);
        BIO_free(bio_data);
        BIO_free(bio_out);
        PKCS7_free(pk7);
        X509_free(cert1);
        EVP_PKEY_free(a_key);
    }
    else{
        printf("pkcs7 sign success\n");

        fclose(cert);
        fclose(key);
        fclose(sign_out);
        BIO_free(bio_data);
        BIO_free(bio_out);
        PKCS7_free(pk7);
        X509_free(cert1);
        EVP_PKEY_free(a_key);
    }

    return 1;
}