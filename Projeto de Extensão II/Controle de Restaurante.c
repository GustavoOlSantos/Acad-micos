/* PROGRAMA PARA CONTROLE DE UM RESTAURANTE

====> Desenvolvedores:
• Franklin Gaio Filgueira Filho
• Gustavo Oliveira Ferreira Dos Santos
• Maria Clara Aguiar dos Santos Campos Dias
• Pedro Henrique Graciliano Taka
• Rayra de Medeiros Bastos
• Vivian Da Silva Mota

====> Ci�ncia da Computação - Noturno

*/


#include <stdio.h>  //=> Padr�o para controle de Input e Output
#include <stdlib.h> //=> Aloca��o de mem�ria, convers�es etc
#include <string.h> //=> Manipula��o de Strings
#include <conio.h>  //=> Fun��es para uso do Console
#include <locale.h> //=> Corre��es de Escrita com o setLocale

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
    date data; //=> Data fixo at� fechamento de caixa

    enum tipo
    {
        balanca = 0,
        quentinha = 1
    } type; //=> Controla se � Quentinha ou por balanca

    float peso,
        pRefeicao;

    enum codigo
    {
        refrigerante,
        mate,
        suco,
        agua,
        cerveja,
    } bebida; //=> Controla o Pre�o das bebidas, se houver

    float pBebida;
    float pTotal; //=> Somat�rio pRef + Pbeb
} Comanda;

//=> Calcula o Pre�o pago pela venda
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
    printf("====> Tipo de Refei��o: ");
    printf("\n� [0] Balan�a     - R$%.2f o Kg", pKgFixo);
    printf("\n� [1] Quentinha    - R$20.00 + 0.50 (Pre�o fixo + embalagem)\n");

    printf("R: ");
    scanf("%d", &p.type);

    switch (p.type)
    {
    case quentinha:

        p.peso = 0;
        p.pTotal = p.pRefeicao = 20.00 + 0.50; //=> Calcula o pre�o fixo da Refei��o e Embalagem

        break;

    case balanca:

        printf("\nPeso em KG: ");
        scanf("%f", &p.peso);
        fflush(stdin);

        p.pRefeicao = precoPago(p.peso, pKgFixo); //=> Calcula o Pre�o da Refeição
        p.pTotal = p.pRefeicao;                   //=> Adiciona o Pre�o da Refeição no SubTotal
        break;
    }

    //=> Bebidas
    printf("\nPossui Bebidas?\n");
    printf("\n� [0] n�o, finalizar");
    printf("\n� [1] sim, adicionar \n");
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
            printf("\n� [0] refrigerante - R$%.2f", bebida[0]);
            printf("\n� [1] mate         - R$%.2f", bebida[1]);
            printf("\n� [2] suco         - R$%.2f", bebida[2]);
            printf("\n� [3] �gua         - R$%.2f", bebida[3]);
            printf("\n� [4] cerveja      - R$%.2f\n\n", bebida[4]);

            printf("R: ");
            scanf("%d", &p.bebida);        //=> Obt�m o C�digo da Bebida
            p.pBebida += bebida[p.bebida]; //=> Procura o C�digo na Array de Pre�os

            printf("Deseja cadastrar outra bebida?\n");
            printf("Resposta (S/N): ");
            getchar();
            scanf("%1c", &confirma);
            fflush(stdin);

        } while (toupper(confirma) != 'N');

        p.pTotal += p.pBebida; //=> Incrementa o Pre�o da bebida no Total

        break;
    }

    clear();

    printf("==========> Resumo do Pedido tipo: ");
    p.type == 0 ? printf("Balan�a") : printf("Quentinha");

    printf("\nPeso: ");
    p.type == 0 ? printf("%.2f Kg", p.peso) : printf("N�o considerado");
    printf("\nStatus Bebida: ");
    p.bebida != 5 ? printf("Possui Bebida") : printf("N�o h� bebida nesse pedido");

    printf("\n\nPre�o da Refei��o:R$ %.2f", p.pRefeicao);
    printf("\nPre�o da Bebida: R$%.2f", p.pBebida);

    printf("\n\n==========> Pre�o Total da Refei��o: R$%.2f\n\n", p.pTotal);
    system("PAUSE");

    return p;
}

