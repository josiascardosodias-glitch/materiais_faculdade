"""Escrever um programa que calcule as raízes de uma equação de 2o. grau,
sendo fornecidos os valores dos coeficientes a, b, e c (inteiros). Cuidar
quando as raízes são imaginárias e quando não for uma equação de 2o. grau
(a=0)."""

from math import sqrt

b = int(input("Qual o valor da raiz de a: "))
a = int(input("Qual o valor da raiz de b: "))
c = int(input("Qual o valor da raiz de c: "))

if a == 0:
    print("Não é uma equação de segundo grau")
else:
    delta = 2 * 2 - 4 * a * c
    if delta < 0:
        print("Raizes imaginarias")
    else:
        r1 = (-b + sqrt(delta)) / (2 * a)
        r2 = (-b - sqrt(delta)) / (2 * a)
        print(f"As raizes são {r1} e {r2}")