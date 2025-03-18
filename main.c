#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define len(arr) sizeof(arr)/sizeof(arr[0])
#define max(a, b) a > b ? a : b;
#define min(a, b) a < b ? a : b;
#define comp_impl(a,b) (a.mask & a.prism) == (b.mask & b.prism)

typedef struct implikant{
	int mask;
	int prism;
} implikant;

int nCr(int n, int k);
int* gen_combinations(int* arr, int length, int elem_num);
char* get_file_contents();
int max_bit(int* setOf, int length);
int get_bite_size(int num);
void print_implikants(implikant*, int);
implikant* distinct_impl(implikant* implicants, int lenght);

int main(int argc, char** argv){

	int onset[] = { 1,7 };
	int offset[] = { 0,5 };

	int off_len = len(offset);
	int bit_ammount = max(
		max_bit(onset, len(onset)),
		max_bit(offset, off_len)
	);

	int base = bit_ammount;

	// TODO: Add checking whether or not the all of alloc were succesfull
	int* comb = (int*) malloc(bit_ammount*sizeof(int));

	
	while (0<bit_ammount--) {
		comb[bit_ammount]=1<<bit_ammount;
	}

	int* blokada = (int*) calloc(off_len,sizeof(int));

	implikant* all_implicants = (implikant *) calloc(1,sizeof(implikant));
	long curr_imp_size = 0;
	int curr_imp_index = 0;

	// for each onset
	for(int i = 0; i<len(onset); i++){
		// make a block
		for(int j = 0; j<off_len; j++){
			blokada[j] = offset[j] ^ onset[i];
		}
		
		int* tmp;
		int tmp_len;
		int anws;
		int impl_index;
		// check and add implicants
		for(int j = 1;j<=base;j++){
			// this creates all possible combinations for base and j and puts it into comb
			tmp = gen_combinations(comb, base, j);
			tmp_len = nCr(base, j);

			for(int l = 0; l<tmp_len; l++){
				printf("%i, ", tmp[l]);
			}
			printf("\n");

			// TODO: Add checking whether or not the alloc was succesfull
			implikant* implikants = (implikant *) calloc(tmp_len, sizeof(implikant));
			if(!implikants){
				
			}
			impl_index = 0;

			for (int k = 0; k < tmp_len; k++) {
				anws=0;

				for (int l = 0; l < off_len;l++) {
					anws |= blokada[l] & tmp[k];
				}

				printf("anws = %i\n", anws);
				
				if(anws){
					implikant tmp_impl;
					tmp_impl.mask = tmp[k];
					tmp_impl.prism = onset[i];
					implikants[impl_index++] = tmp_impl;
				}
			}

			// TODO: Add checking whether or not the realloc was succesfull
			if(impl_index){
				curr_imp_size+=impl_index;
				all_implicants = realloc(all_implicants, curr_imp_size*sizeof(implikant));
				while (curr_imp_index<curr_imp_size) {
					all_implicants[curr_imp_index++]=implikants[--impl_index];
				}
				free(implikants);
				free(tmp);

				break;
			}
		
			free(implikants);
			free(tmp);
		}
	}

	printf("There are %li implicants\n", curr_imp_size);
	print_implikants(all_implicants, curr_imp_size);

	implikant* distinct_impl = malloc(sizeof(implikant) * curr_imp_size);
	int dist_size = 0;

	for(int i = 0; i < curr_imp_size; i++){
		int is_not_in = 1;
		for(int j = 0; j<dist_size; j++){
			if(comp_impl(distinct_impl[j], all_implicants[i])){
				is_not_in=0;
				break;
			}
		}

		if(is_not_in) distinct_impl[dist_size++]=all_implicants[i];
	}

	distinct_impl = realloc(distinct_impl, dist_size);
	free(all_implicants);

	printf("There are %i distinclt implicants\n", dist_size);
	print_implikants(distinct_impl, dist_size);

	for(int i = 0; i<len(onset);i++){
		for(int j = 0; j<dist_size; j++){

		}
	}

	free(distinct_impl);

	free(comb);
	free(blokada);

	return 0;
}

implikant* distinct_impl(implikant* implicants, int lenght){
	implikant* distinct_impl = malloc(sizeof(implikant) * lenght);
	int dist_size = 0;

	for(int i = 0; i < lenght; i++){
		int is_not_in = 1;
		for(int j = 0; j<dist_size; j++){
			if(comp_impl(distinct_impl[j], implicants[i])){
				is_not_in=0;
				break;
			}
		}

		if(is_not_in) distinct_impl[dist_size++]=implicants[i];
	}

	distinct_impl = realloc(distinct_impl, dist_size);
	free(implicants);
	printf("There are %i disctinct implicants\n", dist_size);
	return distinct_impl;
}

void print_implikants(implikant* a, int length){
	while (length--) {
		printf("mask: %i, prism: %i\n", a[length].mask, a[length].prism);
	}	
}

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



