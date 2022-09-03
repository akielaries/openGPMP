# python modules we need for this week.
import pandas as pd
import plotnine as p9

# try to import the other python modules needed for this class.
import torch
import torchtext
import sklearn

zip_df = pd.read_csv(
    "../data/zip.test.gz",
    header=None,
    sep=" ")

# index on columns.
zip_df[0] # first column.

# subset on rows (everything but the first).
zip_df[1:] # still 257 columns.

# subset on columns using index (maybe named).
zip_df.loc[:,1:]

# subset on columns using column numbers (always int).
zip_df.iloc[:,1:]

# list all attributes/methods.
dir(zip_df)
help(zip_df.iloc)

zip_mat = zip_df.iloc[:,1:].to_numpy()
zip_mat.shape

import numpy as np

# 16 repeated, BAD/-5 on general usage rubric.
index_vec = np.arange(16)
np.repeat(index_vec, 16)

# GOOD, define n_pixels to hold repeated number.
n_pixels = 16
index_vec = np.arange(n_pixels)
image_index = 0 # one arbitrary example image to plot.
zip_mat[image_index,:] 
one_image_df = pd.DataFrame({
    "col":np.tile(index_vec, n_pixels),
    "row":-np.repeat(index_vec, n_pixels),
    "intensity":zip_mat[image_index,:]
})
one_image_df

gg = p9.ggplot()+\
    p9.geom_raster(
        p9.aes(
# names are visual properties, values are column names.
            x="col",
            y="row",
            fill="intensity",
            ),
        data=one_image_df)
gg.save("01_visualizing_digits.png")
## TODO scale_fill_gradient for black-white legend.
## TODO coord_equal to force square pixels.
## TODO facet_grid or facet_wrap(["id","label"]) to display multiple panels/examples.

# another python plotting module is seaborn, which does not yet
# implement much of the functionality we need, for example geom tile
# or rect.

import seaborn.objects as so
plot_obj = so.Plot().add(
    # mark=THERE IS NO EQUIVALENT OF GEOM_RECT YET https://seaborn.pydata.org/nextgen/
    data=one_image_df, 
    x="col", y="row", fill="intensity")
so.Plot(mpg, x="displ", y="hwy", color="drv").add(so.Line(), so.Agg()).add(so.Scatter())



