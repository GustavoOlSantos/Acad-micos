* Aluno: Gustavo Oliveira Ferreira dos Santos
* Curso: Ciência da Computação

* Programa Principal
PROGRAM Fatoracao_main

  INTEGER :: Number
  INTEGER :: FATORIAL

  PRINT *, "Insira um número para ser Fatorado: "
  READ (*,*) Number

  if (Number > 1) then
  
    FATORIAL = Number * Fatorar(Number)
    PRINT *, "Resultado da Fatoração: ", FATORIAL
    
  else
  
    PRINT *, "Não é possível fatorar esse número!"
  end if

CONTAINS
* Declaração da Função
  RECURSIVE FUNCTION Fatorar(num) RESULT(retorno)
  
    INTEGER :: num
    INTEGER :: fat
    INTEGER :: retorno

    fat = num - 1
    
    if (fat /= 1) then
        retorno = Fatorar(fat)
        retorno = fat * retorno 

    else if (fat == 1) then
        retorno = fat
    end if
        
  END FUNCTION Fatorar

END PROGRAM Fatoracao_main