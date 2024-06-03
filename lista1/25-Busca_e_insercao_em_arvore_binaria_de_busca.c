#include <stdio.h>
#include <stdlib.h>

struct noArvore
{
	int info;
	struct noArvore *esq, *dir;
};
typedef struct noArvore *PtrArvore;

// Faz busca na arvore
// Retorna o noh buscado
// Retorna NULL se nao encontrar
PtrArvore buscaArvore(PtrArvore a, int valor)
{
	if (a == NULL)
		return NULL;
	if (a->info == valor)
		return a;
	if (valor < a->info)
		return buscaArvore(a->esq, valor);
	else
		return buscaArvore(a->dir, valor);
}

// Insere no na arvore de busca
// Nao insere no repetido
// Retorna 0 en caso de sucesso
// Retorna -1 em caso o no ja exista na arvore
// Retorna -2 em caso de falha na alocação de memoria
int insereArvore(PtrArvore *a, int valor)
{
	if (*a == NULL)
	{ // Insere valor na posicao
		*a = malloc(sizeof(struct noArvore));
		if (*a == NULL)
			return -2; // Erro na alocacao de memoria
		(*a)->info = valor;
		(*a)->esq = (*a)->dir = NULL;
		return 0; // Insercao ocorrida com sucesso
	}
	if ((*a)->info == valor) // Chave ja existe na arvore
		return -1;
	if (valor < (*a)->info)
		return insereArvore(&((*a)->esq), valor);
	else
		return insereArvore(&((*a)->dir), valor);
}

#define ESPACOS 5
void desenhaArvore(PtrArvore a, int nivel)
{
	int i;
	if (a == NULL)
		return;
	if (a->dir != NULL)
	{
		desenhaArvore(a->dir, nivel + 1);
		for (i = 0; i < ESPACOS * nivel; i++)
			printf(" ");
		printf(" /\n");
	}
	for (i = 0; i < ESPACOS * nivel; i++)
		printf(" ");
	printf("%d\n", a->info);
	if (a->esq != NULL)
	{
		for (i = 0; i < ESPACOS * nivel; i++)
			printf(" ");
		printf(" \\\n");
		desenhaArvore(a->esq, nivel + 1);
	}
}

int main(void)
{
	int valor[12] = {4, 8, 2, 5, 9, 0, 4, 3, 1, 9, 7, 6};
	int i, v, r;
	PtrArvore a = NULL, p;
	for (i = 0; i < 12; i++)
	{
		r = insereArvore(&a, valor[i]);
		switch (r)
		{
		case 0:
			printf("Valor %d inserido com sucesso.\n", valor[i]);
			break;
		case -1:
			printf("Valor %d jah existe na arvore.\n", valor[i]);
			break;
		case -2:
			printf("Erro na alocacao de memoria.\n");
		}
	}
	desenhaArvore(a, 0);
	printf("\nValor a ser procurado: ");
	scanf("%d", &v);
	p = buscaArvore(a, v);
	if (p == NULL)
		printf("Valor nao encontrado.\n");
	else
		printf("Valor no noh encontrado: %d.\n", p->info);
	return 0;
}
