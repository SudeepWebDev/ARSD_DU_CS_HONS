import numpy as np
import matplotlib.pyplot as plt


def f(x):
    return -10 * np.cos(np.pi * x - 2.2) + (x + 1.5) * x


# Define the range of x values
x = np.linspace(-5, 5, 1000)

# Plot the function
plt.plot(x, f(x))

# Find the global minimum
global_min = np.min(f(x))
global_min_x = x[np.argmin(f(x))]

# Plot the global minimum
plt.plot(global_min_x, global_min, "ro")

# Add labels and title
plt.xlabel("x")
plt.ylabel("f(x)")
plt.title("Global Optimal Solution of f(x)")

# Show the plot
plt.show()
