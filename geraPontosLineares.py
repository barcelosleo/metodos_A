import sys
import random

def f(r1, r2, x):
	return r1*x + r2 + random.randint(-100, 100)

def main():
	caminhoArquivo = sys.argv[1]
	pN = int(sys.argv[2])
	file = open("{}/pontos.dat".format(caminhoArquivo), "w")
	r1 = random.randint(-10, 10)
	r2 = random.randint(-10, 10)

	print("f(x) = {}x^2 + {}".format(r1, r2))


	for i in range(0, pN):
		file.write("{} {}\n".format(i, f(r1, r2, i)))

	file.close()

main()