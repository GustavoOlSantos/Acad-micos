/* PROGRAMA PARA CONTROLE DE VENDAS DIÃRIAS DE UMA LOJA DE ROUPAS

====> Desenvolvedores:
• Franklin Gaio Filgueira Filho
• Gustavo Oliveira Ferreira Dos Santos
• Maria Clara Aguiar dos SantosCampos Dias
• Pedro Henrique Graciliano Taka
• Rayra de Medeiros Bastos
• Vivian Da Silva Mota
• Thiago Martins Rodrigues da Silva

====> Ciência da Computação - Noturno

*/

#include <stdio.h>  //=> Padrão para controle de Input e Output
#include <stdlib.h> //=> Alocação de memória, conversões etc
#include <string.h> //=> Manipulação de Strings
#include <conio.h>  //=> Funções para uso do Console
#include <locale.h> //=> Correções de Escrita com o setLocale

#define max 500 //=> Maximo de Vendas por dia
#define maxCodigo 10000

typedef struct
{
    int cliente;
    int codigo;
    char nome[50];
    char marca[50];
    int quantidade;
    float pUnid;
    float pPago;
} Produto;

//=> Calcula o Preçoo pago pela venda
float precoPago(float valor, int qtd)
{
    return (valor * qtd);
}

//=> Aplica o Desconto de 10% para cada Produto
float desconto(float valor)
{
    return (valor - (valor * 10 / 100));
}

//=> Verifica o item mais vendido
int maisVendido(int *codigos)
{
    int maxCount = 0;
    int cont = 0;
    int maisfrequente = -1; //=> Inicializa com um valor inválido

    for (cont = 0; cont < maxCodigo; ++cont)
    {
        if (codigos[cont] > maxCount)
        {
            //=> Recebe a QTD de ocorrências desse produto
            maxCount = codigos[cont];
            maisfrequente = cont;
        }
    }

    return maisfrequente;
}

//=> Verifica o Item menos Vendido
int menosVendido(int *codigos)
{
    int minCount = 9999999;
    int cont = 0;
    int menosfrequente = -1; // Inicializa com um valor inválido

    for (cont = 0; cont < maxCodigo; ++cont)
    {
        if (codigos[cont] > 0 && codigos[cont] < minCount)
        {
            //=> Recebe a QTD de ocorrências desse produto
            minCount = codigos[cont];
            menosfrequente = cont;
        }
    }

    return menosfrequente;
}

//=> Ordena os Produtos em decrescente Agrupados pelo cliente
void bubbleSort(Produto *Vendas, float *clientes, int qtd)
{
    int i, j;

    for (i = 0; i < qtd - 1; i++)
    {
        for (j = 0; j < qtd - i - 1; j++)
        {
            if (clientes[Vendas[j].cliente] < clientes[Vendas[j + 1].cliente])
            {
                // Trocar vendas[j] e vendas[j + 1]
                Produto temp = Vendas[j];
                Vendas[j] = Vendas[j + 1];
                Vendas[j + 1] = temp;
            }
        }
    }
}

//=> Limpa a tela em todos os sistemas
int clear()
{
#ifdef _WIN32
    return system("cls");
#else
    return system("clear");
#endif
}

void cabecalho(char *mensagem)
{
    clear();
    setlocale(LC_ALL, "Portuguese");
    printf("* * * * [%s] * * * *\n\n", mensagem);
}

Produto entrada_dados(int cliente)
{
    Produto p;

    p.cliente = cliente; // Indica os Clientes

    printf("Código do Produto (de 0 a 9999): ");
    scanf("%d", &p.codigo);

    fflush(stdin);

    printf("Nome: ");
    // fgets(p.nome, 100, stdin);
    scanf("%49[^\n]%*c", p.nome);

    fflush(stdin);

    printf("Marca: ");
    // fgets(p.marca, 100, stdin);
    scanf("%49[^\n]%*c", p.marca);

    printf("Quantidade: ");
    scanf("%d", &p.quantidade);

    printf("Preço da Unidade: ");
    scanf("%f", &p.pUnid);

    getchar();

    p.pPago = precoPago(p.pUnid, p.quantidade);

    return p;
}

