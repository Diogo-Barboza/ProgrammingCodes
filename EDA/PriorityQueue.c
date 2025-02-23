#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Item;

#define key(A) A
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {Item t=A; A=B; B=t;}

static Item *pq;
static int N;

void show(int v[], int l, int r){
  for (int i = 1; i <= r; i++)
  {
    printf("%d ", v[i]);
  }
  printf("\n");
}

int is_sorted(int v[], int l, int r){
  int p;
  for (p=r; p>1 && v[p-1]<=v[p]; p--);
  return (p==0);
}

void PQinit(int maxN){
  pq = malloc(sizeof(Item)*(maxN+1));
  N = 0;
}

int PQempty(){
  return N==0;
}

void fixUp(int k){
  while (k>1 && less(pq[k/2], pq[k]))
  {
    exch(pq[k], pq[k/2]);
    k = k/2;
  }
}

void fixDown(int k, int N){
  int j;
  while (2*k <= N)    
  {
    j = 2*k;
    //troque com o maior filho
    if(j<N && less(pq[j], pq[j+1])) j++;

    //Se pk não precisar mais descer, pare
    if(!less(pq[k], pq[j])) break;

    //se nao, afunde
    exch(pq[k], pq[j]);
    k = j;
  }
}

void PQinsert(Item v){
  pq[++N] = v; // Inserir na ultima posicao
  fixUp(N);
}

Item PQdelmax(){
  //troque topo -> ultimo
  exch(pq[1], pq[N]);
  //reposicionane o ultimo
  fixDown(1, N-1);
  //devolva o maximo
  return pq[N--];
}

void PQsort(Item *v, int l, int r){
  PQinit(r-l+1);
  N = r-l-1;
  for(int k=l; k<=r; k++){
    PQinsert(v[k]);
  }
  for (int k=r; k>=1; k--)
  {
    v[k] = PQdelmax();
  }
}

void heap_sort(Item *v, int l, int r){
  pq = v+l-1;
  N = r-l+1;

  for (int k=N/2; k>=1; k--)
  {
    fixDown(k,N);
  }
  while (N>1)
  {
    exch(pq[1], pq[N]);
    fixDown(1, N--);
  }
}

//time ./a.out pqsort < input/10-aleatorio
int main(int argc, char *argv[]){
  int n;
  scanf("%d", &n);
  if(argc>1){
    //ordenação
    int *v = malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &v[i]);
    }

    if(n<50){
      show(v, 0, n-1);
    }

    if(!strcmp(argv[1], "pqsort"))
      PQsort(v, 0, n-1);
    else if (!strcmp(argv[1], "heap"))
      heap_sort(v,0, n-1);
    
    if(n<50)
      show(v, 0, n-1);
    
    if(is_sorted(v, 0, n-1)) printf("ordenado.\n");
    else printf("Não ordenado.\n");
  }else
  {
    //fila de prioridades
    PQinit(n);
    char e; 
    int b;
    while (scanf(" %c", &e))
    {
      if(e=='i'){
        scanf("%d", &b);
        if(N<n) PQinsert(b);
        show(pq, 1, N);
      }else if (e=='d')
      {
        if((N+1)>0) PQdelmax();
        show(pq, 1, N+1);
      }
    }
  }

  return 0;
}