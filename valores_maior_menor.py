"""Escrever um programa que leia 3 valores inteiros distintos e os escreva em
ordem crescente."""

maior = menor = meio = 0

v1 = int(input("Digite um número: "))
v2 = int(input("Digite um outro número: "))
v3 = int(input("Digite um ultimo número: "))

if v1 < v2 and v1 < v3:
    menor = v1
    if v2 < v3:
        maior = v3
        meio = v2
    else:
        maior = v2
        meio = v3

elif v2 < v1 and v2 < v3:
    menor = v2
    if v1 < v3:
        meio = v1
        maior = v3
    else:
        maior = v1
        meio = v3

else:
    menor = v3
    if v1 < v2:
        meio = v1
        maior = v2
    else:
        maior = v1
        meio = v2

print(f"sequência dos valores: {maior}, {meio}, {menor}.")