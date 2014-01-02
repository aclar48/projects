#include<stdio.h>
#include<stdlib.h>


int findmax(int *A, int n) {


	int curmax =0;
	int tempmax = 0;

	for(int i =0; i < n; i++) {
		if((tempmax += A[i]) > 0);
		else tempmax = 0;
		if(tempmax > curmax) curmax = tempmax;
	}
	return curmax;

}

int main(int argc,char **argv) {
	int n;
	if(argc  < 3) {  puts("Usage kadane, num entires in array, array entries"); return 1; }
	else n = atoi(argv[1]);
	int *A = (int *) calloc(n,sizeof(int));
	for(int i = 0; i < n; i++) A[i] = atoi(argv[2+i]);
	
	printf("Max is: %d\n",findmax(A,n));

	return 0;
}
		
