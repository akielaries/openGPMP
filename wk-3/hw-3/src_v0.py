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
import warnings # silence plethora of warning we get when running this
from statistics import mode
import sklearn
from sklearn.model_selection import KFold #train/test splits
from sklearn.model_selection import GridSearchCV #selecting best # of neighbors
from sklearn.neighbors import KNeighborsClassifier #nearest_neighbors prediction.
from sklearn.pipeline import make_pipeline # increase iteration sz
from sklearn.preprocessing import StandardScaler # 
from sklearn.linear_model import LogisticRegression

# our src files we want to download. spam and test sets
test_url = 'https://hastie.su.domains/ElemStatLearn/datasets/zip.test.gz'
test_file = 'zip.test.gz'
train_url = 'https://hastie.su.domains/ElemStatLearn/datasets/zip.train.gz'
train_file = 'zip.train.gz'
spam_url = 'https://hastie.su.domains/ElemStatLearn/datasets/spam.data'
spam_file = 'spam.data'

# number of columns in test file (257) count from zero
conc_cols = 257
# number of columns in spam file (56) count from zero
spam_cols = 57

kf = KFold(n_splits=3, shuffle=True, random_state=1)

# increase the max iteration from default 100
pipe = make_pipeline(StandardScaler(), LogisticRegression(max_iter=1000))

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
def df_init(src_test, src_train, src_spam, data_dict):
    # read in downloaded src file as a pandas dataframe
    # seperate dataframes because different manipulations will be done
    df_test = pd.read_csv(src_test, header=None, sep=" ")
    df_train = pd.read_csv(src_train, header=None, sep=" ")
    df_spam = pd.read_csv(src_spam, header=None, sep=" ")
    
    # reassign concatenated test and train frame
    df_conc = pd.concat([df_test, df_train])

    # remove any rows which have non-01 labels
    df_conc[0] = df_conc[0].astype(int)
    df_spam[0] = df_spam[0].astype(int)
    df_conc = df_conc[df_conc[0].isin([0, 1])]
    df_spam = df_spam[df_spam[0].isin([0, 1])]
    
    # initialize and convert outputs to a label vector
    df_conc_labels = df_conc[0]
    df_spam_labels = df_spam[spam_cols]
    """
    Convert our dataframe to a dictionary with numpy array exlcuding the 
    first column; iloc for row and col specifying. 
    """
    
    data_dict = {
        "test":(df_conc.loc[:,1:conc_cols-1].to_numpy(), df_conc[0]),
        "spam":(df_spam.loc[:,spam_cols-1:].to_numpy(), df_spam[0]),
    }
    # print our dataframes to visualize in tabular form
    print(df_conc)
    print(df_spam)
    print(data_dict)
    return df_conc, df_spam, data_dict
    #print(df_test, df_train, df_spam, data_dict)

"""
algorithm shown in class and from our demo.
"""
def train(data_dict):
    test_acc_df_list = []
    # increase the max iteration from default 100
    pipe = make_pipeline(StandardScaler(), LogisticRegression(max_iter=1000))

    for data_set, (input_mat, output_vec) in data_dict.items():
        print(data_set)
    
        # kf = KFold(n_splits=3, shuffle=True, random_state=1)
    
        for fold_id, indices in enumerate(kf.split(input_mat)):
            print(fold_id)
            index_dict = dict(zip(["train","test"], indices))
            param_dicts = [{'n_neighbors':[x]} for x in range(1, 21)]
    
            # does subtrain/validation splits.
            clf = GridSearchCV(KNeighborsClassifier(), param_dicts)
            # copy above for linear model. call cv=5 in initial pipe was not
            # recognized; try a call here
            linear_model = sklearn.linear_model.LogisticRegressionCV(cv=5)
            set_data_dict = {}
    
            for set_name, index_vec in index_dict.items():
                set_data_dict[set_name] = ( 
                    input_mat [ index_vec ],
                    output_vec.iloc[index_vec]
                    )   
            # * is unpacking a tuple to use as the different positional arguments
            # clf.fit(set_data_dict["train"][0], set_data_dict["train"][1])
            # train models and stub out linear_model
            clf.fit(*set_data_dict["train"])
            # method 2: dict instead of tuple.
            set_data_dict = {}

            for set_name, index_vec in index_dict.items():
                set_data_dict[set_name] = { 
                    "X":input_mat[index_vec],
                    "y":output_vec.iloc[index_vec]
                    }   
            # ** is unpacking a dict to use as the named arguments
            # train models and stub out linear_model and create algo for finding 
            # mode
            # clf.fit(X=set_data_dict["train"]["X"], y=set_data_dict["train"]["y"]])
            clf.fit(**set_data_dict["train"])
            #mode = max(set(output_vec))
            featureless_model = mode(output_vec)
            linear_model.fit(**set_data_dict["train"])
            
            clf.best_params_
    
            cv_df = pd.DataFrame(clf.cv_results_)
            cv_df.loc[:,["param_n_neighbors","mean_test_score"]]
            
            pred_dict = { 
                "nearest_neighbors":clf.predict(set_data_dict["test"]["X"]),
                #TODO add featureless and linear_model.
                "featureless": featureless_model,
                "linear_model": linear_model.predict(set_data_dict["test"]["X"])
                }
    
            for algorithm, pred_vec in pred_dict.items():
                test_acc_dict = { 
                    "test_accuracy_percentage":(
                        pred_vec == set_data_dict["test"]["y"]).mean()*100,
                    "data_set":data_set,
                    "fold_id":fold_id,
                    "algorithm":algorithm
                    }   
                test_acc_df_list.append(pd.DataFrame(test_acc_dict, index=[0]))

    test_acc_df = pd.concat(test_acc_df_list)

    return test_acc_df

"""
an attempt to modularize our code to improve readibility, this method 
will make a ggplot to visually examine which learning algorithm is 
best for each data set
"""
def plot(test_acc_df):
    gg = (p9.ggplot(test_acc_df,
            p9.aes(x='test_accuracy_percentage'
            ,y='algorithm'))
          # .~ spreads vals across columns
          +p9.facet_grid('.~ data_set')
          # Use geom_point to create scatterplots
          +p9.geom_point())
    print(gg)


def main():
    warnings.filterwarnings('ignore')
    data_dict = {}
    # retrieve our source files. Spam and test. 
    retrieve(test_file, test_url)
    retrieve(train_file, train_url)
    retrieve(spam_file, spam_url)
    
    # call method to initialize our data frames, convert to numpy arrays, 
    (test, train, spam, _dict) = df_init(test_file, train_file, spam_file, data_dict)  
    # call method to perform our algorithm shown in class and the demo
    trained_data = train(_dict)
    
    # plot our values by passing in the previously filled variable d
    viz_data = plot(trained_data)

if __name__ == '__main__':
    # run main
    main()

