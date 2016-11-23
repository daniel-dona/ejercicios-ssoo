#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>

#define PATH_MAX 4096

void SumaRecursiva(const char *nodo, int *suma){

  DIR *d;
  struct dirent *entr;
  struct stat s;
  char nuevo[PATH_MAX+1];
  
  if((d = opendir(nodo)) == NULL){
    fprintf(stderr, "Error al abrir el stream del directorio");
    exit(EXIT_FAILURE);
  }
  
  while((entr = readdir(d)) != NULL){
    if(strcmp(entr->d_name, ".") == 0 || strcmp(entr->d_name, "..") == 0){
      continue;
    }
    
    sprintf(nuevo, "%s/%s", nodo, entr->d_name);
    if(stat(nuevo, &s) == -1){
      fprintf(stderr, "Error al obtener atributos del archivo %s", nuevo);
      exit(EXIT_FAILURE);
    }
    
    if(strlen(nodo) + strlen(entr->d_name)+2 > sizeof(nuevo)){
      fprintf(stderr, "Nombre demasiado largo");
      exit(EXIT_FAILURE);
    }
    
    if(S_ISREG(s.st_mode)){
      *suma = *suma + (int)s.st_size;
    }
    
    if(S_ISDIR(s.st_mode)){
      *suma = *suma + (int)s.st_size;
      SumaRecursiva(nuevo, suma);
    }
  } 
  closedir(d);
}
  
int main(int argc, char *argv[]){
  
  int suma = 0;
  int tamano = 0;
  
  if(argc < 3){
    fprintf(stderr, "Error en la línea de ordenes");
    exit(EXIT_FAILURE);
  }
  
  if(argv[1][0] == '-'){
    tamano = atoi(++argv[1]);
    ++argv;
    --argc;
  }else{
    fprintf(stderr, "No hay opcion de tamano");
    exit(EXIT_FAILURE);
  }
  
  while(--argc > 0){
    SumaRecursiva(*++argv, &suma);
    if(suma > tamano){
      printf("%s\tTotal Size: %d Bytes\n", *argv, suma);
    }
  }
  exit(EXIT_SUCCESS);
}
    
  
   
