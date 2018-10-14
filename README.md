Convenience function to replace every occurance of a string in a file with a replacement string, outputs to another file.

Compile with ````make```` and run with ````./example````.


definition in replace.h:

````
int replaceinfile(char *originalfile, char *destinationfile, char *placeholder, char *replacement);
// 0 = failure, 1 = success
````

See main.c for a usage example
