#include <stdio.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

    //criando a estrutura da sala
typedef struct Sala{
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

    //Protótipos das funções para manipulação das salas
Sala* criarSala(char *nome);
void conectarSalas(Sala *origem, Sala *esq, Sala *dir);
void explorarSalas(Sala *atual);    

int main() {

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

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
        // 3. Iniciar o jogo
    printf("Bem-vindo ao Simulador de Exploracao!\n");
    explorarSalas(hall);
        // Limpeza simples (Opcional para este exemplo pequeno)
    free(hall); free(biblio); free(cozinha); 
    free(sotao); free(jardim); free(dispensa); free(porao);

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

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
void explorarSalas(Sala *atual) {
    char escolha;

    while (atual != NULL) {
        printf("\n---------------------------------");
        printf("\nVoce esta agora no(a): **%s**", atual->nome);
        printf("\nCaminhos disponiveis:");
        
        if (atual->esquerda) printf("\n[e] Ir para a esquerda: %s", atual->esquerda->nome);
        if (atual->direita)  printf("\n[d] Ir para a direita: %s", atual->direita->nome);
        printf("\n[s] Sair da exploracao");
        printf("\nEscolha: ");
        
        scanf(" %c", &escolha); // Espaço antes de %c limpa o buffer do teclado

        if (escolha == 's') {
            printf("Saindo da mansão... Ate a proxima!\n");
            break;
        } else if (escolha == 'e' && atual->esquerda) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita) {
            atual = atual->direita;
        } else {
            printf("\n[!] Caminho invalido ou sem saida!");
        }
    }
}


