import matplotlib.pyplot as plt
import numpy as np

# Define constraint equations
x = np.linspace(0, 10, 1000)
y1 = (6 - 2 * x) / 3
y2 = (9 - 3 * x) / 2

# Plot constraint lines
plt.plot(x, y1, label='2x + 3y <= 6')
plt.plot(x, y2, label='3x + 2y <= 9')

# Shade feasible region
y3 = np.maximum(y1, y2)
plt.fill_between(x, y3, 0, where=(x >= 0) & (y1 >= 0) & (y2 >= 0), alpha=0.2)

# Define objective function
z = lambda x, y: 5 * x + 4 * y

# Evaluate objective function at corner points
corners = [(0, 0), (0, 3), (1.8, 1.2), (3, 0)]
values = [z(*corner) for corner in corners]

# Plot corner points and optimal solution
plt.scatter(*zip(*corners))
plt.annotate(f'Optimal solution: {max(values)}', corners[values.index(max(values))])

# Add labels and legend
plt.xlabel('x')
plt.ylabel('y')
plt.title('Graphical Solution of LPP')
plt.legend()

# Show plot
plt.show()
