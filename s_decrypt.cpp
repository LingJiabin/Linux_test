#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<openssl/safestack.h>
#include<openssl/pkcs7.h>
#include<openssl/pem.h>

#define DATA ("env_test")
#define DATA_OUT ("test_out")
#define PRIVATE_KEY ("private.key")

int main(int argc, char **argv){

    int flags = PKCS7_DETACHED;
    flags &= ~PKCS7_DETACHED;

    BIO *in = BIO_new(BIO_s_file());
    BIO *out = BIO_new(BIO_s_file());
    BIO *indata = NULL;
    BIO *key = NULL;
    PKCS7 *pk7 = NULL;
    EVP_PKEY *E_key = NULL;
    X509* recip = NULL;

    FILE *data_out = fopen(DATA_OUT, "w");
    FILE *key_in = fopen(PRIVATE_KEY, "r");

    E_key = PEM_read_PrivateKey(key_in, NULL, NULL, NULL);
    /*
    if(E_key == NULL){
        printf("E_key==NULL \n");
    }
    if((PEM_write_bio_PrivateKey(key, E_key, NULL, NULL, NULL, NULL, NULL))==0){
        printf("E_key 0 \n");
    }
*/
    if((PEM_write_bio_PrivateKey(key, E_key, NULL, NULL, NULL, NULL, NULL))==0){
        printf("key 0 \n");
    }
    

    BIO_read_filename(in, DATA);
    BIO_set_fp(out, data_out, BIO_NOCLOSE);

    pk7 = SMIME_read_PKCS7(in, &indata);

    if(pk7==NULL){
        printf("pk7==NULL \n");
    }

    if(PKCS7_decrypt(pk7, E_key, recip, out, flags)==NULL){
        printf("failure decrypt\n");
        fclose(data_out);
        fclose(key_in);
        BIO_free(in);
        BIO_free(out);
        BIO_free(indata);
        PKCS7_free(pk7);
        EVP_PKEY_free(E_key);
        X509_free(recip);
    }
    else{
        printf("seccess decrypt\n");
        fclose(data_out);
        fclose(key_in);
        BIO_free(in);
        BIO_free(out);
        BIO_free(indata);
        PKCS7_free(pk7);
        EVP_PKEY_free(E_key);
        X509_free(recip);
    }

    return 1;
}   