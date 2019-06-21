import sys
import random

def f(coefficients, x):
	result = 0
	for degree, coefficient in enumerate(coefficients):
		result += coefficient * x ** degree
	return result + random.randint(-100, 100)

def main():
	caminhoArquivo = sys.argv[1]
	pN = int(sys.argv[2])
	degree = int(sys.argv[3]) + 1
	file = open("{}/pontos.dat".format(caminhoArquivo), "w")
	coefficients = []
	for i in range(degree):
		coefficients.append(random.randint(-10, 10))

	func = ""
	for degree, coefficient in enumerate(coefficients):
		func += f"+ {coefficient}x^{degree}"

	print(f"f(x) = {func}")

	for i in range(-pN, pN):
		file.write("{} {}\n".format(i, f(coefficients, i)))

	file.close()

main()