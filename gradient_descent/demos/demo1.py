import pandas as pd
import numpy as np

spam_df = pd.read_csv(
    "~/teaching/cs570-spring-2022/data/spam.data",
    header=None,
    sep=" ")

spam_features = spam_df.iloc[:,:-1].to_numpy()
spam_labels = spam_df.iloc[:,-1].to_numpy()
# 1. feature scaling
spam_features.mean()
spam_features.mean(axis=0)
spam_features.var(axis=0) # var = sd^2
np.sqrt(spam_features.var(axis=0))

np.random.seed(1)
n_folds = 5
fold_vec = np.random.randint(low=0, high=n_folds, size=spam_labels.size)
validation_fold = 0
is_set_dict = {
    "validation":fold_vec == validation_fold,
    "subtrain":fold_vec != validation_fold,
}

set_features = {}
set_labels = {}
for set_name, is_set in is_set_dict.items():
    set_features[set_name] = spam_features[is_set,:]
    set_labels[set_name] = spam_labels[is_set]
{set_name:array.shape for set_name, array in set_features.items()}

subtrain_mean = set_features["subtrain"].mean(axis=0)
subtrain_sd = np.sqrt(set_features["subtrain"].var(axis=0))

scaled_features = {
    set_name:(set_mat-subtrain_mean)/subtrain_sd
    for set_name, set_mat in set_features.items()
    }
{set_name:set_mat.mean(axis=0) for set_name, set_mat in scaled_features.items()}
{set_name:set_mat.var(axis=0) for set_name, set_mat in scaled_features.items()}

nrow, ncol = scaled_features["subtrain"].shape
weight_vec = np.zeros(ncol+1)
learn_features = np.column_stack([
    np.repeat(1, nrow),


    scaled_features["subtrain"]
])
learn_features[:,0]
subtrain_labels = np.where(set_labels["subtrain"]==1, 1, -1)
step_size = 0.001

for iteration in range(10):
    pred_vec = np.matmul(learn_features, weight_vec)
    log_loss = np.log(1+np.exp(-subtrain_labels * pred_vec))
    print("iteration=%d log_loss=%s"%(iteration,log_loss.mean()))
    grad_loss_pred = -subtrain_labels/(1+np.exp(subtrain_labels * pred_vec))
    grad_loss_weight_mat = grad_loss_pred * learn_features.T
    grad_vec = grad_loss_weight_mat.sum(axis=1)
    weight_vec -= step_size * grad_vec
#computing weight/intercept for use with features on original scale.
orig_weight_vec = weight_vec[1:] / subtrain_sd
orig_intercept = weight_vec[0] - (orig_weight_vec * subtrain_mean).sum()
# predicted values using either scaled or unscaled features agree:
np.matmul(learn_features, weight_vec)
np.matmul(set_features["subtrain"], orig_weight_vec) + orig_intercept
