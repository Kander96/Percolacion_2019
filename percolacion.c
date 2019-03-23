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
int clasificar(int *red, int dim);

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
	
	clasificar(red,dim);	
	printf("\n");
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

int clasificar(int *red, int dim){

	int label=2;
	int s1,s2;
	if(*red==1){	//esto se encarga del primer nodo
		*red=label;
		label++;
		}
	 
	for (int j=1; j<dim; j++){	//esto se encarga de la primera fila
		s1=*(red+j-1);
		if(*(red+j)!=0){
			if(s1==0){
				*(red+j)=label;
				label++;
			}
			else{
				*(red+j)=s1;
			}
		}
	}
	
	for(int i=1; i<dim; i++){
		s1=*(red+(i-1)*dim);	//esto se encarga de la primera columna
		if(*(red+i*dim)!=0){
			if(s1==0){
				*(red+i*dim)=label;
				label++;
			}
			else{
				*(red+i*dim)=s1;
			}
		}
		for(int j=1; j<dim; j++){
			s1=*(red+(i-1)*dim+j);
			s2=*(red+i*dim+j-1);
			if(*(red+i*dim+j)!=0){
				if(s1*s2==0){
					if(s1==s2){
						*(red+i*dim+j)=label;
						label++;
					}
					else if(s1!=0){
						*(red+i*dim+j)=s1;
					}
					else{
						*(red+i*dim+j)=s2;
					}
				}
				//else{
				//	hoshen();
				//}	
			}
			
		}
	}
	
	

	return 0;
}

