#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define M 2147483697
#define Q 127773
#define R 2836
#define A 16807

float aleatorio(int *seed); 
int asignar_proba(float *probabilidad,int *seed,int dim);
int poblar(int *red, float *probabilidad,int dim, float p);
int imprimir(int *red, int dim);
int clasificar(int *red, int *hist,int dim);
int hoshen(int *red,int *hist, int s1, int s2, int i);
int corregir_etiqueta(int *red,int *hist, int dim);
int percola(int *red, int dim, int *c);
int contar_clusters(int *red, int *clusters, int dim);
int masa_total(int *red, int dim);
int masa_percolante(int *red, int dim, int *c);


//cuando le paso una variable a una funcion no pongo el asterisco a los punteros.

int main(int argc,char *argv[]){
	int dim;
	int item;
	dim=4;
	item=0;
			
	sscanf(argv[1],"%i",&dim);	
	sscanf(argv[2],"%i",&item);
	
	srand(time(NULL));
		
	float p;
	//float p_critica=0.0;
	int *red;
	red = (int*)malloc(dim*dim*sizeof(int)); 
	int *seed;
	seed = (int*)malloc(sizeof(int));
	int *c;
	c=(int*)malloc(sizeof(int));
	int *hist;
	hist= (int*)malloc((dim*dim/2+2)*sizeof(int));
	float *probabilidad;
	probabilidad = (float*)malloc(dim*dim*sizeof(float));
	int *clusters;
	clusters = (int*)malloc((dim*dim+1)*sizeof(int));
	
	if(item==11){
		FILE *file;
		char filename[64];
		int N=1000; //hay que hacer la cuenta para fijar el N.
		//float p_crit_cuad=0.0;
		//float sigma=0.0;
		sprintf(filename, "probabilidad_critica_dim_%i.txt", dim);
		file=fopen(filename,"w");
		for(int j=1; j<N+1; j++){
		
			asignar_proba(probabilidad,seed,dim);
		
			int a=1;
			p=0.0;
		
			for(int i=1; i<11; i++){
			
				p+=a*1/powl(2,i);
				poblar(red,probabilidad,dim,p); 
				clasificar(red,hist,dim);	
				corregir_etiqueta(red,hist,dim);
				a=percola(red,dim,c);
			}
		
			fprintf(file,"%f\n",p);
			//p_critica+=p/N;
			//p_crit_cuad+=powl(p,2)/N;
		}
		//sigma=sqrt(p_crit_cuad-powl(p_critica,2));
		//fprintf(file,"%f\t%f\n",sigma,p_critica);
		//printf("%f\t%f\n",sigma,p_critica);
		fclose(file);
	}
	else if(item==12){
		FILE * file;
		char filename[64];
		int N=100;
		int D=10000;
		p=0.0;
		sprintf(filename, "distribucion_de_probabilidad_dim_%i.txt", dim);
		file=fopen(filename,"w");
		for(int i=0; i<N+1; i++){
			int a=0;
			float b=0.0;
			for(int j=0; j<D; j++){
			
				asignar_proba(probabilidad,seed,dim);
				poblar(red,probabilidad,dim,p);
				clasificar(red,hist,dim);	
				corregir_etiqueta(red,hist,dim);
				a=percola(red,dim,c);
				a=-(a-1)/2;
				b+=a/(float) D;
			}
			fprintf(file,"%f\t%f\n",p,b);
			p+=1.0/N;
		}
		fclose(file);
	}
	
	else if(item==14){
		p=0.54;
		int N=1000;
		
		for (int i=0; i<10; i++){
			
			p+=0.01;
			char filename[64];
			FILE *out;
			sprintf(filename, "ej_1_4_p_%.4f_dim_%i.txt", p, dim);
			out = fopen( filename, "w");
			for(int j=0; j<N; j++){
				asignar_proba(probabilidad,seed,dim);
				poblar(red,probabilidad,dim,p);
				clasificar(red,hist,dim);	
				corregir_etiqueta(red,hist,dim);
				contar_clusters(red,clusters,dim);
			}
			for(int j=1; j<dim*dim+1; j++){
				fprintf(out,"%i\t%f\n",j,*(clusters+j)*1.0/N);
				*(clusters+j)=0;
			}
			fclose(out);
		}
	}
	
	else if(item==2){
		p=0.0;
		char filename[64];
		int m;
		float P_inf=0.0;
		int N=1000;
		int D=100;
		FILE *out;
		sprintf(filename, "archivo%i.txt", dim);
		out = fopen(filename,"w");
		for(int i=0; i<D+1; i++){
			for(int j=0; j<N; j++){
				asignar_proba(probabilidad,seed,dim);
				poblar(red,probabilidad,dim,p);
				clasificar(red,hist,dim);	
				corregir_etiqueta(red,hist,dim);
				percola(red,dim,c);
				m=masa_percolante(red,dim,c);
				P_inf+=m*1.0/(dim*dim);
			}
			P_inf=P_inf/N;
			fprintf(out,"%f\t%f\n",p,P_inf);
			p+=1.0/D;
		}
		fclose(out);
	}
	
	else if(item==3){
		int m=0;
		float D;
		p=0.5927;
		int N=1000;
		for(int i=0; i<N; i++){
			asignar_proba(probabilidad,seed,dim);
			poblar(red,probabilidad,dim,p);
			clasificar(red,hist,dim);	
			corregir_etiqueta(red,hist,dim);
			percola(red,dim,c);
			m+=masa_percolante(red,dim,c);
		}
		m=m*1.0/N;
		D=log(m)/log(dim);
		printf("%i\t%f\n",m,D);
	}
	
	else if(item==5){
		p=0.57;
		char filename[64];
		FILE *out;
		sprintf(filename, "ejercicio_5.txt");
		out = fopen(filename,"w");
		int N=1000;
		for(int i=0; i<31; i++){
			for(int j=0; j<N; j++){
				asignar_proba(probabilidad,seed,dim);
				poblar(red,probabilidad,dim,p);
				clasificar(red,hist,dim);	
				corregir_etiqueta(red,hist,dim);
				contar_clusters(red,clusters,dim);
			}
			fprintf(out,"%f\t",p);
			for(int j=1; j<16; j++){
				fprintf(out,"%f\t",*(clusters+j)*1.0/N);
				*(clusters+j)=0;
			}
			fprintf(out,"\n");
			p+=0.001;
		}
		fclose(out);
	}
	
	return 0;
}

