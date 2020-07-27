/* 构造SMIME格式的数字信封
使用参数：
    明文内容：test
    接收者证书：my.pem
输出文件：
    密文：test.env
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<openssl/safestack.h>
#include<openssl/pkcs7.h>
#include<openssl/pem.h>
#include<openssl/evp.h>
/*
#define DATA ("test")
#define CERT ("my.pem")
#define DATA_OUT ("env_test")
*/

int SMIME_Encrypt(char *Data, char *Signer, char *Out){

    int flags = PKCS7_DETACHED;
    const EVP_CIPHER *cipher = NULL;
    flags &= ~PKCS7_DETACHED;

    FILE *cert = fopen(Signer, "r");
    FILE *data_out = fopen(Out, "w");
    BIO *in = BIO_new(BIO_s_file());
    BIO *out = BIO_new(BIO_s_file());
    STACK_OF(X509) *encerts = NULL;
    X509 *cert1 = NULL; 
    PKCS7 *pk7 = NULL; 
    BIO_read_filename(in, Data);
    BIO_set_fp(out, data_out, BIO_NOCLOSE);

    if((PEM_read_X509(cert, &cert1, NULL, NULL))==NULL){
        printf("cert1 NULL\n");
        return 0;
    }

    encerts = sk_X509_new_null();
    cipher = EVP_des_ede3_cbc();

    if((sk_X509_push(encerts, cert1))==NULL){
        printf("push X509 NULL\n");
        return 0;
    }

    if((pk7 = PKCS7_encrypt(encerts, in, cipher, flags))==NULL){
        printf("pk7==NULL \n");
        return 0;
    }

    if((SMIME_write_PKCS7(out, pk7, in, flags))==0){
        printf("write == 0 \n");

        //EVP_CIPHER_meth_free((EVP_CIPHER *)cipher);
        fclose(cert);
        fclose(data_out);
        BIO_free(in);
        BIO_free(out);
        sk_X509_free(encerts);
        X509_free(cert1); 
        PKCS7_free(pk7); 
        return 0;

    }else{
        printf("seccess write \n");
        
        //EVP_CIPHER_meth_free((EVP_CIPHER *)cipher);
        fclose(cert);
        fclose(data_out);
        BIO_free(in);
        BIO_free(out);
        sk_X509_free(encerts);
        X509_free(cert1); 
        PKCS7_free(pk7); 
        return 1;
    }
}
