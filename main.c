#include <stdio.h>
#include "replace.h"

int
main(void)
{
	int ret;
	ret = replaceinfile("input.txt", "output.txt", "%PLACEHOLDER%", "replacement string");
	if (ret == 0)
		puts("failed");
	return 0;
}
