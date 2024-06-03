#include <stdio.h>

int main()
{
    //=> Declaração dos Vetores
    int vetorA[11];
    int vetorB[11];
    int vetorC[11];

    //=> Contador Auxiliar
    int cont = 0;

    //=> Inicia a Obtenção de Valores do 1º Vetor(A)
    printf("Digite um numero para compor o vetor A: ");
    do
    {
        scanf("%d", &vetorA[cont]);
        cont++;

        if (cont <= 9)
        {
            printf("\nproximo numero: ");
        }
    } while (cont <= 9);
    vetorA[10] = '\0';

    //=> Inicia a Obtenção de Valores do 2º Vetor(B)
    cont = 0;
    printf("\n\nDigite um numero para compor o vetor B: ");
    do
    {
        scanf("%d", &vetorB[cont]);
        cont++;

        if (cont <= 9)
        {
            printf("\nproximo numero: ");
        }
    } while (cont <= 9);
    vetorB[10] = '\0';

    //=> Inicia as Operações dos Valores para o 3º Vetor(C)
    cont = 0;
    do
    {
        vetorC[cont] = ((vetorA[cont] + vetorB[cont]) * (vetorA[cont] + vetorB[cont]));
        cont++;
    } while (cont <= 9);
    vetorC[10] = '\0';

    //=> Exibição dos Valores Obtidos:
    printf("\n\n=============== RESULTADOS ===============\n\n");
    for (cont = 0; cont <= 9; cont++)
    {
        printf("Valor %d: %d\n", cont, vetorC[cont]);
    }

    system("pause");
}