#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "investidor.h"

Investidor *novoInvestidor(int dinheiro){
    Investidor *inv;
    inv = (Investidor*)malloc(sizeof(Investidor));
    if(inv!=NULL){
        printf("\nInforme o nome do investidor: ");
        fgets(inv->name, sizeof(inv->name), stdin);
        inv->name[strlen(inv->name)-1] = '\0';
        inv->dinheiro = dinheiro;
        inv->totalLucro = 0;
        inv->qtdInvestimentos = 0;
        inv->investimentos = (Investimento*)malloc(sizeof(Investimento)*100);
        if(inv->investimentos!=NULL){
            return inv;
        }
        free(inv);
    }
    return NULL;
}

int destroyInvestidor(Investidor *inv){
    if(inv!=NULL){
        free(inv->investimentos);
        free(inv);
        return 1;
    }
    return 0;
}

void printAcao(Acao *ac, int i){
    if(ac!=NULL){
        printf("%d - Lucro da Acao: %d\n", i, ac->lucro);
        printf("%d - Preco da Acao: %d\n", i, ac->preco);
    }
}

// Recebe o vetor de ações
int compra(Acao* acoes, Investidor* inv, int* ct, int qntdAcoes){

    int choice = 0, i = 0, cont;
    double lucro_da_rodada=0, lucroAtual=0, custo_da_rodada=0, porcentagem =0, dinheiro = inv->dinheiro;

    setbuf(stdin, NULL);
    printf("\nDigite o numero da acao ou -1 para sair:\n");
    scanf("%d", &choice);
    if (choice == -1) return -1;

  
    printf("Digite a porcentagem da acao (1 a 100%%):\n");
    scanf(" %lf", &porcentagem);

    //printar processo para informar usuario da escolha que ele fara para ver se ele tem certeza
    printf("\n----------------------------------\n");
    printf("\nInvestimento\n");
    printf("Lucro :%lf\n", ((porcentagem/100)* acoes[choice].lucro));
    printf("Preco :%lf\n", ((porcentagem/100)* acoes[choice].preco));
    printf("\n----------------------------------\n");

    
    int querContinuar;
    printf("\nQuer continuar o investimento?(0 - nao/ 1 - sim)\n");
    scanf("%d", &querContinuar);

    switch(querContinuar){
        case(1):
            // Incremento o valor que estah no cont da função main
            cont = ++*ct;
            //Lucro e custo da compra
            lucro_da_rodada = (double) ((porcentagem/100)* acoes[choice].lucro);
            custo_da_rodada = (double) ((porcentagem/100)* acoes[choice].preco);
            lucroAtual = inv->totalLucro + lucro_da_rodada;
            dinheiro = dinheiro - custo_da_rodada;

            // Atualiza na struct inv
            inv->dinheiro = dinheiro;
            inv->totalLucro = lucroAtual;
            inv->qtdInvestimentos= cont;
            inv->investimentos[cont-1].porcentagem = porcentagem;
            inv->investimentos[cont-1].lucro = lucro_da_rodada;
            inv->investimentos[cont-1].d_investido = custo_da_rodada;
            inv->investimentos[cont-1].acao->lucro = acoes[choice].lucro;
            inv->investimentos[cont-1].acao->preco = acoes[choice].preco;
            printf("\n----Compra realizada----\n");
            printf("\nDinheiro Atual:%lf\n", inv->dinheiro);
            printf("Lucro Atual:%lf\n", inv->totalLucro);
            printf("Vezes investidas:%d\n", inv->qtdInvestimentos);
            printf("\n--------------------------\n");
            printf("\nCarteira de Acoes:\n");
            printf("\n--------------------------\n");

            break;
        
        default:
            printf("\nInvestimento cancelado\n");
            break;

        }
    
    
   

    //Para exibir o valor de cada compra eh preciso converter os tipos nas structs que estão incompatíveis
    for (i = 0; i < cont; i ++){
        printf("\n Custo:%lf Lucro %lf\n",inv->investimentos[i].d_investido,inv->investimentos[i].lucro);
        }
    
    

return 0;
}


void ranking(double pontuacao, char* nome){

    FILE* record;

    record = fopen("records.txt", "w");

    //escrevendo a pontuação e o nome no arquivo

    fprintf(record,"%lf ", pontuacao);
    fprintf(record,"%s", nome);

    fclose(record);
    }