# coding: utf-8 #

import numpy as np

A = np.array([
	[7,2,1],
	[0,3,-1],
	[-3,4,-2],
])

b = np.array([21, 5, -1])

b1 = np.linalg.inv(A).dot(b)
b2 = np.linalg.solve(A, b)

print(b1)
print(b2)