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
void grava_arquivo();
void cadastra_produto(); // CADASTRA UM PRODUTO OU ENCAMINHA PARA ALTERA_PRODUTO E GRAVA NO ARQUIVO
Sproduto *altera_produto(); // ALTERA/DELETA UM PRODUTO NO VETOR DE PRODUTOS

// FUNÇÃO MAIN
int main(){
    menu_principal();
}

void menu_principal(){ // MOSTRA O MENU PRINCIPAL DO PROGRAMA
    int op;
    while(1){
        system("cls");
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
            cadastra_produto();
            printf("\nDigite enter para continuar...\n");
            getchar(); //limpar o buffer
            getchar();
        }

    }
}

FILE *abre_arquivo(char *a, char *b){
    FILE *p;
    p = fopen(a,b);
    return p;
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

Sproduto *le_produto(int n){
    Sproduto *aux = (Sproduto*) malloc(sizeof(Sproduto));
    aux->codigo = n;
    printf("Nome: ");
    scanf("%s", aux->nome);
    printf("Valor da compra: ");
    getchar();
    scanf("%f", &(aux->val_compra));
    printf("Valor da venda: ");
    getchar();
    scanf("%f", &(aux->preco));
    printf("Quantidade: ");
    getchar();
    scanf("%i", &(aux->quant));
    return aux;
}

void grava_arquivo(FILE *p, Sproduto *prod, int n){
    int i;
    for(i=0;i<n;i++){
        fprintf(p, "%i : %s : %.2f : %.2f : %i\n", prod[i].codigo, prod[i].nome, prod[i].val_compra, prod[i].preco, prod[i].quant);
        printf("Produto gravado:\n%i : %s : %.2f : %.2f : %i\n", prod[i].codigo, prod[i].nome, prod[i].val_compra, prod[i].preco, prod[i].quant);
    }
    printf("\nArquivos gravados com sucesso!\n");
}

void cadastra_produto(){
    int aux, n=1, i, verifica = 0;
    FILE *p = abre_arquivo("produtos.txt", "r");

    if(verifica_abertura(p)==0){
        Sproduto *produto;
        produto = (Sproduto*) malloc(sizeof(Sproduto));
        FILE *p = abre_arquivo("produtos.txt", "w");
        printf("Cadastre o primeiro produto: \n");
        printf("\nDigite o codigo do produto: ");
        scanf("%i", &aux);
        produto = le_produto(aux);
        grava_arquivo(p,produto,1);
        fclose(p);
        free(produto);
    }
    else{
        Sproduto *produto = NULL;
        while(!feof(p)){ // CARREGA OS PRODUTOS EM UM VETOR DE ESTRUTURA ALOCADO DINAMICAMENTE
            produto = (Sproduto*) realloc(produto, sizeof(Sproduto)*n);
            fscanf(p,"%i : %s : %f : %f : %i\n", &(produto[n-1].codigo), produto[n-1].nome, &(produto[n-1].val_compra), &(produto[n-1].preco), &(produto[n-1].quant));
            c = fgetc(p);
            if(c == EOF) break;
            else fseek(p, ftell(p)-1, SEEK_SET);
            n++;
        }
        fclose(p);

        FILE *p = abre_arquivo("produtos.txt", "w");
        printf("Digite o codigo do produto: ");
        scanf("%i", &aux);
        for(i=0;i<n;i++){
            if(produto[i].codigo == aux){
                produto = altera_produto(produto, &n, aux);
                grava_arquivo(p,produto,n);
                fclose(p);
                free(produto);
                verifica++;
                break;
            }
        }
        if(verifica == 0){
            n++;
            produto = (Sproduto*) realloc(produto, sizeof(Sproduto)*n);
            produto[n-1].codigo = aux;
            printf("Nome: ");
            scanf("%s", produto[n-1].nome);
            printf("Valor da compra: ");
            getchar();
            scanf("%f", &(produto[n-1].val_compra));
            printf("Valor da venda: ");
            getchar();
            scanf("%f", &(produto[n-1].preco));
            printf("Quantidade: ");
            getchar();
            scanf("%i", &(produto[n-1].quant));
            grava_arquivo(p,produto,n);
            fclose(p);
            free(produto);
        }

    }

}

Sproduto *altera_produto(Sproduto *produto, int *n, int aux){ // ALTERA E EXCLUI
    int op, i, a = *n, s=0;
    printf("\nEsse ID de produto ja esta cadastrado no sistema. O que deseja fazer?");
    printf("\n1) Alterar\n2) Excluir\nOpcao: ");
    scanf("%i", &op);
    if(op==1){
        Sproduto *entrada = le_produto(aux);
        Sproduto *saida = (Sproduto*) malloc(sizeof(Sproduto)*a);
        for(i=0;i<a;i++){
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
        return saida;
    }
    else if(op==2){
        a--;
        Sproduto *saida = (Sproduto*) malloc(sizeof(Sproduto)*a);
        for(i=0;i<a+1;i++){
            if(produto[i].codigo != aux){
                saida[s].codigo = produto[i].codigo;
                strcpy(saida[s].nome, produto[i].nome);
                saida[s].val_compra = produto[i].val_compra;
                saida[s].preco = produto[i].preco;
                saida[s].quant = produto[i].quant;
                s++;
            }

        }
        *n = a;
        return saida;
    }

}





/**/
