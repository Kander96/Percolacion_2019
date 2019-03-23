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
int clasificar(int *red, int *hist,int dim);
int hoshen(int *red,int *hist, int s1, int s2, int i);
int corregir_etiqueta(int *red,int *hist, int dim);
int percola(int *red, int dim);


int main(int argc,char *argv[]){
	int dim;
	float p;
	dim=3;
	p=0.5;
		
	sscanf(argv[1],"%i",&dim);
	sscanf(argv[2],"%f",&p);	

	int *red;
	red = (int*)malloc(dim*dim*sizeof(int)); 
	int *hist;
	hist= (int*)malloc((dim*dim/2+2)*sizeof(int));
	
	for(int i=0; i<(dim*dim/2+2); i++){
		*(hist+i)=i;
	}
	
	//printf("%d %.1f",dim,p);	

	poblar(red,dim,p); //cuando le paso una variable a una funcion no pongo el asterisco a los punteros.
	imprimir(red,dim);
	
	clasificar(red,hist,dim);	
	
	imprimir(red,dim);
	corregir_etiqueta(red,hist,dim);
	
	imprimir(red,dim);
	
	percola(red,dim);
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
			printf("%d\t", *(red+i*dim+j));
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

int clasificar(int *red, int *hist, int dim){

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
				else{
					hoshen(red,hist,s1,s2,i*dim+j);
				}	
			}
			
		}
	}
	
	

	return 0;
}

int hoshen(int *red,int *hist, int s1, int s2, int i){

	int max,min;
	
	while(*(hist+s1)<0){
		s1=-*(hist+s1);
	}
	while(*(hist+s2)<0){
		s2=-*(hist+s2);
	}
	min=s1;
	max=s2;
	if(s2<s1){
		min=s2;
		max=s1;
	}
	
	*(red+i)=min;
	*(hist+max)=-min;
	*(hist+min)=min;	
	
	return 0;
}

int corregir_etiqueta(int *red,int *hist,int dim){
	int a;
	for(int i=0; i<dim*dim; i++ ){
		a=*(red+i);
		while(*(hist+a)<0){
			a=-*(hist+a);
		}
		*(red+i)=a;
	}
	return 0;
}

int percola(int *red,int dim){
	int *perc1;
	int *perc2;
	int a,b,percola;
	percola=0;
	
	perc1=(int*)malloc((dim*dim/2+2)*sizeof(int));
	perc2=(int*)malloc((dim*dim/2+2)*sizeof(int));
	
	for(int i=0; i<(dim*dim/2+2); i++){
		*(perc1+i)=0;
		*(perc2+i)=0;
	}
	for(int i=0; i<dim; i++){
		a=*(red+i);
		b=*(red+(dim-1)*dim+i);
		*(perc1+a)+=a;
		*(perc2+b)+=b;
	}	
	for(int i=2; i<(dim*dim/2+2); i++){
		if((*(perc1+i))*(*(perc2+i))!=0){
			percola=1;
			printf("El sistema percola!\n");
			
		}
	}

	return percola;
}
