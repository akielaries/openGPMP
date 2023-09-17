import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

print("using sklearn LinearRegression class")
# Step 1: Load the dataset
file_path = "../data/school_scores.csv"
data = pd.read_csv(file_path)

# Step 2: Prepare the data
X = data[['Year']]  # Features (Year)
y = data['GPA']      # Target variable (GPA)

# Step 3: Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42,
                                                    shuffle=False)

# Step 4: Create and train a Linear Regression model on the training data
model = LinearRegression()
model.fit(X_train, y_train)

# Step 5: Make predictions on the testing data
y_pred = model.predict(X_test)

# Step 6: Evaluate the model's performance
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

print(f"Mean Squared Error: {mse:.6f}")
print(f"R-squared (R2) Score: {r2:.6f}")

# Step 7: Make predictions for the specified years
#years_to_predict = [1995, 1997, 1999, 2001, 2003, 2005, 2006, 2007, 2016, 2017]
years_to_predict = [2007]
predictions = model.predict(pd.DataFrame({'Year': years_to_predict}))

# Step 8: Display the predicted GPA for each year
for year, prediction in zip(years_to_predict, predictions):
    print(f'Year: {year}, Predicted GPA: {prediction:.6f}')
# Step 7: Get the slope (m) and intercept (b) of the best-fit line
slope = model.coef_[0]
intercept = model.intercept_

# Step 8: Print the equation of the best-fit line (y = mx + b)
print(f"Equation of the best-fit line: y = {slope:.6f}x + {intercept:.6f}")

