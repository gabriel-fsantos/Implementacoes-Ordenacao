#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>

//se der erro de compilação usa esse comando no teminal
//sudo apt-get install libssl-dev

typedef long TipoChave;
typedef int TipoIndice;
typedef struct TipoItem {
  TipoChave Chave;
  /* outros componentes */
} TipoItem;

void Bubblesort(TipoItem *A, TipoIndice n){
  TipoIndice i, j;
  TipoItem aux;
  for (j = 0; j < n-1; j++){
    for (i = 0; i < n-1; i++){
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
    x = A[Min]; A[Min] = A[i]; A[i] = x;
  }
}

void Particao(TipoIndice Esq, TipoIndice Dir, TipoIndice *i, TipoIndice *j, TipoItem *A){
  TipoItem x, w;
  *i = Esq;  *j = Dir;
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

void QuickSort(TipoItem *A, TipoIndice n){
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
  Constroi(A, n);  /* constroi o heap */
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
    Merge(A, i, m, j); /*Intercala A[i..m] e A[m+1..j] em A[i..j] */
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
      printf("ERRO: ");
      Imprime(V, n);
      return;
    }
  }
  printf("OK:\n");
  Imprime(V, n);
}

double rand0a1(){
  double resultado =  (double) rand()/ INT_MAX; /* Dividir pelo maior inteiro */
  if(resultado > 1.0){
    resultado = 1.0;
  }
  return resultado;
}

void Permut( TipoItem *A, int n){
  int i,j;
  TipoItem b;
  for(int i = n-1; i>0; i --){
    j = (i * rand0a1()) + 1 ;
    b = A[i];
    A[i] = A[j];
    A[j] = b;
  }
}

int main(int argc, char *argv[]){
  int n = 20, i;
  TipoItem A[n], B[n];

  for (i = 1; i <= n; i++) {
    A[i].Chave = i;
  }

  Permut (A,n);
  Copia (A,B,n);
 
  printf("Desordenado : \n");
  Imprime(A, n);

  printf("Bubblesort   ");
  Bubblesort(B, n);
  Testa(B, n);
  Copia(A, B, n);

  printf("Insercao  ");
  Insercao(B, n);
  Testa(B, n);
  Copia(A, B, n);

  printf("Selecao   ");
  Selecao(B, n);
  Testa(B, n);
  Copia(A, B, n);

  printf("Quicksort ");
  QuickSort(B, n);
  Testa(B, n);
  Copia(A, B, n);

  printf("Heapsort  ");
  Heapsort(B, n);
  Testa(B, n);
  Copia(A, B, n);

  printf("Mergesort  ");
  Mergesort(B, 1, n);
  Testa(B, n);
  Copia(A, B, n);

  return 0;
}