#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <iomanip>
#include <algorithm>

namespace node
{

template <class TYPE>
class treeNode
{
public:
	TYPE value_;
	int height_;
	std::shared_ptr<treeNode> left_;
	std::shared_ptr<treeNode> right_;

	treeNode(TYPE value)
	{
		left_ = nullptr;
		right_ = nullptr;
		value_ = value;
		height_ = 0;
	}
};

template <class TYPE>
int height(std::shared_ptr<node::treeNode<TYPE>> t)
{
	if(t == nullptr)
	{
		return -1;
	}
	return t->height_;
}

} // namespace node

#endif
