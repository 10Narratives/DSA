#include <string.h>

#define BASIS 37

//полиномиальная сумма кодов симвлово в строке
long long calcStr(char *str){
	long long result = 0;
	int len = strlen(str);
	for(int i = 0; i < len; i++)
		result += (result * BASIS + (int) str[i]);
	return result;
}

int genHash(char *str, int msize){
	return calcStr(str) % msize;
}

int incHash(char *str, int msize){
	return 1 + calcStr(str) % (msize - 1);
}

int doHash(char *str, int index, int msize){
	return (genHash(str, msize) + index * incHash(str, msize)) % msize;
}
