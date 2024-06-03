#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO_PALAVRA 15

struct noArvore
{
	char *palavra;
	int contador;
	struct noArvore *esq, *dir;
};
typedef struct noArvore *Arvore;

// Função para inserir ou atualizar um nó na árvore
int inserir(Arvore *raiz, char *palavra)
{
	int comp;

	if (*raiz == NULL)
	{
		*raiz = malloc(sizeof(struct noArvore));

		if (*raiz == NULL)
		{
			return -1; // Falha na alocacao de memoria
		}

		(*raiz)->palavra = strdup(palavra); // Aloca e copia a palavra
		(*raiz)->contador = 1;
		(*raiz)->esq = NULL;
		(*raiz)->dir = NULL;
		return 0;
	}

	comp = strcmp(palavra, (*raiz)->palavra); // Compara as palavras

	if (comp == 0)
	{ // Se as palavras forem iguais, atualiza o contador
		(*raiz)->contador++;
		return 0;
	}
	else if (comp < 0)
	{ // Se a palavra atual for menor na ordem alfabética, insere na esquerda
		return inserir(&((*raiz)->esq), palavra);
	}
	else
	{ // Se a palavra atual for maior na ordem alfabética, insere na direita
		return inserir(&((*raiz)->dir), palavra);
	}
}

// Função para imprimir a árvore em ordem alfabética
void imprimirArvore(Arvore raiz)
{
	if (raiz != NULL)
	{
		imprimirArvore(raiz->esq);
		printf("%s (%d)\n", raiz->palavra, raiz->contador);
		imprimirArvore(raiz->dir);
	}
}

// Função para liberar a memória da árvore
void liberarArvore(Arvore raiz)
{
	if (raiz != NULL)
	{
		liberarArvore(raiz->esq);
		liberarArvore(raiz->dir);
		free(raiz->palavra);
		free(raiz);
	}
}

void processaPalavras(char *str[])
{
	Arvore a = NULL;
	int cont, result;

	printf("Inserindo Palavras na Arvore...\n\n");
	for (cont = 0; strcmp(str[cont], "") != 0; cont++)
	{
		printf("%s\t", str[cont]);
		if (cont % 6 == 0 && cont != 0)
		{
			printf("\n");
		}

		result = inserir(&a, str[cont]);
		switch (result)
		{

		default:
			break;

		case -1:
			printf("Erro na alocacao de memoria.\n");
			system("PAUSE");
			exit(1);
			break;
		}
	}

	printf("\n\n===> Exibindo Palavras em Ordem Alfabética e suas repetições:\n");
	imprimirArvore(a);
	system("PAUSE");

	// Libera a memória da árvore
	// liberarArvore(a);
}

int main(void)
{
	//===> Declarações de Variáveis
	char *palavra[] = {"carro", "navio", "carro", "aviao", "carro", "camelo",
					   "carro", "motocicleta", "carro", "navio", "aviao",
					   "carro", "navio", ""};

	//===> Inicializações
	setlocale(LC_ALL, "Portuguese");

	//===> Processamento das palavras em Árvore Binária
	processaPalavras(palavra);
	return 0;
}
