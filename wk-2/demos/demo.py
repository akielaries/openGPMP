import os
import urllib.request
import pandas as pd
from sklearn.model_selection import KFold #train/test splits
from sklearn.model_selection import GridSearchCV #selecting best # of neighbors
from sklearn.neighbors import KNeighborsClassifier #nearest_neighbors prediction.
# TODO add import linear_model.


# our src file we want to download
src_url = 'https://github.com/tdhock/cs570-spring-2022/raw/master/data/zip.test.gz'
src_file = 'zip.test.gz'

if not os.path.isfile(src_file):
    urllib.request.urlretrieve(src_url, src_file)
    print("Downloading src file...")

else:
    print("File already exists in this folder...continuing anyway\n")

# read in downloaded src file as a pandas dataframe
zip_df = pd.read_csv(src_file, header=None, sep=" ")


is01 = zip_df[0].isin([0,1])
zip01_df = zip_df.loc[is01,:]

data_dict = {
    "zip":(zip01_df.loc[:,1:].to_numpy(), zip01_df[0]),
    #"spam":TODO
}

test_acc_df_list = []
for data_set, (input_mat, output_vec) in data_dict.items():
    print(data_set)
    kf = KFold(n_splits=3, shuffle=True, random_state=1)
    for fold_id, indices in enumerate(kf.split(input_mat)):
        print(fold_id)
        index_dict = dict(zip(["train","test"], indices))
        param_dicts = [{'n_neighbors':[x]} for x in range(1, 21)]
        # does subtrain/validation splits.
        clf = GridSearchCV(KNeighborsClassifier(), param_dicts)
        set_data_dict = {}
        for set_name, index_vec in index_dict.items():
            set_data_dict[set_name] = (
                input_mat [ index_vec ],
                output_vec.iloc[index_vec]
                )
        # * is unpacking a tuple to use as the different positional arguments
        # clf.fit(set_data_dict["train"][0], set_data_dict["train"][1])
        clf.fit(*set_data_dict["train"])
        # method 2: dict instead of tuple.
        set_data_dict = {}
        for set_name, index_vec in index_dict.items():
            set_data_dict[set_name] = {
                "X":input_mat[index_vec],
                "y":output_vec.iloc[index_vec]
                }
        # ** is unpacking a dict to use as the named arguments
        # clf.fit(X=set_data_dict["train"]["X"], y=set_data_dict["train"]["y"]])
        clf.fit(**set_data_dict["train"])
        clf.best_params_
        cv_df = pd.DataFrame(clf.cv_results_)
        cv_df.loc[:,["param_n_neighbors","mean_test_score"]]
        pred_dict = {
            "nearest_neighbors":clf.predict(set_data_dict["test"]["X"])
            #TODO add featureless and linear_model.
            }
        for algorithm, pred_vec in pred_dict.items():
            test_acc_dict = {
                "test_accuracy_percent":(
                    pred_vec == set_data_dict["test"]["y"]).mean()*100,
                "data_set":data_set,
                "fold_id":fold_id,
                "algorithm":algorithm
                }
            test_acc_df_list.append(pd.DataFrame(test_acc_dict, index=[0]))
                
test_acc_df = pd.concat(test_acc_df_list)


