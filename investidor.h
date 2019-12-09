#ifndef _INVESTIDOR_
#define _INVESTIDOR_

typedef struct acao
{
    int lucro;
    int preco;
} Acao;


typedef struct _investimento_
{
    Acao *acao;
    double porcentagem;
    double lucro;
    double d_investido;

}Investimento;


typedef struct _investidor_
{
    char name[300];
    double dinheiro;
    double totalLucro;
    int qtdInvestimentos;
    Investimento *investimentos;

}Investidor;

Investidor *novoInvestidor(int dinheiro);
int destroyInvestidor(Investidor *inv);

void printAcao(Acao *ac, int i);
int compra(Acao*, Investidor*, int*,  int qntdAcoes);

#endif // INVESTIDOR_H_INCLUDED
