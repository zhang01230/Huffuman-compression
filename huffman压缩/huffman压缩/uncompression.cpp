#define _CRT_SECURE_NO_WARNINGS
#include"file.h"

void FileInfo::uncompression(const string& s)
{
	if (getfilepostfix(s) != "hz")
	{
		cout << "��ʽ����" << endl;
		exit(0);
	}
	FILE* Fin = fopen(s.c_str(), "rb");
	if (Fin == nullptr)
	{
		cout << "��ѹ����ַ����" << endl;
		exit(0);
	}

	string uncpr_name;
	cout << "�������ѹ����ļ����ƣ�";
	cin >> uncpr_name;
	cout << endl;
	uncpr_name += '.';
	Get_line_info(Fin, uncpr_name);	

	string line_info;
	Get_line_info(Fin, line_info);
	size_t line_count = atoi(line_info.c_str());

	for (int i = 0; i < line_count; i++)
	{
		line_info = "";
		Get_line_info(Fin, line_info);

		if (line_info == "")
		{
			line_info += '\n';//����\n�����������Բ��ᱣ��\n��������Ҫ�ڴ˱���һ��
			Get_line_info(Fin, line_info);
		}
		unsigned char pos = line_info[0];
		record_Info[pos]._ch = line_info[0];
		record_Info[pos]._count = atoi(line_info.c_str()+2);//�ַ���Ƶ��  ������Ҫ��2

	}

	Info invalid;
	HuffmanTree<Info> hf(record_Info, invalid);//��ԭ��

	
	unsigned char buffer[1024];//��ѹ��
	FILE* Fout = fopen(uncpr_name.c_str(), "wb");
	TreeNode<Info>*cur = hf.getroot();
	size_t filesize = 0;
	while (1)
	{
		int size = fread(buffer, 1, 1024, Fin);
		if (size == 0)
			break;
		for (int i = 0; i < size; i++)
		{
			unsigned char ch = buffer[i];
			for (int j = 0; j < 8; j++)
			{
				if (ch & 0x80)//������λ,�������Ҽ��
					cur = cur->_right;//�����ң�С����
				else
					cur = cur->_left;
				ch <<= 1;
				if (cur->_left == nullptr && cur->_right == nullptr)
				{
					filesize += 1;//ͳ�Ƴ����˶����ֽ�
					fputc(cur->_val._ch, Fout);
					cur = hf.getroot();
					if (filesize == cur->_val._count)
					{
						break;//���ڵ��count�����ļ��Ĵ�С��
					}
				}
			}
		}
	}
	fclose(Fin);
	fclose(Fout);
}


void FileInfo::Get_line_info(FILE* Fin, string&s)
{
	while (!feof(Fin))
	{
		unsigned char ch = fgetc(Fin);
		if (ch == '\n')
			break;
		s += ch;
	}
}