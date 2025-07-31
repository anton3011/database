#ifndef record_H
#define record_H
#include <memory>
#include <stdio.h>
#include "condition.hpp"


enum class read_status
{
	success,
	eof,
	format,
	memory,
};


class record
{
	private:
		std::unique_ptr<char []> name = nullptr;
		int phone = 0;
		int group = 0;
	public:
		record () = default;
		~record () = default;

		const char * get_name () const { return name.get (); }
		int get_phone () const { return phone; }
		int get_group () const { return group; }

		int init (const char *n, int p, int g);
		record (record &&x) = default;
		record& operator= (record&& x) = default;
		record (const record &x) = delete;
		record& operator= (const record&x) = delete;

		bool compare_name (condition x, const record& y) const;
		bool compare_phone (condition x, const record& y) const;
		bool compare_group (condition x, const record& y) const;

		void print (const ordering order[] = nullptr, FILE * fp = stdout);
		void print_r (FILE * fp = stdout);
		read_status read (FILE *fp = stdin);
};
# endif