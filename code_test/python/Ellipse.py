#input
import numpy as np
import matplotlib.pyplot as plt

a = 960
b = 768

e = np.sqrt(a**2 - b**2) / a

theta = np.linspace(0, 2*np.pi, 129)

x = a * np.cos(theta)
y = b * np.sin(theta)

fig = plt.figure(figsize=(6, 6))
ax = fig.add_subplot(111)
ax.grid()
ax.set_aspect('equal')
ax.set_title("Ellipse (e={:.2f})".format(e), fontsize=16)
ax.set_xlabel("x", fontsize=14)
ax.set_ylabel("y", fontsize=14)
ax.set_xlim(-960, 960)
ax.set_ylim(-768, 768)

ax.plot(x, y, color="red")

# plt.show()
#  UserWarning: Matplotlib is currently using agg, which is a non-GUI backend, so cannot show the figure.

plt.savefig("./Ellipse_0")