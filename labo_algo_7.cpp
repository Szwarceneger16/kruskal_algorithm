// labo_algo_7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "kruskal.h"

int main()
{
	kruskal k1("g1.txt",true,true);
	list<uf_edge*> mst = k1.get_mst();
	mst.print(printer);
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Liczba krawedzi i suma wag: " << k1.get_edge_count() << ", " << k1.get_sum_of_rank() << std::endl;
	std::cout << "Czas sortowania: " << k1.get_sorting_time();
	std::cout << " . Czas oblcizen petli kruskala: " << k1.get_kruskal_time() << std::endl;
	std::cout << "Liczba operacji find: " << k1.get_find_counter() << std::endl;
}
