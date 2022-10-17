# lib for retrieving src file from web
import urllib.request
# lib for reading files on OS
import os
# lib used for copying src file info into destination
import shutil

import pandas as pd
import plotnine as p9
import numpy as np

# our src file we want to download
src_url = 'https://github.com/tdhock/cs570-spring-2022/raw/master/data/zip.test.gz'
src_file = 'zip.test.gz'

def main():
    """
    backbone code from the python.org lib docs to  
        - check if a file exists in the current directory
        - retrieve a file given the url
    """
    if not os.path.isfile(src_file):
        urllib.request.urlretrieve(src_url, src_file)
        print("Downloading src file...")

    else:
        print("File already exists in this folder...continuing anyway\n")
        
    # read in downloaded src file as a pandas dataframe 
    zip_df = pd.read_csv(src_file, header=None, sep=" ")

    """
    convert dataframe to numpy array exlcuding the first column; iloc for row
    and col specifying. 
    """
    zip_arr = zip_df.iloc[:,1:].to_numpy()
    # printing shape of array
    print("Shape of our converted array: ", zip_arr.shape, "\n")

    """
    code for formatting important data values that correspond to imgs
    as well as looping thru first 9 rows and wrapping them into one grid
    """
    # define num of pixels
    pixels = 16
    index_vec = np.arange(pixels)
    # index of our images; arbitrary example to plot one of them
    img_index = 0
    zip_arr[img_index,:]
    
    img_df = pd.DataFrame({
        "col":np.tile(index_vec, pixels),
        "row":-np.repeat(index_vec, pixels),
        "intensity":zip_arr[img_index,:],
    })

    # print table of our values col, row, intensity
    print(img_df)
    
    """
    display plot using plotnine
    """
    gg = p9.ggplot()+p9.ggtitle("index")+p9.geom_raster(
        p9.aes(
            # assign vals to our img properties
            label = "0-9",
            x = "col",
            y = "row",
            fill = "intensity",),
        data = img_df) #+ p9.facet_grid("~col")
    
    """
    attempted to wrap our images 0-9 to be displayed together but was not sure what the
    observation and label variables are supposed to signify, I was thinking if I set 
    the initial condition of the loop to img_index 0 and go up to 9, put them in a 
    pandas dataframe then wrap them that our feed should be correct. I attempted to 
    use facet_grid but could not get the correct parameters working for the method. This 
    resulted in incomplete code and not the desired result. I was only able to display a single 
    hardcoded image with img_index before I ran out of time
    """
    print(gg)

if __name__ == '__main__':
    # run main
    main()

