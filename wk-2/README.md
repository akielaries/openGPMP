K-fold cross-validation for hyper-parameter tuning and model comparison

In this project your goal is to implement several binary
classification learning algorithms, and use K-Fold cross-validation to
(1) train hyper-parameters and (2) compare prediction accuracy.

For this project you need to use scikit-learn.
- sklearn.model_selection.KFold can be used to split the full data set
  into train/test sets.
- sklearn.model_selection.GridSearchCV can be used to split the train
  set into subtrain/validation sets for learning hyper-parameters
  (n_neighbors in KNeighborsClassifier, l1_ratio and alpha in LogisticRegressionCV, etc).

*** Experiments/application
- Use spam and zip.train data sets from
  [[https://web.stanford.edu/~hastie/ElemStatLearn/data.html]], [[file:~/teaching/cs570-spring-2022/data/][local copy
  here]]. After using pandas.read_csv, remove any rows which have non-01
  labels (so we can do binary classification in both data sets). Then
  convert inputs to a numpy matrix and convert outputs to a label
  vector. Store the two data sets in a dictionary called data_dict
  with two keys, data set names: spam and zip. Each value in that dict
  should store the data set, for example as a tuple (inputs,outputs).
- Now write a for loop over entries in data_dict, the goal is to apply
  the same exact machine learning algorithms to both data sets. Please
  avoid special case code like if data_set=="spam".
- In each iteration you should use sklearn.model_selection.KFold to
  split the full data set into K=3 train/test sets. There should be
  another for loop over splits / test sets.
- Use GridSearchCV(cv=5) with KNeighborsClassifier to implement
  internal subtrain/validation splits that automatically chooses the
  best value for n_neighbors (from 1 to 20), using 5-fold
  cross-validation. After calling the fit method, the best_params_
  attribute stores which hyper-parameter was selected as best, so
  print out that value. Is it always the same for each data set and
  split, or does it vary?
- Use sklearn.linear_model.LogisticRegressionCV(cv=5) to implement a
  linear model which uses 5-fold cross-validation to choose the
  regularization/alpha hyper-parameter. Actually, you probably need to
  scale the inputs before learning the linear model, as described on
  the scikit-learn [[https://scikit-learn.org/stable/modules/preprocessing.html][pre-processing]] tutorial page. You may need to
  increase the max_iter parameter from its default of 100, for
  example, 

#+BEGIN_SRC 
pipe = make_pipeline(StandardScaler(), LogisticRegression(cv=5, max_iter=1000))
#+END_SRC

- Also write code that computes what is the more frequent
  class label (0 or 1) in the train set. Hint: use [[https://pandas.pydata.org/docs/reference/api/pandas.Series.value_counts.html][value_counts]] and
  [[https://pandas.pydata.org/docs/reference/api/pandas.Series.idxmax.html][idxmax]] methods.
- Now compute predictions on the test set, and store them in a
  dictionary called pred_dict with three keys: nearest_neighbors,
  linear_model, featureless. Values should each be 1d numpy arrays
  (vector of predicted class labels). You can use
  predict(test_features) method for nearest_neighbors and
  linear_model. Featureless should be a vector of either all 0 or all
  1 (whichever was more frequent in the train set labels), for
  comparison with a simple baseline (any properly trained machine
  learning model should be at least as accurate as the featureless
  baseline).
- Write a for loop over pred_dict entries, and in each iteration
  compute the test accuracy (percent correctly predicted labels in
  test set).
- Jump out of all of those for loops, then use
  pd.concat(list_of_data_frames) to combine test accuracy values into
  a single DataFrame with columns data_set, fold_id, algorithm,
  test_accuracy_percent. Print out that table and show it in your
  PDF report.
- Also make a ggplot to visually examine which learning algorithm is
  best for each data set. Use geom_point with x="test_accuracy_percent", y="algorithm", and facet_grid(". ~ data_set"). Which algorithm is most accurate for zip data? For spam data?
  
Extra credit:
- GridSearchCV has a cv_results_ attribute which is a dictionary which
  stores the mean accuracy over splits, for each hyper-parameter
  (n_neighbors, alpha, etc). Make a plot that shows the validation
  accuracy as a function of a hyper-parameter for one or more
  algorithms and/or data sets.
- if you compute and plot ROC curves for each (test fold, algorithm)
  combination. Make sure each algorithm is drawn in a different color,
  and there is a legend that the reader can use to read the figure.
- try two different versions of nearest neighbors, with and without
  StandardScaler(), and save/print/plot test accuracy values for both
  versions.
- if you compute area under the ROC curve (AUC) and include
  that as another evaluation metric (in a separate panel/plot) to
  compare the test accuracy of the algorithms.
- If you do an analysis of how many train data you need to get optimal
  prediction accuracy. Use a for loop over train data sizes, 10, 50,
  100, etc. Plot y=test accuracy as a function of x=train data size.
  
** FAQ

- How to fix KeyError: something is not in index?  "not in index"
  indicates you are not using the indexing correctly. Please refer to
  the [[https://pandas.pydata.org/pandas-docs/stable/user_guide/indexing.html][pandas]]/[[https://numpy.org/doc/stable/user/basics.indexing.html#basics-indexing][numpy]] documentation for correct usage examples. You may
  need to use DF.loc[rows,cols] or DF.iloc[rows,cols]. Also KFold
  examples may be useful,
  https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.KFold.html
- What is the difference betwen loc and iloc? loc uses the index
  (row/column names) whereas iloc uses integer row/column numbers.
