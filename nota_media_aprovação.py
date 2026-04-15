"""Escrever um programa que leia o nome e as 3 notas obtidas por um aluno
durante o semestre. Calcular a sua média (aritmética) e informar se ele foi
aprovado por média ou ficou em exame. A média de aprovação é 8.0."""

n1 = float(input("Qual foi sua primeira nota: "))
n2 = float(input("Qual foi sua segunda nota: "))
n3 = float(input("Qual foi sua terçeira nota: "))

nota = (n1 + n2 + n3) / 3
if nota >= 8:
    print("Você foi aprovado")
else:
    print("Você não atingiu a média e precisara realizar o exame")