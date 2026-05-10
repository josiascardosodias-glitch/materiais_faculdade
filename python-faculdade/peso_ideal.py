"""Escrever um programa que leia a altura e o sexo de uma pessoa e calcule o
seu peso ideal utilizando as seguintes fórmulas:
• para homens: (72,7 x altura) - 58
• para mulheres: (61,2 x altura) - 44,7"""

alt = float(input("Qual a sua altura: "))
sexo = input("Qual o seu gênero [M/F]: ").upper()

if sexo == "M":
    peso = ((72.7 * alt) - 58)

else:
    peso = ((61.2 * alt) - 44.7)

print(f"O seu peso ideal é de {peso:.0f} kg")