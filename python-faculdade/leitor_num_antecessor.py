""" Escreva um programa para ler um valor (do teclado) e escrever (na tela) o
seu antecessor. """

from a_uteis_Dev import uteis

uteis.cabecalho("Digite um número e veja o seu antecessor")
num = int(input("Digite um número: "))
print(f"Você digitou o número {num}, seu antecessor é o número {num-1}")