#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc,char *argv[]){
	int L;
	float p;

	sscanf(argv[1],"%i",&L);
	sscanf(argv[2],"%f",&p);
	
	printf("%d %.1f",L,p);	
}
