#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define len(arr) sizeof(arr)/sizeof(arr[0])
#define max(a, b) a > b ? a : b;
#define min(a, b) a < b ? a : b;

int testOnCr();

// max combination that can be compute is (30 13)
int nCr(int n, int k){
	if(n<k) return -1;	
	k = min(k, n-k);

	long int tmp = 1;
	int i=k;

	while(i>0){
		tmp*=n--;
		i--;
	}

	while(k>0) tmp/=k--;

	return tmp;
}

int get_bite_size(int num){
	int size=1;
	num>>=1;

	while (num>0) {
		size++;
		num>>=1;
	}
	return size;
}


int max_bit(int* setOf, int length){
	int local_max=0;
	
	while(0<length--){
		int bite_size = get_bite_size(setOf[length]);
		local_max = max(bite_size,local_max);
	}

	return local_max;
}

char* get_file_contents(){
	FILE* input_fd;
	long file_len;
	char* input;

	input_fd = fopen("input", "r");

	if (!input_fd){
		perror("Couldn't open the file");
		exit(errno);
	}

	fseek(input_fd, 0, SEEK_END);
	file_len = ftell(input_fd);

	if(!file_len){
		printf("File has no contents, please write on/off sets");
		fclose(input_fd);
		return 0;
	}
	fseek(input_fd, 0, SEEK_SET);

	input = (char*) malloc(file_len*sizeof(char));

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
	return input;
}

// Remember to free the pointer given from this function =)
int* gen_combinations(int* arr, int length, int elem_num){
	int* out = (int *) calloc(nCr(length, elem_num), sizeof(int));
	int index_out = 0;

	if(elem_num==0){
		out[0]=0;
		return out;
	}

	int max_index = length-elem_num+1;

	for(int i = 0; i < max_index; i++){
		int* tmp = gen_combinations(&(arr[i+1]), length-i-1, elem_num-1);
		int tmp_len = nCr(length-i-1, elem_num-1);

		while(tmp_len){
			out[index_out++]=tmp[--tmp_len]+arr[i];
		}
		free(tmp);
	}	
	
	return out;
}



int main(int argc, char** argv){

	int onset[] = { 1,4,5 };
	int offset[] = { 2,3,7,8 };

	int bit_ammount = max(
		max_bit(onset, len(onset)),
		max_bit(offset, len(offset))
	);

	int base = bit_ammount;

	int* comb = (int*) malloc(bit_ammount*sizeof(int));

	
	while (0<bit_ammount--) {
		comb[bit_ammount]=1<<bit_ammount;
	}

	int* blokada = (int*) calloc(len(offset),sizeof(int));

	for(int i = 0; i<len(onset); i++){
		for(int j = 0; j<len(offset); j++){
			blokada[j] = offset[j] ^ onset[i];
		}
		
		int* tmp;
		for(int j = 1;j<base;j++){
			tmp = gen_combinations(comb, base, j);

			free(tmp);
		}
	}

	free(comb);
	free(blokada);

	return 0;
}

int testGenComb(){

	int comb[] = {1,2,4,8};
	int base = 4;
	int bit_num = 2;
	
	int* combs = gen_combinations(comb, base, bit_num);
	
	printf("Our combination is: \n");
	for(int i = 0; i<nCr(base,bit_num);i++){
		printf("%i ", combs[i]);
	}
	printf("\n");

	free(combs);
	return 0;
}

int testOnCr(){
	int i = 1;
	while(1){
		for(int j=0;j<=i;j++){
			int wynik = nCr(i,j);
			printf("(%i %i): %i\n", i, j, wynik);
			if(wynik<0){
				return 0;
			}
		}
		i++;
	}
	return 0;
}
