#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define PATH_MAX 4096

void enlace(char *archivo,char *sufijo);
int main(int argc,char *argv[]){

	int i;

	if(argc<2){ 
		fprintf(stderr,"Numero de argumentos incorrecto");
		return EXIT_FAILURE;
	}
	
	if(argv[1][0] == '-'){
		for(i=2;i<argc;i++){
			enlace(argv[i],argv[1]+1);
		}
	}else{
		for(i=1;i<argc;i++){
			enlace(argv[i],"soft");
		}
	}

	return EXIT_SUCCESS;

}


void enlace(char *archivo,char *sufijo){

	char nombre[PATH_MAX+1];
	
	if((strlen(archivo) + strlen(sufijo)+2)> PATH_MAX){
		fprintf(stderr,"Error,nombre demasiado largo");
		exit(EXIT_FAILURE);
	}
	
	sprintf(nombre,"%s.%s",archivo,sufijo);
	symlink(archivo,nombre);
	

}
