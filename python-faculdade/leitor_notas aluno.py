""" Escrever um programa que leia as 3 notas de um aluno e calcule a média
final deste aluno. Considerar que a média é ponderada e que os pesos das
notas são: 2,3 e 5, respectivamente. """

from a_uteis_Dev import uteis

uteis.cabecalho("Digite Suas três notas para saber o valor de sua média ponderada")

nota1 = float(input("Digite o valor da primeira nota: "))
nota2 = float(input("Digite o valor da segunda nota: "))
nota3 = float(input("Digite o valor da terceira nota: "))
media = ((nota1 * 2) + (nota2 * 3) + (nota3 * 5)) / (2 + 3 + 5)

print(f"O valor da sua média foi de {media:.1f}")