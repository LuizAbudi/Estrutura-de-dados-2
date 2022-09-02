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


typedef struct{
    char chave[4]; //3 char
    char nome[31];
    char sexo;//1 char
    int idade;// 2
    char caracteristica[31];  //30
    char numeroTel[15]; //14

} Professor;
    //80 + | = 86char por linha do arq


void adicionaRegistro(FILE* arq, Professor p)
{
    int topo;
    int size;

    while(!feof(arq))
    {
        fscanf(arq, "size=%d top=%d\n", &size, &topo);
        printf("sizeADC=%d topADC=%d\n\n", size, top);
    
        if(size = -1)
        {
            fseek(arq, 86, SEEK_END);
            fprintf(arq, "%s|%s|%c|%d|%s|%s\n", p.chave, p.nome, p.sexo, p.idade, p.caracteristica, p.numeroTel);

        }
        
    }


}

/*
void removeRegistro(FILE* arq, int id);

{
    char *buffer;
    int buffersize = 127;

    while (!feof(arq))
    {
        buffer = fgets(buffer, buffersize, arq);

    }

}
*/

//#####################################################
//############### MAIN ###########################
int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "");

    printf("Numero de parametros fornecidos: %d\n", argc);

    if (argc != 5)
    {
        printf("Quantidade de parametros invalida\n");
        return 0;
    }

    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    // abrir os arquivos em modo leitura e escrita
    FILE *input1 = fopen(argv[1], "r");
    FILE *operations1 = fopen(argv[2], "r");
    FILE *temp = fopen(argv[3], "w");
    FILE *output1 = fopen(argv[4], "w");
 

    // Verificar se o arquivo de entrada é válido
    //setbuf(entrada, NULL);
    if (input1 == NULL)
    {
        printf("O arquivo de INPUT nao pode ser aberto corretamente!\n");
        return 1;
    }
    else
    {
        printf("\nO arquivo INPUT foi aberto com sucesso!\n");
    }

       // Verificar se o arquivo operations é válido
    if (operations1 == NULL)
    {
        printf("O arquivo OPERATIONS nao pode ser aberto corretamente!\n\n");
        return 1;
    }
    else
    {
        printf("O arquivo OPERATION foi aberto com sucesso!\n");
    } // else


       // Verificar se o arquivo temp é válido
    if (temp == NULL)
    {
        printf("O arquivo TEMP nao pode ser criado corretamente!\n\n");
        return 1;
    }
    else
    {
        printf("O arquivo TEMP foi criado com sucesso!\n");
    } // else


    // Verificar se o arquivo de saída é válido
    if (output1 == NULL)
    {
        printf("O arquivo OUTPUT nao pode ser criado corretamente!\n\n");
        return 1;
    }
    else
    {
        printf("O arquivo OUTPUT foi criado com sucesso!\n\n");
    } // else

    int size = 0;
    int top = 0;

    //Pegando o valor do size e top do arq de entrada
    fscanf(input1, "size=%d top=%d\n", &size, &top);
    printf("size=%d top=%d\n\n", size, top);

    char tipoOp;
    char espaco;
    char novaPessoa[size];
    char novaChave[5];

    //Criando um arquivo para armazenar os dados novos a serem inseridos 
    FILE *novosDados = fopen("novosDados.txt", "w");
     // Verificar se o arquivo de saída é válido
    if (output1 == NULL)
    {
        printf("O arquivo OUTPUT nao pode ser criado corretamente!\n\n");
        return 1;
    }
    else
    {
        printf("O arquivo OUTPUT foi criado com sucesso!\n\n");
    } // else

    

    while(!feof(operations1))
    {
        fscanf(operations1, "%c ", &tipoOp);
        printf("\nChar: %c\n", tipoOp);    
        

        if(tipoOp == 'i')
        {
            printf("<entrei no I>\n");
            //le a linha que possui uma nova pessoa para cadastro
            fgets(novaPessoa, 90, operations1);
            printf("Teste: %s\n", novaPessoa);

            //calcula o tamnho da string nova
            int len = strlen(novaPessoa);
            //percorre a nova string trocando ',' por '|'
            for(int i = 0; i < len; i++)
            {
              if(novaPessoa[i] == ',')
              {
                novaPessoa[i] = '|';
              }
            }
            printf("NOVA STRING: %s", novaPessoa);
            //escreve os dados prontos para insercao em um arquivo temporario
            fwrite(novaPessoa, 1, len, novosDados);

            //CHAMA FUNCAO ADICIONAR
            

        }//if i

        if(tipoOp == 'd')
        {
            printf("<entrei no D>\n");
            fgets(novaChave, 5, operations1);
            printf("String chave: %s\n", novaChave);

            //chamar funçao para storage compaction
              //comparar as strings para ver se sera invalidada ou n


        }//if d 

        //if(tipoOp != 'd' && tipoOp != 'i')
        //{
        //    printf("Operacao nao reconhecida");
        //    continue;
        // }


    }//while
    

    //PARA REMOVER REGISTO
                //se for d 
                //CHAMA A FUNÇAO DE REMOVER
                    //le a chave do registro
                    //procura a chave no arq de entrada
                        //se achou 
                            //CHAMA FUNÇAO STORAGE COMPACTION
                                //invalida o a linha colocando *(valor do topo)|
                                //atualiza o valor do topo           



    fclose(input1);
    fclose(operations1);
    fclose(temp);
    fclose(output1);
    fclose(novosDados);

    return 0;
} // main

//