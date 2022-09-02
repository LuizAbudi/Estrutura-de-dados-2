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
#define HEROI 50

typedef struct 
{
  int chave;            // chave 
  int RRN;              // é a referencia p leitura/gravação do registro
} KeyNode;

typedef struct
{
  char chave[3];         // chave numerica pode ter até 3 digitos
  char primeiroNome[16]; // primero nome do heroi
  char sobrenome[16];    // seu sobrenome
  char nomeHeroi[16];    // nome do Heroi, alias
  char poder[16];        // poder
  char fraqueza[21];     // fraqueza
  char cidade[21];       // cidade que defende
  char profissao[21];    // profissao da sua identidade secreta
} Heroi[HEROI];

//#####################################################
//############### Insertion Sort ##########################
/*
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
    }     // while

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
    }     // if/else

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
    //printf("\nCont quick = %d\n", comp_quick);
    int pivo;
    if (inicio < fim)
    {
        pivo = Particiona(v, inicio, fim);
        QuickSort(v, inicio, pivo - 1);
        QuickSort(v, pivo + 1, fim);
    }
    //printf("\nComparacoes - %d quick\n", comp_quick);
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
        //printf("\nCont particiona = %d\n", comp_quick);

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

    //compara
    comp_heap++;
    if (esq <= tam - 1 && v[esq] > v[i])
    {
        maior = esq;
    }

    //comprara
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
}*/
/*
int numeroRegistros(FILE *arq)
{
  fseek(arq, 0, SEEK_SET);

  char *copiadora;
  int contador = -1;

  while (!feof(arq))
  {
    if (fgets(copiadora, BUFSIZ, arq) != NULL)
    {
      contador++
    }
  }

  printf("CONTADOR: %d", contador);

  return contador;
}

void lerRegistroComRRN(FILE *arq, int RRN)
{

  for 

  heroi[i]

}
*/

/*
void keySort (FILE *saida, Heroi hero[], char sort, int qtde) 
{

  printf("\n ENTREI!!!\n");
  printf("\n sort: %c\n", sort);
  printf("\n qtde: %d\n", qtde);

  for (int i = 0; i < qtde; i++)
  {
    printf("\n %s\n", hero[i]);

  }

//----------------------------------------------------------------
// ----------------- Vetor KeyNode e Vetor Chave -----------------
//----------------------------------------------------------------

  int vetorChave[qtde];
  KeyNode key[qtde];
  printf("\nVetor desordenado = {");
  for (int i = 0; i < qtde; i++)
  {
    vetorChave[i] = atoi(hero[i].chave);
    key[i].chave  = atoi(hero[i].chave);
    key[i].RRN = i;
  }
  
  for (int i = 0; i < qtde; i++)
  {
    printf("%d - %d, ", key[i].chave, key[i].RRN);
    fprintf(saida, "%d - %d, ", key[i].chave, key[i].RRN);
  }
*/
   /*
  switch (sort)
  {
  case 'Q':
    
    //QuickSort(Heroi h, 0, qtde);
    break;

  case 'M':
    
    break;

  case 'H':

    break;
  case 'I':

    break;
  
  default:
  
    break;
  }
  

}
*/
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

  //----------------------------------------------------------------
  // ------------------------ Vetor Heroi ------------------------
  //----------------------------------------------------------------

  Heroi h[qtde];
  char copiadora[200];
  int i = 0;
  char *token = NULL;

  while (!feof(input1))
  {
    if (fgets(copiadora, BUFSIZ, input1) != NULL)
    {
      printf("\nDADOS DO ARQ: %s\n", copiadora);
    }

    token = strtok(copiadora, "|");
    printf("CHAVE: %s\n", token);
    strcpy(h[i]->chave, token);
    printf("CHAVE HEROI: %s\n\n", h[i]->chave);

    token = strtok(NULL, "|");
    printf("NOME: %s\n", token);
    strcpy(h[i]->primeiroNome, token);
    printf("NOME H: %s\n\n", h[i]->primeiroNome);

    token = strtok(NULL, "|");
    printf("SOBRENOME: %s\n", token);
    strcpy(h[i]->sobrenome, token);
    printf("SOBRENOME H: %s\n\n", h[i]->sobrenome);

    token = strtok(NULL, "|");
    printf("NOME HEROI: %s\n", token);
    strcpy(h[i]->nomeHeroi, token);
    printf("NOME HEROI H: %s\n\n", h[i]->nomeHeroi);

    token = strtok(NULL, "|");
    printf("PODER: %s\n", token);
    strcpy(h[i]->poder, token);
    printf("PODER H: %s\n\n", h[i]->poder);

    token = strtok(NULL, "|");
    printf("FRAQUEZA: %s\n", token);
    strcpy(h[i]->fraqueza, token);
    printf("FRAQUEZA H: %s\n\n", h[i]->fraqueza);

    token = strtok(NULL, "|");
    printf("CIDADE: %s\n", token);
    strcpy(h[i]->cidade, token);
    printf("CIDADE H: %s\n\n", h[i]->cidade);

    token = strtok(NULL, "|");
    printf("PROFISSAO: %s\n", token);
    strcpy(h[i]->profissao, token);
    printf("PROFISSAO H: %s\n\n", h[i]->profissao);

    i++;
  }

  for(int i = 0; i < qtde; i++)
  {

    printf("HEROI: %s|%s|%s|%s|%s|%s|%s|%s\n", h[i]->chave, h[i]->primeiroNome, h[i]->sobrenome, h[i]->nomeHeroi, 
                                               h[i]->poder, h[i]->fraqueza, h[i]->cidade, h[i]->profissao);
   
  }
  for(int i = 0; i < qtde; i++)
  {

    printf("HEROI SUMIR: %s\n", h[i]->nomeHeroi);   
  }
    

//keySort(output1, h, sort, qtde);

// --------------------------------------------------------------  


  fclose(input1);
  fclose(output1);

 
  return 0;
} // main





/*   instruções

 - vetor das chaves
 - vetor de KeyNodes(structs)
 - vetor de Herois(structs)

{12, 37, 62, 5, 27, 29, 81, 68, 33, 72, 66, 14, 51, 46, 79, 54, 7, 48, 64, 94, 96, 40}
RRN:
12 - 0
37 - 1
62 - 2
05 - 3
27 - 4
29 - 5
81 - 6
68 - 7
33 - 8
72 - 9
66 - 10
14 - 11
51 - 12
46 - 13
79 - 14
54 - 15
07 - 16
48 - 17
64 - 18
94 - 19
96 - 20
40 - 21


  -criar arrayitem com chave e RRN(Indice do vetor Herois)
  -criar vetor com as chaves(int)
  -jogar nos sorts
  -imprimir no arqSaida de acordo com os RRNs dos arrayitem(comparando as chaves)




*/