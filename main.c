/************************************************
LAED1 - Trabalho Pratico 2
Aluno: Gabriel Ferreira dos Santos / Rebeca Larrisa Silva Gaia
Matricula: 20183025526 / 20183025508
Descricao do programa: Metodos de Ordenação
Data: 22/11/2019
************************************************/
/* Referências:
http://www2.dcc.ufmg.br/livros/algoritmos/implementacoes.php
https://sites.google.com/site/nataliacefetmg/home/aed1_20192
*/
#include <sys/resource.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define U "Bubblesort" // 1
#define I "Insercao"   // 2
#define S "Selecao"    // 3
#define Q "Quicksort"  // 4
#define H "Heapsort"   // 5
#define M "Mergesort"  // 6

typedef long TipoChave;
typedef int TipoIndice;
typedef struct TipoItem {
  TipoChave Chave;
  char nome[100];
} TipoItem;

void Bubblesort(TipoItem *A, TipoIndice n){
  int i, j;
  TipoItem aux;
  for (j = 1; j <= n-1; j++){
    for (i = 1; i <= n-1; i++){
      if (A[i].Chave > A[i+1].Chave){
        aux = A[i];
        A[i] = A[i+1];
        A[i+1] = aux;
      }
    }
  }
}

void Insercao(TipoItem *A, TipoIndice n){
  TipoIndice i, j;
  TipoItem x;
  for (i = 2; i <= n; i++){
    x = A[i]; 
    j = i - 1;
    A[0] = x;  /* sentinela */
    while (x.Chave < A[j].Chave){
      A[j+1] = A[j]; 
      j--;
    }
    A[j+1] = x;
  } 
}

void Selecao(TipoItem *A, TipoIndice n){
  TipoIndice i, j, Min;
  TipoItem x;
  for (i = 1; i <= n - 1; i++){
    Min = i;
    for (j = i + 1; j <= n; j++){
      if (A[j].Chave < A[Min].Chave){
        Min = j;
      }
    }
    x = A[Min];
    A[Min] = A[i];
    A[i] = x;
  }
}

void Particao(TipoIndice Esq, TipoIndice Dir, TipoIndice *i, TipoIndice *j, TipoItem *A){
  TipoItem x, w;
  *i = Esq;
  *j = Dir;
  x = A[(*i + *j) / 2]; /* obtem o pivo x */
  do{
    while (x.Chave > A[*i].Chave) (*i)++;
    while (x.Chave < A[*j].Chave) (*j)--;
    if (*i <= *j){
      w = A[*i]; 
      A[*i] = A[*j];
      A[*j] = w;
      (*i)++; 
      (*j)--;
    }
  } while (*i <= *j);
}

void Ordena(TipoIndice Esq, TipoIndice Dir, TipoItem *A){
  TipoIndice i, j;
  Particao(Esq, Dir, &i, &j, A);
  if (Esq < j) Ordena(Esq, j, A);
  if (i < Dir) Ordena(i, Dir, A);
}

void Quicksort(TipoItem *A, TipoIndice n){
  Ordena(1, n, A);
}

void Refaz(TipoIndice Esq, TipoIndice Dir, TipoItem *A){
  TipoIndice i = Esq;
  int j;
  TipoItem x;
  j = i * 2;
  x = A[i];
  while (j <= Dir){
    if (j < Dir){
      if (A[j].Chave < A[j+1].Chave)
        j++;
      }
      if (x.Chave >= A[j].Chave) goto L999;
      A[i] = A[j];
      i = j;  j = i * 2;
    }
  L999: A[i] = x;
}

void Constroi(TipoItem *A, TipoIndice n){
  TipoIndice Esq;
  Esq = n / 2 + 1;
  while (Esq > 1){
    Esq--;
    Refaz(Esq, n, A);
  }
}

void Heapsort(TipoItem *A, TipoIndice n){
  TipoIndice Esq, Dir;
  TipoItem x;
  Constroi(A, n);
  Esq = 1;  
  Dir = n;
  while (Dir > 1){
    x = A[1];
    A[1] = A[Dir];
    A[Dir] = x;
    Dir--; 
    Refaz(Esq, Dir, A);
  }
}

void Merge(TipoItem *A, int i, int m, int j){
  TipoItem *B = (TipoItem*)malloc ((j+i+1) * sizeof (TipoItem));
  int x;
  int k = i;
  int l = m+1;
  for (x = i; x <= j; x++){
    B[x] = A[x];
  }
  x = i;
  while (k <= m && l <= j) {
    if (B[k].Chave <= B[l].Chave){
      A[x++] = B[k++];
    }
    else{
      A[x++] = B[l++];
    }
  } 
  while (k <= m){
    A[x++] = B[k++];
  }
  while (l <= j){
    A[x++] = B[l++];
  }
}

void Mergesort(TipoItem *A, int i, int j){
  int m;
  if (i < j){
    m = (i + j - 1) / 2;
    Mergesort(A, i, m);
    Mergesort(A, m + 1, j);
    Merge(A, i, m, j);
  }
}

void Imprime(TipoItem *V, TipoIndice n){
  for (int i = 1; i <= n; i++){
    printf("%li ", V[i].Chave);
    printf("\n");
  }
}