//=> Função Para testes
void saida_dados(Comanda saida, int dia, int mes, int count)
{
    if (count != 1 && dia != saida.data.dia && mes == saida.data.mes)
    {
        printf("\n\n* * * * * Novo dia! * * * * *\n\n");
    }

    if (count != 1 && (mes != saida.data.mes))
    {
        printf("\n\n* * * * * Novo m�s! * * * * *\n\n");
    }

    printf("=============> Venda Num: %d\n\n", saida.venda);

    printf("Data: %d/%d/%d\n", saida.data.dia, saida.data.mes, saida.data.ano);
    printf("\n==> Tipo de Refei��o: ");
    saida.type == 0 ? printf("Balan�a") : printf("Quentinha");

    printf("\nPeso: ");
    saida.type == 0 ? printf("%.2f Kg", saida.peso) : printf("N�o considerado");

    printf("\nPre�o da Refei��o: %.2f", saida.pRefeicao);

    printf("\n\n==> Status Bebida: ");
    saida.bebida != 5 ? printf("Possui Bebida") : printf("N�o h� bebida nesse pedido");
    printf("\nPre�o da Bebida: %.2f", saida.pBebida);

    printf("\n\n====> Subtotal: %.2f\n\n", saida.pTotal);
}

int main()
{
    //==========> Vari�veis de Opera��o/Venda
    int dia, mes, ano;
    const float pfixo = 75.00; //=> Pre�o Fixo do Kg
    float precos[5] = {7.00, 5.00, 8.00, 3.00, 10.00};

    int clientes = 0, //=> Incrementa ao finalizar uma venda
        counter = 0,  //=> Comparador do contProd
        op = 0;       //=> Opera��o do Usu�rio
    char confirma,    //=> Confirma��o de Opera��o
        flag;

    //==========> Vari�veis de Relat�rio

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
                     12}; //=> Array que ser� ordenada em rela��o aos valores de Venda mensais

    char nomeMeses[12][1][10];
    strcpy(nomeMeses[0][0], "Janeiro");
    strcpy(nomeMeses[0][1], "Fevereiro");
    strcpy(nomeMeses[0][2], "Mar�o");
    strcpy(nomeMeses[0][3], "Abril");
    strcpy(nomeMeses[0][4], "Maio");
    strcpy(nomeMeses[0][5], "Junho");
    strcpy(nomeMeses[0][6], "Julho");
    strcpy(nomeMeses[0][7], "Agosto");
    strcpy(nomeMeses[0][8], "Setembro");
    strcpy(nomeMeses[0][9], "Outubro");
    strcpy(nomeMeses[0][10], "Novembro");
    strcpy(nomeMeses[0][11], "Dezembro");

    int opR;               //=> Opera��o do Usu�rio P/ Relat�rios
    float Vtotal = 0;      //=> Arrecada��o Total do relat�rio solicitado
    int qtdClient = 0;     //=> Verifica o Total de vendas presente no arquivo
    int count = 0;         //=> Comparador com qtdClient
    int dia_anterior = -1; //=> Verifica altera��es no dia
    int mes_anterior = -1; //=> Verifica altera��es no mês

    //========== Estruturas, Arquivos e Ponteiros
    Comanda venda[max]; //=> Registro de Vendas
    FILE *arquivo;      //=> Ponteiro para o Arquivo de Registro

    arquivo = fopen("restaurante.dat", "a+b");

    if (arquivo == NULL)
    {
        printf("\nFalha na abertura do arquivo bin�rio\n");
        return 1;
    }

    setlocale(LC_ALL, "Portuguese"); //=> Configura o CharSet

    //=> Funcionamento do Caixa
    do
    {
        cabecalho("Insira a Data: ");

        printf("Siga essa Formata��o (dd/mm/yyyy): ");
        scanf("%2d/%2d/%4d", &dia, &mes, &ano);
        clear();
        confirma = 'N';

        //=> Repete a Inser��o de Data
        if ((dia <= 0 || dia > 31) || (mes <= 0 || mes > 12) || ano <= 0)
        {
            continue;
        }

        do
        {
            clear();
            printf("====> Data Selecionada: %d/%d/%d\n\n", dia, mes, ano);

            printf("+--------------------------+\n");
            printf("| * * * * OP��ES * * * * |\n");
            printf("+--------------------------+\n");
            printf("| [1]: Nova Venda          |\n");
            printf("| [2]: Alterar Data        |\n");
            printf("| [3]: Relat�rios          |\n");
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
                    printf("| * * * * RELAT�RIOS * * * * |\n");
                    printf("+----------------------------+\n");
                    printf("| [1]: Vendas Di�rias        |\n");
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
                        //=> Relat�rio Di�rio
                        cabecalho("RELAT�RIO DI�RIO");

                        count = qtdClient = Vtotal = 0;
                        memset(ReadVenda, 0, sizeof(Comanda));
                        rewind(arquivo);

                        while (fread(&ReadVenda[qtdClient + 1], sizeof(Comanda), 1, arquivo) == 1)
                        {
                            //=> Se a data encontrada no registro, for a mesma do dia definido
                            //=> Permite a escrita dos dados em outra posi��o, se n�o, subscreve
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
                        //=> Relat�rio Mensal
                        cabecalho("RELAT�RIO MENSAL");

                        count = qtdClient = Vtotal = 0;
                        memset(ReadVenda, 0, sizeof(Comanda));
                        rewind(arquivo);

                        while (fread(&ReadVenda[qtdClient + 1], sizeof(Comanda), 1, arquivo) == 1)
                        {
                            //=> Se a data encontrada no registro, for a mesma do dia definido
                            //=> Permite a escrita dos dados em outra posi��o, se n�o, subscreve
                            if (ReadVenda[qtdClient + 1].data.mes == mes && ReadVenda[qtdClient + 1].data.ano == ano)
                            {
                                Vtotal += ReadVenda[qtdClient + 1].pTotal;
                                qtdClient++;
                            }
                        }

                        if (qtdClient > 0)
                        {
                            printf("====> Data para listagem: %d/%d\n", mes, ano);
                            printf("Total arrecadado nesse m�s: R$%.2f \n\n", Vtotal);

                            for (count = 1; count < qtdClient + 1; count++)
                            {
                                saida_dados(ReadVenda[count], dia_anterior, mes_anterior, count);
                                dia_anterior = ReadVenda[count].data.dia;
                                mes_anterior = ReadVenda[count].data.mes;
                            }
                        }

                        else
                        {
                            printf("Nenhum Registro encontrado para o m�s selecionado!\n\n");
                        }

                        system("PAUSE");
                        break;

                    case 3:
                        //=> Relat�rio Anual
                        cabecalho("RELAT�RIO ANUAL");

                        //=> Zera todas as vari�veis
                        count = qtdClient = Vtotal = 0;
                        memset(ReadVenda, 0, sizeof(Comanda));
                        rewind(arquivo);

                        while (fread(&ReadVenda[qtdClient + 1], sizeof(Comanda), 1, arquivo) == 1)
                        {
                            //=> Se a data encontrada no registro, for a mesma do dia definido
                            //=> Permite a escrita dos dados em outra posi��o, se n�o, subscreve
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
                            printf("Ordena��o pela arrecada��o mensal: \n");

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
                            perror("Erro: Não foi Poss�vel retornar ao fim do arquivo");
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
