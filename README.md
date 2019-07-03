# genoFreq

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/2de26ea929034dfc93cd461a39cd25e6)](https://www.codacy.com/app/mr-eyes/genoFreq?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=mr-eyes/genoFreq&amp;utm_campaign=Badge_Grade) [![Build Status](https://travis-ci.org/mr-eyes/genoFreq.svg?branch=master)](https://travis-ci.org/mr-eyes/genoFreq)

## **Summarize and visualize the genotypes categories per sample in a VCF file.**

**genoFreq** is designed to process very large VCF files **(Terabytes)** with high speed & very low memory consumption.

---

## Build

```shell
git clone --recursive https://github.com/mr-eyes/genoFreq.git
mkdir -p genoFreq/build && cd genoFreq/build/
cmake ..
make
```

### Install Python dependencies

`python -m pip install -r requirements.txt`

## 1- Generate genotype frequencies

> Run

```shell
./genoFreq <file.vcf/file.vcf.gz> <output_dir> <optional: max_haplotype_number, default=6>
```

> Output Sample "TSV"

| sample              | ./.  | 0/0  | 0/1 | 0/2 | 0/3 | 0/4 | 0/5 | 0/6 | 1/0 | 1/1 | 1/2 | 1/3 | 1/4 | 1/5 | 1/6 | 2/0 | 2/1 | 2/2 | 2/3 | 2/4 | 2/5 | 2/6 | 3/0 | 3/1 | 3/2 | 3/3 | 3/4 | 3/5 | 3/6 | 4/0 | 4/1 | 4/2 | 4/3 | 4/4 | 4/5 | 4/6 | 5/0 | 5/1 | 5/2 | 5/3 | 5/4 | 5/5 | 5/6 | 6/0 | 
|---------------------|------|------|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| 
| SAMPLE1 | 1443 | 6168 | 98  | 3   | 0   | 0   | 0   | 0   | 0   | 18  | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 
| SAMPLE2 | 3361 | 4259 | 58  | 2   | 0   | 0   | 0   | 0   | 0   | 49  | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 
| SAMPLE3 | 2856 | 4740 | 98  | 1   | 0   | 0   | 0   | 0   | 0   | 35  | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |    0 | 

## 2- Combine multiple frequencies TSVs (Optional)

> Run

`python scripts/combine_freqs.py <file1.tsv> <file2.tsv> ...`

Or

`python scripts/combine_freqs.py ./*tsv`

## 3- Simplify genoTypes to categories

> Run

```shell
python scripts/simplify.py <genpFreq.tsv>
```

> Output Sample "TSV"

| sample              | ungenotyped | homo_WT | homo_MT | hetero | comp_het | 
|---------------------|-------------|---------|---------|--------|----------| 
| SAMPLE1 | 1443        | 6168    | 18      | 101    | 0        | 
| SAMPLE2 | 3361        | 4259    | 50      | 60     | 0        | 
| SAMPLE3 | 2856        | 4740    | 35      | 99     | 0        | 

## 4- Merge samples meta information with genotypes frequencies

> Meta information file sample (flixble for changes)

| SampleID | Breed  | Sex | Coverage | 
|----------|--------|-----|----------| 
| SAMPLE1  | Breed1 | M   | 9.62     | 
| SAMPLE2  | Breed2 | M   | 13.69    | 
| SAMPLE3  | Breed3  | M   | 13.69    | 

> Run

```shell
python scripts/merge.py <metaInfo.tsv> <genoFreq.tsv>
```

> Sample

| SampleID | Breed  | Sex | Coverage | ungenotyped | homo_WT | homo_MT | hetero | comp_het | 
|----------|--------|-----|----------|-------------|---------|---------|--------|----------| 
| SAMPLE1  | Breed1 | M   | 9.62     | 1443        | 6168    | 18      | 101    | 0        | 
| SAMPLE2  | Breed2 | M   | 13.69    | 3361        | 4259    | 50      | 60     | 0        | 
| SAMPLE3  | Breed3 | M   | 13.69    | 2856        | 4740    | 35      | 99     | 0        | 

## 5- Visualization

> Run

```shell
python scripts/plot.py <merged_file.tsv> <x_axis> <y_axis>
```

> Sample
![](https://ibin.co/4majI6U9yiDO.png)
