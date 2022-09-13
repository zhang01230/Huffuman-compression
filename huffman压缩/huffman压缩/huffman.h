#pragma once

#include<string>
#include<vector>
#include<queue>
using namespace std;

template <class N>
class TreeNode
{
public:
	TreeNode(const N& val)
		:_left(nullptr)
		,_right(nullptr)
		, _val(val)
	{
		;
	}

	TreeNode* _left;//需要让别的也可访问，所以是public
	TreeNode* _right;
	TreeNode* _parent;
	N _val;//根据传参类型来创建对象
};



template<class T>//传参类型
class HuffmanTree
{
public:
	typedef TreeNode<T> TreeNode;

	class cmp
	{
	public:
		bool operator()(const TreeNode* left, const TreeNode* right)
		{
			return left->_val > right->_val;
		}
	};
	
	HuffmanTree()
		:_root(nullptr)
	{
		;
	}

	HuffmanTree(const vector<T> &val)
	{
		priority_queue< TreeNode* , vector<TreeNode*>, cmp> q;
		for (auto&v : val)
		{
			q.push(new TreeNode(v));
		}

		while (q.size()>1)//需要取出两个数，所以至少有两个数
		{
			TreeNode* left = q.top();//小的在左，大的在右
			q.pop();
			TreeNode* right = q.top();
			q.pop();

			TreeNode* parent = new TreeNode(left->_val + right->_val);
			parent->_left = left;
			parent->_right = right;
			q.push(parent);//用这一棵树的父节点存入优先级队列进行比较，从而合成更大的树
		}

		_root = q.top();//跳出循环时，队首就是整棵树的根节点

	}

	~HuffmanTree()
	{
		Destory(_root);
	}



	void Destory(TreeNode* root)
	{
		if (root)
		{
			Destory(root->_left);
			Destory(root->_right);
			delete(root);
			root = nullptr;
		}
	}

private:
	TreeNode* _root;
};

