/**
 * @file bubblesort
 * @author Luiz Gustavo Pasini Abudi & Ian Ferranti
 * @date 05-04-2002
 * @brief Algoritmos de OrdenaÃ§Ã£o
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>

//############### Bubble Sort ##########################
void bubblesort(int *v, int elemento, int *interacao_bublle)
{
    bool trocar = true;
    int aux = 0;
    interacao_bublle = 0;

    while (trocar == true)
    {
        trocar = false;

        for (int i = 0; i < elemento - 1; i++)
        {
            interacao_bublle++;
            if (v[i] > v[i + 1])
            {

                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;

                trocar = true;

            } // if
        }     // for

    } // while
}

//#####################################################
//############### Insertion Sort ######################
void InsertionSort(int *v, int tam, int *interacao_insertion)
{
    int aux;
    int j;
    interacao_insertion = 0;

    for (int i = 1; i < tam; i++)
    {
        aux = v[i];
        j = i - 1;
        interacao_insertion++;
        while (j >= 0 && aux < v[j])
        {
            v[j + 1] = v[j];
            j = j - 1;
        } // while
        v[j + 1] = aux;

    } // for

} // Insertion

//#####################################################
//############### Selection Sort ######################

void selectionsort(int *v, int tam, int *interacao_selection)
{
    int i, i_menor, menor;
    int aux;
    interacao_selection = 0;

    // percorre o v com indice i
    for (i = 0; i < tam - 1; i++)
    {
        menor = i;
        // percorre o vetor procurando o menor
        for (i_menor = i + 1; i_menor < tam; i_menor++)
        {
            interacao_selection++;
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
} // selection

//#####################################################
//############### Merge Sort ##########################

void Merge(int *v, int inicio, int meio, int fim, int *interacao_merge)
{
    int i = 0; // indice do vetor auxiliar
    int tam_vet = (fim - inicio) + 1;
    int *vet_aux = malloc(tam_vet * sizeof(int));
    int aux1 = inicio;
    int aux2 = meio + 1;

    while (aux1 <= meio && aux2 <= fim)
    {
        // incrementa o contador
        interacao_merge++;

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

} // merge

void MergeSort(int *v, int inicio, int fim, int *interacao_merge)
{
    int meio;

    if (inicio < fim)
    {
        meio = ((inicio + fim) / 2);
        MergeSort(v, inicio, meio, interacao_merge);
        MergeSort(v, meio + 1, fim, interacao_merge);
        Merge(v, inicio, meio, fim, interacao_merge);
    } // if
} // merge sort

//#####################################################
//############### Quick Sort ##########################
void QuickSort(int v[], int inicio, int fim, int *interacao_quick)
{
    int pivo;
    if (inicio < fim)
    {
        pivo = Particiona(v, inicio, fim, interacao_quick);
        QuickSort(v, inicio, pivo - 1, interacao_quick);
        QuickSort(v, pivo + 1, fim, interacao_quick);
    }
}

int Particiona(int v[], int inicio, int fim, int *interacao_quick)
{
    int esq = inicio;
    int dir = fim;
    int pivo = v[inicio];
    int temp = 0;
    interacao_quick = 0;

    while (esq < dir)
    {
        // incrementa o contador
        interacao_quick++;

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

// #####################################################
// FUNCAO IMPRIMIR VETOR NO ARQUIVO E ORDENADO
void printOrdernado(FILE *saida, int *vetor_bubble, int *vetor_selection, int *vetor_insertion, int *vetor_merge, int *vetor_quick,
                    int tamanho_vet, int interacao_bubble, int interacao_selection, int interacao_insertion, int interacao_merge, int interacao_quick,
                    clock_t tempo_bubble, clock_t tempo_selection, clock_t tempo_insertion, clock_t tempo_merge, clock_t tempo_quick)
{
    int i = 0;
    fprintf(saida, "InsertionSort: ");
    for (vetor_insertion = vetor_insertion[i]; i < tamanho_vet; i++)
    {
        fprintf(saida, "%d, %d comp, %d ms ", vetor_insertion[i], interacao_insertion, ((int)tempo_bubble) / ((CLOCKS_PER_SEC / 1000)));
    }
    fprintf(saida, "\n");

    i = 0;
    fprintf(saida, "SelectionSort: ");
    for (vetor_selection[i]; i < tamanho_vet; i++)
    {
        fprintf(saida, "%d, %d comp, %ld ms ", vetor_selection[i], interacao_selection, ((int)tempo_selection) / ((CLOCKS_PER_SEC / 1000)));
    }
    fprintf(saida, "\n");

    i = 0;
    fprintf(saida, "BubbleSort: ");
    for (vetor_bubble[i]; i < tamanho_vet; i++)
    {
        fprintf(saida, "%d, %d comp, %ld ms ", vetor_bubble[i], interacao_bubble, ((int)tempo_bubble) / ((CLOCKS_PER_SEC / 1000)));
    }
    fprintf(saida, "\n");

    i = 0;
    fprintf(saida, "MergeSort: ");
    for (vetor_merge[i]; i < tamanho_vet; i++)
    {
        fprintf(saida, "%d, %d comp, %ld ms ", vetor_merge[i], interacao_merge, ((int)tempo_merge) / ((CLOCKS_PER_SEC / 1000)));
    }
    fprintf(saida, "\n");

    i = 0;
    fprintf(saida, "QuickSort: ");
    for (vetor_quick[i]; i < tamanho_vet; i++)
    {
        fprintf(saida, "%d, %d comp, %ld ms ", vetor_quick[i], interacao_quick, ((int)tempo_quick) / ((CLOCKS_PER_SEC / 1000)));
    }
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

    // Verificar se o arquivo de entrada Ã© vÃ¡lido
    if (entrada == NULL)
    {
        printf("O arquivo de ENTRADA não pode ser aberto corretamente!\n");
        exit(1);
    }
    else
    {
        printf("O arquivo foi aberto com sucesso!\n\n");
    }
    // Verificar se o arquivo de saÃ­da Ã© vÃ¡lido
    if (saida == NULL)
    {
        printf("O arquivo de Saida não pode ser criado corretamente!\n\n");
        exit(1);
    }
    else
    {
        printf("O arquivo foi criado com sucesso!\n");
    } // else

    int tamanho_vet = 0;
    // obter o primeiro caracter do arquivo de entrada
    fscanf(entrada, "%d\n", &tamanho_vet);
    printf("O valor %d é o tamanho do vetor\n", tamanho_vet);

    // iniciando o vetor de tamanho vet
    int vetor[tamanho_vet];

    char tipo_ordem;
    // obter o tipo de ordenacao do arquivo
    setbuf(entrada, NULL);
    
    // fseek(entrada, sizeof((int)tipo_ordem), SEEK_SET);
    tipo_ordem = getc(entrada);
    printf("O valor %c não é valido\n", tipo_ordem);

    if (tipo_ordem != 'c', tipo_ordem != 'd', tipo_ordem != 'r')
    {
        printf("entrei\n");
        printf("O valor %c não é valido", tipo_ordem);
        fclose(entrada);
        fclose(saida);
        return 0;
    }

    for (int i = 1; i <= tamanho_vet; i++)
    {

        switch (tipo_ordem)
        {
        // se o arquivo for do tipo c em ORDEM CRESCENTE
        case 'c':
            vetor[i - 1] = i;
            break;

        // se o arquivo for do tipo c em ORDEM DECRESCENTE
        case 'd':
            vetor[i - 1] = tamanho_vet - i;
            break;

        // se o arquivo for do tipo c em ORDEM RANDOMICA
        case 'r':
            vetor[i - 1] = (rand() % 32000);
            break;

        default:
            break;
        } // switch
    }     // for

    // definindo as variaveis dos vetores e contadores de interacÃµes
    int *vetor_bubble;
    int *vetor_selection;
    int *vetor_insertion;
    int *vetor_merge;
    int *vetor_quick;
    int *vetor_heap;
    int interacao_bublle;
    int interacao_selection;
    int interacao_insertion;
    int interacao_merge;
    int interacao_quick;
    // int interacao_heap;

    // copia o valor do vetor do arq para os vetores das funcoes
    for (int j = 0; j < tamanho_vet; j++)
    {
        vetor_bubble[j] = vetor[j];
        vetor_selection[j] = vetor[j];
        vetor_insertion[j] = vetor[j];
        vetor_merge[j] = vetor[j];
        vetor_quick[j] = vetor[j];
        vetor_heap[j] = vetor[j];
    } // for

    //###############################################################
    // Calculando o tempo de cada sort

    clock_t tempo_bubble;
    clock_t tempo_selection;
    clock_t tempo_insertion;
    clock_t tempo_merge;
    clock_t tempo_quick;
    // clock_t tempo_heap;

    tempo_bubble = clock();
    // chamada da funÃ§ao para executar as ordenaÃ§oes dos valores
    bubblesort(vetor_bubble, tamanho_vet, &interacao_bublle);
    // calculando o tempo
    tempo_bubble = clock() - tempo_bubble;

    tempo_selection = clock();
    selectionsort(vetor_selection, tamanho_vet, &interacao_selection);
    tempo_selection = clock() - tempo_selection;

    tempo_insertion = clock();
    InsertionSort(vetor_insertion, tamanho_vet, &interacao_insertion);
    tempo_insertion = clock() - tempo_insertion;

    tempo_merge = clock();
    MergeSort(vetor_merge, 0, tamanho_vet, &interacao_merge);
    tempo_merge = clock() - tempo_merge;

    tempo_quick = clock();
    QuickSort(vetor_quick, 0, tamanho_vet, &interacao_quick);
    tempo_quick = clock() - tempo_quick;

    printOrdernado(saida, vetor_bubble, vetor_selection, vetor_insertion, vetor_merge, vetor_quick,
                   tamanho_vet, interacao_bublle, interacao_selection, interacao_insertion, interacao_merge,
                   interacao_quick, tempo_bubble, tempo_selection, tempo_insertion, tempo_merge, tempo_quick);

    fclose(entrada);
    fclose(saida);

    return 0;
} // main

/*

-> ARRUMAR O BUG DE PEGAR CHAR DO ARQ LINHA:313
-> IMPLEMENTAR HEAPSORT
-> IMPLEMENTAR CONTADOR, TEMPO E ORDENAÇAO HEAP SORT
-> VERIFICAR SE O CODIGO ESTA IMPRIMINDO CORRETAMENTE NO ARQUIVO
-> VERIFICAR TODAS AS POSSIBILIDADES DE ENTRADA
-> COMENTAR O CODIGO (EXPLICAÇAO)

*/