alu = int(input("Quantos alunos tem na turma: "))

cont = 0
while cont < alu:
    nome = input("Digite seu nome: ").title()
    n1 = int(input("Qual foi a sua primeira nota: "))
    n2 = int(input("Qual foi a sua segunda nota: "))
    media = (n1 + n2) / 2
    print(f"O aluno {nome} teve média {media:.2f}")
    cont += 1