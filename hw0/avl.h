#ifndef AVL_H
#define AVL_H

#include "node.h"

namespace avlTree
{

template <class TYPE>
class avlTree
{
private:
	std::shared_ptr<node::treeNode<TYPE>> root_;

	void balance_node(std::shared_ptr<node::treeNode<TYPE>> &);
	void R_insert(std::shared_ptr<node::treeNode<TYPE>>& t, TYPE value);
	void rotateLeft(std::shared_ptr<node::treeNode<TYPE>>& t);
	void rotateDoubleLeft(std::shared_ptr<node::treeNode<TYPE>>& t);
	void rotateRight(std::shared_ptr<node::treeNode<TYPE>>& t);
	void rotateDoubleRight(std::shared_ptr<node::treeNode<TYPE>>& t);
	std::string R_traverse_pre_order(const std::shared_ptr<node::treeNode<TYPE>>& t, int level = 0) const;
	std::string R_traverse_in_order(const std::shared_ptr<node::treeNode<TYPE>>& t) const;
	std::string R_traverse_post_order(const std::shared_ptr<node::treeNode<TYPE>>& t) const;
	std::shared_ptr<node::treeNode<TYPE>> R_search(TYPE value, const std::shared_ptr<node::treeNode<TYPE>>& t) const;
	bool R_delete(std::shared_ptr<node::treeNode<TYPE>>& t, TYPE value);
public:
	avlTree();
	void insert(TYPE value);
	bool remove(TYPE value);
	std::shared_ptr<node::treeNode<TYPE>> search(TYPE value) const;
	void delete_tree();
	std::string traverse_pre_order() const;
	std::string traverse_in_order() const;
	std::string traverse_post_order() const;
	std::string check_balance();
        std::shared_ptr<node::treeNode<TYPE>> findMax(std::shared_ptr<node::treeNode<TYPE>>& t);
        bool is_empty(){ return (root_ == nullptr) ? true : false; };
};

// PRIVATE FUNCTIONS
template <class TYPE>
void avlTree<TYPE>::balance_node(std::shared_ptr<node::treeNode<TYPE>> & t)
{
	if(t == nullptr)
	{
		return;
	}

	if( node::height(t->left_) - node::height(t->right_) > 1)
	{
		if( node::height(t->left_->left_) >= node::height(t->left_->right_) )
		{
			rotateRight(t);
		}
		else
		{
			rotateDoubleRight(t);
		}
	}
	else if( node::height(t->right_) - node::height(t->left_) > 1)
	{
		if( node::height(t->right_->right_) >= node::height(t->right_->left_) )
		{
			rotateLeft(t);
		}
		else
		{
			rotateDoubleLeft(t);
		}
	}

	t->height_ = std::max( node::height(t->left_), node::height(t->right_) ) + 1;
}

template <class TYPE>
void avlTree<TYPE>::R_insert(std::shared_ptr<node::treeNode<TYPE>>& t, TYPE value)
{
	if(t == nullptr)
	{
		t = std::make_shared<node::treeNode<TYPE>>(value);
	}
	else
	{
		if(value == t->value_)
		{
			return;
		}
		else if(value < t->value_)
		{
			R_insert(t->left_, value);
		}
		else if(value > t->value_)
		{
			R_insert(t->right_, value);
		}
	}

	balance_node(t);
}

template <class TYPE>
void avlTree<TYPE>::rotateLeft(std::shared_ptr<node::treeNode<TYPE>>& t)
{
	std::shared_ptr<node::treeNode<TYPE>> promotedNode = t->right_;

	t->right_ = promotedNode->left_;
	promotedNode->left_ = t;
	t->height_ = std::max( node::height(t->left_), node::height(t->right_) ) + 1;
	promotedNode->height_ = std::max( node::height(promotedNode->left_), t->height_ ) + 1;
	t = promotedNode;
}

template <class TYPE>
void avlTree<TYPE>::rotateDoubleLeft(std::shared_ptr<node::treeNode<TYPE>>& t)
{
	rotateRight(t->right_);
	rotateLeft(t);
}

template <class TYPE>
void avlTree<TYPE>::rotateRight(std::shared_ptr<node::treeNode<TYPE>>& t)
{
	std::shared_ptr<node::treeNode<TYPE>> promotedNode = t->left_;
	std::shared_ptr<node::treeNode<TYPE>> save_branch = promotedNode->right_;

	t->left_ = save_branch;
	promotedNode->right_ = t;
	t->height_ = std::max( node::height(t->left_), node::height(t->right_) ) + 1;
	promotedNode->height_ = std::max( node::height(promotedNode->left_), t->height_ ) + 1;
	t = promotedNode;
}

template <class TYPE>
void avlTree<TYPE>::rotateDoubleRight(std::shared_ptr<node::treeNode<TYPE>>& t)
{
	rotateLeft(t->left_);
	rotateRight(t);
}

template <class TYPE>
std::string avlTree<TYPE>::R_traverse_pre_order(const std::shared_ptr<node::treeNode<TYPE>>& t, int level) const
{
	if(t == nullptr)
	{
		return "";
	}

	std::stringstream ss;
        if(level != 0)
        {
            ss << std::setw(level) << " ";
        }
	ss
		<< t->value_ << " "
		<< R_traverse_pre_order(t->left_, level + 4) << " " 
		<< R_traverse_pre_order(t->right_, level + 4) << " ";

	return ss.str();
}

template <class TYPE>
std::string avlTree<TYPE>::R_traverse_in_order(const std::shared_ptr<node::treeNode<TYPE>>& t) const
{
	if(t == nullptr)
	{
		return "";
	}

	std::stringstream ss;
	ss
		<< R_traverse_in_order(t->left_) << " "
		<< t->value_ << " "
		<< R_traverse_in_order(t->right_) << " ";

	return ss.str();
}

template <class TYPE>
std::string avlTree<TYPE>::R_traverse_post_order(const std::shared_ptr<node::treeNode<TYPE>>& t) const
{
	if(t == nullptr)
	{
		return "";
	}

	std::stringstream ss;
	ss
		<< R_traverse_post_order(t->right_) << " "
		<< R_traverse_post_order(t->left_) << " "
		<< t->value_ << " ";

	return ss.str();
}

template <class TYPE>
std::shared_ptr<node::treeNode<TYPE>> avlTree<TYPE>::R_search(TYPE value, const std::shared_ptr<node::treeNode<TYPE>>& t) const
{
	if(t == nullptr)
	{
		return nullptr;
	}

	if( value == t->value_ )
	{
		return t;
	}
	else if( value < t->value_ )
	{
		return R_search(value, t->left_);
	}
	else if( value > t->value_ )
	{
		return R_search(value, t->right_);
	}

	return nullptr;
}

template <class TYPE>
bool avlTree<TYPE>::R_delete(std::shared_ptr<node::treeNode<TYPE>>& t, TYPE value)
{
        bool found = false;

	if(t == nullptr)
	{
            return false;
	}
        if(value == t->value_)
        {
            if(t->left_ != nullptr && t->right_ != nullptr)     //case two children
            {
                std::shared_ptr<node::treeNode<TYPE>> switch_node = findMax(t->left_);
                t->value_ = switch_node->value_;
                std::cout << "Switching with node: " << switch_node->value_ << std::endl;
                found = R_delete(switch_node, switch_node->value_);
            }
            else   // case one child
            {
                t = (t->left_ != nullptr) ? t->left_ : t->right_;
                found = true;
            }
        }
        else if(value > t->value_)
        {
            found = R_delete(t->right_, value);
        }
        else if(value < t->value_)
        {
            found = R_delete(t->left_, value);
        }

	balance_node ( t );
        return found;
}


// PUBLIC FUNCTIONS
template <class TYPE>
avlTree<TYPE>::avlTree()
{
	root_ = nullptr;
}

template <class TYPE>
void avlTree<TYPE>::insert(TYPE value)
{
	R_insert(root_, value);
}

template <class TYPE>
bool avlTree<TYPE>::remove(TYPE value)
{
	return R_delete(root_, value);
}

template <class TYPE>
std::shared_ptr<node::treeNode<TYPE>> avlTree<TYPE>::search(TYPE value) const
{
	return R_search(value, root_);
}

template <class TYPE>
void avlTree<TYPE>::delete_tree()
{
	root_ = nullptr;
}

template <class TYPE>
std::string avlTree<TYPE>::traverse_pre_order() const
{
        std::string ordering = R_traverse_pre_order(root_);
        //https://stackoverflow.com/questions/8362094/replace-multiple-spaces-with-one-space-in-a-string
        std::string::iterator last = 
                std::unique(ordering.begin(), ordering.end(),
                [=](char first, char second){ return (first == second) && (first == ' '); }
                );
        ordering.erase(last, ordering.end());
        if(ordering.length() > 0 && ordering[0] == ' ')
        {
            ordering.erase(0, 1);
        }
        return ordering;
}

template <class TYPE>
std::string avlTree<TYPE>::traverse_in_order() const
{
        std::string ordering = R_traverse_in_order(root_);
        //https://stackoverflow.com/questions/8362094/replace-multiple-spaces-with-one-space-in-a-string
        std::string::iterator last = 
                std::unique(ordering.begin(), ordering.end(),
                [=](char first, char second){ return (first == second) && (first == ' '); }
                );
        ordering.erase(last, ordering.end());
        if(ordering.length() > 0 && ordering[0] == ' ')
        {
            ordering.erase(0, 1);
        }
        return ordering;
}

template <class TYPE>
std::string avlTree<TYPE>::traverse_post_order() const
{
        std::string ordering = R_traverse_post_order(root_);
        //https://stackoverflow.com/questions/8362094/replace-multiple-spaces-with-one-space-in-a-string
        std::string::iterator last = 
                std::unique(ordering.begin(), ordering.end(),
                [=](char first, char second){ return (first == second) && (first == ' '); }
                );
        ordering.erase(last, ordering.end());
        if(ordering.length() > 0 && ordering[0] == ' ')
        {
            ordering.erase(0, 1);
        }
        return ordering;
}

template <class TYPE>
std::string avlTree<TYPE>::check_balance()
{
    std::stringstream ss;
    ss << -node::height(root_->left_) + node::height(root_->right_);
    return ss.str();
}

template <class TYPE>
std::shared_ptr<node::treeNode<TYPE>> avlTree<TYPE>::findMax(std::shared_ptr<node::treeNode<TYPE>>& t)
{
    if(t == nullptr)
    {
        std::string s = "Cannot find max of null pointer!\n";
        throw(s);
    }

    while(t->right_ != nullptr)
    {
        t = t->right_;
    }
    //if(t->right_ != nullptr)
    //{
    //    findMax(t->right_);
    //}

    return t;
}

} //namespace avlTree

#endif
