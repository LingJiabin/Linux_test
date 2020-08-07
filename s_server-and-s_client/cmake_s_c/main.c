#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>


#include "lib/s_server.h"
#include "lib/s_client.h"



int main(int argc, char **argv){

    int opt;    
    int opt_n;
    int opt_index;
    char *opstring = "i:p:k:c:f:";
    static struct option long_option[] = {
        {"server", 0, NULL, '1'},
        {"client", 0, NULL, '2'},
        {"Ip", 1, NULL, 'i'},
        {"Port", 1, NULL, 'p'},
        {"Key", 1, NULL, 'k' },
        {"Cert", 1, NULL, 'c'},
        {"CAfile", 1, NULL, 'f'},
        {0, 0, 0, 0}
    };

    char *i = NULL, *k = NULL, *c = NULL, *ca = NULL;
    int p;

    while((opt = getopt_long(argc, argv, opstring, long_option, &opt_index))!=-1){
        switch (opt)
        {
        case 'i':
            i = argv[optind-1];
	    printf("ip:%s\n", i);
            break;
        case 'p':
            p = atoi(argv[optind-1]);
            printf("port:%d\n", p);
            break;
        case 'k':
            k = argv[optind-1];
            break;
        case 'c':
            c = argv[optind-1];
            break;
        case 'f':
            ca = argv[optind-1];
            break;
        default:
            opt_n = opt;
            break;
        }
    }

    int ret = 0;
    switch (opt_n)
    {
    case '1':
        ret = s_server(i, p, k, c, ca);
        break;
    default:
        ret = s_client(i, p, k, c, ca);
        break;
    }


    return 1;
}
