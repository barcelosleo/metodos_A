from scipy import integrate
import numpy as np
import matplotlib.pyplot as plt

def f(x):
	return np.exp(-x**2)*np.sin(x)

dx = 10e-5

x = np.arange(0, 2, dx)
y = f(x)

method  = None

while method not in ['S', 's', 'T', 't']:
	method = input("Método de integração? [T]rapézio [S]impson\n")
	if method not in ['S', 's', 'T', 't']:
		print("Método Inválido")

if method in ['S', 's']:
	I = integrate.simps(y,x)
else:
	I = integrate.trapz(y,x)


plt.plot(x, y, label='f(x)', color = 'black')
plt.fill_between(x, 0, y, alpha = 0.5)


plt.xlabel('x')
plt.ylabel('y')

# plt.title("Simple Plot")

# plt.legend("$$\\int_0^2 e^-x^2 sin(x) dx$$")
plt.text(0.25, 0.15, r"$\int_0^2 e^{-x^2} sin(x) dx \ \backsimeq \ $" + f"{round(I, 6)}\nMétodo: {'Simpson' if method in ['s', 'S'] else 'Trapézio'}")
plt.legend()

plt.savefig("figure.png")

plt.show()