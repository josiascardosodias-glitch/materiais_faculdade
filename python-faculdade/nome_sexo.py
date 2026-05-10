"""Escrever um programa que leia o nome e o sexo de uma pessoa e informe se
ela é homem ou mulher."""

nome = input("Digite o seu nome: ").title()
sexo = input("Qual o seu sexo M (homem) / F (mulher): ").upper()

if sexo == "M":
    print(f"Olá {nome}, Você é um homem")
if sexo == "F":
    print(f"Olá {nome}, Você é uma mulher")