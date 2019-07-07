# coding: utf-8 #

import numpy as np
import matplotlib.pyplot as plt

x = []
y = []

arquivo = input("Nome do arquivo a ser lido: [dados.dat]") or "dados.dat"
colunas = input("Colunas de onde serão lidos os valores: [2 3]") or "2 3"
cx, cy = [int(c) - 1 for c in colunas.split()]

with open(arquivo, "r") as file:
	for line in file.readlines():
		linha = line.split()
		x.append(float(linha[cx]))
		y.append(float(linha[cy]))

plt.plot(x, y, 'o', label='Pontos Originais')
coef = np.polyfit(x, y, 1)

f = lambda x: x * coef[0] + coef[1]

labelFit = f"f(x) = {round(coef[0], 1)}x {'-' if coef[1] < 0 else '+'} {round(abs(coef[1]), 1)}"

plt.plot(range(10), [f(i) for i in range(round(x[0]), round(x[-1]))], label=labelFit)

plt.xlabel('x')
plt.ylabel('y')

plt.legend()

plt.show()