//=> Função Para testes
void saida_dados(Produto saida)
{
    printf("Produto Vendido =============\n\n");
    printf("Cliente: %d", saida.cliente);
    printf("\nCódigo (até 3 dígitos): %d", saida.codigo);
    printf("\nNome: %s", saida.nome);
    printf("\nMarca: %s", saida.marca);
    printf("\nQuantidade: %d", saida.quantidade);
    printf("\nPreço Unidade: %.2f", saida.pUnid);
    printf("\nPreço Pago: %.2f", saida.pPago);

    printf("\n============================");
}

int main()
{

    //==========> Variáveis de Operação/Venda
    int clientes = 0, //=> Incrementa ao finalizar uma venda
        contProd = 0, //=> Incrementa a cada produto adicionado
        counter = 0,  //=> Comparador do contProd
        op = 0,       //=> Operação do Usuário
        opVenda = 0;  //=> Operação de Venda
    char confirma,    //=> Confirmação de Operação
        flag;

    int contProd2 = 0;

    //==========> Variáveis de Relatório
    float faturamento;          //=> Armazena o Faturamento Total Diário
    int QtdProd, QtdCliente;    //=> Quantidade de produtos vendidos e de clientes
    int codigoCount[maxCodigo] = {0}; //=> Armazena a ocorrência de cada código/produto
    int maisVend;               //=> Produto Mais Vendido
    int menosVend;              //=> Produto Menos Vendido

    Produto ReadVenda[max];  //=> Armazena os Dados Encontrados no Arquivo
    float PTotal[max] = {0}; //=> Armazena o Preço pago por cada cliente

    //==========> Estruturas, Arquivos e Ponteiros
    Produto venda[max]; //=> Registro de Vendas
    FILE *arquivo;      //=> Ponteiro para o Arquivo de Registro

    arquivo = fopen("loja_roupa.dat", "w+b");

    if (arquivo == NULL)
    {
        printf("\nFalha na abertura do arquivo binário\n");
        return 1;
    }

    setlocale(LC_ALL, "Portuguese"); //=> Configura o CharSet

    //=> Funcionamento do Caixa
    do
    {
        clear();
        printf("+----------------------+\n");
        printf("| * * * * OPÇÕES * * * * |\n");
        printf("+----------------------+\n");

        printf("| [1]: Novo Cliente     |\n");
        printf("| [2]: Fechar Caixa     |\n");
        printf("+----------------------+\n");

        printf("Resposta: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            do
            {
                if (clientes != 0)
                {
                    flag = ' ';
                    while (toupper(flag) != 'S' && toupper(flag) != 'N')
                    {
                        clear();
                        printf("Deseja Cadastrar outro cliente? (S/N): ");
                        scanf("%1c", &flag);

                        fflush(stdin);
                    }

                    if (toupper(flag) == 'N')
                    {
                        break;
                    }
                }

                flag = ' ';
                clientes++;
                contProd2 = 0;

                do
                {
                    clear();
                    printf("[1] Novo Produto\n");
                    printf("[2] Fechar Venda\n");
                    printf("Resposta: ");

                    scanf("%d", &opVenda);

                    if (opVenda == 1)
                    {
                        venda[contProd] = entrada_dados(clientes);
                        contProd++;
                        contProd2++;
                    }
                    else
                    {
                        clear();
                        printf("Venda Encerrada!");
                        sleep(2);
                    }
                } while (opVenda == 1);

                if (toupper(flag) != 'N')
                {
                    //=> Cadastra todos os produtos desse mesmo cliente de uma vez
                    for (; counter < contProd; counter++)
                    {

                        if (contProd2 >= 3)
                        {
                            venda[counter].pPago = desconto(venda[counter].pPago);
                        }

                        fwrite(&venda[counter], sizeof(venda[counter]), 1, arquivo);

                        if (ferror(arquivo))
                        {
                            printf("\nFalha no Cadastro da Venda\n\n");
                            system("PAUSE");
                            return 1;
                        }
                    }
                }
            } while (toupper(flag) != 'N');
            break;

        case 2:
            do
            {
                clear();
                printf("Tem certeza que deseja fechar o caixa?\n");
                printf("Resposta (S/N): ");
                scanf("%1c", &confirma);
                fflush(stdin);

            } while (toupper(confirma) != 'S' && toupper(confirma) != 'N');
        }
    } while (toupper(confirma) != 'S');

    //=> Encerramento
    do
    {
        clear();
        printf("+--------------------------+\n");
        printf("| * * * * OPÇÕES * * * * |\n");
        printf("+--------------------------+\n");
        printf("| [1]: Relatório Geral     |\n");
        printf("| [2]: Lista de Vendas     |\n");
        printf("| [3]: Encerrar            |\n");
        printf("+--------------------------+\n");

        printf("Resposta: ");
        scanf("%d", &op);

        switch (op)
        {
        //=> Relatório Geral
        case 1:;

            //=> Limpa as variáveis
            int clienteAnterior = 0;
            counter = faturamento = QtdProd = QtdCliente = 0;

            memset(ReadVenda, 0, sizeof(Produto));
            memset(codigoCount, 0, 1);

            //=> Reposiciona o ponteiro para o início do Arquivo
            rewind(arquivo);

            //=> Executa enquanto o arquivo não chegar ao fim
            while (!feof(arquivo))
            {
                //=> Realiza a leitura
                fread(&venda, sizeof(Produto), 1, arquivo);

                if (venda->cliente != clienteAnterior)
                {
                    QtdCliente++; //=> Obtém a Qtd de cliente a cada mudança
                }

                if (!feof(arquivo))
                {
                    clienteAnterior = venda->cliente;
                    faturamento += venda->pPago; //=> Calcula o faturamento

                    if (venda->codigo != NULL)
                    {
                        QtdProd++;                                       //=> Incrementa o total de produtos, se houver código
                        codigoCount[venda->codigo] += venda->quantidade; //=> Soma o Total desse produto, se houver código
                    }
                }

                counter++;
            }

            maisVend = maisVendido(codigoCount);
            menosVend = menosVendido(codigoCount);

            cabecalho("INFORMAÇÕES GERAIS");
            printf("=======> Faturamento Diário: R$%.2f\n\n", faturamento);

            printf("Total de Clientes: %d", QtdCliente);
            printf(" /  Total Produtos vendidos: %d\n", QtdProd);
            printf("Produto mais vendido: %d \n", maisVend);
            printf("Produto menos vendido: %d\n\n\n", menosVend);

            system("PAUSE");
            break;

        //=> Lista de Vendas
        case 2:

            //=> Limpa as variáveis
            QtdProd = counter = 0;
            memset(ReadVenda, 0, sizeof(Produto));
            memset(PTotal, 0, sizeof(PTotal));

            //=> Reposiciona o ponteiro para o início do Arquivo
            rewind(arquivo);

            //=> Executa enquanto o arquivo não chegar ao fim
            while (fread(&ReadVenda[QtdProd], sizeof(Produto), 1, arquivo) == 1)
            {
                // Calcula o Preço total pago na compra de cada cliente
                PTotal[ReadVenda[QtdProd].cliente] += ReadVenda[QtdProd].pPago;
                QtdProd++;
            }

            bubbleSort(ReadVenda, PTotal, QtdProd);
            cabecalho("LISTAGEM ORDENADA");

            int cliente_atual = -1;
            for (counter = 0; counter < QtdProd; counter++)
            {
                if (ReadVenda[counter].cliente != cliente_atual)
                {
                    //=> Se encontrar um cliente diferente, faz display do valor pago
                    if (cliente_atual != -1)
                    {
                        printf("==> Preço Total da Compra: %.2f \n\n", PTotal[cliente_atual]);
                    }

                    //=> Obtém a venda do cliente novo
                    cliente_atual = ReadVenda[counter].cliente;

                    counter == 0 ? printf("=======> Cliente Nº %d \n", cliente_atual) : printf("\n\n=======> Cliente Nº %d \n", cliente_atual);
                }

                printf("\nCódigo: %d  Nome: %s   Marca: %s\n", ReadVenda[counter].codigo, ReadVenda[counter].nome, ReadVenda[counter].marca);
                printf("Quantidade: %d   Preço Unitário: %.2f    Preço Pago: %.2f\n", ReadVenda[counter].quantidade, ReadVenda[counter].pUnid, ReadVenda[counter].pPago);
            }

            //=> Imprimir o Preço pago pelo Último cliente
            if (cliente_atual != -1)
            {
                 printf("\n==> Preço Total da Compra: %.2f \n\n", PTotal[cliente_atual]);
            }

            printf("\n\n\n");
            system("PAUSE");
            break;

        default:
            clear();
            printf("Encerrando Programa");
            sleep(1);
            printf("..");
            sleep(1);
            printf(".\n");
            break;
        }

    } while (op != 3);

    system("PAUSE");
    fclose(arquivo);

    return 0;
}
