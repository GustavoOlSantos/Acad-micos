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
#include <string.h>
#include <conio.h>
#include <locale.h>

#define TAMANHO_PILHA 5

typedef struct
{
	int topo;
	int manobras[6];
	char *placa[6];
} PilhaEstacionada;

typedef struct
{
	char topo;
	int manobras[6];
	char *placas[6];
} PilhaRetirada;

/* Expressão de Teste Original
E-ABC1234
E-DEF5678
E-GHI9012
S-DEF5678
E-JKL3456 */

//=> Protótipos das Funções
void empilhaEstacionamento(PilhaEstacionada *pilha, char placa[8], int manobras);
int desempilhaEstacionamento(PilhaEstacionada *entradas, PilhaRetirada *saida, char placa[8]);
void empilhaRetirada(PilhaRetirada *pilha, char placa[8], int manobras);
int desempilhaRetirada(PilhaEstacionada *entrada, PilhaRetirada *saida);
void imprimePilha(PilhaEstacionada *entrada, PilhaRetirada *saida);
void Pilha(PilhaEstacionada *estacionamento);
int placaExiste(PilhaEstacionada *pilha, char placa[8]);

void empilhaEstacionamento(PilhaEstacionada *pilha, char placa[8], int manobras)
{
	if (pilha->topo == TAMANHO_PILHA - 1)
	{
		printf("Erro: Estacionamento Lotado.\n");
		exit(0);
	}

	// Verifica se a placa já está na pilha
	if (placaExiste(pilha, placa))
	{
		printf("\n\nErro: Placa %s já está no estacionamento.\n\n", placa);
		return;
	}

	//=> Incrementa o topo e salva a placa
	pilha->topo++;
	pilha->manobras[pilha->topo] = manobras == -1 ? 0 : manobras;

	//=> Aloca memória para a placa e a salva
	pilha->placa[pilha->topo] = strdup(placa);

	if (manobras == -1)
	{
		printf("===> Veículo Estacionado:\n");
		printf("Placa: %s\n", pilha->placa[pilha->topo]);
		printf("Manobras: %d\n", pilha->manobras[pilha->topo]);
	}
}

int desempilhaEstacionamento(PilhaEstacionada *entrada, PilhaRetirada *saida, char placa[8])
{
	if (entrada->topo == -1)
	{
		printf("Erro: Estacionamento Vazio.\n");
		return -1;
	}

	//=> Enquanto a placa for diferente, salva as placas na entradas de retirada
	while (strcmp(placa, entrada->placa[entrada->topo]))
	{

		printf("Manobrando Carro: %s\n", entrada->placa[entrada->topo]);
		empilhaRetirada(saida, entrada->placa[entrada->topo], entrada->manobras[entrada->topo]++);
		free(entrada->placa[entrada->topo]);

		entrada->topo--;
	}
	free(entrada->placa[entrada->topo]);
	return entrada->manobras[entrada->topo--];
}

void empilhaRetirada(PilhaRetirada *pilha, char placa[8], int manobras)
{
	if (pilha->topo == TAMANHO_PILHA - 1)
	{
		printf("Erro: Estacionamento Lotado.\n");
		exit(0);
	}

	//=> Incrementa o topo, a quantidade de manobras e salva a placa
	pilha->topo++;
	pilha->manobras[pilha->topo] = manobras + 1;

	//=> Aloca memória para a placa e a salva
	pilha->placas[pilha->topo] = (char *)malloc(strlen(placa) + 1);
	if (pilha->placas[pilha->topo] == NULL)
	{
		printf("Erro: Falha ao alocar memória.\n");
		exit(1);
	}
	strcpy(pilha->placas[pilha->topo], placa);
}

int desempilhaRetirada(PilhaEstacionada *entrada, PilhaRetirada *saida)
{
	if (saida->topo == -1)
	{
		printf("Erro: Nenhum carro foi manobrado.\n");
		return -2;
	}

	empilhaEstacionamento(entrada, saida->placas[saida->topo], saida->manobras[saida->topo]);
	free(saida->placas[saida->topo]);
	saida->topo--;
	return saida->topo;
}

void imprimePilha(PilhaEstacionada *entrada, PilhaRetirada *saida)
{

	if (saida == NULL)
	{
		int i = entrada->topo;
		printf("\nCarros Estacionados:");
		while (i >= 0)
		{
			printf("===> Carro %d\n", i);
			printf("Placa: %s\n", entrada->placa[i]);
			printf("Qtd de Manobras %d\n\n", entrada->manobras[i]);
			i--;
		}
		printf("\n\n");
	}

	else
	{
		int i = saida->topo;
		printf("\nCarros Estacionados:");
		while (i >= 0)
		{
			printf("===> Carro %d\n", i);
			printf(" %s\n", saida->placas[i]);
			printf(" %d\n\n", saida->manobras[i]);
			i--;
		}
		printf("\n\n");
	}
}

void Pilha(PilhaEstacionada *estacionamento)
{
	int i = estacionamento->topo;
	printf("Carros Estacionados:\n");
	while (i >= 0)
	{
		printf("%d - %s\n", i, estacionamento->placa[i]);
		i--;
	}
	printf("\n");
}

void cabecalho(PilhaEstacionada *p)
{
	printf("=======================================\n");
	printf("      Controle de Estacionamento       \n");
	printf("=======================================\n");

	Pilha(p);
}

// Função para verificar se a placa já está na pilha
int placaExiste(PilhaEstacionada *pilha, char placa[8])
{
	for (int cont = 0; cont <= pilha->topo; cont++)
	{
		if (strcmp(pilha->placa[cont], placa) == 0)
		{
			return 1; // Placa encontrada
		}
	}
	return 0; // Placa não encontrada
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

int main(void)
{

	//=> Declarações
	PilhaEstacionada estacionamento = {-1};
	PilhaRetirada saidas = {-1};

	//=> Define a operação(in/out) e a placa do carro
	const char *carros[] = {
		"E-ABC1234\0",
		"E-DEF5678\0",
		"E-GHI9012\0",
		"S-DEF5678\0",
		"E-JKL3456\0"};

	int tamanho = sizeof(carros) / sizeof(carros[0]);
	char copia[10];

	char *op;
	char placa[8];
	int manobras;
	int cont;

	setlocale(LC_ALL, "Portuguese");
	cabecalho(&estacionamento);

	//=> Estaciona ou Retira os Veículos
	for (cont = 0; cont < tamanho; cont++)
	{

		strcpy(copia, carros[cont]);	  //=> Copia a Operação e Placa do carro
		op = strtok(copia, "-");		  //=> Operação (E=Estacionar, S=Sair)
		strcpy(placa, strtok(NULL, "-")); //=> Placa do Carro

		switch (*op)
		{
		case 'E':
			empilhaEstacionamento(&estacionamento, placa, -1);
			system("PAUSE");
			clear();
			cabecalho(&estacionamento);
			break;

		case 'S':
			manobras = desempilhaEstacionamento(&estacionamento, &saidas, placa);

			printf("\nEstacionando novamente os veículos manobrados...\n");
			while (desempilhaRetirada(&estacionamento, &saidas) != -1)
				;

			//=> Retorna a quantidade de manobras e decrementa o topo
			printf("\n===> Veículo Retirado:\n");
			printf("Placa: %s\n", placa);
			printf("Manobras: %d\n", manobras);

			system("PAUSE");
			clear();
			cabecalho(&estacionamento);
			break;
		}
	}

	// imprimePilha(&estacionamento, NULL);
	system("PAUSE");
	return 0;
}
