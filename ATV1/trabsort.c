/**
 * @file bubblesort
 * @author Luiz Gustavo Pasini Abudi & Ian Ferranti
 * @date 05-04-2002
 * @brief Algoritmos de Ordenação
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>

 int comp_quick = 0;


//############### Bubble Sort ##########################
int bubblesort(int *v, int elemento)
{
    bool trocar = true;
    int aux = 0;
    int comp_bubble = 0;

    while (trocar == true)
    {
        trocar = false;
        for (int i = 0; i < elemento - 1; i++)
        {
            comp_bubble++;
            if (v[i] > v[i + 1])
            {
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
                trocar = true;

            } // if
        }     // for

    } // while
    printf("%d interacoes - BUBBLE\n", comp_bubble);
    return comp_bubble;
}

//#####################################################
//############### Insertion Sort ######################
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
//############### Selection Sort ######################

int selectionsort(int *v, int tam)
{

    int i, i_menor, menor;
    int aux;
    int comp_selection = 0;

    // percorre o v com indice i
    for (i = 0; i < tam - 1; i++)
    {
        menor = i;
        comp_selection++;
        // percorre o vetor procurando o menor
        for (i_menor = i + 1; i_menor < tam; i_menor++)
        {
            // acha o menor
            if (v[i_menor] < v[menor])
            {
                menor = i_menor;
            } // if
        }     // for

        if (menor != i)
        {
            aux = v[menor];
            v[menor] = v[i];
            v[i] = aux;
        } // if

    } // for
    printf("%d interacoes - Selection\n", comp_selection);
    return comp_selection;

} // selection

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
}

// #####################################################
// FUNCAO IMPRIMIR VETOR NO ARQUIVO E ORDENADO
void printOrdernado(FILE *saida, int *vetor_bubble, int *vetor_selection, int *vetor_insertion, int *vetor_merge, int *vetor_quick,
                    int *vetor_heap, int tamanho_vet, int comp_bubble, int comp_selection, int comp_insertion, int comp_merge, int comp_quick, 
                    int comp_heap, double tempo_bubble, double tempo_selection, double tempo_insertion, double tempo_merge, double tempo_quick, 
                    double tempo_heap)
{

    printf("print no arq");

    int i;
    fprintf(saida, "InsertionSort: ");
    for (i = 0; i < tamanho_vet - 1; i++)
    {
        fprintf(saida, " %d", vetor_insertion[i]);
    }
    fprintf(saida, " %d, ", vetor_insertion[i]);
    fprintf(saida, "%d comp, %ld ms ", comp_insertion, ((int)tempo_insertion) / ((CLOCKS_PER_SEC / 1000)));
    fprintf(saida, "\n");

    fprintf(saida, "SelectionSort: ");
    for (i = 0; i < tamanho_vet - 1; i++)
    {
        fprintf(saida, " %d", vetor_selection[i]);
    }
    fprintf(saida, " %d, ", vetor_selection[i]);
    fprintf(saida, "%d comp, %ld ms ", comp_selection, ((int)tempo_selection) / ((CLOCKS_PER_SEC / 1000)));
    fprintf(saida, "\n");

    fprintf(saida, "BubbleSort: ");
    for (i = 0; i < tamanho_vet - 1; i++)
    {
        fprintf(saida, " %d", vetor_bubble[i]);
    }
    fprintf(saida, " %d, ", vetor_bubble[i]);
    fprintf(saida, "%d comp, %ld ms ", comp_bubble, ((int)tempo_bubble) / ((CLOCKS_PER_SEC / 1000)));
    fprintf(saida, "\n"); 

    
    fprintf(saida, "MergeSort: ");
    for (i = 0; i < tamanho_vet - 1; i++)
    {
        fprintf(saida, " %d", vetor_merge[i]);
        
    }
    fprintf(saida, " %d, ", vetor_merge[i]);
    fprintf(saida, "%d comp, %ld ms ", comp_merge, ((int)tempo_merge) / ((CLOCKS_PER_SEC / 1000)));
    fprintf(saida, "\n");

    fprintf(saida, "QuickSort: ");
    for (i = 0; i < tamanho_vet - 1; i++)
    {
        fprintf(saida, " %d", vetor_quick[i]);
    }
    fprintf(saida, " %d, ", vetor_quick[i]);
    fprintf(saida, " %d comp, %ld ms ", comp_quick, ((int)tempo_quick) / ((CLOCKS_PER_SEC / 1000)));
    fprintf(saida, "\n");

    
    fprintf(saida, "HeapSort: ");
    for (i = 0; i < tamanho_vet - 1; i++)
    {
        fprintf(saida, "%d ", vetor_heap[i]);
    }
    fprintf(saida, " %d, ", vetor_heap[i]);
    fprintf(saida, "%d comp, %ld ms ", comp_heap, ((int)tempo_heap) / ((CLOCKS_PER_SEC / 1000)));
    fprintf(saida, "\n");
}

//#####################################################

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
    FILE *entrada = fopen(argv[1], "r");
    FILE *saida = fopen(argv[2], "w");

    // Verificar se o arquivo de entrada é válido
    setbuf(entrada, NULL);
    if (entrada == NULL)
    {
        printf("O arquivo de ENTRADA nao pode ser aberto corretamente!\n");
        exit(1);
    }
    else
    {
        printf("O arquivo foi aberto com sucesso!\n\n");
    }
    // Verificar se o arquivo de saída é válido
    if (saida == NULL)
    {
        printf("O arquivo de Saida nao pode ser criado corretamente!\n\n");
        exit(1);
    }
    else
    {
        printf("O arquivo foi criado com sucesso!\n");
    } // else

    int tamanho_vet = 0;
    // obter o primeiro caracter do arquivo de entrada
    fscanf(entrada, "%d\n", &tamanho_vet);
    printf("O valor %d e o tamanho do vetor\n", tamanho_vet);

    // iniciando o vetor de tamanho vet
    int vetor[tamanho_vet];
    // setbuf(entrada, NULL);
    char tipo_ordem;
    // obter o tipo de ordenacao do arquivo

    tipo_ordem = getc(entrada);

    if (tipo_ordem != 'c' && tipo_ordem != 'd' && tipo_ordem != 'r')
    {
        printf("entrei\n");
        printf("O valor %c nao e  valido", tipo_ordem);
        fprintf(saida, "Arquivo Inválido!");
        fclose(entrada);
        fclose(saida);
        return 0;
    }

    switch (tipo_ordem)
    {
        // se o arquivo for do tipo c em ORDEM CRESCENTE
    case 'c':
        printf("Tipo c\n");
        for (int i = 1; i <= tamanho_vet; i++)
        {
            vetor[i - 1] = i;

        } // for
        break;

    // se o arquivo for do tipo c em ORDEM DECRESCENTE
    case 'd':
        printf("Tipo d\n");
        for (int i = 1; i <= tamanho_vet; i++)
        {
            vetor[i - 1] = tamanho_vet - i;
        } // for
        break;

    // se o arquivo for do tipo c em ORDEM RANDOMICA
    case 'r':
        printf("Tipo r\n");
        for (int i = 1; i <= tamanho_vet; i++)
        {
            vetor[i - 1] = (rand() % 32000);
        } // for
        break;

    default:
        break;
    } // switch

    // definindo as variaveis dos vetores e contadores de interacões
    int vetor_bubble[tamanho_vet];
    int vetor_selection[tamanho_vet];
    int vetor_insertion[tamanho_vet];
    int vetor_merge[tamanho_vet];
    int vetor_quick[tamanho_vet];
    int vetor_heap[tamanho_vet];
    int comp_bubble;
    int comp_selection;
    int comp_insertion;
    int comp_merge = 0;
    //int comp_quick = 0;
    int comp_heap = 0;

    // copia o valor do vetor do arq para os vetores das funcoes
    int j;
    for (j = 0; j < tamanho_vet; j++)
    {
        vetor_bubble[j] = vetor[j];
        vetor_selection[j] = vetor[j];
        vetor_insertion[j] = vetor[j];
        vetor_merge[j] = vetor[j];
        vetor_quick[j] = vetor[j];
        vetor_heap[j] = vetor[j];
    } // for

    printf("\nBubble: ");
    for (int x = 0; x < tamanho_vet; x++)
    {
        printf("%d ", vetor_bubble[x]);
    }

    printf("\ninsertion: ");
    for (int x = 0; x < tamanho_vet; x++)
    {
        printf("%d ", vetor_insertion[x]);
    }

    printf("\nselection: ");
    for (int x = 0; x < tamanho_vet; x++)
    {
        printf("%d ", vetor_selection[x]);
    }

    printf("\nmerge: ");
    for (int x = 0; x < tamanho_vet; x++)
    {
        printf("%d ", vetor_merge[x]);
    }

    printf("\nquick: ");
    for (int x = 0; x < tamanho_vet; x++)
    {
        printf("%d ", vetor_quick[x]);
    }

    printf("\nheap: ");
    for (int x = 0; x < tamanho_vet; x++)
    {
        printf("%d ", vetor_heap[x]);
    }

    //###############################################################
    // Calculando o tempo de cada sort

    clock_t inicio;
    clock_t fim; 

    printf("\nchamada Sort\n");
    
    inicio = clock();
    // chamada da funcao para executar as ordenaçoes dos valores
    comp_bubble = bubblesort(vetor_bubble, tamanho_vet);
    // calculando o tempo
    fim = clock();
    double tempo_bubble = ((double)(fim - inicio)) / (CLOCKS_PER_SEC / 1000);
    printf("\ntempo bubble: %ld\n", tempo_bubble);

    inicio = clock();
    comp_selection = selectionsort(vetor_selection, tamanho_vet);
    fim = clock();
    double tempo_selection = ((double)(fim - inicio)) / (CLOCKS_PER_SEC / 1000);
    printf("\ntempo selection: %ld\n", tempo_selection);

    inicio = clock();
    comp_insertion = InsertionSort(vetor_insertion, tamanho_vet);
    fim = clock();
    double tempo_insertion = ((double)(fim - inicio)) / (CLOCKS_PER_SEC / 1000);
    printf("\ntempo insertion: %ld\n", tempo_insertion);

    inicio = clock();
    comp_merge = MergeSort(vetor_merge, 0, tamanho_vet);
    printf("\nComp Merge: %d\n", comp_merge);
    fim = clock();
    double tempo_merge = ((double)(fim - inicio)) / (CLOCKS_PER_SEC / 1000);
    printf("\ntempo merge: %ld\n", tempo_merge);

    inicio = clock();
    QuickSort(vetor_quick, 0, tamanho_vet);
    fim = clock();
    double tempo_quick = ((double)(fim - inicio)) / (CLOCKS_PER_SEC / 1000);
    printf("\ntempo quick: %ld\n", tempo_quick);

    inicio = clock();
    comp_heap = HeapSort(vetor_heap, tamanho_vet);
    fim = clock();
    double tempo_heap = ((double)(fim - inicio)) / (CLOCKS_PER_SEC / 1000);
    printf("\ntempo heap: %ld\n", tempo_heap);


    printOrdernado(saida, vetor_bubble, vetor_selection, vetor_insertion, vetor_merge, vetor_quick, vetor_heap,
                   tamanho_vet, comp_bubble, comp_selection, comp_insertion, comp_merge,
                   comp_quick, comp_heap, tempo_bubble, tempo_selection, tempo_insertion, tempo_merge, tempo_quick, tempo_heap);

    fclose(entrada);
    fclose(saida);

    return 0;
} // main

/*
-> ARRUMAR OS CONTADORES LINHA: 29, 59, 88, 120, 206
-> IMPLEMENTAR CONTADOR, TEMPO E ORDENACAO HEAP SORT
-> VERIFICAR SE O CODIGO ESTA IMPRIMINDO CORRETAMENTE NO ARQUIVO
-> VERIFICAR TODAS AS POSSIBILIDADES DE ENTRADA
-> COMENTAR O CODIGO (EXPLICACAO)
*/