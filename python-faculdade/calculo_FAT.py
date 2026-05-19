n = int(input("Digite a quantidade de números que você quer percorrer no fatorial: "))

fat = con = 1
i = 0
if n == 0:
    print("Erro: valor impossivel de calcular")
else:
    while i < n:
        i = i + 1
        fat = fat * i
print(f"FAT({i}) {fat}")