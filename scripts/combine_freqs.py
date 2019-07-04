#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

if len(sys.argv) < 2:
    sys.exit("run: python combine_freqs.py <file1> <file2> ...")
    

allfiles = sys.argv[1:]

combined = dict()

header = ""

for _ in allfiles:
    with open(_, 'r') as tsv:
        header = next(tsv).strip().split()[1:]

        for line in tsv:
            line = line.strip().split()
            sample_name = line[0]
            values = list(map(int, line[1:]))

            if sample_name not in combined:
                combined[sample_name] = dict()
                for geno in header:
                    combined[sample_name][geno] = 0


            for i in range(len(values)):
                combined[sample_name][header[i]] += values[i]


with open("combined.tsv" , 'w') as comb:
    comb.write("sample\t")
    comb.write("\t".join(header))
    comb.write("\n")

    for sample, genos in combined.items():
        comb.write(sample + "\t")
        delimiter = ""
        for geno, value in genos.items():
            comb.write(delimiter + str(value))
            delimiter = "\t"

        comb.write("\n")