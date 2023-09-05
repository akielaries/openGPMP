import pandas as pd
pd.set_option('display.float_format', '{:.2f}'.format)  # Set the float format to display without scientific notation

# Load the dataset
data = pd.read_csv('../data/Tetuan_power_consumption.csv')
print(data)

# Convert the 'DateTime' column to a datetime object
data['DateTime'] = pd.to_datetime(data['DateTime'])

# Extract the month and year from the DateTime column
data['Month'] = data['DateTime'].dt.month
data['Year'] = data['DateTime'].dt.year

# Specify the zone you want to calculate power consumption for (e.g., Zone 1)
selected_zone = 'Zone 1 Power Consumption'

# Calculate the total power consumption for each month and year for the selected zone
monthly_power_consumption = data.groupby(['Year', 'Month'])[selected_zone].sum().reset_index()

# Display the result with full numbers
print(monthly_power_consumption)

