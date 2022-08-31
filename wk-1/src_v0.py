"""
Homework 1 for Professor Hockings CS499-599 Deep Learning course
Author: Akiel Aries

Details:

"""
# lib for retrieving src file from web
import urllib.request
# lib for reading files on OS
import os.path
# lib used for copying src file info into destination

import pandas as pd
import plotnine as p9

# read compressed data
zip_df = pd.read_csv("zip.test.gz", header=None, sep=" ")

# method for downloading our source file if DNE on filesystem
def retrieve(src_url, src_file, dest_file):
    # backbone code from the python.org lib docs
    
    if not os.path.exists(src_file):
        
        with urllib.request.urlopen(src_url) as respone:
            shutil.copyfileobj(response, dest_file)




def main():
    # our src file we want to download
    src_url = 'https://github.com/tdhock/cs570-spring-2022/raw/master/\
            data/zip.test.gz'
    src_file = 'zip.test.gz'
    dest_file = os.path.abspath("~/Desktop/Trunk/github/private_repos/\
            CS499-599_deep-learning/hw-1/zip.test.gz")

    retrieve(src_url, src_file, dest_file)



