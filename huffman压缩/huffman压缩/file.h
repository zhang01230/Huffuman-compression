#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<string>
#include<iostream>
#include"huffman.h"

using namespace std;

class Info
{
public:
	char _ch;//字符
	string _s;//编码
	size_t _count;//出现次数
	
	Info(size_t n=0)//缺省
		:_count(n)
		,_ch(0)
	{
		;
	}

	Info operator+(const Info& other)const
	{
		return Info(_count + other._count);
	}

	bool operator>(const Info& other)const
	{
		return _count > other._count;
	}

	bool operator==(const Info& other)const
	{
		return _count == other._count;
	}

	bool operator<(const Info& other)const
	{
		return _count < other._count;
	}
	bool operator!=(const Info& other)const
	{
		return _count != other._count;
	}
};


class FileInfo
{
public:
	FileInfo();
	void compression(const string& s);
	void uncompression(const string& s);
	vector<Info> _Info;//32位下只有256种状态


	void gethuffmancode(TreeNode<Info>* root);
};