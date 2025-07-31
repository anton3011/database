#ifndef LIST2_NODE_HPP
#define LIST2_NODE_HPP
#include "record.hpp"

class list2_node: public record
{
private:
	list2_node* next = nullptr;
	list2_node* prev = nullptr;
public:
	list2_node() {
        next = nullptr;
        prev = nullptr;
    }
	list2_node (const list2_node& r) = delete;
	list2_node (list2_node&& r) = default;
	~list2_node() { next = nullptr; prev = nullptr;}
	//list2_node& operator=(const list2_node& r){*(record*)this = r; next = nullptr; prev = nullptr; return *this;}
	list2_node& operator=(const list2_node& r) = delete;
	list2_node& operator=(list2_node&& r){*(record*)(this) = (record&&)r; next = r.next; r.next = nullptr; prev = r.prev; r.prev = nullptr; return *this;}
	//list2_node& operator=(list2_node&& r) = default;
	friend class list2;
	friend class data_base;
	list2_node* getnext() {return next;}
	list2_node* getprev() {return prev;}
	void setnext(list2_node* a) {next = a;}
	void setprev(list2_node* a) {prev = a;}
};
#endif 
