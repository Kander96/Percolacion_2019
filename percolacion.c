#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

float random(int *seed) 
int poblar(int *red, int dim, float p)

int main(int argc,char *argv[]){
	int dim;
	float p;

	sscanf(argv[1],"%i",&dim);
	sscanf(argv[2],"%f",&p);
	
	printf("%d %.1f",dim,p);	
}

int random(int *seed){

}

int poblar(int *red, int dim, int p){
	int i;

	srand(time(NULL));
	int *seed= (float)rand()/(float)rand_max

	for (i=0, i<dim*dim, i=i+1){
		*(red+i)=0
		if(random(*seed)<p)
			*(red+i)=1; 
	}
}


