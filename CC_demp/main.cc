#include "lib/p7_sign.h"
#include "lib/p7_verify.h"
#include "lib/s_decrypt.h"
#include "lib/s_encrypt.h"

#include <stdio.h>
#include <stdlib.h>



int main(int argc, char **argv){

	int ret = 0;
	int com = *argv[1] - '0';
	//printf("com: %d argv[1]:%s\n", com, argv[1]);
	char *Data, *En_Data, *Sign_Data;
	char *Key;
	char *Signer;
	char *Out;

	switch (com)
	{
	case 1:
		Data = argv[2];
		Key = argv[3];
		Signer = argv[4];
		Out = argv[5];
		ret = P7_Sign(Data, Key, Signer, Out);
		break;
	case 2:
		Sign_Data = argv[2];
		Signer = argv[3];
		ret = P7_Verify(Sign_Data, Signer);
		break;
	case 3:
		Data = argv[2];
		Signer = argv[3];
		Out = argv[4];
		ret = SMIME_Encrypt(Data, Signer, Out);
		break;
	case 4:
		En_Data = argv[2];
		Key = argv[3];
		Out = argv[4];
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
