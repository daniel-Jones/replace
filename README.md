Convenience function to replace every occurance of a string in a file with a replacement string, outputs to another file.

Compile with ````make```` and run with ````./example````.


definition in replace.h:

````
int replaceinfile(char *originalfile, char *destinationfile, char *placeholder, char *replacement);
// 0 = failure, 1 = success
````
input.txt

````

Normal text file

%PLACEHOLDER%
%PLACEHOLDER%
%PLACEHOLDER%

With lines and whatever, %PLACEHOLDER%

123%PLACEHOLDER%123	
ok %PLACEHOLDER% ok
````

output.txt

````

Normal text file

replacement string
replacement string
replacement string

With lines and whatever, replacement string

123replacement string123	
ok replacement string ok
````

See main.c for a usage example
