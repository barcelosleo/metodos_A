import random

def f(r1, r2, x):
	if random.random() > 0.5:
		s = -1
	else:
		s = 1
	return r1*x + r2 + random.random()*10*s;

def main():
	file = open("pontos.dat", "w")
	pN = 100
	r1 = random.random() / random.random()**2
	r2 = random.random()

	for i in range(0, pN):
		file.write("{} {}\n".format(i, f(r1, r2, i)))
		print("{} {}".format(i, f(r1, r2, i)))

	file.close()

main()