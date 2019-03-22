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
int imprimir(int *red, int dim);


int main(int argc,char *argv[]){
	int dim;
	float p;
	dim=3;
	p=0.5;
	
	sscanf(argv[1],"%i",&dim);
	sscanf(argv[2],"%f",&p);	

	int *red;
	red = (int*)malloc(dim*dim*sizeof(int)); 

	
	//printf("%d %.1f",dim,p);	

	poblar(red,dim,p); //cuando le paso una variable a una funcion no pongo el asterisco a los punteros.
	imprimir(red,dim);	
	
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
	int *seed;
	seed = (int*)malloc(sizeof(int));
	*seed=rand();
	
	for (i=0; i<dim*dim; i++){
		*(red+i)=0;
		if(aleatorio(seed)<p){
			*(red+i)=1;}
	}
	
	return 0;
}

int imprimir(int *red, int dim){
	
	for (int i=0; i<dim; i++){
		for (int j=0; j<dim; j++){
			printf("%d ", *(red+i*dim+j));
		}
		printf("\n");
	}
	return 0;
}

