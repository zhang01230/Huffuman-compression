#define _CRT_SECURE_NO_WARNINGS
#include"file.h"

FileInfo::FileInfo()
{
	record_Info.resize(256);
	for (int i = 0; i < 256; i++)
	{
		record_Info[i]._ch = i;//记录一共能产生的256种状态，即256个字符
	}
}

void FileInfo::compression(const string& s)
{
	FILE* Fin = fopen(s.c_str(), "rb");//因为需要转化为二进制，所以不能存在负数，因此直接以二进制读取

	if (Fin == nullptr)
	{
		cout << "error" << endl;
		return;
	}

	//因为不存在负数，且范围是0-256所以用unsigned char
	unsigned char buffer[1024]={0};//循环一次读取1kb，直到读取完全部内容
	int flag = 0;
	while (1)
	{
		size_t sz = fread(buffer, 1, 1024, Fin);//返回值是读到的个数

		if (sz == 0)
		{
			break;
		}

		for (int i = 0; i < sz; i++)
		{
			flag = 1;
			record_Info[buffer[i]]._count++;//统计每个字符出现次数
		}
	}
	if (flag == 0)
	{
		cout << "压缩文件不能为空" << endl;
		exit(0);
	}
	fseek(Fin, 0, SEEK_SET);


	//创建一个匿名函数，构造函数会使count为0，此时就是无效值
	Info invalid;
	HuffmanTree<Info> tree(record_Info,invalid);//构建树

	gethuffmancode(tree.getroot());


	cout << "请输入压缩后的名称:";
	string name_hz   ;
	cin >> name_hz;
	cout << endl;
	name_hz += ".hz";
	FILE* Fout = fopen(name_hz.c_str(), "wb");//创建该文件进行写入

	writeheadinfo(s, Fout);

	char bits = 0;//储存二进制数据，因为最后以字符串形式写入，所以用char类型	
	int count = 0;//记录已储存的bit位
	while (1)
	{
		size_t size = fread(buffer, 1, 1024, Fin); 
		if (size == 0)
			return;
		for (int i = 0; i < size; i++)
		{
			string& _s = record_Info[buffer[i]]._s;
			for (int j = 0; j < _s.size(); j++)
			{
				count++;
				bits <<= 1;
				if (_s[j] == '1')
					bits |= 1;//让这一位变为1
				if (count == 8)
				{
					fputc(bits, Fout);
					bits = 0;
					count = 0;
				}
			}
		}
		if (count > 0 && count < 8)//最后一位没满8bit时
		{
			bits <<= (8 - count);
			fputc(bits, Fout);
		}
		fclose(Fin);
		fclose(Fout);
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
		string& _s = record_Info[root->_val._ch]._s;
		TreeNode<Info>* cur = root;
		TreeNode<Info>* parent = cur->_parent;
		while (parent)
		{
			if (cur == parent->_left)//是左子树
				_s += '0';
			else
				_s += '1';
			cur = parent;
			parent = cur->_parent;
		}
		reverse(_s.begin(), _s.end());
	}
}


void FileInfo::writeheadinfo(const string& s, FILE* Fout)
{
	string head = getfilepostfix(s);//文件类型
	head += "\n";

	int line_count = 0;
	string frequence;
	for (auto&fre : record_Info)
	{
		if (fre._count == 0)
			continue;
		frequence += fre._ch;
		frequence += "-";
		frequence += to_string(fre._count);
		frequence += '\n';

		line_count++;
	}
	head += to_string(line_count);
	head += '\n';
	head += frequence;

	fwrite(head.c_str(), 1, head.size(), Fout);
}


string FileInfo::getfilepostfix(const string s)
{
	return s.substr(s.find_last_of('.') + 1);//返回.后面的位置
}

