#define _CRT_SECURE_NO_WARNINGS
#include"file.h"

FileInfo::FileInfo()
{
	_Info.resize(256);
	for (int i = 0; i < 256; i++)
	{
		_Info[i]._ch = i;//��¼һ���ܲ�����256��״̬����256���ַ�
	}
}

void FileInfo::compression(const string& s)
{
	FILE* Fin = fopen(s.c_str(), "r");
	if (Fin == nullptr)
	{
		cout << "error" << endl;
		return;
	}
	char buffer[1024];//һ�ζ�1kb
	while (1)
	{
		size_t sz=fread(buffer, 1, 1024, Fin);//����ֵ�Ƕ����ĸ���
		
		if (sz == 0)
			break;

		for (int i = 0; i < sz; i++)
		{
			_Info[ buffer[i] ]._count++;//ͳ��ÿ���ַ����ִ���
		}

		Info invalid;//���캯����ʹcountΪ0����ʱ������Чֵ
		HuffmanTree<Info> tree(_Info,invalid);//������

		gethuffmancode(tree.getroot());
	}
}

void FileInfo::gethuffmancode(TreeNode<Info>* root)
{
	if (root == nullptr)
		return;
	gethuffmancode(root->_left);
	gethuffmancode(root->_right);

	if (root->_left == nullptr && root->_right == nullptr)
	{
		string& _s = _Info[root->_val._ch]._s;
		TreeNode<Info>* cur = root;
		TreeNode<Info>* parent = cur->_parent;
		while (parent)
		{
			if (cur == parent->_left)//��������
				_s += '0';
			else
				_s += '1';
			cur = parent;
			parent = cur->_parent;
		}
		reverse(_s.begin(), _s.end());
	}
}

void FileInfo::uncompression(const string& s)
{

}