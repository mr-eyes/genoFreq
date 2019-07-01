import sys
import gzip
from concurrent import futures


class GenoFreq:

    def __init__(self, file_name):
        self.file_name = file_name
        self.all_genotypes = self.get_all_genotypes()

    def get_all_genotypes(self):
        all_genotypes = ["./."]
        for i in range(7):
            for j in range(7):
                all_genotypes.append(str(i) + "/" + str(j))

        return all_genotypes


    def create_index(self, samples_list):
                
        # Construct Samples Index
        samples_idx = dict()    
        sample_to_id = dict()
        id_to_sample = dict()
        
        for sample_id, sample_name in enumerate(samples_list, start = 1):      
            samples_idx[sample_name] = dict()
            sample_to_id[sample_name] = sample_id
            id_to_sample[sample_id] = sample_name
            for gtype in self.all_genotypes:
                samples_idx[sample_name][gtype] = 0
                
        self.id_to_sample = id_to_sample
        self.index = samples_idx


    def analyze(self, record):
        genotypes = [rec.split(":")[0] for rec in record.split("\t")[9:]]
        for i, genotype in enumerate(genotypes, start = 1):
            self.index[self.id_to_sample[i]][genotype] += 1


    def write_results(self):
        ## Exporting results
        print("writing results...") 
        with open(self.file_name + "_results.tsv", 'w') as results:
            all_genotypes = GENO.all_genotypes
            header = "Sample" + "\t" + "\t".join(all_genotypes) + "\n"
            results.write(header)
            for sample_name, frequencies in self.index.items():
                row = sample_name + "\t" + "\t".join(list(map(str, frequencies.values()))) + "\n"
                results.write(row)



if len(sys.argv) < 2:
    sys.exit("run: pypy genotype_freq.py <vcf.gz>")
else:
    file_name = sys.argv[1]
    print("processing {} ...".format(file_name))


GENO = GenoFreq(file_name)

with gzip.open(GENO.file_name, 'rb') as vcf:

        # Skip all meta info lines
        tmp = "##"
        while(tmp[0:2] == "##"):
            tmp = next(vcf)
            continue

        # Construct samples names
        else:
            GENO.create_index(tmp.split()[9:])

        # Main Iteration
        for vcf_record in vcf:
            GENO.analyze(vcf_record)



GENO.write_results()


