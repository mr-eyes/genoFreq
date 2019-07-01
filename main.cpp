#include <iostream>
#include <fstream>
#include "genoFreq.hpp"
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>


int main(int argc, char** argv)
{

    GenoFreq *GENO = new GenoFreq(argv[1]);
    
    std::ifstream file(GENO->file_name , std::ios_base::in | std::ios_base::binary);
    try {

        boost::iostreams::filtering_istream in;
        in.push(boost::iostreams::gzip_decompressor());
        in.push(file);
        
        std::string str = "##";

        while(str.substr(0,2) == "##"){
            std::getline(in, str);
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
    catch(const boost::iostreams::gzip_error& e) {
         std::cout << e.what() << '\n';
    }


}