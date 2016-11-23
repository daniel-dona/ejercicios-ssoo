#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define PATH_MAX 4096


void buscarOcultos(char *dir,int tam);
int main(int argc,char *argv[]){

	if(argc!= 3){
		fprintf(stderr,"El numero de argumentos es invalido\n");
		return 1;
	}
	buscarOcultos(argv[2],atoi(argv[1]));

	return 0;

}


void buscarOcultos(char *dir,int tam){

	DIR *d;			 /* Manejador del directorio*/
	struct stat st;
	struct dirent *sd;
	char nomOcu[PATH_MAX];/* Directorio + nombre del nodo*/
	char nombre[PATH_MAX];

	/* Apertura del directorio */
	if((d=opendir(dir)) == NULL){
		fprintf(stderr,"Error al abrir el directorio");
		exit (1);
	}
	
	/* Bucle de lectura de nodos del directorio */	

	while((sd=readdir(d)) != NULL){
		/* Se omite el directorio actual y el padre */
		if(strcmp(sd->d_name,".")==0 || strcmp(sd->d_name,"..")==0)
			continue;
		
		/* Ruta absoluta del fichero */
		sprintf(nomOcu,"%s%s",dir,sd->d_name);

		/* Copiamos el nombre del fichero */
		strcpy(nombre,sd->d_name);

		if(stat(nomOcu,&st) == -1){
			fprintf(stderr,"Error en %s\n",nomOcu);
			exit(1);
		}
		if(S_ISREG(st.st_mode) && st.st_size <tam){
			if(nombre[0] == '.'){
				printf("%s\t%d\n",nomOcu,tam);
			}
		}			

		else if(S_ISDIR(st.st_mode)){
			buscarOcultos(nomOcu,tam);
		}
	}
	closedir(d);


}


