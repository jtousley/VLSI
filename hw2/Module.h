#ifndef MODULE_H
#define MODULE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>

#define INPUT_FILE "input_file.txt"
#define TEST_CASE_ONE "12V3V4V5V6V7V8V9VaVbVcVdVeVfVgViVjVkVlV"
#define TEST_CASE_TWO "12H3H4H5H6H7H8H9HaHbHcHdHeHfHgHiHjHkHlH"
#define TEST_CASE_THREE "213546H7VHVa8V9HcVHgHibdHkVHfeHVlHVjHVH"


namespace Module
{

// A partitioning block
class Module
{
private:
    std::string _name; // usually a single character 1 - L
    double _area; // total area of the block
    double _ratio; // ratio of height to width
    double _width; // width of block
    double _height; // height of block
    std::vector<std::pair<double, double>> _possibles; // first is height, second is width

public:
    Module(char name)
    { 
        _name = name;
        _area = _ratio = _width = _height = 0.0;
    }
    Module(std::string name, double area, double ratio, double width, double height) : _name(name), _area(area), _ratio(ratio), _width(width), _height(height){}

    std::string Name(){ return _name; }
    double Area(){ return _area; }
    double Ratio(){ return _ratio; }
    double Width(){ return _width; }
    double Height(){ return _height; }
    std::vector<std::pair<double,double>> Possibles(){ return _possibles; }
    // adds possible solutions, ignores  any duplicates or larger values every time a new value is added
    void addPoss(std::pair<double, double> val)
    { 
        for(unsigned int i = 0; i < _possibles.size(); i++)
        {
            if((val.first >= _possibles[i].first && val.second > _possibles[i].second) || (val.first > _possibles[i].first && val.second >= _possibles[i].second))
            {
                return;
            }
        }
        _possibles.push_back(val);
    }

};

} //namespace

#endif
