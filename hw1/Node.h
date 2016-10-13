#ifndef NODE_H
#define NODE_H

#include "Module.h"

#include <memory>
#include <algorithm>

namespace Node
{

// A skewed tree consists of these nodes
class Node
{
public:
    Module::Module _data;
    std::shared_ptr<Node> _left;
    std::shared_ptr<Node> _right;
    bool _done; // if both children are operands
    bool _operand;

    Node(Module::Module data) : _data(data), _left(nullptr), _right(nullptr), _done(false), _operand(false){}

    bool Done(){ return _done; }
    bool Operand(){ return _operand; }
    void setDone(bool val){ _done = val; }
    void setOperand(bool val){ _operand = val; }
    void setData(Module::Module data){ _data = data; }
    bool isOperand(){ 
        if(_data.Name() == "H" || _data.Name() == "V")
        { 
            return false;
        }
        else
            return true;
    }

    std::string Name(){ return _data.Name(); } // forwarding function to get the name from the Module
    double Area(){ return _data.Area(); } // forwarding function to get area
    double Ratio(){ return _data.Ratio(); } // forwarding function to get ratio
    double Width(){ return _data.Width(); } // forwarding function to get width
    double Height(){ return _data.Height(); } // forwarding function to get height
    void addPoss(std::pair<double, double> val){ return _data.addPoss(val); } // forwarding function to add a possible solution to the Module
    std::vector<std::pair<double, double>> Possibles(){ return _data.Possibles(); }

}; // node

} // namespace

#endif
