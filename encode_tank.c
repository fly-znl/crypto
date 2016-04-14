#include <stdio.h>
#include <string.h>

int getFileSize(const char *name)
{
	FILE *file = fopen(name, "rb");
    fseek(file, 0, SEEK_END);
    int fsize = ftell(file);
    fclose(file);
    return fsize;
}

void 
encodeFile(const char *name)
{
	printf("----encodeFile---%s\n", name);
	int fileSize = getFileSize(name);

    FILE *file = fopen(name, "rb");

    char *content = (char *)malloc(fileSize);

    size_t size = fread(content, 1, fileSize, file);
    fclose(file);

    printf("file size:%d\n content:\n%s\n", size, content);

    int offset = 10;

    int resultSize = size - offset;
    char *result = (char *)malloc(resultSize);

    for (int i = offset; i < size ; ++i)
    {
    	result[i - offset] = content[i] ^ 23;
    	// printf("---------%c\n", content[offset + 2] ^ 23);
    }
    
    FILE *wfile = fopen(name, "wb");
    fwrite(result , resultSize, 1, wfile);
    fclose(wfile);


}

int 
main(int argc, char const *argv[])
{
	if(argc >= 1)
	{
		encodeFile(argv[1]);
	}

    encodeFile("json.lua");
	// encodeFile("ActivityAddUpCashRef.lua");
	// system("pause");
}