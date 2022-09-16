#define _CRT_SECURE_NO_WARNINGS
#include"file.h"

FileInfo::FileInfo()
{
	record_Info.resize(256);
	for (int i = 0; i < 256; i++)
	{
		record_Info[i]._ch = i;//��¼һ���ܲ�����256��״̬����256���ַ�
	}
}

void FileInfo::compression(const string& s)
{
	FILE* Fin = fopen(s.c_str(), "rb");//��Ϊ��Ҫת��Ϊ�����ƣ����Բ��ܴ��ڸ��������ֱ���Զ����ƶ�ȡ

	if (Fin == nullptr)
	{
		cout << "error" << endl;
		return;
	}

	//��Ϊ�����ڸ������ҷ�Χ��0-256������unsigned char
	unsigned char buffer[1024]={0};//ѭ��һ�ζ�ȡ1kb��ֱ����ȡ��ȫ������
	int flag = 0;
	while (1)
	{
		size_t sz = fread(buffer, 1, 1024, Fin);//����ֵ�Ƕ����ĸ���

		if (sz == 0)
		{
			break;
		}

		for (int i = 0; i < sz; i++)
		{
			flag = 1;
			record_Info[buffer[i]]._count++;//ͳ��ÿ���ַ����ִ���
		}
	}
	if (flag == 0)
	{
		cout << "ѹ���ļ�����Ϊ��" << endl;
		exit(0);
	}
	fseek(Fin, 0, SEEK_SET);


	//����һ���������������캯����ʹcountΪ0����ʱ������Чֵ
	Info invalid;
	HuffmanTree<Info> tree(record_Info,invalid);//������

	gethuffmancode(tree.getroot());


	cout << "������ѹ���������:";
	string name_hz   ;
	cin >> name_hz;
	cout << endl;
	name_hz += ".hz";
	FILE* Fout = fopen(name_hz.c_str(), "wb");//�������ļ�����д��

	writeheadinfo(s, Fout);

	char bits = 0;//������������ݣ���Ϊ������ַ�����ʽд�룬������char����	
	int count = 0;//��¼�Ѵ����bitλ
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
					bits |= 1;//����һλ��Ϊ1
				if (count == 8)
				{
					fputc(bits, Fout);
					bits = 0;
					count = 0;
				}
			}
		}
		if (count > 0 && count < 8)//���һλû��8bitʱ
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


void FileInfo::writeheadinfo(const string& s, FILE* Fout)
{
	string head = getfilepostfix(s);//�ļ�����
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
	return s.substr(s.find_last_of('.') + 1);//����.�����λ��
}

