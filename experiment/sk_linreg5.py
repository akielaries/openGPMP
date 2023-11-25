import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error
import numpy as np

# Step 1: Load the dataset
data = pd.read_csv('../data/Tetuan_power_consumption.csv')

# Convert the 'DateTime' column to a datetime object
data['DateTime'] = pd.to_datetime(data['DateTime'])

# Step 2: Extract month and calculate monthly power consumption for Zone 1
data['Month'] = data['DateTime'].dt.month
monthly_power_consumption = data.groupby(['Month'])['Zone 1 Power Consumption'].sum()

# Step 3: Prepare the data for training and testing
# Create a DataFrame for training with columns: Month, Power Consumption
# We are considering data from January to November for 2017 for training
train_data = pd.DataFrame({'Month': range(1, 12), 'Power Consumption': monthly_power_consumption[:-1]})

# Create a DataFrame for testing with columns: Month
# We want to predict December's power consumption in 2017
test_data = pd.DataFrame({'Month': [12]})

# Step 4: Train a predictive model and make predictions for 2018
X_train = train_data[['Month']]
y_train = train_data['Power Consumption']
X_test = test_data[['Month']]

# Initialize and fit a Linear Regression model
model = LinearRegression()
model.fit(X_train, y_train)

# Predict power consumption for December 2018
predicted_power_2018 = model.predict(X_test)

# Display the predictions
print("Predicted Power Consumption for December 2018 (Zone 1):", predicted_power_2018[0])

