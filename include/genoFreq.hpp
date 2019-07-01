#include <string>
#include <unordered_map>
#include <vector>
#include <google/sparse_hash_map>

using google::sparse_hash_map;      // namespace where class lives by defaul


class GenoFreq{

public:

    std::string file_name;
    std::vector<std::string> all_genotype = {"./."};
    sparse_hash_map<std::string, sparse_hash_map<std::string,int>> index;
    std::unordered_map<int,std::string> id_to_sample;
    std::unordered_map<std::string,int> sample_to_id;

    GenoFreq(std::string filename);

    void get_all_genotypes();

    void create_index(std::vector<std::string> &);

    void analyze(std::string &);

    void write_results();

    std::string extract_gtype(const std::string& s);

    std::vector<std::string> extract_all_gtypes(const std::string& s);

    std::vector<std::string> split(const std::string& record, char delimiter);


};