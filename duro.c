#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PATH_MAX 4096

void enlace(char *archivo,char *sufijo);
int main(int argc,char *argv[]){

	int i;
	if(argc<2){
		fprintf(stderr,"Numero de argumentos incorrecto");
		exit(1);
	}
	
	if(argv[1][0] == '-'){
		for(i=2;i<argc;i++){
			enlace(argv[i],argv[1]+1);
		}
	}else{
		for(i=1;i<argc;i++){
			enlace(argv[i],"hard");
		}
	}
	return 0;


}


void enlace(char *archivo,char *sufijo){

	char nombre[PATH_MAX+1];
	if((strlen(archivo) + strlen(sufijo)+2)> PATH_MAX){
		fprintf(stderr,"Error,nombre demasiado largo");
		exit(1);
	}
	sprintf(nombre,"%s.%s",archivo,sufijo);
	link(archivo,nombre);
	

}
