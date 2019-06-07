import sys

def mostraLista(lista):
	for i in lista:
		print(i)

def getFibonacci(max):
	lista = [0, 1, 1];

	for i in range(0, max):
		lista.append(lista[-1] + lista[-2])

	return lista

if __name__ == "__main__":
	mostraLista(getFibonacci(10 if not len(sys.argv) == 2 else int(sys.argv[1])))