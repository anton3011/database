#ifndef condition_H
#define condition_H

enum class condition
{
	none, // not specified
	eq, //equal
	ne, //not equal
	lt, // less than
	gt, // great than
	le, // less equal
	ge, // great equal
	like, // strings only: match pattern
	nlike, // strings only: not match pattern
};

enum class ordering
{
	none, // not specified
	name, // print name
	phone, // print phone
	group, // print group
};

enum class operation
{
	none, // not specified
	land, // logical and
	lor,// logical or
};

enum class command_type
{
	none,// uninitialized
	quit,// end of input stream
	insert, // add record
	select, // find by conditions specified
	del,// delete record
};

# endif