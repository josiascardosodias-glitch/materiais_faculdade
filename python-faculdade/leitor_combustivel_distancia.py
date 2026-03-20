""" Escrever um programa para determinar o consumo médio de um automóvel
sendo fornecidos a distância total percorrida pelo automóvel e o total de
combustível gasto. """

from a_uteis_Dev import uteis

uteis.cabecalho("Vamos descobrir qual foi o consumo médio de combustivel do seu automovel")
combustivel = int(input(f"Qual foi a quantidade de combustivel gasto após a sua viagem: "))
distanccia = int(input("Qual a distância percorrida durante a sua viagem: "))
res = distanccia / combustivel

print(f"O consumo médio do seu automóvel é de {res:.1f}km por litro")