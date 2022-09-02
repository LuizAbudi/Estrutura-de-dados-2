/**
 * @file
 * @author Luiz Gustavo Pasini Abudi & Ian Ferranti
 * @date 05-04-2002
 * @brief
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

int comp_quick = 0;

#define BUFFER 150

typedef struct
{
  int chave; // chave é a chave canonica de um registro
  int RRN;   // é a referencia p leitura/gravação do registro
} KeyNode;

typedef struct
{
  char chave[3];         // chave numerica pode ter até 3 digitos
  char primeiroNome[21]; // primero nome do heroi
  char sobrenome[21];    // seu sobrenome
  char nomeHeroi[21];    // nome do Heroi, alias
  char poder[21];        // poder
  char fraqueza[21];     // fraqueza
  char cidade[21];       // cidade que defende
  char profissao[21];    // profissao da sua identidade secreta
} Heroi;

//#####################################################
//############### Insertion Sort ##########################

int InsertionSort(int *v, int tam)
{
  int aux;
  int j;
  int comp_insertion = 0;

  for (int i = 1; i < tam; i++)
  {
    aux = v[i];
    j = i - 1;
    comp_insertion++;
    while (j >= 0 && aux < v[j])
    {
      v[j + 1] = v[j];
      j = j - 1;
    } // while
    v[j + 1] = aux;
  } // for
  printf("%d interacoes - insertion\n", comp_insertion);
  return comp_insertion;
} // Insertion

//#####################################################
//############### Merge Sort ##########################

int Merge(int *v, int inicio, int meio, int fim)
{
  int i = 0; // indice do vetor auxiliar
  int tam_vet = (fim - inicio) + 1;
  int *vet_aux = malloc(tam_vet * sizeof(int));
  int aux1 = inicio;
  int aux2 = meio + 1;
  int comp_merge = 0;

  while (aux1 <= meio && aux2 <= fim)
  {
    // incrementa o contador
    comp_merge++;

    if (v[aux1] < v[aux2])
    {
      vet_aux[i++] = v[aux1++];
    }
    else
    {
      vet_aux[i++] = v[aux2++];
    } // if/else
  }   // while

  int n;

  if (aux1 > meio)
  {
    n = fim - aux2 + 1;

    for (int j = 0; j < n; j++)
    {
      vet_aux[i++] = v[aux2++];
    } // for
  }
  else
  {

    n = meio - aux1 + 1;

    for (int j = 0; j < n; j++)
    {
      vet_aux[i++] = v[aux1++];
    } // for
  }   // if/else

  int j = 0;
  int start = inicio;

  while (j < tam_vet)
  {
    v[start] = vet_aux[j];
    j++;
    start++;
  } // while

  free(vet_aux);
  return comp_merge;

} // merge

int MergeSort(int *v, int inicio, int fim)
{
  int meio;
  int comp_merge = 0;

  if (inicio < fim)
  {
    meio = ((inicio + fim) / 2);
    comp_merge = comp_merge + MergeSort(v, inicio, meio);
    comp_merge = comp_merge + MergeSort(v, meio + 1, fim);
    comp_merge = comp_merge + Merge(v, inicio, meio, fim);
  } // if
  return comp_merge;
} // merge sort

//#####################################################
//############### Quick Sort ##########################

void QuickSort(int v[], int inicio, int fim)
{
  // printf("\nCont quick = %d\n", comp_quick);
  int pivo;
  if (inicio < fim)
  {
    pivo = Particiona(v, inicio, fim);
    QuickSort(v, inicio, pivo - 1);
    QuickSort(v, pivo + 1, fim);
  }
  // printf("\nComparacoes - %d quick\n", comp_quick);
}

int Particiona(int v[], int inicio, int fim)
{
  int esq = inicio;
  int dir = fim;
  int pivo = v[inicio];
  int temp = 0;

  while (esq < dir)
  {
    // incrementa o contador
    comp_quick++;
    // printf("\nCont particiona = %d\n", comp_quick);

    while (v[esq] <= pivo && esq <= fim)
    {
      esq++;
    }

    while (v[dir] > pivo && dir >= inicio)
    {
      dir--;
    }

    if (esq < dir)
    {
      temp = v[esq];
      v[esq] = v[dir];
      v[dir] = temp;
    }
  }

  temp = v[inicio];
  v[inicio] = v[dir];
  v[dir] = temp;

  return dir;
}

//#####################################################
//############### Heap Sort ###########################

int Max_Heapify(int *v, int i, int tam)
{

  int esq = (2 * i) + 1;
  int dir = (2 * i) + 2;
  int maior = i;
  int temp = 0;
  int comp_heap = 0;

  // compara
  comp_heap++;
  if (esq <= tam - 1 && v[esq] > v[i])
  {
    maior = esq;
  }

  // comprara
  comp_heap++;
  if (dir <= tam - 1 && v[dir] > v[maior])
  {
    maior = dir;
  }

  if (maior != i)
  {
    temp = v[i];
    v[i] = v[maior];
    v[maior] = temp;
    Max_Heapify(v, maior, tam);
  }

  return comp_heap;
}

void Build_Max_Heap(int *v, int tam)
{

  int i = (tam - 2) / 2;
  while (i >= 0)
  {
    Max_Heapify(v, i--, tam);
  }
}

int HeapSort(int *v, int tam)
{
  int temp = 0;

  int comp_heap = 0;

  Build_Max_Heap(v, tam);

  while (tam != 1)
  {
    temp = v[0];
    v[0] = v[tam - 1];
    v[tam - 1] = temp;
    tam--;

    comp_heap = comp_heap + Max_Heapify(v, 0, tam);
  }

  printf("Comp - Heap: %d", comp_heap);
  return comp_heap;
}

void keySort(FILE *saida, Heroi hero[], char sort, int qtde, char order)
{

  printf("\n ENTREI!!!\n");
  printf("\n sort: %c\n", sort);
  printf("\n qtde: %d\n", qtde);

  for (int i = 0; i < qtde; i++)
  {
    printf("\n %d\n", i);
    printaHeroi(&hero[i]);
  }

  //----------------------------------------------------------------
  // ----------------- Vetor KeyNode e Vetor Chave -----------------
  //----------------------------------------------------------------

  int vetorChave[qtde];
  KeyNode key[qtde];

  for (int i = 0; i < qtde; i++)
  {
    vetorChave[i] = atoi(hero[i].chave);
    key[i].chave = atoi(hero[i].chave);
    key[i].RRN = i;
  }

  for (int i = 0; i < qtde; i++)
  {
    printf("%d - %d\n", key[i].chave, key[i].RRN);
  }

  //----------------------------------------------------------------
  // ----------------- Ordena o vetor Chave ------------------------
  //----------------------------------------------------------------

  switch (sort)
  {
  case 'Q':
    QuickSort(vetorChave, 0, qtde - 1);
    break;

  case 'M':
    MergeSort(vetorChave, 0, qtde - 1);
    break;

  case 'H':
    HeapSort(vetorChave, qtde);
    break;
  case 'I':
    InsertionSort(vetorChave, qtde);
    break;

  default:

    break;
  }

  printf("\n Vetor Ordenadooooooooooooooooooooooooooooooooooooooooooooooo\n");

  for (int i = 0; i < qtde; i++)
  {
    printf("%d, \n", vetorChave[i]);
  }

  //----------------------------------------------------------------
  // ----------------- Imprime no arquivo --------------------------
  //----------------------------------------------------------------

  if (order == 'C')
  {
    for (int i = 0; i < qtde; i++)
    {
      for (int j = 0; j < qtde; j++)
      {
        if (vetorChave[i] == key[j].chave)
          printaHeroiArq(&hero[key[j].RRN], saida);
      }
    }
  }
  else
  {
    for (int i = qtde; i >= 0; i--)
    {
      for (int j = qtde; j >= 0; j--)
      {
        if (vetorChave[i] == key[j].chave)
          printaHeroiArq(&hero[key[j].RRN], saida);
      }
    }
  }
}

Heroi quebraStringEmHeroi(char *string)
{
  Heroi ret;
  char *aux = strtok(string, "|\n");

  strcpy(ret.chave, aux);
  aux = strtok(NULL, "|\n");
  strcpy(ret.primeiroNome, aux);
  aux = strtok(NULL, "|\n");
  strcpy(ret.sobrenome, aux);
  aux = strtok(NULL, "|\n");
  strcpy(ret.nomeHeroi, aux);
  aux = strtok(NULL, "|\n");
  strcpy(ret.poder, aux);
  aux = strtok(NULL, "|\n");
  strcpy(ret.fraqueza, aux);
  aux = strtok(NULL, "|\n");
  strcpy(ret.cidade, aux);
  aux = strtok(NULL, "|\n");
  strcpy(ret.profissao, aux);

  return (ret);
}

void printaHeroi(Heroi *h)
{
  printf("------------------\n");
  printf("Chave: %s\n", h->chave);
  printf("Nome: %s\n", h->primeiroNome);
  printf("Sobrenome: %s\n", h->sobrenome);
  printf("Nome heroi: %s\n", h->nomeHeroi);
  printf("Poder: %s\n", h->poder);
  printf("Fraqueza: %s\n", h->fraqueza);
  printf("Cidade: %s\n", h->cidade);
  printf("Profissao: %s\n", h->profissao);
  printf("------------------\n");
}

void printaHeroiArq(Heroi *h, FILE *saida)
{
  fprintf(saida, "%s|", h->chave);
  fprintf(saida, "%s|", h->primeiroNome);
  fprintf(saida, "%s|", h->sobrenome);
  fprintf(saida, "%s|", h->nomeHeroi);
  fprintf(saida, "%s|", h->poder);
  fprintf(saida, "%s|", h->fraqueza);
  fprintf(saida, "%s|", h->cidade);
  fprintf(saida, "%s\n", h->profissao);
}

//#####################################################
//############### MAIN ###########################
int main(int argc, char const *argv[])
{
  setlocale(LC_ALL, "");

  printf("Numero de parametros fornecidos: %d\n", argc);

  if (argc != 3)
  {
    printf("Quantidade de parametros invalida\n");
    return 0;
  }

  for (int i = 0; i < argc; i++)
  {
    printf("argv[%d] = %s\n", i, argv[i]);
  }

  // abrir os arquivos em modo leitura e escrita
  FILE *input1 = fopen(argv[1], "r+");
  FILE *output1 = fopen(argv[2], "w");

  // Verificar se o arquivo de entrada eh valido
  // setbuf(entrada, NULL);
  if (input1 == NULL)
  {
    printf("O arquivo de INPUT nao pode ser aberto corretamente!\n");
    return 1;
  }
  else
  {
    printf("\nO arquivo INPUT foi aberto com sucesso!\n");
  }

  // Verificar se o arquivo de saida eh valido
  if (output1 == NULL)
  {
    printf("O arquivo OUTPUT nao pode ser criado corretamente!\n\n");
    return 1;
  }
  else
  {
    printf("O arquivo OUTPUT foi criado com sucesso!\n\n");
  } // else
  // Verificar se o arquivo de saÃ­da Ã© vÃ¡lido

  int size = 0;
  int top = 0;
  int qtde = 0;
  char sort;
  char order;

  // Pegando o valor do indice do arq de entrada
  fscanf(input1, "SIZE=%d TOP=-1 QTDE=%d SORT=%c ORDER=%c\n", &size, &qtde, &sort, &order);
  printf("SIZE=%d TOP=-1 QTDE=%d SORT=%c ORDER=%c\n\n", size, qtde, sort, order);

  if (sort == 'Q' || sort == 'M' || sort == 'H' || sort == 'I')
  {
    printf("\t\t----------SORT OK----------\n");
  }
  else
  {
    printf("\nO SORT RECEBIDO %c NAO FOI ACEITO\n", sort);
    return 0;
  }

  if (order == 'C' || order == 'D')
  {
    printf("\t\t----------ORDER OK----------\n");
  }
  else
  {
    printf("\nO ORDER RECEBIDO %c NAO FOI ACEITO\n", order);
    return 0;
  }

  // ------------------------------------------------------------------------------------

  char copiadora[200];

  printf("-------- qtde= %d -----", qtde);

  Heroi h[qtde];

  int i = 0;
  char *token = NULL;

  while (!feof(input1))
  {
    if (fgets(copiadora, BUFSIZ, input1) != NULL)
    {
      printf("\nDADOS DO ARQ: %s\n", copiadora);
      h[i] = quebraStringEmHeroi(&copiadora);
      printf("--------------- Indice %d -----------------", i);
      printaHeroi(&h[i]);
    }
    i++;
  }

  fprintf(output1, "SIZE=%d TOP=-1 QTDE=%d SORT=%c ORDER=%c\n", size, qtde, sort, order);
  keySort(output1, h, sort, qtde, order);

  fclose(input1);
  fclose(output1);

  return 0;
} // main
