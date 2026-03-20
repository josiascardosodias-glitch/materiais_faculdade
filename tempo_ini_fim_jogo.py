""" Escrever um programa que leia o tempo inicial e final de uma partida de tênis no formato hor:min:seg e informe o tempo de duração da mesma no formato
hor:min:seg. """

from a_uteis_Dev import uteis

# variaveis que serão usadas no print
hora = min = seg = 0
uteis.cabecalho("Vamos descobrir qual foi o tempo de duração de uma partida de tênis")

# Variaveis que receberão os horarios de inicio e final do jogo
hora_ini = input("Que horas eram no inicio da partida (Hora:Min:Seg): ") 
hora_fim = input("Que horas eram no fim da partida (Hora:Min:seg): ")

# Desmembramos o horario recebido em três variaveis e tranformamos o tipo delas de string para int
hora1, min1, seg1 = map(int, hora_ini.split(":"))
hora2, min2, seg2 = map(int, hora_fim.split(":"))

# Somamos e convertemos os dois horarios em segundos
temp_total_ini = (hora1 * 3600) + (min1 * 60) + seg1
temp_total_fim = (hora2 * 3600) + (min2 * 60) + seg2

# Utilizamos os dois tempos totais para saber a diferença de tempo do jogo (ainda em segundos)
temp_total_jogo = temp_total_fim - temp_total_ini

# Convertemos a diferença entre os jogos em hora, min, e seg e guardamos essas informações nas variaveis do inico do programa
while temp_total_jogo != 0:
    seg += 1
    temp_total_jogo -= 1
    if seg == 60:
        min += 1
        seg -= 60
        if min == 60:
            hora += 1
            min -= 60
            
print(f"A duração total da partida foi de {hora}:{min}:{seg}")