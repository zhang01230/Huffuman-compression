#pragma once

#include<vector>
#include<queue>
using namespace std;

template <class N>
class TreeNode
{
public:
	TreeNode(const N& val=N())
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		, _val(val)
	{
		;
	}

	TreeNode<N>* _left;//需要让别的也可访问，所以是public
	TreeNode<N>* _right;
	TreeNode<N>* _parent;
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
			return (left->_val > right->_val);
		}
	};
	
	HuffmanTree()
		:_root(nullptr)
	{
		;
	}

	TreeNode* getroot()
	{
		return _root;
	}

	HuffmanTree(const vector<T> &val,const T& invalid)
	{
		priority_queue< TreeNode* , vector<TreeNode*>, cmp> q;
		for (auto&v : val)
		{
			if(v!=invalid)
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
			left->_parent = parent;


			parent->_right = right;
			right->_parent = parent;
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

