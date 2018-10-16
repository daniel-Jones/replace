#include <stdio.h>
#include <stdlib.h>
#include "replace.h"

int
main(void)
{
	int ret;
	ret = replaceinfile("input.txt", "output.txt", "%PLACEHOLDER%", "replacement string");
	if (ret == 0)
		puts("failed");
	char *rep = replaceinmemory("this string this string is a test string", "string", "word");
	printf("%s\n", rep);
	free(rep);
	return 0;
}
