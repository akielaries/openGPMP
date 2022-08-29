Homework week 1

The goal of this coding project is to get you up and running with
python, including
- downloading data files.
- reading CSV data into python as a DataFrame.
- printing a summary of the number of rows/columns in a DataFrame.
- basic data visualization using plotnine.

** Part 1: visualizing image data

Your goal is to write a python script that performs the following steps:

1. use urllib.request.urlretrieve to programmatically download a copy
   of the zip.test data set from
   https://github.com/tdhock/cs570-spring-2022/raw/master/data/zip.test.gz
   (original was from
   https://web.stanford.edu/~hastie/ElemStatLearn/datasets/zip.test.gz
   but is now broken).  Use an if statement so that the download only
   happens if the file does not yet exist on your system. Make sure
   the saved file has the gz suffix, which indicates that the file has
   been compressed using gzip. This data file represents images of
   handwritten digits, one example per line/row. Each example is one
   of the ten possible digits (as indicated by the label in the first
   column). Use pandas.read_csv to read the compressed CSV data file
   into python as a DataFrame (you may need to use sep/header
   arguments to parse the CSV correctly). Print the shape attribute --
   how many rows/columns are there?
2. Convert the DataFrame to a numpy.array, which is a more useful data
   structure for machine learning algorithms. Make sure to exclude the
   label column (that is the first column). Print the shape attribute
   to show the number of rows and columns. What is the number of
   rows/observations/example digits? What is the number of
   columns/features/pixels per example?
3. First convert one row of your input data matrix into a DataFrame
   with columns row,col,intensity where row,col go from 0 to 15, and
   intensity are the input values (-1 to 1). Use
   numpy.repeat/resize/arange to create row/col without any for
   loops. Then plug that DataFrame into plotnine with geom_tile/raster
   to visualize one row from that data set as an image of a digit. Use
   ggtitle to show the label of the chosen example.
4. Make a facetted/multi-panel plot of several images. First use a for
   loop over several rows of the data, say the first nine rows. In
   each iteration of the for loop you should construct a DataFrame
   with columns observation,label,intensity,row,col. Then at the end
   of the for loop use pd.concat(list_of_data_frames) to construct a
   single DataFrame which you can use as the data set in
   geom_tile/raster. Finally use facet_wrap to visualize those images
   in separate panels (similar to slides from class). To make sure
   each panel title shows the observation number/row along with the
   label (digit class from 0 to 9), use
   facet_wrap(["observation","label"],labeller="label_both").

For your homework please upload in bblearn a single PDF file, with (1)
your python code, (2) the corresponding results/output (after running
your python code), and (3) your commentary/interpretation/answers to
questions.

** Part 2: advanced data visualization (extra credit for CS499 undergrads, required for CS599 graduate students)

These are exercises taken from
https://rcdata.nau.edu/genomic-ml/animint2-manual/Ch02-ggplot2.html
which are in R, and the goal is to translate the code into
python/plotnine (the variable name viz.aligned below refers to ggplot
code on that web page). Please download the [[file:WorldBank.csv]] data
set.

1. In viz.aligned we showed a ggplot with a scatterplot panel on the
   left and a time series panel on the right. Make another version of
   the data visualization with the time series panel on the left and
   the scatterplot panel on the right. Hint: the order of panels can
   be controlled by using a pandas.Categorical(categories=order) in
   facet_grid. For example plotnine.facet_grid(". ~ x") means use the different
   values of the x variable in different facets, where x =
   pandas.Categorical(values, order).
2. In viz.aligned the scatterplot displays fertility rate and life
   expectancy, but the time series displays only fertility rate. Make
   another version of the data visualization that shows both time
   series. There should be only one ggplot that looks something like
   [[https://rcdata.nau.edu/genomic-ml/WorldBank-facets/][this]]. Hint: add another geom_point and use both horizontal and
   vertical panels in facet_grid(row_var ~ col_var).
3. Create a multi-panel data visualization (scatterplot of data for
   one year in each panel) that shows each year of the WorldBank data
   set in a separate panel of one ggplot. Hint: use facet_wrap.

** FAQ

- how to save figures? use something like 
#+begin_src python
plotnine.ggplot().save("file.png", width=10, height=5, units="in", dpi=100)
#+end_src
- how to show figures in jupyter notebooks? try using print on the
  ggplot object, like
#+begin_src python
gg = plotnine.ggplot()
print(gg)
#+end_src
- how to adjust the space used for the legend? use something like
  plotnine.theme(subplots_adjust={'right': 0.5})
- my digits are being displayed but rotated/upside down? Try changing
  the x/y mapping or order of values (decreasing vs increasing).
- I am having trouble adding the pandas.Categorical to each layer for
  faceting. Do you have any tips?
  https://pandas.pydata.org/docs/reference/api/pandas.Categorical.html
- when I try matplotlib.use("cairo") in jupyter notebooks it throws
  the ModuleNotFound error? Try removing that line of code (use
  default backend).



