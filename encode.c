#include <stdio.h>
#include <string.h>
#include "xxtea.h"

#define ENCODE_KEY "Key"
#define ENCODE_SIGN "XXTEA"

int getFileSize(const char *name)
{
	FILE *file = fopen(name, "rb");
    fseek(file, 0, SEEK_END);
    int fsize = ftell(file);
    fclose(file);
    return fsize;
}

void 
encodeFile(const char *name, unsigned char *key, char *sign)
{
	int fileSize = getFileSize(name);

    FILE *file = fopen(name, "rb");

    printf("read file size:%d\n", fileSize);

    char *content = (char *)malloc(fileSize);

    size_t size = fread(content, 1, fileSize, file);
    fclose(file);

    printf("file size:%d\n content:11\n%s\n", size, content);

    xxtea_long ret_length;

    unsigned char *result = xxtea_encrypt(content, size, key, strlen(key), &ret_length);
    printf("len11:%d\n", ret_length);
    
    free(content);

    xxtea_long signContentLen =  ret_length + strlen(sign);
    unsigned char* signContent = (unsigned char *)malloc(signContentLen);
    memcpy(signContent, sign, strlen(sign));
    memcpy(signContent + strlen(sign), result, ret_length);

    FILE *wfile = fopen(name, "wb");
    fwrite(signContent, signContentLen, 1, wfile);
    fclose(wfile);

    free(signContent);
}

void 
decodeFile(const char *name, unsigned char *key, char *sign)
{
	int fileSize = getFileSize(name);

	FILE *file = fopen(name, "rb");
    char *content = (char *)malloc(fileSize);

    size_t size = fread(content, 1, fileSize, file);
    fclose(file);

    printf("file size:%d\n content:11\n%s\n", size, content);

    xxtea_long signLen = strlen(sign);
    printf("signLen:%d\n", signLen);

    xxtea_long ret_length;

    unsigned char *result = xxtea_decrypt(content + signLen, size - signLen, key, strlen(key), &ret_length);
    printf("len11:%d\n", ret_length);

    free(content);

    FILE *wfile = fopen(name, "wb");
    fwrite(result, ret_length, 1, wfile);
    fclose(wfile);
}

int 
main(int argc, char const *argv[])
{
	printf("argc: %d\n", argc);

	if(argc >= 3)
	{
		unsigned char *key;
		char *sign;
		if(argc >= 4)
		{
			key = (unsigned char *)argv[3];
		}
		else
		{
			key = ENCODE_KEY;
		}
		if(argc >= 5)
		{
			sign = (char *)argv[4];
		}
		else
		{
			sign = ENCODE_SIGN;
		}

	    printf("0:%s 1:%s\n", argv[1], argv[2]);
	    if(strcmp(argv[1], "e") == 0)
	    {
	    	encodeFile(argv[2], key, sign);
	    }
	    else if(strcmp(argv[1], "d") == 0)
	    {
	    	decodeFile(argv[2], key, sign);
	    }
	}
	// decodeFile("main.lua");

	// system("pause");
	return 0;
}