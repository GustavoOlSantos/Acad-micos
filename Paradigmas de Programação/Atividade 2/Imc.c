#include <stdio.h>

int main()
{

	float peso = 0;
	float imc = 0;
	float altura = 0;

	printf("Digite seu peso em KG: ");
	scanf("%f", &peso);

	printf("Digite sua altura em Metros: ");
	scanf("%f", &altura);

	imc = peso / (altura * altura);

	if (imc < 16)
	{
		printf("Magreza grave! \n");
	}
	else if (imc < 17)
	{
		printf("Magreza moderada! \n");
	}
	else if (imc < 18.5)
	{
		printf("Magreza leve! \n");
	}
	else if (imc < 25)
	{
		printf("Saud�vel");
	}
	else if (imc < 30)
	{
		printf("Sobrepeso! \n");
	}
	else if (imc < 35)
	{
		printf("Obesidade grau I (acentuada)\n");
	}
	else if (imc < 40)
	{
		printf("Obesidade grau II (Severa)");
	}
	else
	{
		printf("Obesidade Grau III (M�rbida)");
	}

	printf("\n");
	system("pause");
	return 0;
}
