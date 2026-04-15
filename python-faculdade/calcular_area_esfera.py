""" Escrever um programa para calcular o volume de uma esfera sendo
fornecido o valor de seu raio. """

import math
from a_uteis_Dev import uteis

uteis.cabecalho("Digite o valor do raio para descobrirmos qual o volume da sua esfera")

raio = float(input("Digite o valor do raio: "))
volume = (4/3)*math.pi*(raio*3)

print(f"O volume da nossa esfera é {volume:.1f} metros cubicos")