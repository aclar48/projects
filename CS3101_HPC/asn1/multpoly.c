#include<stdio.h>
#include<stdlib.h>




void MultPoly(int *A,int n, int *B, int m, int *C) { //First method


	for(int i = 0; i < n+m-1; i++) 	C[i] = 0;

	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) C[i+j] = C[i+j] + A[i]*B[j];

}

void MultPoly2Helper(int *A, int n, int *B, int m,  int *C) { //Used to reduce size of call stack for method 2

	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) C[i+j] +=  A[i]*B[j];



}

void MultPoly2Rec (int *A, int i, int j, int *B, int k, int l, int *C, int p, int q) { //Second method
	

	int da = j -i;


	if(da == 0) {
		
		
	 C[p] +=  A[i]*B[k];
	
	}


	else {

	int m = (da + 1)/2;
	MultPoly2Rec(A, i, i+m-1, B, k, k+m-1,C,p,p+2*m-2);
	MultPoly2Rec(A, i, i+m-1, B, k+m, l, C, p+m, p+3*m-2);
	MultPoly2Rec(A, i+m, j, B, k+m, l, C, p+2*m, q);
	MultPoly2Rec(A, i+m, j, B, k, k+m-1, C, p+m, p+3*m-2);
	}
	

	

}

void MultPoly2( int *A, int i, int j, int  *B, int k, int l, int *C, int p, int q) {

	if(j > 65536) {
		 MultPoly2Rec(A, 65536 , j , B, 65536, l , C, p ,q );
	
		 MultPoly2Helper(A, 65537, B, 65537, C);
	}
	else MultPoly(A, j+1, B, l+1, C);




}





int main(int argc, char *argv[]) {
	int n;
	if(argc < 3) puts("Usage multpoly int(power of 2) test type(1 or 2)");
	else {
	n = atoi(argv[1]);
	printf("%d\n",n);
	int *A = (int *) malloc(n*sizeof(int));
	int *B = (int *) malloc(n*sizeof(int));
	int *E = (int *) malloc(n*sizeof(int));
	int *F = (int *) malloc(n*sizeof(int));
	int *C = (int *) malloc(2*n*sizeof(int));	
	int *D = (int *) calloc(2*n,sizeof(int));

	for(int i = 0; i < n; i++) {			//Generate 2 identical pesudo-random number sets
		A[i] = E[i] = rand() % 32;
		B[i] = F[i] = rand() % 16;
	}
	if(atoi(argv[2]) == 1) { puts("Testing method 1"); MultPoly (A, n, B, n, C); }

	else if(atoi(argv[2]) == 2){ puts("Testing method 2"); MultPoly2 (E,0,  n-1, F, 0, n-1, D, 0, 2*n - 2);  }


	
	return 0;
	}
}







