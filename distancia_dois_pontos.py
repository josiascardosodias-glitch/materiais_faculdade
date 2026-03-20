""" Escrever um programa que leia dois pontos quaisquer no plano, p1(x1,y1) e
p2(x2,y2) e calcule a distância entre eles. """

from a_uteis_Dev import uteis
from math import sqrt

uteis.cabecalho("Vamos calcular a distância entre dois pontos no plano")
xp1 = int(input("Digite o valor do x do 1° ponto: "))
yp1 = int(input("Digite o valor do y do 1° ponto: "))
xp2 = int(input("Digite o valor do x do 2° ponto: "))
yp2 = int(input("Digite o valor do y do 2° ponto: "))
distancia = sqrt((xp1-xp2)**2 + (yp1-yp2)**2)

print(f"A distância entre o 1° ponto e o 2° ponto é de {distancia:.1f}")