""" Escreva um programa para calcular a área de um retângulo sendo fornecidas
as suas dimensões (base e altura). """

from a_uteis_Dev import uteis

uteis.cabecalho("Insira o valor da base e da altura de um retângulo para descobrir a sua área")

base = float(input("Digite o valor da base do nosso retângulo: "))
altura = float(input("Digite o valor da altura do nosso retângulo: "))
area = base * altura

print(f"A área do nosso triangulo é de {area:.1f} Metros quadrados")