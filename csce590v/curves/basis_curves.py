#*********************************
# Plot basis curves for spline segments
# Manuel Serna-Aguilera
#*********************************

import numpy as np
import matplotlib.pyplot as plt
import sys

curve = sys.argv[1]
curve_name = ''

x_min = 0
x_max = 1
y_min = 0
y_max = 1

t = np.linspace(x_min, x_max, num=100, endpoint=True) # define domain

if curve == 'bezier':
	curve_name = 'Bezier Curve'
	y0 = (1-t)**3
	y1 = t**3
	y2 = 3 * (1-t)**2 * t
	y3 = 3 * (1-t) * t**2
	
	plt.plot(t, y0, '-b', label=r'$y0 = (1-t)^3$')
	plt.plot(t, y1, '-r', label=r'$y1 = t^3$')
	plt.plot(t, y2, '-c', label=r'$y2 = 3(1-t)^2t$')
	plt.plot(t, y3, '-m', label=r'$y3 = 3(1-t)t^2$')

# Plot polynomials
axes = plt.gca()
axes.set_xlim([x_min, x_max])
axes.set_ylim([y_min, y_max])
plt.title(curve_name)
plt.legend(loc='upper left')
plt.show()

