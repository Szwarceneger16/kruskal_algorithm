#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Union_Find.h"
#include "heap.h"
#include "list.h"
#include <time.h>

inline bool compare(uf_edge* const left, uf_edge* const right) { return left->len < right->len; }

void printer(uf_edge* const in)
{
	std::cout << in->src << " -> " << in->dest << " || " << in->len << std::endl;
}

class kruskal
{
	int apex_count;
	int edge_count;
	double sum_of_rank;
	std::ifstream input_file;
	DynamicArray<uf_edge*> tab;
	list<uf_edge*> mst;
	double sorting_time;
	double kruskal_time;
	int find_counter;

public:
	kruskal(std::string path,bool union_by_rank = false,bool path_compression = false)
	{
		input_file.open(path);
		if (!input_file.good()) throw my_exceptions_class(5, "kruskal_mst");

		std::string line;
		input_file >> apex_count;
		for (int i = 0; i <= this->apex_count; i++) getline(input_file, line);
		input_file >> edge_count;
		//std::cout << apex_count << "  " << edge_count;
		int a = 0, b = 0; double c = 0;
		for (int i = 0; i < this->edge_count; i++)
		{
			input_file >> a >> b >> c;
			tab.add(new uf_edge(a, b, c));
		}
		clock_t start = clock();
		heap_sort_inplace<uf_edge*>(tab, compare);
		clock_t end = clock();
		sorting_time = (double(end) - double(start)) / CLOCKS_PER_SEC;
		/*tab.print(printer);
		std::cout << "--------------" << std::endl;*/
		
		Union_Find uf(this->apex_count);
		uf_edge* tmp;
		start = clock();
		if (union_by_rank && !path_compression)
		{
			for (int i = 0; i < this->edge_count; i++)
			{
				tmp = tab[i];
				if (uf._find(tmp->src) != uf._find(tmp->dest))
				{
					mst.add_tail(new uf_edge(tmp));
					uf._union_br(tmp->src, tmp->dest);
					sum_of_rank += tmp->len;
				}
			}
		}
		else if (union_by_rank && path_compression)
		{
			for (int i = 0; i < this->edge_count; i++)
			{
				tmp = tab[i];
				if (uf._find_pc(tmp->src) != uf._find_pc(tmp->dest))
				{
					mst.add_tail(new uf_edge(tmp));
					uf._union_br(tmp->src, tmp->dest);
					sum_of_rank += tmp->len;
				}
			}
		}
		else if (!union_by_rank && path_compression)
		{
			for (int i = 0; i < this->edge_count; i++)
			{
				tmp = tab[i];
				if (uf._find_pc(tmp->src) != uf._find_pc(tmp->dest))
				{
					mst.add_tail(new uf_edge(tmp));
					uf._union(tmp->src, tmp->dest);
					sum_of_rank += tmp->len;
				}
			}
		}
		else
		{
			for (int i = 0; i < this->edge_count; i++)
			{
				tmp = tab[i];
				if (uf._find(tmp->src) != uf._find(tmp->dest))
				{
					mst.add_tail(new uf_edge(tmp));
					uf._union(tmp->src, tmp->dest);
					sum_of_rank += tmp->len;
				}
			}
		}
		end = clock();
		kruskal_time = (double(end) - double(start)) / CLOCKS_PER_SEC;
		find_counter = uf.get_find_counter();
	}

	int get_edge_count(void) { return this->edge_count; }
	double get_sorting_time(void) { return this->sorting_time; }
	double get_sum_of_rank(void) { return this->sum_of_rank; }
	double get_kruskal_time(void) { return this->kruskal_time; }
	int get_find_counter(void) { return this->find_counter; }

	list<uf_edge*> get_mst(void)
	{
		return this->mst;
	}

	//~kruskal()
	//{
	//	tab.erase_ptr();
	//}
};

