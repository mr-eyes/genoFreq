#ifndef GENOFREQ_INCLUDE_GENOFREQ_H_
#define GENOFREQ_INCLUDE_GENOFREQ_H_

#include <string>
#include <unordered_map>
#include <vector>
#include <parallel_hashmap/phmap.h>
#include <set>

using phmap::flat_hash_map;

class GenoFreq {
 public:
  std::string file_name;
  std::string output_dir;

  std::vector<std::string> all_genotype = {"./."};

  flat_hash_map<std::string,
                flat_hash_map<std::string, flat_hash_map<std::string, int>>> index;

  flat_hash_map<int, std::string> id_to_sample;
  std::unordered_map<std::string, int> sample_to_id;
  std::set<std::string> filters_list;

  GenoFreq(std::string filename, int max_haplotype, std::string output_dir);

  void get_all_genotypes(int);

  void create_index(std::set<std::string> &, std::vector<std::string> &);

  void analyze(std::string &);

  void write_results();

  std::vector<std::string> extract_all_gtypes(const std::string &s);

  std::vector<std::string> split(const std::string &record, char delimiter);
};

#endif  // GENOFREQ_INCLUDE_GENOFREQ_H_