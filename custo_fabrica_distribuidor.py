""" O custo ao consumidor de um carro novo é a soma do custo de fábrica com a
percentagem do distribuidor e dos impostos (aplicados ao custo de fábrica).
Supondo que a percentagem do distribuidor seja de 28% e os impostos 45%,
escrever um programa que leia o custo de fábrica de um carro e informe o
custo ao consumidor desse carro. """

from a_uteis_Dev import uteis

uteis.cabecalho("Vamos descobrir qual o custo do seu carro novo")
cust_fabrica = float(input("Digite o valor do custo de fábrica do carro: "))
valor_final = cust_fabrica + ((cust_fabrica * 28) / 100) + ((cust_fabrica * 45) / 100)

print(f"O valor final do seu carro será de {valor_final}R$")