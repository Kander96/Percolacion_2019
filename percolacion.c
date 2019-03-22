#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define M 2147483697
#define Q 127773
#define R 2836
#define A 16807

float aleatorio(int *seed); 
int poblar(int *red, int dim, float p);

int main(int argc,char *argv[]){
	int dim;
	float p;
	int *red;

	sscanf(argv[1],"%i",&dim);
	sscanf(argv[2],"%f",&p);
	
	//printf("%d %.1f",dim,p);	

	//poblar(*red,dim,p); Esto no anduvo
}

float aleatorio(int *seed){
	int k;
	float x;
	k = (*seed)/Q;
	*seed=A*(*seed-k*Q)-k*R;
	if (*seed < 0.0)
		*seed=(*seed)+M;
	x=(*seed)/(float) M;
	return x;
}

int poblar(int *red, int dim, float p){
	int i;

	srand(time(NULL));
	int *seed= rand();

	for (i=0; i<dim*dim; i=i+1){
		*(red+i)=0;
		if(aleatorio(*seed)<p){
			*(red+i)=1;}
		printf("%d", *(red+i)); 
	}
	printf("\n");
	return 0;
}


