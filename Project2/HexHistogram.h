#ifndef HEXHISTOGRAM_H
#define HEXHISTOGRAM_H
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <list>
class HexHistogram
{
private:
    std::ifstream file;
    int lines;
    int unique;
    int num_values;
    unsigned int min = 4294967295;
    std::map<unsigned int, int> histo;
    std::list<std::string> hex;
    std::map<int,unsigned int> line_map;
public:
    HexHistogram(std::string file_name);
    ~HexHistogram();
    virtual int get_value_count();
    virtual int get_unique_value_count();
    virtual int get_line_count();
    virtual std::string get_smallest_number(int line_num);
    virtual void print();
};

#endif // HEXHISTOGRAM_H
