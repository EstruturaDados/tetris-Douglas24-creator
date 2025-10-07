#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5 // tamanho fixo da fila

// estrututa de uma peça
typedef struct {
    char nome;
    int id; // identificador
} Peca;

// estrtutura da fila circular
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// inicializando fila vazia
void iniciarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// verificar se fila está cheia
int filaCheia(Fila *f) {
    return (f->total == MAX);
}

// verificar se fila está vazia
int filaVazia(Fila *f) {
    return (f->total == 0);
}

// Inserir peça na fila
void inserir(Fila *f, Peca nova) {
    if (filaCheia(f)) {
        printf("Fila cheia! Não é possível inserir nova peça.\n");
        return;
    }

    f->itens[f->fim] = nova;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

// Remover peça
void remover(Fila *f, Peca *retirada) {
    if (filaVazia(f)) {
        printf("Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }

    *retirada = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

// Exibir fila
void exibirFila(Fila *f) {
    printf("\n=== FILA DE PEÇAS ===\n");

    if (filaVazia(f)) {
        printf("(Vazia)\n\n");
        return;
    }

    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n\n");
}

// Gera peça automaticamente
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4]; // seleciona tipo aleatório
    nova.id = id;
    return nova;
}

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função principal
int main() {
    Fila fila;
    iniciarFila(&fila);

    srand(time(NULL)); // inicializa gerador de números aleatórios
    int opcao;
    int contadorID = 0;

    // iniciar fila com 5 peças
    for (int i = 0; i < MAX; i++) {
        inserir(&fila, gerarPeca(contadorID++));
    }

    do {
        system("clear || cls"); // limpa a tela (funciona no Linux e Windows)
        exibirFila(&fila);

        printf("=== MENU TETRIS STACK ===\n");
        printf("1 - Remover peça\n");
        printf("2 - Inserir nova peça\n");
        printf("0 - Sair\n");
        printf("Digite uma opção: ");
        scanf("%d", &opcao);
        limparBuffer(); // limpa o buffer após scanf

        switch (opcao) {
            case 1: {
                Peca retirada;
                remover(&fila, &retirada);
                printf("\nPeça [%c %d] removida!\n", retirada.nome, retirada.id);
                break;
            }
            case 2:
                inserir(&fila, gerarPeca(contadorID++));
                printf("\nNova peça inserida!\n");
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }
        // fila aparecendo após menu
        if (opcao != 0) {
            exibirFila(&fila);
            printf("\nPressione Enter para voltar ao menu...");
            getchar(); // espera o usuário apertar Enter
        }

    } while (opcao != 0);

    return 0;
}