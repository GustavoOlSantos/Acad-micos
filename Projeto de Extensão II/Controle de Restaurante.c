/* PROGRAMA PARA CONTROLE DE UM RESTAURANTE

====> Desenvolvedores:
â€¢ Franklin Gaio Filgueira Filho
â€¢ Gustavo Oliveira Ferreira Dos Santos
â€¢ Maria Clara Aguiar dos Santos Campos Dias
â€¢ Pedro Henrique Graciliano Taka
â€¢ Rayra de Medeiros Bastos
â€¢ Vivian Da Silva Mota

====> Ciência da ComputaÃ§Ã£o - Noturno

*/


#include <stdio.h>  //=> Padrão para controle de Input e Output
#include <stdlib.h> //=> Alocação de memória, conversões etc
#include <string.h> //=> Manipulação de Strings
#include <conio.h>  //=> Funções para uso do Console
#include <locale.h> //=> Correções de Escrita com o setLocale

#define max 100 //=> Maximo de Vendas por dia

typedef struct
{
    int dia,
        mes,
        ano;
} date;

typedef struct
{
    int venda; //=> Controle do total de vendas
    date data; //=> Data fixo até fechamento de caixa

    enum tipo
    {
        balanca = 0,
        quentinha = 1
    } type; //=> Controla se é Quentinha ou por balanca

    float peso,
        pRefeicao;

    enum codigo
    {
        refrigerante,
        mate,
        suco,
        agua,
        cerveja,
    } bebida; //=> Controla o Preço das bebidas, se houver

    float pBebida;
    float pTotal; //=> Somatório pRef + Pbeb
} Comanda;

//=> Calcula o Preço pago pela venda
float precoPago(float peso, float pfixo)
{
    return (peso * pfixo);
}

