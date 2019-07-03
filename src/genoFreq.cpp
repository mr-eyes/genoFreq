#include "genoFreq.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

GenoFreq::GenoFreq(std::string filename, int max_haplotype) {
  this->file_name = filename;
  this->get_all_genotypes(max_haplotype);
}

std::vector<std::string> GenoFreq::extract_all_gtypes(const std::string& s) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);

  while (std::getline(tokenStream, token, '\t'))
    tokens.push_back(token.substr(0, 3));

  return tokens;
}

std::vector<std::string> GenoFreq::split(const std::string& s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);

  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }

  return tokens;
}

void GenoFreq::analyze(std::string& s) {
  std::string token;
  std::istringstream tokenStream(s);
  std::string filter_name;

  int sample_id;

  // skipping
  for (int i = 0; i < 7; i++) std::getline(tokenStream, token, '\t');

  // insert the filter
  filter_name = token;

  // skipping
  for (int i = 0; i < 2; i++) std::getline(tokenStream, token, '\t');

  sample_id = 1;
  while (std::getline(tokenStream, token, '\t')) {
    this->index[filter_name][this->id_to_sample[sample_id]][token.substr(
        0, 3)] += 1;
    sample_id++;
  }
}

void GenoFreq::get_all_genotypes(int max_haplotypes) {
  for (int i = 0; i <= max_haplotypes; i++) {
    for (int j = 0; j <= max_haplotypes; j++) {
      this->all_genotype.push_back(std::to_string(i) + "/" + std::to_string(j));
    }
  }
}

void GenoFreq::create_index(std::set<std::string>& filters_list,
                            std::vector<std::string>& samples_list) {
  this->filters_list = filters_list;

  int sample_id = 1;

  for (const auto& sample_name : samples_list) {
    this->id_to_sample[sample_id] = sample_name;
    this->sample_to_id[sample_name] = sample_id;
    sample_id++;
  }

  for (const auto& filter : filters_list) {
    // std::cout << "FILTER: " << filter << std::endl;

    for (const auto& sample_name : samples_list) {
      for (const auto& gtype : this->all_genotype) {
        this->index[filter][sample_name][gtype] = 0;
      }
    }
  }
}

inline std::string create_dir(std::string output_file, int serial) {
  int dir_err;
  std::string new_name = "";

  if (!serial) {
    dir_err = mkdir(output_file.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    new_name = output_file;
  } else {
    new_name = output_file + "_v." + std::to_string(serial);
    dir_err = mkdir(new_name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  }

  if (-1 == dir_err) return create_dir(output_file, ++serial);

  return new_name;
}

void GenoFreq::write_results() {
  std::string output_file = "";
  std::string delimiter;
  output_file = this->file_name.substr(this->file_name.find_last_of("/\\") + 1);
  size_t dot_i = output_file.find_last_of('.');
  output_file = output_file.substr(0, dot_i);
  output_file = create_dir(output_file, 0);

  std::cerr << "Writing in dir: " << output_file << std::endl;

  for (const auto& filter : this->filters_list) {
    std::ofstream myfile;

    myfile.open(output_file + "/" + filter + "_genoFreq.tsv");
    myfile << "sample\t";

    delimiter = "";
    for (const auto& gtype : this->all_genotype) {
      myfile << delimiter << gtype;
      delimiter = "\t";
    }

    myfile << std::endl;

    for (auto& sample : this->index[filter]) {
      myfile << sample.first << '\t';

      delimiter = "";
      for (const auto& gtype : this->all_genotype) {
        myfile << delimiter << sample.second[gtype];
        delimiter = "\t";
      }

      myfile << "\n";
    }

    myfile.close();
  }
}