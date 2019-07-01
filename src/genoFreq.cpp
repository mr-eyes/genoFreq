#include "genoFreq.hpp"
#include <sstream>
#include <fstream>


GenoFreq::GenoFreq(std::string filename){ 
    this->file_name = filename;
    this->get_all_genotypes();
}


std::string GenoFreq::extract_gtype(const std::string& s)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);

   while (std::getline(tokenStream, token, ':'))
   {
      tokens.push_back(token);
      break;
   }
   
   return tokens[0];
}


std::vector<std::string> GenoFreq::extract_all_gtypes(const std::string& s)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);

   while (std::getline(tokenStream, token, '\t'))
      tokens.push_back(token.substr(0,3));
   
   return tokens;
}


std::vector<std::string> GenoFreq::split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);

   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   
   return tokens;
}

void GenoFreq::analyze(std::string &record){

    // std::unordered_map<int, std::string>::iterator it;
    
    std::string gtype;

    std::vector<std::string> all_samples = this->split(record, '\t');

        for(int i=9; i<all_samples.size(); i++){
            gtype = this->split(all_samples[i], ':')[0];
            this->index[this->id_to_sample[i+1]][gtype] += 1;
        }  
}


void GenoFreq::get_all_genotypes(){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            this->all_genotype.push_back(std::to_string(i) + "/" + std::to_string(j));
        }
    }
}


void GenoFreq::create_index(std::vector<std::string> &samples_list){

    int sample_id = 1;

    for(const auto &sample_name : samples_list){
        this->id_to_sample[sample_id] = sample_name;
        this->sample_to_id[sample_name] = sample_id;

        for(const auto &gtype : this->all_genotype){
            this->index[sample_name][gtype] = 0;
        }

    sample_id++;
    
    }

}


void GenoFreq::write_results(){


    std::ofstream myfile;

    myfile.open (this->file_name + "_genoFreq.tsv");
    myfile << "sample\t";

    std::string delimiter = "";
    for(const auto& gtype : this->all_genotype){
        myfile << delimiter << gtype;
        delimiter = "\t";
    }
    myfile << std::endl;
    

//    delimiter = "";

    for (auto & sample : this->index){
        myfile << sample.first << '\t';
        
        delimiter = "";
        for(const auto& gtype: this->all_genotype){
            myfile << delimiter << sample.second[gtype];
            delimiter = "\t";
        }

            myfile << "\n";
        }

    myfile.close();

}
