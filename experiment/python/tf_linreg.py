import tensorflow as tf
import pandas as pd

# Load the CSV file into a Pandas DataFrame
data = pd.read_csv('../../data/school_scores.csv')

# Split the data into training and testing sets
train_data = data[data['year'] < 2017]
test_data = data[data['year'] == 2017]

# Define the input and output columns
x_col = 'year'
y_col = 'GPA'

# Create a dataset from the training data
train_dataset = tf.data.Dataset.from_tensor_slices((train_data[x_col].values.reshape(-1, 1), train_data[y_col].values.reshape(-1, 1)))
train_dataset = train_dataset.batch(32)

# Define the linear regression model
model = tf.keras.Sequential([
    tf.keras.layers.Dense(1, input_shape=[1])
])

# Compile the model
model.compile(optimizer=tf.keras.optimizers.SGD(learning_rate=0.5), loss='mse')

# Train the model on the training data
model.fit(train_dataset, epochs=100)

# Evaluate the model on the test data
test_loss, test_pred = model.evaluate(test_data[x_col].values.reshape(-1, 1), test_data[y_col].values.reshape(-1, 1))
print('Test loss = {}'.format(test_loss))

# Print the predicted output for the year 2017
test_pred_2017 = model.predict([[2017]])
print('Predicted output for year 2017 = {}'.format(test_pred_2017[0][0]))

