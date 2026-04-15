"""Escrever um programa que solicite o nome do funcionário de uma empresa,
seu salário e o valor do salário mínimo. Calcular o novo salário do funcionário
conforme os seguintes reajustes fornecidos pela empresa (exibir o nome do
funcionário com o seu novo salário):
a) 50% para aqueles que ganham menos do que 3 salários mínimos;
b) 20% para aqueles que ganham entre 3 e 10 salários mínimos;
c) 15% para os demais funcionários."""

nome = input("Digite seu nome: ").title()
sal = float(input("Qual o seu salário atual: "))
sal_min = float(input("Qaul o salário minímo atual no Brasil: "))

if sal < (sal_min * 3):
    sal = sal * 1.50

elif sal > (sal_min * 3) or sal < (sal_min * 10):
    sal = sal * 1.20

else:
    sal = sal * 1.15

print(f"Novo salário de {nome} : {sal:.2f}R$")