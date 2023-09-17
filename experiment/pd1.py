import pandas as pd
import sys
import time


#@profile
def main():
    #pd.set_option('display.float_format', '{:.5f}'.format) 
    pd.set_option('display.min_rows', 30)

    # Load the dataset
    #print("RSS", process.memory_info()[0])
    #data = pd.read_csv('../data/forestfires.csv', usecols = ["month", "day", "temp", "wind"])
    start_time = time.time()

    #data = pd.read_csv('../data/Tetuan_power_consumption.csv', usecols = ["DateTime", "general diffuse flows", "Zone 1 Power Consumption"])
    data = pd.read_csv('../data/1m.csv')
    # Measure the end time
    end_time = time.time()

    # Calculate the execution time in milliseconds
    execution_time_ms = (end_time - start_time) * 1000

    print(f"execution time {execution_time_ms}")

    print(data.to_string())
    # Specify the zone you want to calculate power consumption for (e.g., Zone 1)
    #selected_zone = 'Zone 1 Power Consumption'

    #data = data.sort_values(by=["month", "day"])

    print(data)

    print(data.describe())
    print("FOO")

    print(data.info(memory_usage='deep'))

    print("Pandas mem usage", data.memory_usage(index=False, deep=True).sum())

    print("Sys pandas mem usage", sys.getsizeof(data))

    print("iterate")
    print(sum([sys.getsizeof(s) for s in data]) + data.memory_usage())

    # Calculate the total power consumption for each month and year for the selected zone
    #monthly_power_consumption = data.groupby(['Year', 'Month'])#[selected_zone]#.sum().reset_index()


    # Display the result with full numbers
    #print(monthly_power_consumption.first())

if __name__ == '__main__':
    main()
