#include <stdio.h>

int main(int argc, char** argv){
	char temp[] = "Beautyfull";
	printf("Hello, %s World!\nAnd: %s\n", temp, argv[argc-1]);

	return 0;
}
