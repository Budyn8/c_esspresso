#include "main.c"

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
