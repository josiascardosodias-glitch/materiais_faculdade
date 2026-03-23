""" Escrever um programa que leia 3 valores inteiros e calcule as raízes da
equação de báscara. """

from a_uteis_Dev import uteis
import math

uteis.cabecalho("Vamos calcular o valor das raizes de uma formula de bhaskara")
a = int(input("Digite o valor de a: "))
b = int(input("Digite o valor de b: "))
c = int(input("Digite o valor de c: "))
raiz1 = (-b + math.sqrt(b**2 - 4 * a * c)) / (2 * a)
raiz2 = (-b - math.sqrt(b**2 - 4 * a * c)) / (2 * a)

print(f"O valor da primeira raiz é {raiz1:.2f} \nE o valor da segunda raiz é {raiz2:.2f}")