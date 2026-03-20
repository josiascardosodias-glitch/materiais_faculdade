""" Escrever um programa que leia o nome de um aluno e as notas das 3 provas
que ele obteve no semestre. No final informar o nome do aluno e a sua
média (aritmética). """

from a_uteis_Dev import uteis

uteis.cabecalho("Digite seu nome e as suas três notas ao longo do semestre para saber qual a sua média")
nome = str(input("Digite seu nome: ")).capitalize()
nota1 = float(input("Digite á sua primeira nota no semestre: "))
nota2 = float(input("Digite á sua segunda nota no semestre: "))
nota3 = float(input("Digite á sua terceira nota no semestre: "))
media = (nota1 + nota2 + nota3) / 3

print(f"Ola! {nome}, a sua média neste semestre foi de {media:.1f}")