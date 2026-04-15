"""Escrever um programa que solicite o nome e a idade de uma pessoa e
informe a sua classe eleitoral de acordo com os seguintes critérios:
a) Não eleitor: abaixo de 16 anos
b) Eleitor obrigatório: entre 18 e 65 anos
c) Eleitor facultativo: entre 16 e 17 anos e maior de 65 anos"""

nome = input("Qual o seu nome: ").title()
idade = int(input("Qual a sua idade: "))

if idade < 16:
    print("você não tem idade para votar")
if (idade >= 16 and idade < 18) or idade > 65:
    print("Eleitor facultativo: você não obrigado a votar")
else:
    print("Eleitor obrigatório: você é obrigado á votar")