cont_imp = cont_num = cont_imp_n = 0

cont = ''
while cont != 0:
    cont = int(input("Digite um número do teclado: "))
    cont_num += 1
    if cont % 2 == 1:
        cont_imp += cont
        cont_imp_n += 1

media_imp = cont_imp / cont_imp_n
print(f"A quantidade de números digitados foram {cont_num - 1} e a média dos números impares foi de {media_imp:.2f}")