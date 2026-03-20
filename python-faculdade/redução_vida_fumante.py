""" Escrever um programa para calcular a redução do tempo de vida de um
fumante. Perguntar a quantidade de cigarros fumados por dia e quantos anos
ele já fumou. Considerar que um fumante perde 10 minutos de vida a cada
cigarro, calcular quantos dias de vida um fumante perderá. Exibir o total em
dias com apenas 2 casas decimais. """

from a_uteis_Dev import uteis

uteis.cabecalho("Vamos descobrir quatos dias de vida você já perdeu por causa do cigarro")
quant_cigarros = int(input("Quantos cigarros você fuma por dia: "))
tempo_fumando  = int(input("À quantos anos você fuma: "))
dias_perdidos = (((quant_cigarros * 365 * tempo_fumando) * 10 ) / 1440)

print(f"Você perdeu um total de {dias_perdidos:.2f} dias perdidos de vida")