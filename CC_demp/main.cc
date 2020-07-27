#include "lib/p7_sign.h"
#include "lib/p7_verify.h"
#include "lib/s_decrypt.h"
#include "lib/s_encrypt.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

int main(int argc, char **argv){

	int ret = 0;
	//int com = *argv[1] - '0';
	//printf("com: %d argv[1]:%s\n", com, argv[1]);
	int opt;
	int opt_n;
	int opt_index = 0;
	char *optString = "i:o:k:c:";

	static struct option long_option[] = {
		{"sign", 0, NULL, 's'},
		{"verify", 0, NULL, 'v'},
		{"encrypt", 0, NULL, 'e'},
		{"decrypt", 0, NULL, 'd'},
		{0, 0, 0, 0}
	};
	
	char *i = NULL, *k = NULL, *c = NULL, *o = NULL;

	while((opt = getopt_long(argc, argv, optString, long_option, &opt_index))!=-1){
		switch (opt)
		{
		case 'i':
			i = argv[optind-1];
			break;
		case 'k':
			k = argv[optind-1];
			break;
		case 'c':
		c = argv[optind-1];
		break;
		case 'o':
			o = argv[optind-1];
			break;
		default:
			opt_n = opt;
			break;
		}
	}

	char *Data, *En_Data, *Sign_Data;
	char *Key;
	char *Signer;
	char *Out;

	switch (opt_n)
	{
	case 's':
		Data = i;
		Key = k;
		Signer = c;
		Out = o;
		ret = P7_Sign(Data, Key, Signer, Out);
		break;
	case 'v':
		Sign_Data = i;
		Signer = c;
		ret = P7_Verify(Sign_Data, Signer);
		break;
	case 'e':
		Data = i;
		Signer = c;
		Out = o;
		ret = SMIME_Encrypt(Data, Signer, Out);
		break;
	case 'd':
		En_Data = i;
		Key = k;
		Out = o;
		ret = SMIME_Decrypt(En_Data, Key, Out);
		break;
	default:
		ret = 0;
		break;
	}

	if(ret == 1){
		printf("success \n");
		return 1;
	}
	else{
		printf("failure \n");
		return 0;
	}

}
