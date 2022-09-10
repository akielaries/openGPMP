import pandas as pd
import numpy as np
import plotnine as p9


companies = ['AA', 'AAPL', 'BA', 'YHOO']

d = {}
for name in companies:
    d[name] = pd.DataFrame()
#    print(list(companies).index('AA'))

print(d['AA'])


#print(d)




