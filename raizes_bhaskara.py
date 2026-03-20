""" Escrever um programa que leia 3 valores inteiros e calcule as raízes da
equação de báscara. """

from a_uteis_Dev import uteis
from math import sqrt

uteis.cabecalho("Vamos calcular o valor das raizes de uma formula de bhaskara")
a = int(input("Digite o valor de a: "))
b = int(input("Digite o valor de b: "))
delta = int(input("Digite o valor de delta: "))
raiz1 = (-b + sqrt(delta)) / (2 * a)
raiz2 = (-b - sqrt(delta)) / (2 * a)

print(f"O valor da primeira raiz é {raiz1} e o valor da segunda raiz é {raiz2}")