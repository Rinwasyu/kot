#include <stdlib.h>
#include <string.h>

char *strjoin(char *str1, char *str2) {
	char *str = (char *)malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));
	memset(str, 0, sizeof(char) * (strlen(str1) + strlen(str2) + 1));
	return strcat(strcat(str, str1), str2);
}