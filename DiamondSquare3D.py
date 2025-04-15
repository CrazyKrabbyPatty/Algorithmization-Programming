import numpy as np
import random
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def diamond_square(size, roughness):
    height_map = np.zeros((size, size))

    # Инициализируем 
    height_map[0, 0] = random.random()
    height_map[0, size - 1] = random.random()
    height_map[size - 1, 0] = random.random()
    height_map[size - 1, size - 1] = random.random()
    
    step_size = size - 1
    while step_size > 1:
        half_step = step_size // 2
        
        # Diamond
        for x in range(0, size - 1, step_size):
            for y in range(0, size - 1, step_size):
                center = (x + half_step, y + half_step)
                avg = (height_map[x, y] + height_map[x + step_size, y] +
                       height_map[x, y + step_size] + height_map[x + step_size, y + step_size]) / 4.0
                height_map[center] = avg + random.uniform(-roughness, roughness)
        
        # Square
        for x in range(0, size, half_step):
            for y in range((x + half_step) % step_size, size, step_size):
                avg = 0.0
                count = 0
                if x - half_step >= 0:
                    avg += height_map[x - half_step, y]
                    count += 1
                if x + half_step < size:
                    avg += height_map[x + half_step, y]
                    count += 1
                if y - half_step >= 0:
                    avg += height_map[x, y - half_step]
                    count += 1
                if y + half_step < size:
                    avg += height_map[x, y + half_step]
                    count += 1
                
                height_map[x, y] = (avg / count) + random.uniform(-roughness, roughness)
        
        step_size //= 2
        roughness /= 2
    
    return height_map

def plot_3d(height_map):
    size = height_map.shape[0]
    x = np.linspace(0, 1, size)
    y = np.linspace(0, 1, size)
    X, Y = np.meshgrid(x, y)

    fig = plt.figure(figsize=(10, 7))
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_surface(X, Y, height_map, cmap='terrain', edgecolor='none')

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Height')
    ax.set_title('3D Diamond-Square Terrain')

    plt.show()

# Генерация карты визуализация
size = 65  # Степень должна быть степению двойки + 1 (..., 65, 257, 513, ...)
roughness = 1.0  
height_map = diamond_square(size, roughness)
plot_3d(height_map)