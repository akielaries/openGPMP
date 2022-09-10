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
test_url = 'https://github.com/tdhock/cs499-599-fall-2022/tree/main/data/zip.test.gz'
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
        print("Downloading " + src_file + " from" + src_url + "...\n")

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
"""
#def init_df(src):
    # dict for our source files
    #src_dict = {}
    # create empty list to store dataframes in

    # traverse thru our src files
    #for i in range(len(src)):
        # read in downloaded src file as a pandas dataframe
        # src[name] = pd.read_csv(src, header=None, sep=" ")
        #df = pd.
        # print name of our dataframe by traversing thru our dictionary
        #for name, df in src_dict.items():
        #    print(src_dict)

    
    # read in downloaded src file as a pandas dataframe
    # df2 = pd.read_csv(src2, header=None, sep=" ")
    
    # remove any rows which have non-01 labels
    # df1[0] = df1[0].astype(int)
    # df1 = df1[df1[0].isin([0, 1])]
    # drop empty cols
    # df1 = df1.drop(columns=[test_cols])

# def plot():

def main():
    # list of src files; we want to minimize reusing code
    src_files = [test_file, spam_file]
    # list of src URLS
    src_urls = [test_url, spam_url]
    
    # retrieve our source files. Spam and zip. 
    retrieve(test_file, test_url)
    retrieve(spam_file, spam_url)

    # call method to initialize our data frames 
    #init_df(test_file, spam_file)
    #init_df(src_files)
    
    # initialize dictionary from our two dataframes
    # init_dict()

if __name__ == '__main__':
    # run main
    main()

