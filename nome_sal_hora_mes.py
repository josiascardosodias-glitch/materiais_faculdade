""" Escrever um programa que pergunte o nome de uma pessoa, o quanto ela
por hora (salário por hora) e o número de horas trabalhadas no mês. Calcular
e mostrar o total do seu salário no referido mês. """

from a_uteis_Dev import uteis

uteis.cabecalho("Vamos calcular o seu ganho total deste mês")
nome = str(input("Primeiro nos informe o seu nome: "))
sal_hora = int(input("Digite o quanto você recebe por hora: "))
horas_trabalhadas = int(input("Quantas horas você trabalhou durante este mês: "))
salario = sal_hora * horas_trabalhadas

print(f"Você irá receber um total de {salario:.2f}R$ neste mês")