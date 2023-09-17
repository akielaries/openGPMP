import pandas as pd
from sklearn.linear_model import LinearRegression

# Step 1: Load the dataset
file_path = "../data/forrestfires.csv"
data = pd.read_csv(file_path)

# Step 2: Prepare the data
X = data[['Month']]  # Features (Year)
y = data['rain']      # Target variable (GPA)

# Step 3: Create and train a Linear Regression model
model = LinearRegression()
model.fit(X, y)

# Step 4: Make predictions for the specified years
years_to_predict = [1995, 1997, 1999, 2001, 2003, 2005, 2006, 2007, 2016, 2017]
predictions = model.predict(pd.DataFrame({'Year': years_to_predict}))

# Step 5: Display the predicted GPA for each year
for year, prediction in zip(years_to_predict, predictions):
    print(f'Year: {year}, Predicted GPA: {prediction:.2f}')

