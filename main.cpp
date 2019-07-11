
#include "gzstream.h"
#include "genoFreq.hpp"
#include <set>

int main(int argc, char **argv) {
  int max_haplotype = 6;
  std::string output_dir;
 
  if (argc < 2){
      std::cerr << "run as following" << std::endl;
      std::cerr << "./genoFreq <file.vcf/file.vcf.gz> ";
      std::cerr << "<output_dir> <optional: max_haplotype_number, default=6>" << std::endl;
      exit(0);
  }

  if (argc < 3){
      std::cerr << "must provide output path" << std::endl;
      exit(0);
    }

  output_dir = argv[2];

  if (argc > 3) {
    if (atoi(argv[3]) > 9) {
      std::cerr
          << "cannot process haplotypes number greater than 9\nTerminating..."
          << std::endl;
      
      exit(0);

    } else {
      max_haplotype = atoi(argv[3]);
    }
  }

  GenoFreq *GENO = new GenoFreq(argv[1], max_haplotype, output_dir);

  igzstream in(argv[1]);

  std::string str = "##";

  // Extract all filter names
  std::set<std::string> filter_names;
  while (str.substr(0, 2) == "##") {
    if (str.substr(0, 8) == "##FILTER") {
      filter_names.insert(GENO->split(str, ',')[0].substr(13));
    }
    getline(in, str);
  }

  std::vector<std::string> splitted = GENO->split(str, '\t');
  std::vector<std::string> samples_names;

  for (uint i = 9; i < splitted.size(); i++) {
    samples_names.push_back(splitted[i]);
  }

  GENO->create_index(filter_names, samples_names);

  std::cerr << "Analyzing... " << std::endl;
  std::vector<std::string> all_samples;

  for (std::string str; std::getline(in, str);) GENO->analyze(str);

  GENO->write_results();
}