import seaborn as sns
import pandas as pd 
import matplotlib.pyplot as plt
import sys

if len(sys.argv) < 4:
    sys.exit("run: genoPlot.py <tabular.tsv> <x:colName> <y:colName>")

else:
    file_name = sys.argv[1]
    x = sys.argv[2]
    y = sys.argv[3]

df = pd.read_csv(file_name, sep='\t') 

plot = plt.figure(figsize=(20,15))

plt.subplots_adjust(bottom = 0.3)

rc={'font.size': 15, 'axes.labelsize': 20, 'legend.fontsize': 20.0, 
    'axes.titlesize': 30, 'xtick.labelsize': 15, 'ytick.labelsize': 15}

plt.rcParams.update(**rc)

p = sns.boxplot(x=df[x], y=df[y])

loc, labels = plt.xticks()

z = list(labels)

p.set_xticklabels(labels, rotation=90, ha = "center")

p.set( xticks= range(0, len(z)) )

plt.savefig(file_name + "_x-" + x + "_y-" + y + "_boxplot.png")