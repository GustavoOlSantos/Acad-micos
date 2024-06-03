/*
====> Desenvolvedores:
 • Gustavo Oliveira Ferreira Dos Santos
 • Rayra de Medeiros Bastos
 • Vivian Da Silva Mota
 • Thiago Martins Rodrigues da Silva
-------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

struct No
{
    int num;               //=> Dado Armazenado
    struct No *prox, *ant; //=> Endereço do Próximo/Anterior Item
};
typedef struct No *no;

//=> Menu do Usuário
int menu()
{
    int operacao = 0;

    printf("+------------------------------------------------------------+\n");
    printf("|                            MENU                            |\n");
    printf("+------------------------------------------------------------+\n");
    printf("| [1] Adicionar ao Início da Lista                          |\n");
    printf("| [2] Adicionar ao Final da Lista                            |\n");
    printf("| [3] Adicionar em um ponto específico da Lista             |\n");
    printf("| [4] Listar todos os elementos da lista                     |\n");
    printf("| [5] Listar um elemento específico da lista                |\n");
    printf("| [6] Excluir do início da lista                            |\n");
    printf("| [7] Excluir do final da lista                              |\n");
    printf("| [8] Excluir de um ponto específico da lista               |\n");
    printf("| [9] Liberar os elementos e mostrar a lista vazia           |\n");
    printf("| [0] Terminar                                               |\n");
    printf("+------------------------------------------------------------+\n\n");

    printf("Sua Resposta: ");
    scanf("%d", &operacao);

    return operacao;
}

void addIniLista(no *lista, int valor)
{

    no p, inicio, ultimo;
    p = malloc(sizeof(struct No)); //=> Tenta alocar qum novo espaço para a estrutura

    if (p == NULL)
    {
        printf("Memoria insuficiente.\n");
        system("PAUSE");
        exit(0);
    }

    p->num = valor; //=> Insere o valor no novo nó

    if (*lista == NULL)
    {                //=> Se a lista está vazia
        p->ant = p;  //=> Define o nó Anterior como ele mesmo
        p->prox = p; //=> Define o nó Anterior como ele mesmo
        *lista = p;  //=> Define esse nó como inicio da lista
    }

    else
    {                           //=> Se a lista não está vazia
        ultimo = (*lista)->ant; //=> Busca última posição (anterior ao 1º da lista)
        p->ant = ultimo;        //=> Define último nó como anterior ao novo
        p->prox = *lista;       //=> Define o próximo nó como primeiro da lista
        ultimo->prox = p;       //=> Define o novo nó como sucessor ao antigo último
        (*lista)->ant = p;      //=> Define que o nó novo é antecede o início da lista
        *lista = p;             //=> Define esse nó como inicio da lista
    }
}

void addFimLista(no *lista, int valor)
{

    no p, ultimo;
    p = malloc(sizeof(struct No)); //=> Tenta alocar um novo espaço para a estrutura

    if (p == NULL)
    {
        printf("Memoria insuficiente.\n");
        system("PAUSE");
        exit(0);
    }

    p->num = valor; //=> Insere o valor no novo nó

    if (*lista == NULL)
    {                //=> Se a lista está vazia
        p->ant = p;  //=> Define o nó Anterior como ele mesmo
        p->prox = p; //=> Define o nó Anterior como ele mesmo
        *lista = p;  //=> Define esse nó como inicio da lista
    }

    else
    {                           //=> Se a lista não está vazia
        ultimo = (*lista)->ant; //=> Busca última posição (anterior ao 1º da lista)
        p->ant = ultimo;        //=> Define último nó como anterior ao novo
        p->prox = *lista;       //=> Define o próximo nó como primeiro da lista
        ultimo->prox = p;       //=> Define o novo nó como sucessor ao antigo último
        (*lista)->ant = p;      //=> Define que o nó novo antecede o início da lista
    }
}

void addPosLista(no *lista, int valor, int pos)
{
    no p, alvo, antAlvo;
    int counter = 0;

    p = malloc(sizeof(struct No)); //=> Tenta alocar qum novo espaço para a estrutura

    if (p == NULL)
    {
        printf("Memoria insuficiente.\n");
        system("PAUSE");
        exit(0);
    }

    p->num = valor; //=> Insere o valor no novo nó

    if (*lista == NULL)
    {                //=> Se a lista está vazia
        p->ant = p;  //=> Define o nó Anterior como ele mesmo
        p->prox = p; //=> Define o nó Anterior como ele mesmo
        *lista = p;  //=> Define esse nó como inicio da lista
    }

    else
    { //=> Se a lista não está vazia
        alvo = (*lista);

        do
        { //=> Repete até que se chegue ao início da lista novamente
            counter++;

            //=> Caso encontre a posição desejada
            if (counter == pos)
            {

                antAlvo = alvo->ant; //=> Obtém o elemento anterior ao alvo (alvo-1)
                p->ant = antAlvo;    //=> Posiciona o Novo elemento entre o Alvo e o anterior ao alvo
                p->prox = alvo;      //=> Posiciona o Novo elemento entre o Alvo e o anterior ao alvo
                antAlvo->prox = p;   //=> Define o novo nó como o próximo do alvo-1
                alvo->ant = p;       //=> Define o novo nó como anterior ao alvo

                return;
            }
            alvo = alvo->prox; //=> Procura o próximo elemento
        } while (alvo != *lista);

        printf("\nErro: Posição Inválida!\n");
    }
}

void Listar(no lista)
{
    no p;
    int counter = 0;

    //=> Se a lista não estiver vazia
    if (lista != NULL)
    {
        p = lista;
        printf("============> Elementos salvos na lista: \n");

        do
        { //=> Repete até que se chegue ao início da lista novamente
            counter++;
            printf("Elemento %d \n", counter);
            printf("Valor: %d \n\n", p->num);

            p = p->prox; //=> Procura o próximo elemento
        } while (p != lista);
    }

    else
    {
        printf("\n==> A Lista está vazia! <==\n");
    }
    printf("\n");
}

void ListarUm(no lista, int pos)
{
    no p;
    int counter = 0;

    //=> Se a lista não estiver vazia
    if (lista != NULL)
    {
        p = lista;

        do
        { //=> Repete até que se chegue ao início da lista novamente
            counter++;

            if (counter == pos)
            {
                printf("\n\n==> Elemento %d: \n", pos);
                printf("Valor: %d \n\n", p->num);
                return;
            }
            p = p->prox; //=> Procura o próximo elemento
        } while (p != lista);

        printf("\nErro: Elemento não encontrado!\n");
    }
    printf("\n");
}

int delIniLista(no *lista)
{
    no p, ultimo;
    int valor;

    if (*lista == NULL)
    {
        printf("Erro: lista vazia.\n");
        return -1;
    }

    valor = (*lista)->num;   //=> Armazena o valor do primeiro elemento
    p = (*lista);            //=> Define P como inicio da lista
    ultimo = (*lista)->ant;  //=> Obtém o último elemento
    *lista = (*lista)->prox; //=> Altera o início 1da lista pro próximo elemento
    if (p != p->prox)
    {                           //=> Se tem mais de um item na lista
        (*lista)->ant = ultimo; //=> Aponta o último como anterior ao inicio da lista
        ultimo->prox = *lista;  //=> Aponta o início da lista como próximo ao fim da lista
    }

    else
    {                  //=> Se tem somente um item na lista
        *lista = NULL; //=> Define a lista como vazia
    }

    free(p);
    return valor;
}

int delFimLista(no *lista)
{
    no p, ultimo, penultimo;
    int valor;

    if (*lista == NULL)
    {
        printf("Erro: lista vazia.\n");
        return -1;
    }

    p = (*lista);            //=> Define P como inicio da lista
    ultimo = p->ant;         //=> Obtém o último elemento
    penultimo = ultimo->ant; //=> Obtém o penúltimo elemento
    valor = ultimo->num;     //=> Armazena o valor do último elemento

    if (p != p->prox)
    {                             //=> Se tem mais de um item na lista
        p->ant = penultimo;       //=> Aponta o penúltimo como anterior ao inicio da lista
        penultimo->prox = *lista; //=> Aponta o início da lista como próximo do penultmo da lista
    }

    else
    {                  //=> Se tem somente um item na lista
        *lista = NULL; //=> Define a lista como vazia
    }

    free(ultimo);
    return valor;
}

int delPosLista(no *lista, int pos)
{
    no p, antAlvo, posAlvo;
    int valor, counter = 0;

    if (*lista == NULL)
    {
        printf("Erro: lista vazia.\n");
        return -1;
    }

    p = (*lista); //=> Define P como inicio da lista
    if (p != p->prox)
    { //=> Se tem mais de um item na lista

        do
        { //=> Repete até que se chegue ao início da lista novamente
            counter++;

            //=> Caso encontre a posição desejada
            if (counter == pos)
            {
                valor = p->num;    //=> Armazena o valor do elemento alvo
                antAlvo = p->ant;  //=> Obtém o elemento anterior ao alvo (p-1)
                posAlvo = p->prox; //=> Obtém o elemento posterior ao alvo (p+1)

                antAlvo->prox = posAlvo; //=> Define o p+1 como proximo ao p-1
                posAlvo->ant = antAlvo;  //=> Define o p-1 como anterior ao p+1

                free(p); //=> Libera o p
                return valor;
            }
            p = p->prox; //=> Procura o próximo elemento
        } while (p != *lista);

        printf("\nErro: Posição Inválida!\n");
    }

    else
    {                  //=> Se tem somente um item na lista
        *lista = NULL; //=> Define a lista como vazia
    }

    free(p);
    return valor;
}

int liberar(no *lista)
{
    no p;

    if (*lista == NULL)
    {
        printf("Erro: lista já está vazia.\n");
        return 1;
    }

    p = (*lista);
    do
    { //=> Repete até que se chegue ao início da lista novamente
        p = p->prox;
        free(p->ant);

    } while (p != (*lista));
    *lista = NULL;
    return 0;
}

//=> Limpa a tela
int clear()
{
#ifdef _WIN32
    return system("cls");
#else
    return system("clear");
#endif
}

int main()
{

    //==> Declaração de Variáveis
    int op;         //=> Operação escolhida pelo usuário
    int valor;      //=> Valor a ser armazenado ou retornado
    int pos;        //=> Indicador de posição para adição/exclusão/visualização
    int alerta = 0; //=> Key p/ indicar erros

    //=> Inicializações
    no lista = NULL;                 //=> Lista Inicializa vazia
    setlocale(LC_ALL, "Portuguese"); //=> Caracteres especiais

    //=> Controle do Programa Geral
    do
    {
        //=> Controle de Resposta do Menu
        do
        {
            clear();

            if (alerta == 1)
            {
                printf("Erro: Opção Inválida!\n\n");
            }

            op = menu();
            alerta = (op >= 0 && op <= 9) ? 0 : 1;
        } while (alerta != 0);

        switch (op)
        {

        //=> Adicionar ao INÍCIO da Lista
        case 1:
            printf("Qual Valor deseja Adicionar ao inicio da Lista?\n");
            printf("Resposta: ");
            scanf("%d", &valor);

            addIniLista(&lista, valor);
            system("PAUSE");
            break;

        //=> Adicionar valor ao FIM da lista
        case 2:
            printf("Qual Valor deseja Adicionar ao fim da Lista?\n");
            printf("Resposta: ");
            scanf("%d", &valor);

            addFimLista(&lista, valor);
            system("PAUSE");
            break;

        //=> Adicionar valor a um ponto da lista
        case 3:
            printf("Qual Valor deseja Adicionar à lista?\n");
            printf("Resposta: ");
            scanf("%d", &valor);

            printf("\n\nEm qual posição?\n");
            printf("Resposta: ");
            scanf("%d", &pos);

            addPosLista(&lista, valor, pos);
            system("PAUSE");
            break;

        //=> Apresenta a lista completa
        case 4:
            Listar(lista);
            system("PAUSE");
            break;

        //=> Apresentar um elemento específico da lista
        case 5:
            printf("Qual elemento deseja visualzar?\n");
            printf("Resposta: ");
            scanf("%d", &pos);

            ListarUm(lista, pos);
            system("PAUSE");
            break;

        //=> Apaga o primeiro elemento da lista
        case 6:
            valor = delIniLista(&lista);
            printf("Valor retirado da lista: %d\n\n", valor);
            system("PAUSE");
            break;

        //=> Apaga o último elemento da lista
        case 7:
            valor = delFimLista(&lista);
            printf("Valor retirado da lista: %d\n\n", valor);
            system("PAUSE");
            break;

        case 8:
            printf("Deseja remover de qual posição?\n");
            printf("Resposta: ");
            scanf("%d", &pos);

            delPosLista(&lista, pos);
            system("PAUSE");
            break;

        case 9:
            printf("Liberando a lista.");
            sleep(1);
            printf("..\n");

            int flag = liberar(&lista);
            if (flag == 0)
            {
                Listar(lista);
            }

            system("PAUSE");
            break;

        case 0:
            clear();
            printf("Encerrando Programa...\n");
            system("PAUSE");
            break;
        }
    } while (op != 0);

    return 0;
}