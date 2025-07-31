#ifndef DATA_BASE_HPP
#define DATA_BASE_HPP
#include "list2.hpp"
#include "list2_node.hpp"
#include <stdio.h>
#include <cstring>
using namespace std;

class data_base
{
private:
	list2 **data;
	int d_len_group = 1000;
public:
    data_base() = default;
	void fill(list2 *a);
	data_base(const data_base& x) {data = x.data;}
	data_base(data_base&& x) { data = x.data; x.data = nullptr;}
	~data_base() { if(data) delete_data(); data = nullptr;}
	data_base& operator=(const data_base& x) = delete;
	data_base& operator=(data_base&& x){ data = x.data; x.data = nullptr; return *this;}
	friend class list2;
	friend class record;
	friend class command;
	void delete_data();
    void free_data();
	void r_data(list2 *b);
	void print_data(const ordering * p);
	void delete_spisoc1(list2_node* head2, list2 *arr);
};
#endif 
