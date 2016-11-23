#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXBUFFER 4096

void concatenar(char *origen,  char *destino, int flag){

  int fd_entrada, fd_salida;
  char buffer[MAXBUFFER];
  struct stat s;
  int numLeidos = 0;
  int numLectura;
  
  /*Abrimos el archivo de entrada*/
  if((fd_entrada = open(origen, O_RDONLY)) == -1){
    fprintf(stderr, "Error al abrir el archivo\n");
    exit(1);
  }
  
  /*Abrimos el archivo de salida*/
  if(destino != NULL){
    if((fd_salida = open(destino, O_WRONLY|O_RDONLY|O_CREAT|O_TRUNC, 0664)) == -1){
      fprintf(stderr, "Error de apertura de %s\n", destino);
      exit(1);
    }
  }
  /*Obtenemos los atributos del archivo de entrada para poder así 
  sacar su tamaño y manejar el buffer de lectura */
  if(fstat(fd_entrada, &s) == -1){
    fprintf(stderr, "Error al obtener atributos\n");
    exit(1);
  }

  /*Bucle de control de lectura/escritura*/
  while(numLeidos < s.st_size){
    /*Calculo del numero de bytes que hay que leer */
    if((s.st_size - numLeidos) >= MAXBUFFER) numLectura = MAXBUFFER;
    else numLectura = s.st_size - numLeidos;
    
    /*Posicionamiento en el archivo de salida, nos colocamos al final*/
    if(destino != NULL){
      if((lseek(fd_salida,SEEK_SET,SEEK_END)) == -1){
        fprintf(stderr, "Error al posicionar\n");
        exit(1);
      }
    }
    
    /*Lectura/Escritura*/    
    if(read(fd_entrada, buffer, numLectura) != numLectura){
      fprintf(stderr, "Error al leer la entrada\n");
      exit(1);
    }
    
    if(flag == 0){
      
      if(write(fd_salida, buffer, numLectura) != numLectura){
        fprintf(stderr, "Error al escribir la entrada\n");
        exit(1);
      }
    }
    
    if(flag == 1){  
      if(write(1, buffer, numLectura) != numLectura){ 
         fprintf(stderr, "Error de escritura\n");
         exit(1);   
      }
    } 
    
    numLeidos += numLectura;
    
  }
  
  close(fd_entrada); close(fd_salida);
}

int main (int argc, char *argv[]){
  
  int i;
  int flag = 0;
    
  if(argc < 3){
    fprintf(stderr, "Error en la linea de ordenes. Faltan comandos.\n");
    exit(1);
  }
      
  if((argv)[1][0] == '-'){
    flag = 1;
    for(i=1; i<(argc--); i++) concatenar(argv[i+1], NULL, flag);
  }
  
  if((argv)[argc-1][0] == '-'){
    flag = 1;
    for(i=1; i<argc-1; i++) 
		concatenar(argv[i], NULL, flag);
  
  }else for(i=1; i<argc-1; i++)
   		concatenar(argv[i], argv[argc-1], flag);
  
  exit(EXIT_SUCCESS);
}
         
  
  
