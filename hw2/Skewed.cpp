#include "Skewed.h"

namespace Skewed
{
    void Skewed::Insert(std::shared_ptr<Node::Node>& node, char NPE)
    {
        if(node == nullptr)
        {
            node = std::make_shared<Node::Node>(Node::Node(Module::Module(NPE)));
            if(node->isOperand())
            {
                node->setOperand(true);
                node->setDone(true);
            }
        }
        // insert right
        else if(node->_right == nullptr)
        {
            Insert(node->_right, NPE);
        }
        else if(!node->_right->Done())
        {
            Insert(node->_right, NPE);
        }
        // insert left
        else if(node->_left == nullptr)
        {
            Insert(node->_left, NPE);
        }
        else if(!node->_left->Done())
        {
            Insert(node->_left, NPE);
        }
        
        if(node->_right != nullptr && node->_left != nullptr && node->_left->Done() && node->_right->Done())
        {
            node->setDone(true);
        }
    }

    Skewed::Skewed(std::string NPE)
    {
        std::reverse(NPE.begin(), NPE.end());
        for(unsigned int i = 0 ; i < NPE.size() ; i++)
        {
            Insert(_root, NPE[i]);
        }
    }

    std::string Skewed::post_order_traversal(std::shared_ptr<Node::Node> Node)
    {
        if(Node == nullptr){ return ""; }
        return post_order_traversal(Node->_left) + post_order_traversal(Node->_right) + Node->Name();
    }

    bool Skewed::R_Replace(Module::Module val, std::shared_ptr<Node::Node> node)
    {
        if(node == nullptr){ return false; }
        if(node->Name() == val.Name())
        {
            node->setData(val);
            return true;
        }
        else
        {
            return R_Replace(val, node->_right) || R_Replace(val, node->_left);
        }
    }

    double Skewed::Find_Optimal()
    {
        R_Calculate_Possibilities(_root);
        std::vector<std::pair<double, double>> poss = _root->Possibles();

        // lambdas are love, lambdas are life
        std::pair<double, double> pair = *std::min_element(poss.begin(), poss.end(), 
            [](std::pair<double,double> a, std::pair<double, double> b){ return a.first * a.second < b.first * b.second; } );
        return pair.first * pair.second;
    }

    void Skewed::R_Calculate_Possibilities(std::shared_ptr<Node::Node> node)
    {
        if(node == nullptr) { return; }
        R_Calculate_Possibilities(node->_left);
        R_Calculate_Possibilities(node->_right);

        // only two cases to handle here -- either the node has two children, or zero
        // so no need to check right
        if(node->_left == nullptr)
        {
            double height = node->Height();
            double width = node->Width();
            // blocks can be rotated before they are joined by V and H operators
            // so add both possibilities
            node->addPoss(std::make_pair(height, width));
            node->addPoss(std::make_pair(width, height));
        }
        else if(node->_left != nullptr && node->_right != nullptr)
        {
            std::vector<std::pair<double, double>> Possibles_left = node->_left->Possibles();
            std::vector<std::pair<double, double>> Possibles_right = node->_right->Possibles();

            for(unsigned int i = 0; i < Possibles_left.size(); i++)
            {
                for(unsigned int j = 0; j < Possibles_right.size(); j++)
                {
                    double height = 0.0;
                    double width = 0.0;
                    if(node->Name() == "H")
                    {
                        height = Possibles_left[i].first + Possibles_right[j].first;
                        width = std::max(Possibles_left[i].second, Possibles_right[j].second);
                        // these blocks cannot be rotated, so only one option is possible
                        node->addPoss(std::make_pair(height, width));
                    }
                    else if(node->Name() == "V")
                    {
                        height = std::max(Possibles_left[i].first, Possibles_right[j].first);
                        width = Possibles_left[i].second + Possibles_right[j].second;
                        // these blocks cannot be rotated, so only one option is possible
                        node->addPoss(std::make_pair(height, width));
                    }
                }
            } // for
        } // else
    }


} // namespace
