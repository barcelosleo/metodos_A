# coding: utf-8 #

import numpy as np

m = [
	[7,2,1],
	[0,3,-1],
	[-3,4,-2],
]

print(f"Matriz: {np.array(m)}")

print(f"Inversa: {np.linalg.inv(m)}")

print(f"Determinante: {np.linalg.det(m)}")

traco = 0

for i in range(len(m)):
	for j in range(len(m[i])):
		traco += m[i][j] if i == j else 0

print(f"Traço: {traco}")


