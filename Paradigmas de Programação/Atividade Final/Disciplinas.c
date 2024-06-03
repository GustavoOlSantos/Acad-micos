// Programa Estatística de Disciplinas - Ling. C
#include <stdio.h>

int main()
{

    // Declaração de Variáveis
    int resp = 1;
    int op = 0;
    int tot_calc = 0;
    int tot_base = 0;
    int tot_mode = 0;
    int tot_para = 0;
    int tot_alunos = 0;
    float med = 0;
    float med_calc = 0;
    float med_base = 0;
    float med_mode = 0;
    float med_para = 0;

    // Programa Principal
    while (resp == 1)
    {
        tot_alunos = tot_alunos + 1;

        // Menu de Opções
        printf(" Escolha a sua Disciplina ");
        printf("\n [1] Cálculo de uma Variável");
        printf("\n [2] Bases de Programação");
        printf("\n [3] Modelagem de Novos Negócios");
        printf("\n [4] Paradigmas de Linguagens de Programação");

        printf("\nQual a sua opção: ");
        scanf("%d", &op);

        printf("\nQual foi a sua média? ");
        scanf("%f", &med);

        // Verifica a opção da linguagem
        if (op == 1)
        {
            tot_calc = tot_calc + 1;
            med_calc = med_calc + med;
        }
        else if (op == 2)
        {
            tot_base = tot_base + 1;
            med_base = med_base + med;
        }
        else if (op == 3)
        {
            tot_mode = tot_mode + 1;
            med_mode = med_mode + med;
        }
        else if (op == 4)
        {
            tot_para = tot_para + 1;
            med_para = med_para + med;
        }
        else
            printf("\nEscolha inválida!");

        // Verifica se tem novo alunos
        printf("\nOutro aluno (1-SIM /NÃO: QQ outro número) ?");
        scanf("%d", &resp);
    }

    // Mostra resultados
    printf("\n* * * RELATÓRIO DA PESQUISA * * *");
    printf("\nTotal de alunos que escolheram Cálculo de uma Variável ... %d", tot_calc);
    printf("\nTotal de alunos que escolheram Bases de Programação ... %d", tot_base);
    printf("\nTotal de alunos que escolheram Modelagem de Novos Negócios ... %d", tot_mode);
    printf("\nTotal de alunos que escolheram Paradigmas de Linguagens de Programação ... %d", tot_para);
    printf("\nMédia aritmética das médias de Cálculo de uma Variável ... %2.1f", med_calc / tot_calc);

    printf("\nMédia aritmética das médias de Bases de Programação ... %2.1f", med_base / tot_base);
    printf("\nMédia aritmética das médias de Modelagem de Novos Negócios ... %2.1f", med_mode / tot_mode);
    printf("\nMédia aritmética das médias de Paradigmas de Linguagens de Programação ... %2.1f", med_para / tot_para);
    printf("\nTotal de alunos ..................... %d", tot_alunos);

    if (tot_calc > tot_base && tot_calc > tot_mode && tot_calc > tot_para)
        printf("\nDisciplina de maior adesão foi Cálculo de uma Variável");
    else if (tot_base > tot_calc && tot_base > tot_mode && tot_base > tot_para)
        printf("\nDisciplina com maior adesão foi Bases de Programação");
    else if (tot_mode > tot_calc && tot_mode > tot_base && tot_mode > tot_para)
        printf("\nDisciplina com maior adesão foi Modelagem de Novos Negócios");
    else
        printf("\nDisciplina com maior adesão foi Paradigmas de Linguagens de Programação\n\n");

    system("pause");
    return 0;
}