//=> Ordena os Comandas em decrescente
void bubbleSort(Comanda *Refeicoes, float *pVendas, int *meses, int qtdClient)
{
    int i, j;

    for (i = 0; i < 12 - 1; i++)
    {
        for (j = 0; j < 12 - i - 1; j++)
        {
            if (pVendas[meses[j]] < pVendas[meses[j + 1]])
            {
                // Trocar vendas[j] e vendas[j + 1]
                int temp = meses[j];
                meses[j] = meses[j + 1];
                meses[j + 1] = temp;
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

Comanda entrada_dados(int dia, int mes, int ano, int index, float pKgFixo, float *bebida)
{
    Comanda p;
    int resp;
    char confirma;

    //=> Controle de Data
    p.data.dia = dia;
    p.data.mes = mes;
    p.data.ano = ano;

    p.venda = index + 1;

    clear();
    printf("====> Tipo de Refeição: ");
    printf("\n• [0] Balança     - R$%.2f o Kg", pKgFixo);
    printf("\n• [1] Quentinha    - R$20.00 + 0.50 (Preço fixo + embalagem)\n");

    printf("R: ");
    scanf("%d", &p.type);

    switch (p.type)
    {
    case quentinha:

        p.peso = 0;
        p.pTotal = p.pRefeicao = 20.00 + 0.50; //=> Calcula o preço fixo da Refeição e Embalagem

        break;

    case balanca:

        printf("\nPeso em KG: ");
        scanf("%f", &p.peso);
        fflush(stdin);

        p.pRefeicao = precoPago(p.peso, pKgFixo); //=> Calcula o Preço da RefeiÃ§Ã£o
        p.pTotal = p.pRefeicao;                   //=> Adiciona o Preço da RefeiÃ§Ã£o no SubTotal
        break;
    }

    //=> Bebidas
    printf("\nPossui Bebidas?\n");
    printf("\n• [0] não, finalizar");
    printf("\n• [1] sim, adicionar \n");
    printf("R: ");

    scanf("%d", &resp);
    fflush(stdin);

    switch (resp)
    {
    case 0:
        p.bebida = 5;
        p.pBebida = 0;
        break;

    case 1:
        p.pBebida = 0;
        p.bebida = -1;
        do
        {

            clear();
            printf("====> Selecione a Bebida: ");
            printf("\n• [0] refrigerante - R$%.2f", bebida[0]);
            printf("\n• [1] mate         - R$%.2f", bebida[1]);
            printf("\n• [2] suco         - R$%.2f", bebida[2]);
            printf("\n• [3] Água         - R$%.2f", bebida[3]);
            printf("\n• [4] cerveja      - R$%.2f\n\n", bebida[4]);

            printf("R: ");
            scanf("%d", &p.bebida);        //=> Obtém o Código da Bebida
            p.pBebida += bebida[p.bebida]; //=> Procura o Código na Array de Preços

            printf("Deseja cadastrar outra bebida?\n");
            printf("Resposta (S/N): ");
            getchar();
            scanf("%1c", &confirma);
            fflush(stdin);

        } while (toupper(confirma) != 'N');

        p.pTotal += p.pBebida; //=> Incrementa o Preço da bebida no Total

        break;
    }

    clear();

    printf("==========> Resumo do Pedido tipo: ");
    p.type == 0 ? printf("Balança") : printf("Quentinha");

    printf("\nPeso: ");
    p.type == 0 ? printf("%.2f Kg", p.peso) : printf("Não considerado");
    printf("\nStatus Bebida: ");
    p.bebida != 5 ? printf("Possui Bebida") : printf("Não há bebida nesse pedido");

    printf("\n\nPreço da Refeição:R$ %.2f", p.pRefeicao);
    printf("\nPreço da Bebida: R$%.2f", p.pBebida);

    printf("\n\n==========> Preço Total da Refeição: R$%.2f\n\n", p.pTotal);
    system("PAUSE");

    return p;
}

//=> FunÃ§Ã£o Para testes
void saida_dados(Comanda saida, int dia, int mes, int count)
{
    if (count != 1 && dia != saida.data.dia && mes == saida.data.mes)
    {
        printf("\n\n* * * * * Novo dia! * * * * *\n\n");
    }

    if (count != 1 && (mes != saida.data.mes))
    {
        printf("\n\n* * * * * Novo mês! * * * * *\n\n");
    }

    printf("=============> Venda Num: %d\n\n", saida.venda);

    printf("Data: %d/%d/%d\n", saida.data.dia, saida.data.mes, saida.data.ano);
    printf("\n==> Tipo de Refeição: ");
    saida.type == 0 ? printf("Balança") : printf("Quentinha");

    printf("\nPeso: ");
    saida.type == 0 ? printf("%.2f Kg", saida.peso) : printf("Não considerado");

    printf("\nPreço da Refeição: %.2f", saida.pRefeicao);

    printf("\n\n==> Status Bebida: ");
    saida.bebida != 5 ? printf("Possui Bebida") : printf("Não há bebida nesse pedido");
    printf("\nPreço da Bebida: %.2f", saida.pBebida);

    printf("\n\n====> Subtotal: %.2f\n\n", saida.pTotal);
}

int main()
{
    //==========> Variáveis de Operação/Venda
    int dia, mes, ano;
    const float pfixo = 75.00; //=> Preço Fixo do Kg
    float precos[5] = {7.00, 5.00, 8.00, 3.00, 10.00};

    int clientes = 0, //=> Incrementa ao finalizar uma venda
        counter = 0,  //=> Comparador do contProd
        op = 0;       //=> Operação do Usuário
    char confirma,    //=> Confirmação de Operação
        flag;

    //==========> Variáveis de Relatório

    Comanda ReadVenda[max];   //=> Armazena os Dados Encontrados no Arquivo
    float TotalMes[13] = {0}; //=> Armazena o valor de Venda em cada mes
    int meses[12] = {1,
                     2,
                     3,
                     4,
                     5,
                     6,
                     7,
                     8,
                     9,
                     10,
                     11,
                     12}; //=> Array que será ordenada em relação aos valores de Venda mensais

    char nomeMeses[12][1][10];
    strcpy(nomeMeses[0][0], "Janeiro");
    strcpy(nomeMeses[0][1], "Fevereiro");
    strcpy(nomeMeses[0][2], "Março");
    strcpy(nomeMeses[0][3], "Abril");
    strcpy(nomeMeses[0][4], "Maio");
    strcpy(nomeMeses[0][5], "Junho");
    strcpy(nomeMeses[0][6], "Julho");
    strcpy(nomeMeses[0][7], "Agosto");
    strcpy(nomeMeses[0][8], "Setembro");
    strcpy(nomeMeses[0][9], "Outubro");
    strcpy(nomeMeses[0][10], "Novembro");
    strcpy(nomeMeses[0][11], "Dezembro");

    int opR;               //=> Operação do Usuário P/ Relatórios
    float Vtotal = 0;      //=> Arrecadação Total do relatório solicitado
    int qtdClient = 0;     //=> Verifica o Total de vendas presente no arquivo
    int count = 0;         //=> Comparador com qtdClient
    int dia_anterior = -1; //=> Verifica alterações no dia
    int mes_anterior = -1; //=> Verifica alterações no mÃªs

    //========== Estruturas, Arquivos e Ponteiros
    Comanda venda[max]; //=> Registro de Vendas
    FILE *arquivo;      //=> Ponteiro para o Arquivo de Registro

    arquivo = fopen("restaurante.dat", "a+b");

    if (arquivo == NULL)
    {
        printf("\nFalha na abertura do arquivo binário\n");
        return 1;
    }

    setlocale(LC_ALL, "Portuguese"); //=> Configura o CharSet

    //=> Funcionamento do Caixa
    do
    {
        cabecalho("Insira a Data: ");

        printf("Siga essa Formatação (dd/mm/yyyy): ");
        scanf("%2d/%2d/%4d", &dia, &mes, &ano);
        clear();
        confirma = 'N';

        //=> Repete a Inserção de Data
        if ((dia <= 0 || dia > 31) || (mes <= 0 || mes > 12) || ano <= 0)
        {
            continue;
        }

        do
        {
            clear();
            printf("====> Data Selecionada: %d/%d/%d\n\n", dia, mes, ano);

            printf("+--------------------------+\n");
            printf("| * * * * OPÇÕES * * * * |\n");
            printf("+--------------------------+\n");
            printf("| [1]: Nova Venda          |\n");
            printf("| [2]: Alterar Data        |\n");
            printf("| [3]: Relatórios          |\n");
            printf("| [4]: Fechar Caixa        |\n");
            printf("+--------------------------+\n");

            printf("Resposta: ");
            scanf("%d", &op);
            fflush(stdin);

            switch (op)
            {
            case 1:
                do
                {
                    if (clientes != 0)
                    {
                        flag = " ";
                        while (toupper(flag) != 'S' && toupper(flag) != 'N')
                        {
                            clear();
                            printf("Deseja Cadastrar outra venda? (S/N): ");
                            scanf("%1c", &flag);

                            fflush(stdin);
                        }

                        if (toupper(flag) == 'N')
                        {
                            break;
                        }
                    }

                    flag = " ";

                    venda[clientes] = entrada_dados(dia, mes, ano, clientes, pfixo, precos);
                    fwrite(&venda[clientes], sizeof(Comanda), 1, arquivo);

                    if (ferror(arquivo))
                    {
                        printf("\nFalha no Cadastro da Venda\n\n");
                        system("PAUSE");
                        return 1;
                    }

                    clientes++;
                } while (toupper(flag) != 'N');
                break;

            case 3:
                do
                {
                    clear();
                    printf("====> Data Selecionada: %d/%d/%d\n\n", dia, mes, ano);

                    printf("+----------------------------+\n");
                    printf("| * * * * RELATÓRIOS * * * * |\n");
                    printf("+----------------------------+\n");
                    printf("| [1]: Vendas Diárias        |\n");
                    printf("| [2]: Vendas Mensais        |\n");
                    printf("| [3]: Vendas Anuais         |\n");
                    printf("| [4]: Voltar                |\n");
                    printf("+--------------------------+\n");

                    printf("Resposta: ");
                    scanf("%d", &opR);
                    fflush(stdin);

                    switch (opR)
                    {
                    case 1:
                        //=> Relatório Diário
                        cabecalho("RELATÓRIO DIÁRIO");

                        count = qtdClient = Vtotal = 0;
                        memset(ReadVenda, 0, sizeof(Comanda));
                        rewind(arquivo);

                        while (fread(&ReadVenda[qtdClient + 1], sizeof(Comanda), 1, arquivo) == 1)
                        {
                            //=> Se a data encontrada no registro, for a mesma do dia definido
                            //=> Permite a escrita dos dados em outra posição, se não, subscreve
                            if (ReadVenda[qtdClient + 1].data.dia == dia && ReadVenda[qtdClient + 1].data.mes == mes && ReadVenda[qtdClient + 1].data.ano == ano)
                            {
                                Vtotal += ReadVenda[qtdClient + 1].pTotal;
                                qtdClient++;
                            }
                        }

                        if (qtdClient > 0)
                        {
                            printf("====> Data para listagem: %d/%d/%d\n", dia, mes, ano);
                            printf("Total arrecadado nesse dia: R$%.2f \n\n", Vtotal);

                            for (count = 1; count < qtdClient + 1; count++)
                            {
                                saida_dados(ReadVenda[count], dia_anterior, mes_anterior, count);
                                dia_anterior = ReadVenda[count].data.dia;
                                mes_anterior = ReadVenda[count].data.mes;
                            }
                        }

                        else
                        {
                            printf("Nenhum Registro encontrado para a data selecionada!\n\n");
                        }

                        system("PAUSE");
                        break;

                    case 2:
                        //=> Relatório Mensal
                        cabecalho("RELATÓRIO MENSAL");

                        count = qtdClient = Vtotal = 0;
                        memset(ReadVenda, 0, sizeof(Comanda));
                        rewind(arquivo);

                        while (fread(&ReadVenda[qtdClient + 1], sizeof(Comanda), 1, arquivo) == 1)
                        {
                            //=> Se a data encontrada no registro, for a mesma do dia definido
                            //=> Permite a escrita dos dados em outra posição, se não, subscreve
                            if (ReadVenda[qtdClient + 1].data.mes == mes && ReadVenda[qtdClient + 1].data.ano == ano)
                            {
                                Vtotal += ReadVenda[qtdClient + 1].pTotal;
                                qtdClient++;
                            }
                        }

                        if (qtdClient > 0)
                        {
                            printf("====> Data para listagem: %d/%d\n", mes, ano);
                            printf("Total arrecadado nesse mês: R$%.2f \n\n", Vtotal);

                            for (count = 1; count < qtdClient + 1; count++)
                            {
                                saida_dados(ReadVenda[count], dia_anterior, mes_anterior, count);
                                dia_anterior = ReadVenda[count].data.dia;
                                mes_anterior = ReadVenda[count].data.mes;
                            }
                        }

                        else
                        {
                            printf("Nenhum Registro encontrado para o mês selecionado!\n\n");
                        }

                        system("PAUSE");
                        break;

                    case 3:
                        //=> Relatório Anual
                        cabecalho("RELATÓRIO ANUAL");

                        //=> Zera todas as variáveis
                        count = qtdClient = Vtotal = 0;
                        memset(ReadVenda, 0, sizeof(Comanda));
                        rewind(arquivo);

                        while (fread(&ReadVenda[qtdClient + 1], sizeof(Comanda), 1, arquivo) == 1)
                        {
                            //=> Se a data encontrada no registro, for a mesma do dia definido
                            //=> Permite a escrita dos dados em outra posição, se não, subscreve
                            if (ReadVenda[qtdClient + 1].data.ano == ano)
                            {
                                Vtotal += ReadVenda[qtdClient + 1].pTotal;
                                TotalMes[ReadVenda[qtdClient + 1].data.mes] += ReadVenda[qtdClient + 1].pTotal;
                                qtdClient++;
                            }
                        }

                        bubbleSort(ReadVenda, TotalMes, meses, qtdClient);

                        if (qtdClient > 0)
                        {
                            printf("====> Ano para listagem: %d\n", ano);
                            printf("Total arrecadado nesse ano: R$%.2f \n\n", Vtotal);
                            printf("Ordenação pela arrecadação mensal: \n");

                            for (count = 0; count < 12; count++)
                            {
                                printf("%s - R$%.2f\n", nomeMeses[0][meses[count] - 1], TotalMes[meses[count]]);
                            }

                            system("PAUSE");
                        }

                        else
                        {
                            printf("Nenhum Registro encontrado para o ano selecionado!\n\n");
                        }

                        system("PAUSE");
                        break;

                    default:
                        // Retorna o ponteiro para o fim do arquivo e volta ao menu principal
                        if (fseek(arquivo, 0, SEEK_END) != 0)
                        {
                            perror("Erro: NÃ£o foi Possível retornar ao fim do arquivo");
                            fclose(arquivo);
                            return 1;
                        }

                        break;
                    }

                } while (opR != 4);

                break;

            case 4:
                do
                {
                    clear();
                    printf("Tem certeza que deseja fechar o caixa?\n");
                    printf("Resposta (S/N): ");
                    scanf("%1c", &confirma);
                    fflush(stdin);

                } while (toupper(confirma) != 'S' && toupper(confirma) != 'N');
            }
        } while (op != 2 && toupper(confirma) != 'S');

    } while (toupper(confirma) != 'S');

    clear();
    printf("Encerrando Programa");
    sleep(1);
    printf("..");
    sleep(1);
    printf(".\n");

    system("PAUSE");
    fclose(arquivo);

    return 0;
}
