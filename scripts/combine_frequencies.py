import pandas as pd
import os
from glob import glob

allfiles = glob("./*tsv")


dfs={ i : pd.DataFrame.from_csv(allfiles[i],sep=',',\
header=None,index_col=None) for i in range(len(allfiles))} # n files.

panel=pd.Panel(dfs)

dfs_sum=panel.sum(axis=0)

print(dfs)