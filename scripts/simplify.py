import sys

if len(sys.argv) < 2:
    sys.exit("run: python simplify.py <genpFreq.tsv>")
else:
    file_name = sys.argv[1]



# Construct categories
def construct_categories(all_genos):
    cate = dict()
    id_to_genotype = dict()

    for i, geno in enumerate(all_genos):
        id_to_genotype[i] = geno

        sp = geno.split("/")
        x = sp[0]
        y = sp[1]
        
        # Genotype
        if x == "." and y == ".":
            cate[geno] = "ungenotyped"
        
        elif x == "0" and y == "0":
            cate[geno] = "homo_WT"
        
        elif x == y and int(x) in range(1, 7):
            cate[geno] = "homo_MT"
        
        elif x == "0" and int(y) in range(1, 7):
            cate[geno] = "hetero"
        
        elif x != y and int(x) and int(y):
            cate[geno] = "comp_het"

    return id_to_genotype, cate
    

all_categories = ["ungenotyped", "homo_WT", "homo_MT", "hetero", "comp_het"]


with open(file_name, 'r') as freq, open("simplified_" + file_name , 'w') as simplified:
    header = next(freq).strip().split()[1:]
    simplified.write("sample" + "\t" + "\t".join(all_categories) + "\n")

    id_to_genotype, categories = construct_categories(header)
    row = ""

    for record in freq:
        
        record_categories = {
            "ungenotyped": 0,
            "homo_WT": 0,
            "homo_MT": 0,
            "hetero": 0,
            "comp_het": 0,
            }
        
        splt = record.strip().split()
        row = splt[0] + "\t" # Sample Name
        rest = splt[1:]

        # Process row genotypes
        for i, geno_val in enumerate(rest):
            geno_type = id_to_genotype[i]

            if geno_type not in categories:
                geno_category = categories[geno_type[::-1]]
            else:
                geno_category = categories[geno_type]
            

            record_categories[geno_category] += int(geno_val)
        

        # Construct new row
        delimiter = ""
        for category in all_categories:
            row += delimiter + str(record_categories[category])
            delimiter = "\t"
        
        # Write
        simplified.write(row + "\n")