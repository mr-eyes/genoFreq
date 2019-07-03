# genoFreq

Summarize and visualize the genotypes categories per sample in a VCF file.

## Build

```shell
git clone --recursive https://github.com/mr-eyes/genoFreq.git
mkdir -p genoFreq/build && cd genoFreq/build/
cmake ..
make
```

### Python dependencies

```shell
python -m pip install -r requirements.txt
```

## 1- Generate genotype frequencies

> Execute

```shell
./genoFreq <vcf.gz> <optional: max_haplotype_number, default=6>
```

> Output Sample "TSV"

| sample              | ./.  | 0/0  | 0/1 | 0/2 | 0/3 | 0/4 | 0/5 | 0/6 | 1/0 | 1/1 | 1/2 | 1/3 | 1/4 | 1/5 | 1/6 | 2/0 | 2/1 | 2/2 | 2/3 | 2/4 | 2/5 | 2/6 | 3/0 | 3/1 | 3/2 | 3/3 | 3/4 | 3/5 | 3/6 | 4/0 | 4/1 | 4/2 | 4/3 | 4/4 | 4/5 | 4/6 | 5/0 | 5/1 | 5/2 | 5/3 | 5/4 | 5/5 | 5/6 | 6/0 | 
|---------------------|------|------|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----| 
| SAMPLE1 | 1443 | 6168 | 98  | 3   | 0   | 0   | 0   | 0   | 0   | 18  | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 
| SAMPLE2 | 3361 | 4259 | 58  | 2   | 0   | 0   | 0   | 0   | 0   | 49  | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 
| SAMPLE3 | 2856 | 4740 | 98  | 1   | 0   | 0   | 0   | 0   | 0   | 35  | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |    0 | 

## 2- Simplify genoTypes to categories

> Execute

```shell
python scripts/simplify.py <genpFreq.tsv>
```

> Output Sample "TSV"

| sample              | ungenotyped | homo_WT | homo_MT | hetero | comp_het | 
|---------------------|-------------|---------|---------|--------|----------| 
| SAMPLE1 | 1443        | 6168    | 18      | 101    | 0        | 
| SAMPLE2 | 3361        | 4259    | 50      | 60     | 0        | 
| SAMPLE3 | 2856        | 4740    | 35      | 99     | 0        | 

## 3- Merge samples meta information with genotypes frequencies

> Execute

```shell
python scripts/merge.py <metaInfo.tsv> <genoFreq.tsv>
```

> sample

| SampleID | Breed | Sex | Coverage | HD_Concordance | Unique_variants_per_20mb | Heterozygosity | ungenotyped | homo_WT | homo_MT | hetero | comp_het |
|----------|-------|-----|----------|----------------|--------------------------|----------------|-------------|---------|---------|--------|----------|
| SAMPLE1  | Breed1 | M   | 9.62     | NA             | 0.250035515              | 0.155309014    | 1790        | 5598    | 77      | 265    | 0        |
| SAMPLE2  | Breed2 | M   | 13.69    | NA             | 0.034022612              | 0.171542069    | 2192        | 5215    | 85      | 238    | 0        |
| SAMPLE3  | Breed3 | M   | 13.69    | NA             | 0.05338513               | 0.175761316    | 2572        | 4915    | 97      | 146    | 0        |

## 4- Visualization

> Execute

```shell
python scripts/plot.py <merged_file.tsv> <x_axis> <y_axis>
```

> Sample
![](https://ibin.co/4majI6U9yiDO.png)
