#ifndef command_H
#define command_H

#include <stdio.h>
#include "record.hpp"
#include "condition.hpp"
#include "list2.hpp"

class command : public record
{
	private:
		static const int max_iteams = 3;
		command_type type = command_type::none;
		condition c_name = condition::none;
		condition c_phone = condition::none;
		condition c_group = condition::none;
		operation op1 = operation::none;
		operation op2 = operation::none;
		ordering order[max_iteams] = { };
		ordering order_by[max_iteams] = { };
		char* o_name = nullptr;
		int o_phone = 0;
		int o_group = 0;
		int n_name = 0;
		int n_group = 0;
		int n_phone = 0;
	public:
		command () = default;
		~command () = default;
		//friend class list2;
		//friend class data_base;
		condition operations(char* x);
		bool parse (char * s);
		void print (FILE *fp = stdout) const;
		int apply (int& i);
		int sbor(FILE*np, int k_n, int k_m, int M, FILE*fp = stdin);
		int task_phone(int& i);
		int task_name(int& i);
		int task_group(int& i);
		int task_simbol(int& i);
};

bool proverka(char* s);

# endif