#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<string>
#include<iostream>
#include"huffman.h"

using namespace std;

class Info
{
public:
	char _ch;//�ַ�
	string _s;//����
	size_t _count;//���ִ���
	
	Info(size_t n=0)//ȱʡ
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
	vector<Info> _Info;//32λ��ֻ��256��״̬


	void gethuffmancode(TreeNode<Info>* root);
};