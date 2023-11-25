import pandas as pd
import matplotlib.pyplot as plt

# Load the dataset
file_path = "../data/forestfires.csv"  # Replace with the actual file path
data = pd.read_csv(file_path)

# Extract X and Y coordinates
X = data['X']
Y = data['Y']

# Create a scatterplot
plt.figure(figsize=(8, 6))  # Adjust the figure size as needed
plt.scatter(X, Y, c='red', marker='o', alpha=0.5)
plt.title('Forest Fire Locations')
plt.xlabel('X Coordinate')
plt.ylabel('Y Coordinate')
plt.grid(True)
plt.show()

