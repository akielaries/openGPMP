import os
os.path.exists("foo")

import pandas as pd
zip_df = pd.read_csv(
    "~/Desktop/Trunk/github/private_repos/CS499-599_deep-learning/data/zip.test.gz",
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

zip_mat = zip_df.iloc[:,1:].to_numpy()
zip_mat.shape

import numpy as np

# BAD 16 repeated
index_vec = np.arange(16)
np.repeat(index_vec, 16)

# GOOD
n_pixels = 16
index_vec = np.arange(n_pixels)
image_index = 0
zip_mat[image_index,:] 
one_image_df = pd.DataFrame({
    "col":np.repeat(index_vec, n_pixels),
    "intensity":zip_mat[image_index,:]
})
one_image_df

import plotnine as p9
import matplotlib
matplotlib.use('cairo')

gg = p9.ggplot()+\
    p9.geom_raster(
        p9.aes(
            x="col",
            y="col",#should be row eventually.
            fill="intensity",
            ),
        data=one_image_df)
gg.save("2022_01_13.png")