float aleatorio(int *seed){
	int k;
	float x;
	k = (*seed)/Q;
	*seed=A*(*seed-k*Q)-k*R;
	if (*seed < 0.0)
		*seed=(*seed)+M;
	x=(*seed)* 1.0/M;
	return x;
}

int asignar_proba(float *probabilidad,int *seed,int dim){
	
	*seed=rand();
	for(int i=0; i<dim*dim; i++){
		*(probabilidad+i)=aleatorio(seed);
		//printf("%f ",*(probabilidad+i));
	}
	//printf("\n");
	return 0;
}

int poblar(int *red, float *probabilidad, int dim, float p){
	
		for (int i=0; i<dim*dim; i++){
		*(red+i)=0;
		if(*(probabilidad+i)<p){
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
	
	for(int i=0; i<(dim*dim/2+2); i++){
		*(hist+i)=i;
	}
	
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

int percola(int *red,int dim, int *c){
	int *perc1;
	int *perc2;
	int a,b,percola;
	percola=1;
	*c=0;
	
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
			percola=-1;
			*c=i;
		}
	}

	return percola;
}

int contar_clusters(int *red, int *clusters, int dim){
	int *vect;
	vect=(int*)malloc((dim*dim+1)*sizeof(int));
	
	for(int i=0; i<dim*dim+1; i++){
		//*(clusters+i)=0;
		*(vect+i)=0;
	}
	for(int i =0; i<dim*dim; i++)
		*(vect+*(red+i))+=1;
	for(int i=1; i<dim*dim; i++)
		*(clusters+*(vect+i))+=1;
	return 0;
}

int masa_total(int *red, int dim){
	int m=0;
	for(int i=0; i<dim*dim; i++){
		if(*(red+i)){
			m++;
		}
	}
	return m;
}

int masa_percolante(int *red, int dim, int *c){
	int m=0;
	if(*c!=0){
		for(int i=0; i<dim*dim; i++){
			if(*(red+i)==*c){
				m++;
			}
		}
	}
	return m;
}

