""" Escrever um programa que leia um valor inteiro (quantia financeira) e informe a quantidade de cédulas de 100, 50, 10, 5, 2 e 1 necessárias para formar este valor. """

from a_uteis_Dev import uteis

cem = cinq = dez = cinco = dois = um = 0
uteis.cabecalho("Digite o valor que você deseja receber de volta em troco")
valor_inteiro = int(input("Valor desejado: "))
while valor_inteiro != 0:
    if valor_inteiro >= 100:
        cem += 1
        valor_inteiro -= 100

    elif valor_inteiro >= 50:
        cinq += 1
        valor_inteiro -= 50

    elif valor_inteiro >= 10:
        dez += 1
        valor_inteiro -= 10

    elif valor_inteiro >= 5:
        cinco += 1
        valor_inteiro -= 5

    elif valor_inteiro >= 2:
        dois += 1
        valor_inteiro -= 2

    else:
        um += 1
        valor_inteiro -= 1


print(f"O seu troco ficou: {cem}:100$, {cinq}:50$, {dez}:10$, {cinco}:5$, {dois}:2$ e {um}:1$ cédulas")