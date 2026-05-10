tur = float(input("Quantos alunos tem na turma: "))

cont = soma = 0
while cont < tur:
    nome = input("Qual o seu nome: ").title()
    n1 = float(input(f"Olá {nome}, qual foi a sua nota na prova: "))
    soma += n1
    cont += 1

media = (n1) / tur
print(f"A turma teve média {media:.2f}")
print(cont)