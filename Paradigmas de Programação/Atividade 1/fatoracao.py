# Aluno: Gustavo Oliveira Ferreira dos Santos
# Curso: Ciência da Computação

# Definição da função
def fatorial(num):
    fat = num - 1

    if (fat != 1):
        retorno = fatorial(fat)
        return retorno * fat

    elif (fat == 1):
        return fat

# =================================


# Programa principal
number = int(input("Insira um número para reaizar o fatorial: "))

if (number > 1):
    ResultFatorial = number * fatorial(number)
    print("A fatorial desse número é: ")
    print(ResultFatorial)

else:
    print("Não é possível fatorar este número!")
