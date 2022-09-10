# lib for retrieving src file from web
import urllib.request
# lib for reading files on OS
import os
# lib used for copying src file info into destination
import shutil
import pandas as pd
import plotnine as p9
import numpy as np
from sklearn.model_selection import KFold #train/test splits
from sklearn.model_selection import GridSearchCV #selecting best # of neighbors
from sklearn.neighbors import KNeighborsClassifier #nearest_neighbors prediction.
from sklearn.pipeline import make_pipeline # increase iteration sz
from sklearn.preprocessing import StandardScaler # 
from sklearn.linear_model import LogisticRegression

# our src files we want to download. spam and test sets
test_url = 'https://github.com/tdhock/cs570-spring-2022/raw/master/data/zip.test.gz'
test_file = 'zip.test.gz'
spam_url = 'https://github.com/tdhock/cs499-599-fall-2022/tree/main/data/spam.data'
spam_file = 'spam.data'

# number of columns in test file (257) count from zero
test_cols = 257
# number of columns in spam file (56) count from zero
spam_cols = 57
# dataframe list
test_acc_df_list = []

""" 
our last assignment was only downloading 1 file, to adhere to guidelines and 
avoid repeatable code, created a method we will use to retrieve multiple files. 
"""
def retrieve(src_file, src_url):
    """
    check if a file exists in the current directory
    retrieve a file given the url
    """
    if not os.path.isfile(src_file):
        urllib.request.urlretrieve(src_url, src_file)
        print("Downloading " + src_file + " from " + src_url + "...\n")

    else:
        print(src_file + " already exists in this folder...continuing anyway\n")

"""
since we are initializing multiple dataframes for out multiple
sources of data, I wanted to try and minimize repeating code. 
this method will
    - take in src file 
    - create a dataframe
    - drop specified rows of the src file
    - convert our data into numpy 
Hopefully this is allowed!
    notice: (am repeating code) but spent too much time creating traveral
    type solution going over a list of src_files and src_urls.
    Wanted to seperate file into some seperate functions for the sake of 
    readability.
"""
def df_init(src1, src2):#, spam_file):#, src1_cols, src2_cols):
    # read in downloaded src file as a pandas dataframe
    # seperate dataframes because different manipulations will be done
    df1 = pd.read_csv(src1, header=None, sep=" ")
    df2 = pd.read_csv(src2, header=None, sep='delimiter')

    # remove any rows which have non-01 labels
    df1[0] = df1[0].astype(int)
    # df2[0] = df2[0].astype(int)
    df1 = df1[df1[0].isin([0, 1])]
    # df2 = df2[df2[0].isin([0, 1])]

    # drop empty cols for specifiec rows 
    #df1 = df1.drop(columns=[src1_cols])
    #df2 = df2.drop(columns=[src2_cols])
    
    # initialize and declare vectors for our df columns
    df1_label = df1[0]
    df2_label = df2[spam_cols]
    
    """
    convert dataframe to numpy array exlcuding the first column; iloc for row
    and col specifying. Previous assignment moved from 1->end, this one will go
    from 1-> the specified value from our column definitions
    """
    df1 = df1.iloc[:,1:257].to_numpy()
    df2 = df2.iloc[:,1:57].to_numpy()
    
    print(df1)
    print(df2)
    
"""
an attempt to modularize our code to improve readibility, this method 
will make a ggplot to visually examine which learning algorithm is 
best for each data set
"""
# def plot():

def main():
    # list of src files; we want to minimize reusing code
    #src_files = [test_file, spam_file]
    # list of src URLS
    #src_urls = [test_url, spam_url]
    
    # retrieve our source files. Spam and zip. 
    retrieve(test_file, test_url)
    retrieve(spam_file, spam_url)

    # call method to initialize our data frames, convert to numpy arrays, 
    df_init(test_file, spam_file)#, spam_file)#, test_cols, spam_cols)
    

if __name__ == '__main__':
    # run main
    main()

