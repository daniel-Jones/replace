/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t
getfilelength(FILE *fp)
{
	/* 
	 * return the number of bytes in file fp	
    	 * value of 0 returned is empty or error
	 * it doesn't matter for our purpose
	 */
	size_t retval;
	if (!fp)
		retval = 0;
	else
	{
		fseek(fp, 0, SEEK_END);
		retval = ftell(fp);
		fseek(fp, 0, SEEK_SET);
	}
	return retval;
}

void
replaceappendchar(char *dest, char ch)
{
	int len = strlen(dest);
	dest[len] = ch;
	dest[len+1] = '\0';
}

int
replaceinfile(char *originalfile, char *destinationfile, char *placeholder, char *replacement)
{
	/*
	 * write originalfile into destinationfile replacing every instance 
	 * of placeholder with replacement 
	 */

	/* open files */
	FILE *template = fopen(originalfile, "r");
	FILE *destination = fopen(destinationfile, "w");
	if (!template)
	{
		fclose(destination);
		return 0;
	}
	int ch;
	char *substr;
	size_t filesize = getfilelength(template);
	char *filebuffer = malloc(filesize+1);
	if (!filebuffer)
		return 0;
	fread(filebuffer, 1, filesize, template);
	substr = strstr(filebuffer, placeholder);
	for (size_t i = 0; i < strlen(filebuffer); i++)
	{
		if (i == (substr-filebuffer))
		{
			i += strlen(placeholder);
			substr++;
			substr = strstr(substr, placeholder);
			fprintf(destination, "%s", replacement);
		}
		ch = filebuffer[i];
		fputc(ch, destination);
	}
	fclose(template);
	fclose(destination);
	free(filebuffer);
	return 1;
}

char *
replaceinmemory(char *src, char *placeholder, char *replacement)
{
	/*
	 * replace every placeholder with replacement in source src
	 * return pointer to string, NULL if no placement found
	 * user must free the returned memory
	 */
	char *dest = NULL;
	size_t destsize;
	char *substr = strstr(src, placeholder);
	if (!substr)
		return NULL;
	/* initial dest size if only one placeholder exists */
	destsize = (strlen(src)-strlen(placeholder))+strlen(replacement+1);
	dest = malloc(destsize);
	if (!dest)
		return NULL;
	dest[0] = '\0'; /* junk in memory, we need [0] to be null for strlen() later */
	for (size_t i = 0; i < strlen(src); i++)
	{
		if (i == (substr-src))
		{
			i += strlen(placeholder);
			substr++;
			substr = strstr(substr, placeholder);
			if (substr)
			{
				destsize = (destsize-strlen(placeholder))+strlen(replacement)+1;
				dest = realloc(dest, destsize);
			}
			strcat(dest, replacement);
		}
		replaceappendchar(dest, src[i]);
	}
	return dest;
}
