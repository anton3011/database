#ifndef LIST2_HPP
#define LIST2_HPP
#include "record.hpp"
#include "condition.hpp"
#include "list2_node.hpp"
//#include "data_base.hpp"
#include <stdio.h>
#include <cstring>

class list2
{
private:
	list2_node* head = nullptr;
	list2_node*** vectors = nullptr;
	list2_node**** hesh = nullptr;
	int* len_hesh = nullptr;
	int l = 1000;
	int l_hesh = 5;
	int k_massiv = 0;
	int k_name = 0;
	int m = 0;
	int a_hesh = 95;
	//list2* groups = nullptr;
public:
	list2() = default;
	list2 (const list2& x) {printf("copir\n"); head = x.head; vectors = x.vectors; hesh = x.hesh; len_hesh = x.len_hesh; k_massiv = x.k_massiv; k_name = x.k_name; m = x.m;}
	list2 (list2&& x) {printf("perem\n"); head = x.head; x.head = nullptr; vectors = x.vectors; x.vectors = nullptr; hesh = x.hesh; x.hesh = nullptr; len_hesh = x.len_hesh; len_hesh = nullptr; len_hesh = x.len_hesh; k_massiv = x.k_massiv; k_name = x.k_name; m = x.m;}
	~list2() { if(head) delete_list(); head = nullptr; if(vectors) delete_vectors(); vectors = nullptr;  if(hesh) delete_hesh(); hesh = nullptr; if(len_hesh) delete [] len_hesh; len_hesh = nullptr; }
	list2& operator=(const list2& x) = delete;
	list2& operator=(list2&& x){ head = x.head; x.head = nullptr; vectors = x.vectors; x.vectors = nullptr; hesh = x.hesh; x.hesh = nullptr; len_hesh = x.len_hesh; len_hesh = nullptr; len_hesh = x.len_hesh; k_massiv = x.k_massiv; k_name = x.k_name; m = x.m; return *this;}
	void delete_list();
	void delete_vectors();
	void delete_hesh();
	void print_list();
	int print_vectors(const ordering * p);
	int print_len();
	int print_hesh(const ordering * p);
	int get_length ();
	int read_list();
	friend class record;
	friend class data_base;
	friend class command;
	void Sort1(int i);
	void merge(int i, int n);
	read_status read (FILE*fp);
	read_status r_vector();
	read_status r_hesh();
	int print (const ordering * p);
    int print ();
	int get_length () const;
	list2_node* gethead() {return head;} 
	int task3_p(int k);
	static int f1(int x, int y){ return x - y; }
	static int f2(int x, int y){ return y - x; }
	static int f3(int x, int y){  if(x == y) return 1; return 0; }
	static int f4(int x, int y){ return x - y + 1; }
	static int f5(int x, int y){ return y - x + 1; }
	static int f6(int x, int y){ if(x != y) return 1; return 0; }
	static int g1(const char* x, char* y) {   if(strcmp(x,y) > 0) return 0; return 1; }
	static int g2(const char* x, char* y) {  if(strcmp(x,y) < 0) return 0; return 1;  }
	static int g3(const char* x, char* y) { if(strcmp(x, y) == 0) return 0; return 1;}
	static int g4(const char* x, char* y) {  if(strcmp(x,y) >= 0) return 0; return 1;  }
	static int g5(const char* x, char* y) {  if(strcmp(x,y) <= 0) return 0; return 1;  }
	static int g6(const char* x, char* y) {  if(strcmp(x, y) != 0) return 0; return 1; }
	int task1(int k, int (*cmp)(int, int),const ordering * p, int f_del, int sort, list2* a);
	int task2(int k, int (*cmp)(int, int),const ordering * p, int f_del, int sort, list2* a);
	int task3(char* k, int (*cmp)(const char*, char*),const ordering * p, int f_del, int sort, list2* arr);
	static int strstr_1 (const char *s1, char *s2);
	static int strstr_2 (const char *s1, char *s2);
	static int strcmp12(const char* s1, char* s2);
	static int strcmp34(const char* s1, char* s2);
	static int strcmp5(const char* s1, char* s2);
	static int strcmp6(const char* s1, char* s2);
	static int func(char c, char* s, int& m);
	int task4(char* k, int (*cmp)(const char*, char*),const ordering * p, int flag, int f_del, int sort, list2* a);
	int task8(int a, int (*cmp1)(const int, int), int b, int (*cmp2)(const int, int), char* c, int (*cmp3)(const char*, char*), const ordering * p, int flag, int l, int f_del, int sort, list2* arr);
	int task5(int a, int (*cmp1)(const int, int), int b, int (*cmp2)(const int, int), const ordering * p, int l, int f_del, int sort, list2* arr);
	int task6(int b, int (*cmp2)(const int, int), char* c, int (*cmp3)(const char*, char*), const ordering * p, int flag, int l, int f_del, int sort, list2* arr);
	int task7(int a, int (*cmp1)(const int, int), char* c, int (*cmp3)(const char*, char*), const ordering * p, int flag, int l, int f_del, int sort, list2* arr);
	int isert_(char* s, int a, int b);
	void isert_2(char* s, int a, int b);
	int solve8(char**a,char**b, int n);
	void plus(list2_node* curr1);
	int number_hesh(const char* s);
	int srav(int i, list2_node* currmin, list2_node* curr);
	void delete_spisoc(list2_node* head2, int flag = -1);
	list2_node *merge(list2_node *a, list2_node *b);
	list2_node * mergesort(list2_node* head1);
	void open_file(int k_n, int k_m, int M);
	int strcmp_4 (const char *s1, const char *s2, int a1, int a2);

    int find_record(char *s, int ph, int gr);
};
#endif 
