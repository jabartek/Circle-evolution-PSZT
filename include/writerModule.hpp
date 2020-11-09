#include <iostream>
#include <fstream>
#include <vector>


class WriterModule{

    std::string pathToFile_;
    std::string delimiter_;
    std::ofstream file_;

    public:
    WriterModule(std::string path = "/data/result.csv", std::string delimiter="\t"): pathToFile_(path), delimiter_(delimiter) {
        file_.open(pathToFile_, std::ios::out | std::ios::app);
    };

    template<typename Data>
    void writeLine(std::vector<Data> data){
        for (Data vData : data){
            file_<<vData<<delimiter_;
        }
        file_<<std::endl;;
    }

    void setDelimiter(std::string delimiter){
        this->delimiter_ = delimiter;
    }

    void setPathToFile(std::string path){
        this->pathToFile_ = path;
        file_.open(path, std::ios::out | std::ios::app);
    }

};