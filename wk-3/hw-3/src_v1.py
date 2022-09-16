# lib for retrieving src file from web
import urllib.request
# lib for reading files on OS
import os
# lib used for copying src file info into destination
import shutil
import pandas as pd
import plotnine as p9
import numpy as np
# could not figure out how to calculate the mode of a list, using mode from lib
from statistics import mode
# *<---REMOVE B4 SUB--->*
import glob # find all files in dir w/ *
import warnings # silence warnings while developing 
import sklearn
from sklearn.model_selection import KFold #train/test splits
from sklearn.model_selection import GridSearchCV #selecting best # of neighbors
from sklearn.neighbors import KNeighborsClassifier #nearest_neighbors prediction.
from sklearn.pipeline import make_pipeline # increase iteration sz
from sklearn.preprocessing import StandardScaler # 
from sklearn.linear_model import LogisticRegression

# directory for data files
data_dir = 'data/'
path_files = glob.glob('data/' + '*')
# our src files we want to download; test set
test_url = 'https://hastie.su.domains/ElemStatLearn/datasets/zip.test.gz'
test_file = 'data/zip.test.gz'
# train set
train_url = 'https://hastie.su.domains/ElemStatLearn/datasets/zip.train.gz'
train_file = 'data/zip.train.gz'
# spam set
spam_url = 'https://hastie.su.domains/ElemStatLearn/datasets/spam.data'
spam_file = 'data/spam.data'

# number of columns in test file (257) count from zero
conc_cols = 257 
# number of columns in spam file (56) count from zero
spam_cols = 57
# split our data set into train and test sets
kf = KFold(n_splits=3, shuffle=True, random_state=1)
# increase the max iteration from default 100
pipe = make_pipeline(StandardScaler(), LogisticRegression(max_iter=1000))

""" 
method to download specified files. call from main, pass in
src files to retrieve
"""
def retrieve(src_file, src_url):
    # lets store these files in a directory, create /data if DNE
    if not os.path.exists(data_dir):
        os.makedirs(data_dir)
    
    """
    check if a file exists in the current directory
    retrieve a file given the url
    """
    if not os.path.isfile(src_file):
        urllib.request.urlretrieve(src_url, src_file)

        print("Downloading src file into " + src_file + " from " + src_url + 
              "...\n")
    
    else:
        print(src_file + " already exists in this folder...continuing anyway\n")


"""
MyKNN class, according to *.org guideline, that *should* work just like 
sklearn.neighbors.KNeighborsClassifier
"""
class MyKNN:
    """
    instantiate neighbors param stored as an attribute of our instance
        __init__: recieves constructors args initializing new obj
        self: instance of class for attribute manipulation, always first
        attribute of instance. convention ! keyword
        member
    """
    def __init__(self, n_neighbors):
        # init neighbors attribute of instance
        self.nearest = n_neighbors

    """
    fit method with X=train_features, y=train_labels, storing data as 
    attributes of our instance
        features: input data
        label: output data based on input
    """
    def fit(self, X, y): 
        # store feats/labs in respective lists; can do for loop for many members
        self.train_features = []
        self.train_labels = []
        self.train_features = X
        self.train_labels = y

    """
    compute binary vector of predicted class label
        X = test_features
    """
    def predict(self, test_features):
        # traverse each test data row; features
        for i in  range(len(test_features)):
            # compute distances with all of train data
            #np.diff()

"""
MyCV class, according to *.org guideline, that *should* work just like
sklearn.model_selection.GridSearchCV. this class should perform
best parameter selection thru cross-validation for any estimator

*<--NOTE-->*: nothing in this class should be specific to the nearest 
neighbors algorithm! It should not have any reference to “n_neighbors” in 
the class definition. These methods are sort of copied from the class MyKNN
"""
class MyCV:

    def __init__(self, estimator, param_grid, cv):
        self.train_features = []
        self.train_labels = []

    def fit(self, X, y):

    def predict(self, test_features):


"""
method for removing data directory when program exits
"""
def remove():
    shutil.rmtree(data_dir)
    print("Removing: " + data_dir + "...\n")


def main():
    # supress warnings
    warnings.filterwarnings('ignore')

    # retrieve our data files using retrieve function
    retrieve(test_file, test_url)
    retrieve(train_file, train_url)
    retrieve(spam_file, spam_url)

    # remove data files on exit from data folder
    remove()

# run main
if __name__ == '__main__':
    main()


