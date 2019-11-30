#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int codigo;
    char nome[30];
    float val_compra;
    float preco;
    int quant;
} Sproduto; // estrutura definida para organizar produtos em estoque

typedef struct{
    int cod_prod;
    int cod_venda;
    int quant;
    float val_venda;
} Svenda; // estrutura para trabalhar com operações de caixa, vendas, etc.


// DECLARAÇÃO DAS FUNCÕES USADAS:
void menu_principal();
FILE *abre_arquivo(); //ABRE UM ARQUIVO SOLICITADO
int verifica_abertura();
FILE *proxima_linha(); // PULA O PONTEIRO DO ARQUIVO PARA A PROXIMA LINHA
Sproduto *le_produto(); // LÊ UM PRODUTO DO TECLADO
void cadastra_produto(); // CADASTRA UM PRODUTO OU ENCAMINHA PARA ALTERA_PRODUTO E GRAVA NO ARQUIVO
Sproduto *altera_produto(); // ALTERA/DELETA UM PRODUTO NO VETOR DE PRODUTOS

// FUNÇÃO MAIN
int main(){
    menu_principal();
}

void menu_principal(){ // MOSTRA O MENU PRINCIPAL DO PROGRAMA
    int op;
    while(1){
        printf("\n###SISTEMA DE GERENCIAMENTO DE SUPERMERCADO###\n");
        printf("\n1) Cadastrar/alterar/excluir produtos no estoque");
        printf("\n2) Buscar produto no estoque"); //um ou todos os produtos do estoque
        printf("\n3) Realizar venda");
        printf("\n4) Controle de estoque"); //mostra produtos que tem/não tem no estoque
        printf("\n5) Relatorio");
        printf("\nOpcao: ");
        scanf("%i", &op);
        switch (op) {
            case 1:

        }

    }
}

FILE *abre_arquivo(char *a, char *b){
    FILE *p;
    p = fopen(a,b);
    if(verifica_abertura(p) == 0) {
        printf("Arquivo nao foi aberto. Tente novamente!\n");
        return NULL;
    }
    else return p;
}

int verifica_abertura(FILE *p){
    if(!p) return 0;
    else return 1;
}

FILE *proxima_linha(FILE *p){
    char c;
    c = fgetc(p);
    while(c != '\n'){
        c = fgetc(p);
        if(c==EOF){
            rewind(p);
            break;
        }
    }
    return p;
}

int numero_de_linhas(FILE *p){
    char c;
    int n=0;
    while(c!=EOF){
        if(c=='\n') n++;
    }
    return n;
}

Sproduto *le_produto(int aux){
    Sproduto *aux = (Sproduto*) malloc(sizeof(Sproduto));
    aux->codigo = aux;
    printf("\nDigite os novos valos do produto %i:", aux);
    printf("\nNome: ");
    scanf("%s\n", aux->nome);
    printf("Valor da compra: ");
    scanf("%f", &(produto->val_compra));
    printf("Valor da venda: ");
    scanf("%f", &(produto->preco));
    printf("Quantidade: ");
    scanf("%i", &(produto->quant));
    return aux;
}

void cadastra_produto(){
    FILE *p = abre_arquivo("produtos.txt", "a+");
    int aux, n=0, i;
    printf("Digite o ID do produto: ");
    scanf("%i", &aux);
    n=numero_de_linhas(p);
    if(n>0){
        Sproduto *produto = (Sproduto*) malloc(sizeof(Sproduto)*n);
        for(i=0;i<n;i++){ // CARREGA OS PRODUTOS EM UM VETOR DE PRODUTOS
            fscanf(p, "%i : %s : %f : %f : %i\n", &produto[i].codigo, produto[i].nome, &produto[i].val_compra, &produto[i].preco, &produto[i].quant);
        }
        for(i=0;i<n;i++){
            if(aux==produto[i].codigo){
                altera_produto(produto, aux);
            }
        }
    }

}

Sproduto *altera_produto(Sproduto *produto, int n, int aux){
    int op, i;
    printf("\nEsse ID de produto ja esta cadastrado no sistema. O que deseja fazer?");
    printf("\n1) Alterar\n2) Excluir\nOpcao: ");
    scanf("%i", &op);
    if(op==1){
        Sproduto *entrada = le_produto(aux);
        Sproduto *saida = (Sproduto*) malloc(sizeof(Sproduto)*n);
        for(i=0;i<n;i++){
            if(produto[i].codigo != aux){
                saida[i].codigo = produto[i].codigo;
                strcpy(saida[i].nome, produto[i].nome);
                saida[i].val_compra = produto[i].val_compra;
                saida[i].preco = produto[i].preco;
                saida[i].quant = produto[i].quant;
            }
            else{
                saida[i].codigo = aux;
                strcpy(saida[i].nome, entrada->nome);
                saida[i].val_compra = entrada->val_compra;
                saida[i].preco = entrada->preco;
                saida[i].quant = entrada->quant;
            }
        }
    }

}
