#pragma once
#include<iostream>
#include <type_traits>

#ifndef __MY_EXCEPTIONS
#define __MY_EXCEPTIONS

#include <string>

class my_exceptions_class
{
	short i;
	std::string class_name;
public:
	explicit my_exceptions_class(short ii, std::string name) :i(ii), class_name(name) {};
	std::string get_info(void)
	{
		switch (this->i)
		{
		case 1:
			return "Error! " + this->class_name + " is empty!";
			break;
		case 2:
			return "Error! You passed down value out of range of " + this->class_name + "!!!";
			break;
		case 3:
			return "Error! You pass value smaller than 0! Please Kill yoursefl";
			break;
		case 4:
			return "Error! You haven\'t more memory !!!!";
			break;
		case 5:
			return "Error! I wasn\'t find this value !!!!";
			break;
		default:
			return "I don't recognize this error";
			break;
		}
	}
};
#endif // !__MY_EXCEPTIONS

class uf_edge {
public:
	double len;
	int src;
	int dest;
	uf_edge(int source, int destination, double length) :len(length), src(source), dest(destination) {};
	uf_edge(uf_edge* const copy) :len(copy->len), src(copy->src), dest(copy->dest) {};
};


class Union_Find
{
	const int apex_count;
	int* apex;
	int* rank;
	int find_counter = 0;
public:
	Union_Find(int apex_count):apex_count(apex_count)
	{
		this->apex = new int[apex_count];
		this->rank = new int[apex_count]();
		for (int i = 0; i < apex_count; i++)
		{
			apex[i] = i;
		}
	};

	int get_find_counter(void) { return this->find_counter; }

	void _union(int src,int dest)
	{
		apex[_find(src)] = _find(dest);
	}
	
	void _union_br(int src, int dest)
	{
		int x = _find(src);
		int y = _find(dest);
		
		if (rank[x] < rank[y]) 
			apex[x] = y;
		else if (rank[x] > rank[y]) 
			apex[y] = x;
		else
		{
			apex[y] = x;
			rank[x]++;
		}
	}

	int _find(int src)
	{
		find_counter++;
		if (src == apex[src]) return src;
		return _find(apex[src]);
	}

	int _find_pc(int src)
	{
		find_counter++;
		/*if (src != apex[src]) 
			apex[src] = _find_pc(apex[src]);
		return apex[src];*/
		if (src == apex[src]) return src;
		int f = _find_pc(apex[src]);
		if (f != apex[src]) apex[src] = f;
		return f;
	}

};

