#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	FILE* input_fd;
	input_fd = fopen("input", "r");

	if (!input_fd){
		perror("Couldn't open the file");
		exit(errno);
	}

	fseek(input_fd, 0, SEEK_END);
	long file_len = ftell(input_fd);
	if(!file_len){
		printf("File has no contents, please write on/off sets");
		fclose(input_fd);
		return 0;
	}
	fseek(input_fd, 0, SEEK_SET);

	printf("The length of a file is: %li, And our current position is: %li\n", file_len, ftell(input_fd));

	char* input = (char*) malloc(file_len*sizeof(char));

	if(!input){

		perror("Couldn't allocate memory for input");
		exit(errno);
	}
 
	if(!fread(input, sizeof(char), file_len, input_fd)){
		free(input);
		fclose(input_fd);
		perror("Couldn't read the file");
		exit(errno);
	}

	fclose(input_fd);

	printf("The file data is:\n%s", input);
	free(input);

	return 0;
}
