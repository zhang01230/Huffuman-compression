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

	TreeNode* _left;//��Ҫ�ñ��Ҳ�ɷ��ʣ�������public
	TreeNode* _right;
	TreeNode* _parent;
	N _val;//���ݴ�����������������
};



template<class T>//��������
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

		while (q.size()>1)//��Ҫȡ��������������������������
		{
			TreeNode* left = q.top();//С�����󣬴������
			q.pop();
			TreeNode* right = q.top();
			q.pop();

			TreeNode* parent = new TreeNode(left->_val + right->_val);
			parent->_left = left;
			parent->_right = right;
			q.push(parent);//����һ�����ĸ��ڵ�������ȼ����н��бȽϣ��Ӷ��ϳɸ������
		}

		_root = q.top();//����ѭ��ʱ�����׾����������ĸ��ڵ�

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

