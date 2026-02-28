#include <stdio.h>
#include <string.h>
#include <stdlib.h>

    // Desafio Detective Quest
    // Tema 4 - Árvores e Tabela Hash
const int SIZE = 10; // Tamanho da tabela hash para suspeitos

    //criando a estrutura da sala
typedef struct Sala{
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

typedef struct Pista {
    char texto[100];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;
    // Estrutura para a tabela hash de suspeitos (Nível Mestre)
typedef struct Suspeito {
    char nome[50];
    Pista* pistasAssociadas; // Lista de pistas associadas ao suspeito
    struct Suspeito* proximo; // Para tratar colisões na tabela hash
} Suspeito;
    // Estrutura para a lista encadeada de pistas (em caso de colisão na tabela hash)
typedef struct NoPista {
    char texto[100];
    struct NoPista* proximo;
} NoPista;

    //Protótipos das funções para manipulação das salas
Sala* criarSala(char *nome);
void conectarSalas(Sala *origem, Sala *esq, Sala *dir);
void explorarSalas(Sala *atual, Pista **pistas);  
void inserirPistas(Pista **raiz, char *texto);
void listarPistas(Pista *raiz);  
    //Protótipos das funções para manipulação da tabela hash de suspeitos
void inicializarHash(Suspeito* tabela[]);
void inserirSuspeito(Suspeito* tabela[], char *nome);
void associarPistas(Suspeito* tabela[], char *nomeSuspeito, char *textoPista);
void mostrarRelatorio(Suspeito* tabela[]);
int hash(char *str);

int main() {

        // 1. Criando as salas
    Sala *hall = criarSala("Hall de Entrada");
    Sala *biblio = criarSala("Biblioteca");
    Sala *cozinha = criarSala("Cozinha");
    Sala *sotao = criarSala("Sotao");
    Sala *jardim = criarSala("Jardim Secreto");
    Sala *dispensa = criarSala("Dispensa");
    Sala *porao = criarSala("Porao Escuro");
        // 2. Montando a estrutura da árvore (Mapa)
        // Hall -> Esq: Biblioteca | Dir: Cozinha
    conectarSalas(hall, biblio, cozinha);
        // Biblioteca -> Esq: Sotao | Dir: Jardim
    conectarSalas(biblio, sotao, jardim);
        // Cozinha -> Esq: Dispensa | Dir: Porao
    conectarSalas(cozinha, dispensa, porao);
        // 3. Inicializando a árvore de pistas (vazia)
        // Inicializando Pistas e Tabela Hash de Suspeitos
    Pista *minhasPistas = NULL;
    Suspeito* tabelaSuspeitos[SIZE];
    inicializarHash(tabelaSuspeitos);

    // Inserindo suspeitos fixos para o jogo
    inserirSuspeito(tabelaSuspeitos, "Mordomo");
    inserirSuspeito(tabelaSuspeitos, "Cozinheira");
    inserirSuspeito(tabelaSuspeitos, "Jardineiro");
        // 4. Iniciar o jogo
    printf("Bem-vindo ao Simulador de Exploracao!\n");
    explorarSalas(hall, &minhasPistas);
    
    // Exemplo: Relacionar pistas coletadas com suspeitos
    printf("\n--- FASE DE ACUSACAO ---\n");
    associarPistas(tabelaSuspeitos, "Jardineiro", "Pegada Estranha");
    associarPistas(tabelaSuspeitos, "Mordomo", "Manuscrito Antigo");
    associarPistas(tabelaSuspeitos, "Cozinheira", "Chave Enferrujada");
    associarPistas(tabelaSuspeitos, "Mordomo", "Chave Enferrujada"); // Exemplo de suspeito com mais pistas

    mostrarRelatorio(tabelaSuspeitos);

        // Limpeza simples (Opcional para este exemplo pequeno)
    free(hall); free(biblio); free(cozinha); 
    free(sotao); free(jardim); free(dispensa); free(porao);

    return 0;
}

    // Função para criar uma nova sala na memória
Sala* criarSala(char *nome) {
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala) {
        strcpy(novaSala->nome, nome);
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
    }
    return novaSala;
}
    // Função para conectar as salas (definindo os caminhos)
void conectarSalas(Sala *origem, Sala *esq, Sala *dir) {
    if (origem) {
        origem->esquerda = esq;
        origem->direita = dir;
    }
}
    // Função principal de navegação pelas salas da mansão
void explorarSalas(Sala *atual, Pista **topoPistas) {
    char escolha;

    while (atual != NULL) {
        // --- Lógica de Gatilho de Pistas ---
        if (strcmp(atual->nome, "Biblioteca") == 0) {
            inserirPistas(topoPistas, "Manuscrito Antigo");
        } else if (strcmp(atual->nome, "Porao Escuro") == 0) {
            inserirPistas(topoPistas, "Chave Enferrujada");
        } else if (strcmp(atual->nome, "Jardim Secreto") == 0) {
            inserirPistas(topoPistas, "Pegada Estranha");
        }

        printf("\n---------------------------------");
        printf("\nVoce esta em: **%s**", atual->nome);
        printf("\n[e] Esquerda: %s", (atual->esquerda ? atual->esquerda->nome : "Parede"));
        printf("\n[d] Direita: %s", (atual->direita ? atual->direita->nome : "Parede"));
        printf("\n[p] Listar Evidencias (BST)");
        printf("\n[s] Sair");
        printf("\nEscolha: ");
        
        scanf(" %c", &escolha);

        if (escolha == 's') break;
        if (escolha == 'p') {
            printf("\n--- EVIDENCIAS COLETADAS (Ordem Alfabetica) ---\n");
            if (*topoPistas == NULL) printf("Nenhuma pista encontrada.\n");
            else listarPistas(*topoPistas);
            continue;
        }

        if (escolha == 'e' && atual->esquerda) atual = atual->esquerda;
        else if (escolha == 'd' && atual->direita) atual = atual->direita;
        else printf("\n[!] Caminho sem saida!");
    }
}

void inserirPistas(Pista **raiz, char *texto) {
    if (*raiz == NULL) {
        *raiz = (Pista*)malloc(sizeof(Pista));
        if (*raiz) {
            strcpy((*raiz)->texto, texto);
            (*raiz)->esquerda = NULL;
            (*raiz)->direita = NULL;
        }
    } else {
        if (strcmp(texto, (*raiz)->texto) < 0) {
            inserirPistas(&(*raiz)->esquerda, texto);
        } else if (strcmp(texto, (*raiz)->texto) > 0) {
            inserirPistas(&(*raiz)->direita, texto);
        }
    }
}

void listarPistas(Pista *raiz) {
    if (raiz != NULL) {
        listarPistas(raiz->esquerda);
        printf("- %s\n", raiz->texto);
        listarPistas(raiz->direita);
    }
}

void inicializarHash(Suspeito* tabela[]) {
    for (int i = 0; i < SIZE; i++) {
        tabela[i] = NULL;
    }
}

void inserirSuspeito(Suspeito* tabela[], char *nome) {
    int index = hash(nome);
    Suspeito* novoSuspeito = (Suspeito*)malloc(sizeof(Suspeito));
    if (novoSuspeito) {
        strcpy(novoSuspeito->nome, nome);
        novoSuspeito->pistasAssociadas = NULL;
        novoSuspeito->proximo = tabela[index];
        tabela[index] = novoSuspeito;
    }
}

void associarPistas(Suspeito* tabela[], char *nomeSuspeito, char *textoPista) {
    int index = hash(nomeSuspeito);
    Suspeito* atual = tabela[index];
    while (atual) {
        if (strcmp(atual->nome, nomeSuspeito) == 0) {
            NoPista* novaPista = (NoPista*)malloc(sizeof(NoPista));
            if (novaPista) {
                strcpy(novaPista->texto, textoPista);
                novaPista->proximo = atual->pistasAssociadas;
                atual->pistasAssociadas = novaPista;
            }
            return;
        }
        atual = atual->proximo;
    }
}

void mostrarRelatorio(Suspeito* tabela[]) {
    printf("\n--- RELATORIO DE SUSPEITOS E PISTAS ---\n");
    for (int i = 0; i < SIZE; i++) {
        Suspeito* atual = tabela[i];
        while (atual) {
            printf("Suspeito: %s\n", atual->nome);
            NoPista* pistaAtual = atual->pistasAssociadas;
            if (!pistaAtual) {
                printf("  Nenhuma pista associada.\n");
            } else {
                printf("  Pistas:\n");
                while (pistaAtual) {
                    printf("   - %s\n", pistaAtual->texto);
                    pistaAtual = pistaAtual->proximo;
                }
            }
            atual = atual->proximo;
        }
    }
}

int hash(char *str) {
    int hashValue = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        hashValue += str[i];
    }
    return hashValue % SIZE;
}

