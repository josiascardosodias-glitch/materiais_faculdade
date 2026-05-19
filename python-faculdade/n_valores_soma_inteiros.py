n = int(input("Digite a quantidade de números que que deseja calcular: "))

soma = i = 0
if n == 0:
    print("Valor impossivel de calcular")
else:
    while i < n:
        num = int(input("Digite um número: "))
        soma = soma + num
        i = i + 1
print(soma)