import numpy as np;
import matplotlib.pyplot as plt;

x = np.linspace(-np.pi,np.pi,256,endpoint=True)
y1,y2 = np.sin(x),np.cos(x)
plt.plot(x,y1)
plt.plot(x,y2)
plt.show()