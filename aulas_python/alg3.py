# coding: utf-8 #

import numpy as np

A = np.array([
	[1,1,1],
	[1,3,3],
	[1,3,6],
])

b = np.array([2,0,3])

x, y, z = np.linalg.inv(A).dot(b)

print(f"X = {x}\nY = {y}\nZ = {z}")