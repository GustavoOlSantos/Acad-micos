import java.util.Scanner;

class Disciplinas {
    public static void main(String[ ] args) throws Exception {
        try (Scanner ent = new Scanner(System.in)) {

            // Declaracao de Variaveis
            int resp = 1;
            int op = 0;
            int tot_calc = 0;
            int tot_base = 0;
            int tot_mode = 0;
            int tot_para = 0;
            int tot_alunos = 0;

            double med = 0;
            double med_calc = 0;
            double med_base = 0;
            double med_mode = 0;
            double med_para = 0;

            // Programa Principal
            while (resp == 1){

                // Limpa a tela no windows, no linux e no MacOS
                if (System.getProperty("os.name").contains("Windows"))
                    new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
                else
                    Runtime.getRuntime().exec("clear");

                tot_alunos = tot_alunos+1;

                // Menu de Opcoes
                System.out.println(" Escolha a sua Disciplina ");
                System.out.println("[1] Calculo de uma Variavel");
                System.out.println("[2] Bases de Programacao");
                System.out.println("[3] Modelagem de Novos Negocios");
                System.out.println("[4] Paradigmas de Linguagens de Programacao");
                System.out.print("Qual a sua opcao: ");
                op = ent.nextInt();
                
                System.out.print("Qual foi a sua media? ");
                med = ent.nextDouble();

                // Verifica a opcao da linguagem
                if (op == 1){
                    tot_calc = tot_calc+1;
                    med_calc = med_calc+med;
                }
                else if (op == 2){
                    tot_base = tot_base+1;
                    med_base = med_base+med;
                }
                else if (op == 3){
                    tot_mode = tot_mode+1;
                    med_mode = med_mode+med;
                }

                else if (op == 4){
                    tot_para = tot_para+1;
                    med_para = med_para+med;
                }
                else System.out.println("Escolha invalida!");
                    
                // Verifica se tem novo alunos
                System.out.print("Outro aluno (1-SIM / NÃO: QQ outro número) ?");
                resp = ent.nextInt();
            }
                
            // Mostra resultados
            // Limpa a tela no windows, no linux e no MacOS
            if (System.getProperty("os.name").contains("Windows"))
                new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
            else
                Runtime.getRuntime().exec("clear");
            
                System.out.println("* * * RELATORIO DA PESQUISA * * *");
                System.out.println("Total de alunos que escolheram Calculo de uma Variavel ..." + tot_calc);
                System.out.println("Total de alunos que escolheram Bases de Programacao ..." + tot_base);
                System.out.println("Total de alunos que escolheram Modelagem de Novos Negocios ..." + tot_mode);
                
                System.out.println("Total de alunos que escolheram Paradigmas de Linguagens de Programacao ..." + tot_para);
                
                System.out.println("Media aritmetica das medias de Calculo de uma Variavel ... " + med_calc/tot_calc);
                
                System.out.println("Media aritmetica das medias de Bases de Programacao ... " + med_base/tot_base);
                
                System.out.println("Media aritmetica das medias de Modelagem de Novos Negocios ..." + med_mode/tot_mode);

                System.out.println("Media aritmetica das medias de Paradigmas de Linguagens de Programacao ..." + med_para/tot_para);

                System.out.println("Total de alunos ..................... " + tot_alunos);

                if (tot_calc>tot_base && tot_calc>tot_mode && tot_calc>tot_para)
                    System.out.println("Disciplina de maior adesao foi Calculo de uma Variavel");
                else if (tot_base>tot_calc && tot_base>tot_mode && tot_base>tot_para)
                    System.out.println("Disciplina com maior adesao foi Bases de Programacao");
                else if (tot_mode>tot_calc && tot_mode>tot_base && tot_mode>tot_para)
                    System.out.println("Disciplina com maior adesao foi Modelagem de Novos Negocios");
                else
                    System.out.println("Disciplina com maior adesao foi Paradigmas de Ling. de Programacao");
        }   
    }
}