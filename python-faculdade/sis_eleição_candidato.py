print("=== SISTEMA ELEITORAL ===")

op = -1
c1 = c2 = c3 = nulo = branco = totVotos = perc1 = perc2 = perc3 = 0

while op != 0:
    print("""
Escolha uma das opções de voto:
[1] Candidato Padre.
[2] Candidato Carlos.
[3] Candidato Luiza.
[4] Votar Nulo.
[5] Votar em Branco.
[0] Sair.""")
    op = int(input("Digite aqui: "))
    if op < 6:
        totVotos += 1
    if op == 1:
        c1 += 1
    elif op == 2:
        c2 += 1
    elif op == 3:
        c3 += 1
    elif op == 4:
        nulo += 1
    elif op == 5:
        branco += 1
    elif op == 0:
        print("Saindo...")
    else:
        print("Valor inválido")
print("==" * 10 + " Resultado da eleição " + "==" * 10)
if c1 > c2 and c1 > c3:
    print(f"O canditado com mais votos foi: Candidato Padre com: {c1} votos")
elif c2 > c1 and c2 > c3:
    print(f"O canditado com mais votos foi: Candidato Carlos com: {c2} votos")
elif c3 > c1 and c3 > c2:
    print(f"O canditado com mais votos foi: Candidato Luiza com: {c3} votos")
else:
    print("Houve empate entre os candidatos")
resVotos = 10525 - (totVotos - 1)
perc1 = c1 / totVotos * 100
perc2 = c2 / totVotos * 100
perc3 = c3 / totVotos * 100
print(f"""Total de votos em branco: {branco}
Total de votos nulos: {nulo}
Total de candidatos que decidiram não votar foi de {resVotos}
Percentual de votos de cada candidato:
Candidato 1: {perc1:.2f} %
Candidato 2: {perc2:.2f} %
Candidato 3: {perc3:.2f} %""")