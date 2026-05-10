"""Escrever um programa que leia 3 valores inteiros distintos e informe qual é o
menor."""

v1 = int(input("Digite um valor: "))
v2 = int(input("Digite um outro valor: "))
v3 = int(input("Digite um mais um valor: "))

if v1 < v2 and v1 < v3:
    menor = v1
elif v2 < v1 and v2 < v3:
    menor = v2
else:
    menor = v3

print(f"O menor valor foi = {menor}")