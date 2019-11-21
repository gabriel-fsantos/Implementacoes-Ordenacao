#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  char optc = 0;
  struct option OpcoesLongas[] = {
    {"-a", required_argument, NULL, 'a'},
    {"-n", required_argument, NULL, 'n'},
    {"-t", required_argument, NULL, 't'},
    {"-v", required_argument, NULL, 'v'},
    {"-r", required_argument, NULL, 'r'}
  };

  if(argc == 1) {
    printf("Parametros faltando\n");
    exit(0);
  }

  while((optc = getopt_long(argc, argv, "a:n:t:v:r:", OpcoesLongas, NULL)) != -1) {
    switch(optc) {
      case 'a':
        printf("Metodo: %s\n", optarg);
        break;
      case 'n':
        printf("Quantidade: %s\n", optarg);
        break;
      case 't':
        printf("Tipo: %s\n", optarg);
        break;
      case 'v':
        printf("Imprimir original: %s\n", optarg);
        break;
      case 'r':
        printf("Imprimir ordenado: %s\n", optarg);
        break;
      default:
        printf("Parametros incorretos.\n");
        exit(0);
    }
  }
}