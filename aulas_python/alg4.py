# coding: utf-8 #

import numpy as np
import matplotlib.pyplot as plt

x = []
y = []

with open("dados.dat", "r") as file:
	for line in file.readlines():
		xi, yi = line.split(' ')
		x.append(float(xi))
		y.append(float(yi))


plt.plot(x, y, 'o', label='Pontos Originais')

coef = np.polyfit(x, y, 1)

f = lambda x: x * coef[0] + coef[1]

plt.plot(range(10), [f(i) for i in range(10)], label='Fit')


# plt.xlabel('x label')
# plt.ylabel('y label')

# plt.title("Simple Plot")

plt.legend()

# plt.savefig("figure.png")

plt.show()

# for i in (data):