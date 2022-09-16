#define _CRT_SECURE_NO_WARNINGS
#include"file.h"

void FileInfo::uncompression(const string& s)
{
	if (getfilepostfix(s) != "hz")
	{
		cout << "格式错误" << endl;
		exit(0);
	}
	FILE* Fin = fopen(s.c_str(), "rb");
	if (Fin == nullptr)
	{
		cout << "解压缩地址错误" << endl;
		exit(0);
	}

	string uncpr_name;
	cout << "请输入解压后的文件名称：";
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
			line_info += '\n';//遇到\n会跳出，所以不会保存\n，所以需要在此保存一下
			Get_line_info(Fin, line_info);
		}
		unsigned char pos = line_info[0];
		record_Info[pos]._ch = line_info[0];
		record_Info[pos]._count = atoi(line_info.c_str()+2);//字符：频次  所以需要加2

	}

	Info invalid;
	HuffmanTree<Info> hf(record_Info, invalid);//还原树

	
	unsigned char buffer[1024];//解压缩
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
				if (ch & 0x80)//检测最高位,即从左到右检查
					cur = cur->_right;//大往右，小往左
				else
					cur = cur->_left;
				ch <<= 1;
				if (cur->_left == nullptr && cur->_right == nullptr)
				{
					filesize += 1;//统计出现了多少字节
					fputc(cur->_val._ch, Fout);
					cur = hf.getroot();
					if (filesize == cur->_val._count)
					{
						break;//根节点的count就是文件的大小，
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