""" Escrever um programa que leia o tempo de duração em segundos de um
determinado evento em uma fábrica e informe-o expresso no formato
horas:minutos:segundos. """

from a_uteis_Dev import uteis

hora = min = seg = 0
uteis.cabecalho("Vamos descobrir o tempo de duração do seu programa")
tempo_programa = int(input("Digite a quantidade de segundos que o programa irá durar: "))
while tempo_programa != 0:
    seg += 1
    tempo_programa -= 1
    if seg == 60:
        min += 1
        seg -= 60
        if min == 60:
            hora += 1
            min -= 60

print(f"O programa irá durar {hora} horas, {min} minutos e {seg} segundos")