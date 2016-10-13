#ifndef SKEWED_H
#define SKEWED_H

#include "Node.h"

namespace Skewed
{

// Tree to store Modules for computing floor plans, NPE, etc
class Skewed
{
private:
    std::shared_ptr<Node::Node> _root;
    std::string post_order_traversal(std::shared_ptr<Node::Node>);
    bool R_Replace(Module::Module val, std::shared_ptr<Node::Node> node);
    void R_Calculate_Possibilities(std::shared_ptr<Node::Node> node);
public:
    Skewed(std::string NPE);
    Skewed(std::vector<Module::Module> INPUT);
    void Insert(std::shared_ptr<Node::Node>& node, char NPE);
    bool Replace(Module::Module val){ return R_Replace(val, _root); }
    double Find_Optimal();
    std::string Get_Post_Order(){ return post_order_traversal(_root); }

};

} //namespace

#endif
