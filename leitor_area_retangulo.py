""" Escreva um programa para calcular a área de um retângulo sendo fornecidas
as suas dimensões (base e altura). """

from a_uteis_Dev import uteis

uteis.cabecalho("Insira o valor da base e da altura de um retângulo para descobrir a sua área")

base = float(input("Digite o valor da base do nosso retângulo: ")) # Entrada de dados
altura = float(input("Digite o valor da altura do nosso retângulo: ")) # Entrada de dados
area = base * altura

print(f"A área do nosso retângulo é de {area:.2f} Metros quadrados") # Saída de dados