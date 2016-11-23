#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_MAX 4096

void renombrar(char *viejo,char *ext);
	
int main(int argc,char *argv[]){

	char *ext;

	if(argc<2){ 

		fprintf(stderr,"Numero de argumentos incorrecto\n");
		return EXIT_FAILURE;

	}

	if(argv[1][0] == '-'){

		ext=++argv[1];
		--argc;
		++argv;

	}else{

		ext="old";

	}

	while((--argc)>0){
	
		renombrar(*++argv,ext);

	}

	exit(0);

}

void renombrar(char *viejo,char *ext){

	char nuevo[PATH_MAX+1];

	sprintf(nuevo,"%s.%s",viejo,ext);
	
	if(strlen(viejo) + strlen(ext)+2 >sizeof(nuevo)){

		fprintf(stderr,"Error, nombre demasiado largo\n");
		exit(1);

	}

	if(rename(viejo,nuevo) == -1){

		fprintf(stderr,"Error al renombrar\n");
		exit(1);

	}
		
}
