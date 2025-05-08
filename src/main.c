#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/estoque.h"

void cadastrarProduto() {
    Produto p;
    FILE *arquivo = fopen("data/produtos.dat", "ab");

    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Código do produto: ");
    scanf("%d", &p.codigo);
    getchar();  // limpar o buffer

    printf("Nome do produto: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = 0;

    printf("Descrição: ");
    fgets(p.descricao, sizeof(p.descricao), stdin);
    p.descricao[strcspn(p.descricao, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &p.quantidade);

    printf("Preço: ");
    scanf("%f", &p.preco);

    fwrite(&p, sizeof(Produto), 1, arquivo);
    fclose(arquivo);

    printf("\nProduto cadastrado com sucesso!\n");
}

void exibirProduto(Produto p) {
    printf("\nCódigo: %d\n", p.codigo);
    printf("Nome: %s\n", p.nome);
    printf("Descrição: %s\n", p.descricao);
    printf("Quantidade: %d\n", p.quantidade);
    printf("Preço: R$ %.2f\n", p.preco);
}
void listarProdutos() {
    FILE *arquivo = fopen("data/produtos.dat", "rb");
    Produto p;

    if (!arquivo) {
        printf("Nenhum produto encontrado.\n");
        return;
    }

    printf("\n--- Lista de Produtos ---\n");

    while (fread(&p, sizeof(Produto), 1, arquivo)) {
        exibirProduto(p);
    }

    fclose(arquivo);
}
void alterarEstoque(int tipo) {
    int codigo, quantidade, encontrado = 0;
    Produto p;

    FILE *arquivo = fopen("data/produtos.dat", "rb+");

    if (!arquivo) {
        printf("Arquivo não encontrado.\n");
        return;
    }

    printf("Código do produto: ");
    scanf("%d", &codigo);

    while (fread(&p, sizeof(Produto), 1, arquivo)) {
        if (p.codigo == codigo) {
            encontrado = 1;
            printf("\nProduto encontrado:\n");
            exibirProduto(p);

            printf("\nQuantidade para %s: ", tipo == 1 ? "entrada" : "saída");
            scanf("%d", &quantidade);

            if (tipo == 1) {
                p.quantidade += quantidade;
            } else {
                if (quantidade > p.quantidade) {
                    printf("Erro: Estoque insuficiente.\n");
                    fclose(arquivo);
                    return;
                }
                p.quantidade -= quantidade;
            }

            fseek(arquivo, -sizeof(Produto), SEEK_CUR);
            fwrite(&p, sizeof(Produto), 1, arquivo);
            printf("\nEstoque atualizado com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Produto não encontrado.\n");
    }

    fclose(arquivo);
}
void gerarRelatorio() {
    FILE *entrada = fopen("data/produtos.dat", "rb");
    FILE *saida = fopen("data/relatorio.txt", "w");
    Produto p;

    if (!entrada || !saida) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    fprintf(saida, "Relatório de Estoque\n\n");
    fprintf(saida, "%-10s %-20s %-10s %-10s %-12s\n", "Código", "Nome", "Qtd", "Preço", "Total");

    while (fread(&p, sizeof(Produto), 1, entrada)) {
        float total = p.quantidade * p.preco;
        fprintf(saida, "%-10d %-20s %-10d R$ %-8.2f R$ %-8.2f\n", p.codigo, p.nome, p.quantidade, p.preco, total);
    }

    fclose(entrada);
    fclose(saida);

    printf("\nRelatório gerado com sucesso: data/relatorio.txt\n");
}


int main() {
    int opcao;

    do {
        printf("\n1 - Cadastrar Produto\n2 - Listar Produtos\n3 - Entrada de Produto\n4 - Saída de Produto\n5 - Gerar Relatório\n0 - Sair\nOpção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                alterarEstoque(1);
                break;
            case 4:
                alterarEstoque(2);
                break;  
            case 5:
                gerarRelatorio();
                break;
                     
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
