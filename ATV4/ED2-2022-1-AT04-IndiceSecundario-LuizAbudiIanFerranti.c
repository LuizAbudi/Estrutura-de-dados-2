/**
 * @file
 * @author Luiz Gustavo Pasini Abudi & Ian Ferranti
 * @date 19-06-2002
 * @brief
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE_PK 40

typedef struct
{
    int size;
    int top;
    int qtde;
    int status;
} HeaderInfo;

typedef struct
{
    char ano[5];     // XXXX
    char duracao[6]; // XX:XX
    char titulo[31];
    char artista[21];
    char genero[12];
    char idioma[12];
} Musica;

typedef struct
{
    char chavePrimaria[MAX_SIZE_PK]; // chavePrimaria (titulo + artista)
    int RRN;                         // RRN
} ItemArrayPrimario;

typedef struct
{
    char chavePrimaria[MAX_SIZE_PK];
    char chaveSecundaria[15];
} ItemArraySecundario;

typedef struct
{
    FILE *arqDados;                       // arquivo com os dados (brutos/reais)
    FILE *arqIdxPrimario;                 // arquivo de dump do indice primario
    FILE *arqIdxSecundario;               // arquivo de dump do indice secundario (generos)
    ItemArrayPrimario *arrayPrimario;     // arrayPrimario
    ItemArraySecundario *arraySecundario; // arraySecundario
} IndiceSecundario;

//#####################################################
//############### Função auxiliar qsort ###############
int comparArraySecundario(void *a, void *b)
{
    return strcmp((*(ItemArraySecundario *)a).chaveSecundaria, (*(ItemArraySecundario *)b).chaveSecundaria);
}

int comparArrayPrimario(void *a, void *b)
{
    return strcmp((*(ItemArrayPrimario *)a).chavePrimaria, (*(ItemArrayPrimario *)b).chavePrimaria);
}

//#####################################################
//############### leituraDoCabecalho ##################
HeaderInfo leituraDoCabecalho(IndiceSecundario *idx)
{
    // garante: cabeçote está no começo do arquivo
    fseek(idx->arqDados, 0, SEEK_SET);
    HeaderInfo ret;
    fscanf(idx->arqDados, "SIZE=%d TOP=%d QTDE=%d STATUS=%d\n", &ret.size,
           &ret.top, &ret.qtde, &ret.status);
    return (ret);
}

//#####################################################
//############### criarChavePrimaria ##################
char *criarChavePrimaria(char *titulo, char *artista)
{
    // concatena, maiusculo
    char *chave = malloc(MAX_SIZE_PK * sizeof(char));
    strcpy(chave, titulo);
    strcat(chave, artista);
    // printf("Merge = %s\n", chave);
    for (int i = 0; i < strlen(chave); i++)
    {
        chave[i] = toupper(chave[i]);
    }
    return (chave);
}

//#####################################################
//############### criarChaveSecundaria ################
char *criarChaveSecundaria(char *palavra)
{
    for (int i = 0; i < strlen(palavra); i++)
    {
        palavra[i] = toupper(palavra[i]);
    }
    return (palavra);
}

//#####################################################
//############### quebraStringEmMusica ################
Musica quebraStringEmMusica(char *linha)
{
    Musica music;
    char *pch;
    pch = strtok(linha, "|\n");
    strcpy(music.ano, pch);
    pch = strtok(NULL, "|\n");
    strcpy(music.duracao, pch);
    pch = strtok(NULL, "|\n");
    strcpy(music.titulo, pch);
    pch = strtok(NULL, "|\n");
    strcpy(music.artista, pch);
    pch = strtok(NULL, "|\n");
    strcpy(music.genero, pch);
    pch = strtok(NULL, "|\n");
    strcpy(music.idioma, pch);

    return (music);
}

//#####################################################
//############### iniciaIndiceSecundario ##############
void iniciaIndiceSecundario(IndiceSecundario *ds, char *nomeArquivo, char opcaoChave[MAX_SIZE_PK])
{

    // abrir os arquivos
    ds->arqDados = fopen(nomeArquivo, "r+");
    ds->arqIdxPrimario = fopen("indicePrimario.txt", "w+");
    ds->arqIdxSecundario = fopen("IndiceSecundario.txt", "w+");

    // descobrir qtde de registros no arquivo de arqDados
    HeaderInfo info = leituraDoCabecalho(ds);
    printf("Numero de Registros: %d\n", info.qtde);

    // alocar memoria do arrayPrimario
    ds->arrayPrimario = malloc(info.qtde * sizeof(ItemArrayPrimario));
    // alocar memoria do arraySecundario
    ds->arraySecundario = malloc(info.qtde * sizeof(ItemArraySecundario));

    // Percorre o arquivo (laço):
    char linha[info.size + 1];
    char keyP[MAX_SIZE_PK], keyS[MAX_SIZE_PK];
    Musica registro;
    int RRN = 0;
    ItemArrayPrimario iap;
    ItemArraySecundario ias;

    while (fgets(linha, info.size, ds->arqDados) != NULL)
    {
        // iteração = registro (ano|duracao|titulo|artista|...)
        registro = quebraStringEmMusica(linha);
        // criar chave canonica primaria
        strcpy(keyP, criarChavePrimaria(registro.titulo, registro.artista));
        //     criar chave canonica secundaria (Genero)
        if (strcmp(opcaoChave, "ano") == 0)
        {
            strcpy(keyS, criarChaveSecundaria(registro.ano));
        }
        else if (strcmp(opcaoChave, "titulo") == 0)
        {
            strcpy(keyS, criarChaveSecundaria(registro.titulo));
        }
        else if (strcmp(opcaoChave, "artista") == 0)
        {
            strcpy(keyS, criarChaveSecundaria(registro.artista));
        }
        else if (strcmp(opcaoChave, "genero") == 0)
        {
            strcpy(keyS, criarChaveSecundaria(registro.genero));
        }
        else if (strcmp(opcaoChave, "idioma") == 0)
        {
            strcpy(keyS, criarChaveSecundaria(registro.idioma));
        }
        printf("==========================\n");
        // insere no array primario: (chave primaria | RNN)
        strcpy(iap.chavePrimaria, keyP);
        iap.RRN = RRN;
        ds->arrayPrimario[RRN] = iap;
        // insere no array secundario (chave secundaria | chave primaria)
        strcpy(ias.chavePrimaria, keyP);
        strcpy(ias.chaveSecundaria, keyS);
        printf("keyP = %s\n", ias.chavePrimaria);
        printf("keyS = %s\n", ias.chaveSecundaria);
        ds->arraySecundario[RRN] = ias;
        RRN++;
    }

    // Ordena:
    //     ordena arraySecundario (se tiver chaves iguais, considerar a primaria)
    qsort(ds->arraySecundario, info.qtde, sizeof(ItemArraySecundario), comparArraySecundario);
    //     ordena arrayPrimario
    qsort(ds->arrayPrimario, info.qtde, sizeof(ItemArrayPrimario), comparArrayPrimario);
    // Abrir/Criar os arquivos de dump
    //      grava o indice secundario (arqIdxSecundario)
    for (int i = 0; i < info.qtde; i++)
    {
        fprintf(ds->arqIdxSecundario, "%-40s | %s\n", ds->arraySecundario[i].chavePrimaria, ds->arraySecundario[i].chaveSecundaria);
    }
    //      grava o indice primario (arqIdxPrimario)
    for (int i = 0; i < info.qtde; i++)
    {
        fprintf(ds->arqIdxPrimario, "%-40s | %d\n", ds->arrayPrimario[i].chavePrimaria, ds->arrayPrimario[i].RRN);
    }
}

//#####################################################
//############### Busca as corresponedncias ###########

void buscaCorrespondencias(IndiceSecundario *ds, FILE *saida, char escolha[MAX_SIZE_PK])
{
    char *ret = NULL;
    HeaderInfo info = leituraDoCabecalho(ds);

    for (int i = 0; i < strlen(escolha); i++)
    {
        escolha[i] = toupper(escolha[i]);
    }

    printf("\n ====== %s =====\n", escolha);

    int aux = 0;
    for (int i = 0; i < info.qtde; i++)
    {
        //compara as chaves e imprime no saida o resultado das comparacoes
        if (strcmp(escolha, ds->arraySecundario[i].chaveSecundaria) == 0)
        {
            ret = (char*)malloc((aux+1) * sizeof(char*));
            ret = ds->arraySecundario[i].chavePrimaria;
            imprimeNoArqSaida(ds, saida, ret);
            printf("\n --------- %s ----------", ds->arraySecundario[i].chavePrimaria);
            aux++;
        }
    }
    //caso para erro na entrada do arquivo
    if(ret == NULL){
        printf("Entrada Invalida\n");
        fprintf(saida, "Entrada Invalida\n");
    }

}

//#####################################################
//############### imprimeNoArqSaida ###################
void imprimeNoArqSaida(IndiceSecundario *ds, FILE *saida, char *pesquisa)
{
    HeaderInfo info = leituraDoCabecalho(ds);
    int ret = -1;
    int aux = 0;

    printf("\n ====== %s =====\n", pesquisa);

    for (int i = 0; i < info.qtde; i++)
    {
        if (strcmp(pesquisa, ds->arrayPrimario[i].chavePrimaria) == 0)
        {
            ret = ds->arrayPrimario[i].RRN;
            printf("\n --------- %d ----------", ds->arrayPrimario[i].RRN);
            aux++;
        }
    }

    aux = -1;
    char linha[info.size + 1];

    while (fgets(linha, info.size, ds->arqDados) != NULL)
    {
        aux++;
        if (aux == ret)
            fprintf(saida, "%s", linha);
    }
}

//#####################################################
//############### imprimeIndiceSecundario #############
void imprimeIndiceSecundario(IndiceSecundario *ds)
{
    // int N = sizeof(ds->arraySecundario)/sizeof(ds->arraySecundario[0]);
    int N = leituraDoCabecalho(ds).qtde;
    // percorrer e imprimir as posicoes dos vetores
    ItemArrayPrimario iap;
    ItemArraySecundario ias;
    printf("====================================\n");
    printf(" IDX PRIM | IDX SEC\n");
    printf("====================================\n");
    printf("N = %d\n", N);
    for (int i = 0; i < N; i++)
    {
        iap = ds->arrayPrimario[i];
        ias = ds->arraySecundario[i];
        printf("%d: [%s | %d] [%s | %s]\n", i, iap.chavePrimaria, iap.RRN,
               ias.chaveSecundaria, ias.chavePrimaria);
    }
    printf("====================================\n");
}

//#####################################################
//############### destroiIndiceSecundario #############
void destroiIndiceSecundario(IndiceSecundario *ds)
{
    // verifica se não está atualizado no arquivo
    //      gravar os indices nos arquivos de dump
    // desalocar os vetores (arrayPrimario, arraySecundario)
    free(ds->arraySecundario);
    free(ds->arrayPrimario);
    // fechar os arquivos (dumps, dados)
    fclose(ds->arqDados);
    fclose(ds->arqIdxPrimario);
    fclose(ds->arqIdxSecundario);
}

//#####################################################
//############### MAIN ################################
int main(int argc, char const *argv[])
{
    
    printf("Numero de parametros fornecidos: %d\n", argc);

    if (argc != 4)
    {
        printf("Quantidade de parametros invalida\n");
        return 0;
    }

    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    

    // abrir os arquivos em modo leitura e escrita
    FILE *arqConsulta = fopen(argv[2] , "r+");
    FILE *saida = fopen(argv[3], "w+");
    
    // Verificar se o arquivo de consulta é válido
    if (arqConsulta == NULL)
    {
        printf("O arquivo CONSULTA nao pode ser aberto corretamente!\n\n");
        return 0;
    }
    else
    {
        printf("O arquivo CONSULTA foi aberto com sucesso!\n\n");
    }
    // Verificar se o arquivo de saida é válido
    if (saida == NULL)
    {
        printf("O arquivo OUTPUT nao pode ser criado corretamente!\n\n");
        return 0;
    }
    else
    {
        printf("O arquivo OUTPUT foi criado com sucesso!\n\n");
    }

    //#####################################################
    //########### Leitura do arq de consulta ##############
    char opcaoDeBusca[MAX_SIZE_PK];
    fscanf(arqConsulta, "%s\n", &opcaoDeBusca);
    for (int i = 0; i < strlen(opcaoDeBusca); i++)
    {
        opcaoDeBusca[i] = tolower(opcaoDeBusca[i]);
    }

    char nomeDaOpcao[MAX_SIZE_PK];
    fscanf(arqConsulta, "%s\n", &nomeDaOpcao);

    if (strcmp(opcaoDeBusca, "ano") != 0 && strcmp(opcaoDeBusca, "titulo") != 0 && strcmp(opcaoDeBusca, "artista") != 0 &&
        strcmp(opcaoDeBusca, "genero") != 0 && strcmp(opcaoDeBusca, "idioma") != 0)
    {
        fprintf(saida, "Entrada de opcao invalida!\n");
        printf("\nEntrada de opcao invalida!\n");
        return 0;
    }

    //#####################################################
    //#####################################################
    IndiceSecundario secondIdx;

    iniciaIndiceSecundario(&secondIdx, argv[1], opcaoDeBusca);
    imprimeIndiceSecundario(&secondIdx);
    buscaCorrespondencias(&secondIdx, saida, nomeDaOpcao);
    destroiIndiceSecundario(&secondIdx);
    fclose(arqConsulta);
    fclose(saida);

    return 0;
}