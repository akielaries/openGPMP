import pandas as pd
#pd.set_option('display.float_format', '{:.5f}'.format) 
pd.set_option('display.min_rows', 30)

# Load the dataset
data = pd.read_csv('../data/forestfires.csv', usecols = ["month", "day", "temp", "wind"])

print(data)
# Specify the zone you want to calculate power consumption for (e.g., Zone 1)
#selected_zone = 'Zone 1 Power Consumption'

data = data.sort_values(by=["month", "day"])

print(data)

print(data.describe())

# Calculate the total power consumption for each month and year for the selected zone
#monthly_power_consumption = data.groupby(['Year', 'Month'])#[selected_zone]#.sum().reset_index()


# Display the result with full numbers
#print(monthly_power_consumption.first())

