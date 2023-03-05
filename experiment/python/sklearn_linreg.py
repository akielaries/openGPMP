# testing regression using sklearn

import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split


data = pd.read_csv('../../data/school_scores.csv', index_col=False)
print(data)

X_train, X_test, y_train, y_test = train_test_split(data.drop('GPA',
                                                              axis=1),
                                                    data['GPA'],
                                                    test_size=0.2)

model = LinearRegression()
model.fit(X_train, y_train)

p_1995 = model.predict(pd.DataFrame({'year': [1995]}))
p_1997 = model.predict(pd.DataFrame({'year': [1997]}))
p_1999 = model.predict(pd.DataFrame({'year': [1999]}))
p_2001 = model.predict(pd.DataFrame({'year': [2001]}))
p_2003 = model.predict(pd.DataFrame({'year': [2003]}))
p_2005 = model.predict(pd.DataFrame({'year': [2005]}))
p_2007 = model.predict(pd.DataFrame({'year': [2007]}))
p_2016 = model.predict(pd.DataFrame({'year': [2016]}))
p_2017 = model.predict(pd.DataFrame({'year': [2017]}))

print("Predicted GPA at the year 1995: ", p_1995)
print("Predicted GPA at the year 1997: ", p_1997)
print("Predicted GPA at the year 1999: ", p_1999)
print("Predicted GPA at the year 2001: ", p_2001)
print("Predicted GPA at the year 2003: ", p_2003)
print("Predicted GPA at the year 2005: ", p_2005)
print("Predicted GPA at the year 2007: ", p_2007)
print("Predicted GPA at the year 2016: ", p_2016)
print("Predicted GPA at the year 2017: ", p_2017)
