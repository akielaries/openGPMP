Implementing nearest neighbors classification and cross-validation

In this project your goal is to implement nearest neighbors and K-Fold
cross-validation from scratch, then compare your implementation to
the one you used last week in scikit-learn.

*** Class: MyKNN

This class should work just like sklearn.neighbors.KNeighborsClassifier.
- instantiate it with n_neighbors parameter, which should be stored as
  an attribute of that instance.
- fit(X=train_features, y=train_labels) method should store data as
  members/attributes of that instance.
- predict(X=test_features) should compute a binary vector of predicted
  class labels. For each test data row, use numpy to compute the
  distances with all of the train data. Each distance is the square
  root of the sum of squared differences over all features (you don't
  have to take the square root though because it is a monotonic
  transformation, does not change the ordering of the
  observations). Sort the distances (numpy.argsort) to find the
  smallest n_neighbors values. The predicted class should be the most
  frequent label among the nearest n_neighbors.

*** Class: MyCV

This class should work just like
sklearn.model_selection.GridSearchCV. In other words, it should do
best parameter selection via cross-validation for any estimator (there should
be no code that is specific to nearest neighbors).
- IMPORTANT: nothing in this class should be specific to the nearest
  neighbors algorithm! It should not have any reference to
  "n_neighbors" in the class definition.
- instantiation: MyCV(estimator=MyKNN(),
  param_grid=[{'n_neighbors':n_neighbors} for n_neighbors in
  range(20)], cv=5)
- fit(X=train_features, y=train_labels) should compute the best number
  of neighbors using K-fold cross-validation, with the number of folds
  defined by the cv parameter. Begin by assigning random fold ID
  numbers to each observation. There should be for loops over the K
  subtrain/validation splits, and the parameters (n_neighbors) in
  param_grid. For each, use estimator.fit(*subtrain_data) and
  predict(validation_features) methods of the estimator, then save the
  validation accuracy. For each parameter (n_neighbors) in param_grid
  compute the mean validation accuracy over the K splits. Finally,
  maximize the mean validation accuracy to determine a best parameter
  dictionary (one of the elements of param_grid, key should be
  n_neighbors) to save in the best_params_ attribute. Finally use
  setattr with the key in best_params_ to set the corresponding
  attribute of the estimator, and re-run estimator.fit on the whole
  data set.
- predict(X=test_features) runs estimator.predict(X=test_features) --
  the best number of neighbors should already have been set as an
  attribute of estimator, at the end of the fit method.

*** Experiments/application

- Use the same experimental setup as last week (with 3-fold CV
  train/test splits defined by KFold, and with
  GridSearchCV+KNeighborsClassifier and LogisticRegressionCV), but add
  your MyCV + MyKNN as a new algorithm to compare.
- Make sure to run experiments on both spam and zip data, and show a
  table of resulting test accuracy numbers, as well as a ggplot like
  last week. On the ggplot y axis there should be at least the
  following algorithms: MyCV+MyKNN, featureless,
  GridSearchCV+KNeighborsClassifier and LogisticRegressionCV.
- Does your implementation get similar test accuracy as scikit-learn?
  (it should!)
  
*** Extra credit

- Implement scaling as well, similar to make_pipeline and
  StandardScaler from scikit-learn. Add your method to the test
  accuracy figure, so we should see scaled and unscaled as separate
  algorithms on the test accuracy plot. How does your implementation
  of scaled nearest neighbors compare to unscaled? Which is more
  accurate? How do they compare to the scikit-learn versions? NOTE:
  for some data sets (zip) you may have some features in the train set
  which are constant (zero variance/sd). You can't divide by zero, so
  instead just leave that feature alone (don't attempt to scale it).
- Implement scaling by creating another data set in data_dict, called
  spam_scaled.
- Using the zip and/or spam data, implement a computational experiment
  that demonstrates adding noise features results in lower test
  accuracy, similar to the one shown in the class slides. Make a
  figure that shows test accuracy as a function of the number of noise
  features. Does test accuracy decrease with more noise features, as
  expected?

*** FAQ

- In python how to define methods of a class? Say for MyCV there
  should be something like

#+BEGIN_SRC python
  class MyCV:
      def fit(self, X, y):
	  """This is a method. the first argument should be self."""
	  fold_vec = np.random.randint(
	      low=0, high=self.n_folds, size=zip_labels.size)
	  for test_fold in range(self.n_folds):
	      is_set_dict = {
		  "test":fold_vec == test_fold,
		  "train":fold_vec != test_fold,
	      }
	      model = self.estimator(
		  set_features["subtrain"], set_labels["subtrain"])
	      model.predict(
		  set_features["validation"], set_labels["validation"])
            

  my_instance = MyCV()
  my_instance.n_folds = 5
  my_instance.estimator = MyKNN()
  # This is how to call the method (self argument is omitted).
  my_instance.fit(X=train_X, y=train_y)
#+END_SRC

What should MyCV fit method look like? Here is some pseudo-code:

#+begin_src python
  def fit(train):
      split train into subtrain/validation
      call estimator.fit(subtrain) on each hyper-parameter
      compute validation error for each
      best params = hyper-params with min validation error
      self.best_model = fit(train, best params)
#+end_src

