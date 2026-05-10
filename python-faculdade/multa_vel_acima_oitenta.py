"""Escrever um programa que pergunte a velocidade do carro de um usuário.
Caso ultrapasse 80 km/h, exiba uma mensagem dizendo que o usuário foi
multado. Nesse caso, exiba o valor da multa, cobrando R$ 8,00 por km acima
de 80 km/h."""

vel = int(input("Qual era a sua velocidade: "))

if vel > 80:
    multa = (vel - 80) * 8
    print(f"Você passou da velocidade permitida, sua multa será de {multa}R$")
else:
    print("Tenha uma boa viagem!")