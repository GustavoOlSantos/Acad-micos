-- Aluno: Gustavo Oliveira Ferreira dos Santos
-- Curso: Ciência da Computação

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure fatoracao is

  -- Declaração da Função
  function Fatorar(num : integer) return integer is
  fat       : integer;
  
  begin
  
  fat := num - 1;
  
  if fat /= 1 then
    return fat * Fatorar(fat);
    
  else
    return fat;
  end if;
    
  end Fatorar;
   
   -- Programa Principal
    Number      : integer;
    Fatorial    : integer;
begin
    Put_Line("Insira um número para ser Fatorado: ");
    Get(Number);
    
    if Number >= 1 then
        Fatorial := Number * Fatorar(Number);
        Put("Resultado da Fatoração: ");
        Put(Fatorial);
    
    else
      Put_Line("Não é possível fatorar esse número");
    end if;
end fatoracao;