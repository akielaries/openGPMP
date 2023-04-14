# Tensorflow linear regression trial

import tensorflow as tf
import pandas as pd
from sklearn.model_selection import train_test_split

data = pd.read_csv('../../data/school_scores.csv', index_col=False)
print(data)

X_train, X_test, y_train, y_test = train_test_split(data.drop('GPA',
                                                              axis=1),
                                                    data['GPA'],
                                                    test_size=0.2)

print(X_train)

