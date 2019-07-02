#include <iostream>
#include <string>
#include "gzstream.h"
#include <fstream>
#include "genoFreq.hpp"

int main (int argc, char ** argv)
{

    GenoFreq *GENO = new GenoFreq(argv[1]);

    igzstream in(argv[1]);

    std::ifstream zin(argv[1]);

    std::string str = "##";

    while (str.substr(0,2) == "##")
    {
        getline(in, str);
    }

    std::vector<std::string> splitted = GENO->split(str, '\t');
    std::vector<std::string> samples_names;

    for(int i = 9; i < splitted.size(); i++ ){
        samples_names.push_back(splitted[i]);
    }

    GENO->create_index(samples_names);

    std::cerr << "Analyzing... " << std::endl;

    std::vector<std::string> all_samples;

    int sample_id;

    for(std::string str; std::getline(in, str); ){
        all_samples =  GENO->extract_all_gtypes(str);    
        sample_id = 1;
        for(int i=9; i<all_samples.size(); i++, sample_id++){
            GENO->index[GENO->id_to_sample[sample_id]][all_samples[i]] += 1;
            }
        }

    std::cerr << "writing results... " << std::endl;
    GENO->write_results();

}