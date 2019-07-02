all_categories = ["ungenotyped", "homo_WT", "homo_MT", "hetero", "comp_het"]

freq_file = "simplified_freq.tsv"
meta_file = "metadata.tsv"

sample_info = {}

with open(freq_file, 'r') as freq:
    for line in freq:
        splt = line.strip().split()
        sample_name = splt[0]
        geno_info = "\t".join(splt[1:])
        sample_info[sample_name] = geno_info

new_file_name = "merged_" + meta_file.split(".")[0] + freq_file

with open(meta_file, 'r') as meta, open(new_file_name , 'w') as merged:
    header = next(meta).strip()
    merged.write(header + "\t" + "\t".join(all_categories) + "\n")
    for line in meta:
        splt = line.strip().split()
        sample_name = splt[0]
        meta_info = "\t".join(splt)
        geno_info = sample_info[sample_name]
        new_line = meta_info + "\t" + geno_info + "\n"
        merged.write(new_line)