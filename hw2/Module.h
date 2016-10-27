#ifndef MODULE_H
#define MODULE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>

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
    std::vector<std::pair<double,double>>& Possibles(){ return _possibles; }
    // adds possible solutions, ignores  any duplicates or larger values every time a new value is added
    void addPoss(std::pair<double, double>& val)
    { 
        //_possibles.erase(std::remove_if(_possibles.begin(), _possibles.end(), [&](std::pair<double, double> input){
        //    return ((input.first >= val.first && input.second > val.second) || (input.first > val.first && input.second >= val.second));
        //    }), _possibles.end());

        //for(unsigned int i = 0; i < _possibles.size(); i++)
        //{
        //    if((val.first >= _possibles[i].first && val.second > _possibles[i].second) || (val.first > _possibles[i].first && val.second >= _possibles[i].second))
        //    {
        //        return;
        //    }
        //}
        _possibles.push_back(val);

        for(unsigned int i = 0; i < _possibles.size(); i++)
        {
            _possibles.erase(std::remove_if(_possibles.begin(), _possibles.end(), [&](std::pair<double, double> input){
                return ((input.first >= _possibles[i].first && input.second > _possibles[i].second) || (input.first > _possibles[i].first && input.second >= _possibles[i].second));
                }), _possibles.end());
        }
    }

};

} //namespace

#endif