void Copia(TipoItem *Fonte, TipoItem *Destino, TipoIndice n){
  for (int i = 1; i <= n; i++){
    Destino[i] = Fonte[i];
  }
}

void Testa(TipoItem *V, TipoIndice n){
  for (int i = 2; i <= n; i++) {
    if (V[i].Chave < V[i-1].Chave) {
      printf("ERRO\n");
      return;
    }
  }
  printf("OK\n");
}

void troca(TipoItem *A, int i, int j){
    TipoItem aux;
    aux = A[i];
    A[i] = A[j];
    A[j] = aux;
}

void embaralhar(TipoItem *A, int n){
  srand(time(NULL));
  for (int i = 1; i <= n; i++){
    int r = 1 + rand() % n;
    troca(A, i, r);
  }
}

void embaralhar20(TipoItem *A, int n){
  srand(time(NULL));
  int m = (int) (n * 0.2)/2;;
  for (int i = 1; i <= m; i++){
    int r = 1 + rand() % n;
    troca(A, i, r);
  }
}

void geraCrescente(TipoItem *A, int n){
  for (int i = 1; i <= n; i++) {
    A[i].Chave = i;
  } 
}

void geraDecrescente(TipoItem *A, int n){
  int j = 1; 
  for (int i = n; i >= 1; i--) {
    A[i].Chave = j;
    j++;
  }
}

void geraAleatorio(TipoItem *A, int n){
  geraCrescente(A, n);
  embaralhar(A, n);
}

void geraQuaseOrdenado(TipoItem *A, int n){
  geraCrescente(A, n);
  embaralhar20(A, n);
}

int main(int argc, char** argv) {

  int who = RUSAGE_SELF;
  struct rusage usage;
  long utotalmicroseg, utotalseg;

  char optc = 0;
  struct option OpcoesLongas[] = {
    {"-a", required_argument, NULL, 'a'},
    {"-n", required_argument, NULL, 'n'},
    {"-t", required_argument, NULL, 't'},
    {"-v", required_argument, NULL, 'v'},
    {"-r", required_argument, NULL, 'r'}
  };

  if(argc < 11) {
    printf("Parametros faltando\n");
    exit(0);
  }

  int met = 0, n = 0, t = 0, v = 0, r = 0;

  while((optc = getopt_long(argc, argv, "a:n:t:v:r:", OpcoesLongas, NULL)) != -1) {
    switch(optc) {
      case 'a':
        printf("Metodo: %s\n", optarg);
        if(strcmp(U, optarg) == 0) met = 1;
        if(strcmp(I, optarg) == 0) met = 2;
        if(strcmp(S, optarg) == 0) met = 3;
        if(strcmp(Q, optarg) == 0) met = 4;
        if(strcmp(H, optarg) == 0) met = 5;
        if(strcmp(M, optarg) == 0) met = 6;
        break;
      case 'n':
        printf("Quantidade: %s\n", optarg);
        n = atoi(optarg);
        break;
      case 't':
        printf("Tipo: %s\n", optarg);
        t = atoi(optarg);
        break;
      case 'v':
        printf("Imprimir original: %s\n", optarg);
        if(strcmp("S", optarg) == 0) v = 1;
        break;
      case 'r':
        printf("Imprimir ordenado: %s\n", optarg);
        if(strcmp("S", optarg) == 0) r = 1;
        break;
      default:
        printf("Parametros incorretos.\n");
        exit(0);
    }
  }

  /* TESTES DOS ARGUMENTOS
  printf("A: %d\n", met);
  printf("N: %d\n", n);
  printf("T: %d\n", t);
  printf("V: %d\n", v);
  printf("R: %d\n", r);
  */

  TipoItem *A = malloc((n+1) * sizeof(TipoItem));
  TipoItem *B = malloc((n+1) * sizeof(TipoItem));

  switch(t) {
    case 1:
      geraCrescente(A, n);
      break;
    case 2:
      geraDecrescente(A, n);
      break;
    case 3:
      geraAleatorio(A, n);
      break;
    case 4:
      geraQuaseOrdenado(A, n);
      break;
    default:
      printf("Argumento Invalido\n");
      exit(0);
  }

  Copia(A,B,n);

  switch(met) {
    case 1:
      Bubblesort(A, n);
      break;
    case 2:
      Insercao(A, n);
      break;
    case 3:
      Selecao(A, n);
      break;
    case 4:
      Quicksort(A, n);
      break;
    case 5:
      Heapsort(A, n);
      break;
    case 6:
      Mergesort(A, 1, n);
      break;
    default:
      printf("Argumento Invalido\n");
      exit(0);
  }

  if (v){
    printf("Vetor Original\n");
    Imprime(B, n);
  }
  if (r){
    printf("Vetor Ordenado\n");
    Imprime(A, n);
  }

  Testa(A,n);

  getrusage(who, &usage);
  utotalseg = usage.ru_utime.tv_sec; // segundos
  utotalmicroseg = usage.ru_utime.tv_usec; // microsegundos
  printf("----------------------------------------------------------------------\n");
  printf ("Tempo de usuario: %ld segundos e %ld microssegundos.\n", utotalseg, utotalmicroseg);
  printf("----------------------------------------------------------------------\n");

  free(A);
  free(B);
  return 0;
}