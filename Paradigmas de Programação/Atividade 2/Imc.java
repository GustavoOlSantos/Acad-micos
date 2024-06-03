// Cálculo do IMC - Índice de Massa Corporal
import java.util.Scanner;

public class Imc {
    public static void main(String[] args) throws Exception {
        try (Scanner ent = new Scanner(System.in)) {
            System.out.print("Digite seu peso em Kg: ");
            double peso = Double.parseDouble(ent.nextLine());
            System.out.print("Digite sua altura em metros: ");
            double altura = Double.parseDouble(ent.nextLine());

            // Vamos calcular o IMC
            double imc = peso / (altura * altura);
            System.out.println("Seu IMC é: " + imc);

            if(imc < 16){
                System.out.println("Magreza grave");
            }
            else if(imc < 17){
                System.out.println("Magreza moderada");
            }
            else if(imc < 18.5){
                System.out.println("Magreza leve");
            }
            else if(imc < 25){
                System.out.println("Saudável");
            }
            else if(imc < 30){
                System.out.println("Sobrepeso");
            }
            else if(imc < 35){
                System.out.println("Obesidade Grau I (acentuada)");
            }
            else if(imc < 40){
                System.out.println("Obesidade Grau II (severa)");
            }
            else{
                System.out.println("Obesidade Grau III (mórbida)");
            }
        }
    }
}