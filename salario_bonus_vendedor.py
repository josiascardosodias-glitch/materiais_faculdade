""" Escrever um programa que leia o nome de um vendedor, o seu salário fixo e
o total de vendas efetuadas por ele no mês (em dinheiro). Sabendo que este
vendedor ganha 15% de comissão sobre suas vendas efetuadas, informar o
seu salário no final do mês. """

from a_uteis_Dev import uteis

uteis.cabecalho("Vamos descobrir o seu sálario de acordo com a sua quantidade total de vendas")
nome = str(input("Digite o seu nome: "))
sal_fixo = float(input("Qual a quantidade do seu salário fixo: "))
vendas = int(input("Quantas vendas em dinheiro você efetuou durante o mês: "))
salario = (((sal_fixo * 15 ) / 100) * vendas) + sal_fixo

print(f"O seu salário ao final do mês será de {salario:.2f}R$")