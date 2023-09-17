import pandas as pd
#pd.set_option('display.float_format', '{:.5f}'.format) 
pd.set_option('display.min_rows', 30) 

import time
start_time = time.time()

#data = pd.read_csv('../data/Tetuan_power_consumption.csv',
#                   usecols = ["DateTime", 
#                              "general diffuse flows", 
#                              "Zone 1 Power Consumption"])

data = pd.read_csv('../data/forestfires.csv', usecols = ["month", "day", "temp", "wind"])

# Measure the end time
end_time = time.time()

# Calculate the execution time in milliseconds
execution_time_ms = (end_time - start_time) * 1000

print(f"execution time {execution_time_ms}")

print(data)

