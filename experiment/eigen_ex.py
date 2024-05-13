import numpy as np 
  
# Define the matrix A 
A = np.array([
                [2.0, -1.0, 0.0], 
                [-1.0, 2.0, -1.0],
                [0.0, -1.0, 2.0]
              ]) 


  
# Choose the initial vector x 
x = np.array([[1, 2]]).T 
  
# Define the tolerance for the eigenvalue 
# and eigenvector approximations 
# (i.e. the maximum allowed difference between 
# the approximations and the actual values) 
tol = 1e-6
  
# Define the maximum number of iterations 
max_iter = 100
  
# Define the variable lam_prev to store the 
# previous approximation for the largest eigenvalue 
lam_prev = 0
  
# Iteratively improve the approximations 
# for the largest eigenvalue and eigenvector 
# using the power method 
for i in range(max_iter): 
    # Compute the updated approximation for the eigenvector 
    x = A @ x / np.linalg.norm(A @ x) 
  
    # Compute the updated approximation for the largest eigenvalue 
    lam = (x.T @ A @ x) / (x.T @ x) 
  
    # Check if the approximations have converged 
    if np.abs(lam - lam_prev) < tol: 
        break
  
    # Store the current approximation for the largest eigenvalue 
    lam_prev = lam 
  
# Print the approximations for the 
# largest eigenvalue and eigenvector 
print(float(lam)) 
print(x) 

