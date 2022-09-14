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

	TreeNode<N>* _left;//��Ҫ�ñ��Ҳ�ɷ��ʣ�������public
	TreeNode<N>* _right;
	TreeNode<N>* _parent;
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

		while (q.size()>1)//��Ҫȡ��������������������������
		{
			TreeNode* left = q.top();//С�����󣬴������
			q.pop();
			TreeNode* right = q.top();
			q.pop();

			TreeNode* parent = new TreeNode(left->_val + right->_val);
			parent->_left = left;
			left->_parent = parent;


			parent->_right = right;
			right->_parent = parent;
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

