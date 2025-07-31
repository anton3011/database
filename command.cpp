#include <stdio.h>
#include <cstring>
#include "record.hpp"
#include "command.hpp"
#include "condition.hpp"
#include "list2.hpp"
#include "data_base.hpp"
#include <iostream>
#define LEN 1234
using namespace std;


bool command::parse(char * s) {
	c_name = condition::none;
	c_phone = condition::none;
	c_group = condition::none;
    type = command_type::none;
    op1 = operation::none;
    op2 = operation::none;
	o_phone = 0;
	o_group = 0;
    n_phone = 0;
    n_group = 0;
    n_name = 0;
    int i = 0;
    char* s1 = s;
    char* s2;
	s1 = strtok(s, " (");
    if(!s1)
        return false;
    if(strcmp(s1, "quit;") == 0 || strcmp(s1, "quit") == 0 || strcmp(s1, "quit;\n") == 0 ){
        type = command_type::quit;
        return true;
    }
    else if(strcmp(s1, "delete;") == 0 || strcmp(s1, "delete") == 0  || strcmp(s1, "delete;\n") == 0 ){
        type = command_type::del;
        s2 = s1;
        if(strcmp(s2, "delete;\n") == 0 || strcmp(s1, "delete;") == 0)
            return true;
        s1 = strtok(nullptr, " ");
        if(!s1)
            return false;
        if(strcmp(s1, ";") == 0)
            return true;
    }
    else if(strcmp(s1, "insert(") == 0 || strcmp(s1, "insert") == 0){
        type = command_type::insert;
        s1 = strtok(nullptr, " ();,");
        if(!s)
            return false;
        int n = strlen(s1);
        if(s1[n-1] == '\n')
            s1[n-1] = '\0';
        o_name = s1;
        s1 = strtok(nullptr, " ();,");
        if(s1 == nullptr)
            return false;
        if(proverka(s1) != true)
            return false;
        o_phone = stoi(s1);
        s1 = strtok(nullptr, " ();,");
        if(s1 == nullptr)
            return false;
        if(proverka(s1) != true)
            return false;
        o_group = stoi(s1);
        return true;
    }
    else if(strcmp(s1, "select") == 0){
        type = command_type::select;
        s1 = strtok(nullptr, " ;");
        if(!s1)
            return false;
    }
    while(s1 && strcmp(s1,"where") != 0 && strcmp(s1,"order") != 0  && i < 3) {
        if(strcmp(s1,"*") == 0)
        {
            s1 = strtok(nullptr, " ;");
            break;
        }
        if(strcmp(s1,"name") == 0 || strcmp(s1,"name,") == 0){
            order[i] = ordering::name;
            i++;
        }
        else if(strcmp(s1,"phone") == 0 || strcmp(s1,"phone,") == 0){
            order[i] = ordering::phone;
            i++;
        }
        else if(strcmp(s1,"group") == 0 || strcmp(s1,"group,") == 0){
            order[i] = ordering::group;
            i++;
        }
        s1 = strtok(nullptr, " ;");
    }
    for(; i < 3; i++)
        order[i] = ordering::none;
    if(!s1 || strcmp(s1,"\n") == 0)
    {
        for(i = 0; i < 3; i++)
            order_by[i] = ordering::none;
        return true;
    }
    if(strcmp(s1,"where") != 0 && strcmp(s1,"order") != 0)
        return false;
    i = 0;
    while(s1 && i < 3 && strcmp(s1,"\n") != 0)
    {
        if(strcmp(s1, "order") == 0)
            break;
        if(strcmp(s1, "and") == 0) {
            if(op1 == operation::none)
                op1 = operation::land;
            else
                op2 = operation::land;
        }
        else if(strcmp(s1, "or") == 0) {
            if(op1 == operation::none)
                op1 = operation::lor;
            else
                op2 = operation::lor;
        }
        s1 = strtok(nullptr, " ");
        if(!s1)
            return false;
        if(strcmp(s1,"name") == 0) {
        	s1 = strtok(nullptr, " ");
            if(!s1)
                return false;
            c_name = operations(s1);
            if(strcmp(s1,"like") == 0)
                c_name = condition::like;
            else if(strcmp(s1,"not") == 0)
            {
                s1 = strtok(nullptr, " ");
                if(!s1)
                    return false;
                if(strcmp(s1,"like") == 0)
                    c_name = condition::nlike;
            }
        	s1 = strtok(nullptr, " ;");
            if(!s1)
                return false;
            int n = strlen(s1);
            if(s1[n-1] == '\n')
                s1[n-1] = '\0';
            o_name = s1;
            n_name = i + 1;
        	if(c_name == condition::none)
        		return false;
        }
        else if(strcmp(s1,"phone") == 0) {
            n_phone = i + 1;
        	s1 = strtok(nullptr, " ");
            if(s1 == nullptr)
            {
                return false;
            }
        	c_phone = operations(s1);
        	s1 = strtok(nullptr, " ;");
            if(s1 == nullptr)
            {
                return false;
            }
            if(proverka(s1) != true)
            {
                return false;
            }
        	o_phone = stoi(s1);
        	if(c_phone == condition::none || c_phone == condition::like || c_phone == condition::nlike)
        		return false;
        }
        else if(strcmp(s1,"group") == 0) {
            n_group = i + 1;
        	s1 = strtok(nullptr, " ");
            if(s1 == nullptr)
            {
                return false;
            }
        	c_group = operations(s1);
        	s1 = strtok(nullptr, " ;");
            if(s1 == nullptr)
                return false;
            if(proverka(s1) != true)
            {
                return false;
            }
        	o_group = stoi(s1);
        	if(c_group == condition::none || c_group == condition::like || c_group == condition::nlike)
        		return false;
        }
        i++;
        if(s1)
            s1 = strtok(nullptr, " ");
    }
    i = 0;
    while(s1 &&  i < 3) {
        if(strcmp(s1,"\n") == 0)
            return true;
        if(i == 0 && strcmp(s1, "order") != 0)
            return false;
        if(i == 0)
        {
            s1 = strtok(nullptr, " ");
            if(!s1 || strcmp(s1, "by") != 0)
                return false;
            s1 = strtok(nullptr, " ;");
            if(!s1 || strcmp(s1,"\n") == 0)
                return false;
        }
        if(strcmp(s1,"name") == 0 || strcmp(s1,"name,") == 0){
            order_by[i] = ordering::name;
            i++;
        }
        else if(strcmp(s1,"phone") == 0 || strcmp(s1,"phone,") == 0){
            order_by[i] = ordering::phone;
            i++;
        }
        else if(strcmp(s1,"group") == 0 || strcmp(s1,"group,") == 0){
            order_by[i] = ordering::group;
            i++;
        }
        else
            return false;
        s1 = strtok(nullptr, " ;");
    }
    for(; i < 3; i++)
        order_by[i] = ordering::none;
    if(!s1 || strcmp(s1,"\n") == 0)
        return true;
    return false;
}

void command::print (FILE *fp) const{
    fprintf(fp, "n_name = %d n_group = %d n_phone = %d\n",n_name, n_group, n_phone);
    fprintf(fp, "o_name = %s o_group = %d o_phone = %d\n",o_name, o_group, o_phone);
    for(int i = 0; i < 3; i++)
    {
        if(order[i] == ordering::none)
            fprintf(fp,"none\n");
        if(order[i] == ordering::name)
            fprintf(fp,"name\n");
        if(order[i] == ordering::phone)
            fprintf(fp,"phone\n");
        if(order[i] == ordering::group)
            fprintf(fp,"group\n");
    }

}

int command::apply (int &i) {
	if((type == command_type::select || type == command_type::del) && o_phone != 0 && c_phone != condition::none && c_phone != condition::like && c_phone != condition::nlike && n_phone == i)
		return task_phone(i);
	if((type == command_type::select || type == command_type::del) && o_group != 0 && c_group != condition::none && c_phone != condition::like && c_group != condition::nlike && n_group == i)
		return task_group(i);
	if((type == command_type::select || type == command_type::del) && o_name  && c_name != condition::none && c_name != condition::like && c_name != condition::nlike && n_name == i)
		return task_name(i);
	if((type == command_type::select || type == command_type::del) && o_name  && (c_name == condition::like || c_name == condition::nlike) && n_name == i)
		return task_simbol(i);
    if(type == command_type::quit)
        return -2;
    if(type == command_type::insert && o_phone != 0 && o_group != 0 && o_name && c_phone == condition::none && c_group == condition::none && c_name == condition::none)
        return -1;
    if(type == command_type::del && c_phone == condition::none && c_group == condition::none && c_name == condition::none)
        return -5;
    if(type == command_type::select && c_phone == condition::none && c_name == condition::none && c_group == condition::none)
        return -4;
    return -3;
}

bool proverka(char* s) {
    int i = 0;
    for(i = 0; s[i] != '\0' && s[i] != '\n'; i++){
        if(i >= 9)
            return false;
        if(!(s[i] >= '0' && s[i] <= '9'))
            return false;
    }
    if(i == 0)
        return false;
    return true;
}

int command::task_simbol(int& i) {
    i = -1;
    for(int j = 0; o_name[j] != '\0' && o_name[j] != '\n'; j++){
        if((o_name[j] == '_' && i > 0)  || (o_name[j] == '%') || (o_name[j] == '[' && i < 2 && i != -1))
        {
            i = 1;
            return 4;
        }
        if(o_name[j] == '_')
            i = 0;
        else if(o_name[j] == '%')
            i = 1;
        else if(o_name[j] == '[' && o_name[j+1] == '^')
            i = 3;
        else if(i == -1) i = 2;
    }
    return 4;
}

int command::sbor(FILE*np, int k_n, int k_m,int M, FILE*fp){
	int Res = 0, res = 0, i = 0, f_del = 0, sort = 0, flag_vector = 0, flag_hesh = 0;
	char buf[LEN];
	list2 a, b, c;
    const ordering * p = order;
    a.list2::open_file(k_n, k_m, M);
    if(a.read(np) != read_status::success)
        return -1;
    data_base d_g;
    d_g.fill(&a);
    b.head = nullptr;
    c.head = nullptr;
    int (*f[6])(int, int) = {a.f1, a.f2, a.f3, a.f4, a.f5, a.f6};
    int (*g[6])(const char*, char*) = {a.g1, a.g2, a.g3, a.g4, a.g5, a.g6};
    int (*h[4])(const char*, char*) = {a.strcmp12, a.strcmp34, a.strcmp5, a.strcmp6};
//d_g.print_data(p);
	while(fgets(buf, LEN, fp)){
//d_g.print_data(p);
        f_del = 0;
        sort = 0; 
      //  a.list2::print(p);
//        if(flag_hesh != 0)
//            a.list2::print_hesh(p);
      //  d_g.data_base::print_data(p);
        printf("Query: %s\n", buf);
		if(parse(buf) != true) {
            printf("Ошибка в запросе или в командах\n\n");
            continue;
        }
        i = 1;
		res = apply(i);
        if(type == command_type::del)
            f_del = 1;

        if(f_del == 0 && res != -5)
        {
            if(b.head)
            {
//printf("here 1\n");
//b.print();
//printf("here 1 1\n");
               // a.list2::print_hesh(p);
                b.list2::merge(123,b.list2::get_length());
              //  printf("Ola2\n");
              //  b.list2::print(p);
              //  printf("End\n");
//b.print();
//printf("here 1 1 1\n");
                a.list2::delete_spisoc(b.head);
                b.delete_list();
                b.head = nullptr;
            }
            if(c.head)
            {
//printf("here 2\n");
//c.print();
//printf("here 2 2\n");
             //   d_g.data_base::print_data(p);
                c.list2::merge(321,c.list2::get_length()); //321
//c.print();
//printf("here 2 2 2\n");
             //   printf("Ola\n");
              //  c.list2::print(p);
                d_g.data_base::delete_spisoc1(c.head, &a);    
//                a.list2::delete_spisoc(c.head);
              //  d_g.data_base::print_data(p);
                c.delete_list();
                c.head = nullptr;
            }
           // printf("End\n");
        }
        if(res == -1)
        {
        //    d_g.data_base::print_data(p);
            if (a.find_record(o_name, o_phone, o_group)) {
                printf("insert record is already here\n");
                continue;
            }
            if(flag_hesh == 0)
            {
                if(a.r_hesh() != read_status::success)
                    return -1;
                flag_hesh = 1;
                if(flag_vector == 1)
                    a.list2::merge(123,a.list2::get_length());
            }
            if(flag_vector == 0)
            {
                if(a.r_vector() != read_status::success)
                    return -1;
                flag_vector = 1;
            }
//            if (a.find_record(o_name, o_phone, o_group)) {
//                printf("insert record is already here\n");
//                continue;
//            }
            int isert_flag = 0;
            isert_flag = a.list2::isert_(o_name, o_group, o_phone);
            if(isert_flag)
            {
                if(o_group < 0 || o_group >= 1000)
                    continue;
                if(!d_g.data[o_group]->head)
                    d_g.data[o_group]->list2::isert_2(o_name, o_group, o_phone);
                else
                    d_g.data[o_group]->list2::isert_(o_name, o_group, o_phone);
            }
        //    d_g.data[o_group]->list2::print_vectors(p);
            continue;
        }
        if(res == -5)
        {
            d_g.data_base::free_data();
            if(flag_vector == 1)
                a.list2::delete_vectors();
            if(flag_hesh == 1)
                a.list2::delete_hesh();
            flag_vector = 0;
            flag_hesh = 0;
            a.list2::delete_list();
            printf("\n");
            continue;
        }
        if(order_by[0] != ordering::none)
        {
            if(order_by[0] == ordering::group)
                sort = 3;
            else if(order_by[0] == ordering::name)
                sort = 2;
            else if(order_by[0] == ordering::phone)
                sort = 1;
            if(order_by[1] != ordering::none){
                sort *= 10;
                if(order_by[1] == ordering::group)
                    sort += 3;
                else if(order_by[1] == ordering::name)
                    sort += 2;
                else if(order_by[1] == ordering::phone)
                    sort += 1;
            }
            if(order_by[2] != ordering::none){
                sort *= 10;
                if(order_by[2] == ordering::group)
                    sort += 3;
                else if(order_by[2] == ordering::name)
                    sort += 2;
                else if(order_by[2] == ordering::phone)
                    sort += 1;
            }
        }
        if(res == -4)
        {
//printf("print from here\n");
            if(sort > 0)
                a.list2::merge(sort, a.list2::get_length());
            res = a.list2::print(p);
        //   d_g.data_base::print_data(p);
        //    a.list2::print_hesh(p);
         //   a.list2::print_vectors(p);
            if(sort > 0 && sort != 123)
                a.list2::merge(123, res);
            Res += res;
            continue;
        }
        if(res < 0) {
            if(res == -2){
                printf("The end of programm\n\n");
                d_g.data_base::delete_data();
                return Res;
            }
            printf("Ошибка в сборке\n\n");
            continue;
        }
        if(op1 == operation::none)
        {
            if(res == 1 && n_phone == 1){
                if(flag_vector == 0)
                {
                    if(a.r_vector() != read_status::success)
                        return -1;
                    flag_vector = 1;
                }
                res = a.list2::task1(o_phone, f[i], p, f_del, sort, &c);
            }
            else if(res == 2 && n_group == 1)
            {
                res = 0;
                if(o_group < 0 || o_group >= 1000)
                    continue;
                if(i == 2)
                {
                    res = d_g.data[o_group]->list2::task2(o_group, f[i], p, f_del, sort, &b);
                }
                else if(i == 1 || i == 4){
                    int i_dr = 0;
                    for(;i_dr < o_group; i_dr++)
                        res += d_g.data[i_dr]->list2::task2(o_group, f[i], p, f_del, sort, &b);
                    if(i == 4)
                        res += d_g.data[i_dr]->list2::task2(o_group, f[i], p, f_del, sort, &b);
                }
                else if(i == 0 || i == 3){
                    int i_dr = o_group;
                    if(i == 3)
                        res = d_g.data[i_dr]->list2::task2(o_group, f[i], p, f_del, sort, &b);
                    for(i_dr = i_dr + 1;i_dr < 1000; i_dr++)
                        res += d_g.data[i_dr]->list2::task2(o_group, f[i], p, f_del, sort, &b);
                }
                else {
                    res = a.list2::task2(o_group, f[i], p, f_del, sort, &c);
                }
            }
            else if(res == 3 && n_name == 1){
                char* s = o_name;
                if(flag_hesh == 0)
                {
                    if(a.r_hesh() != read_status::success)
                        return -1;
                    flag_hesh = 1;
                    a.list2::merge(123,a.list2::get_length());
                }
                res = a.list2::task3(s, g[i], p, f_del, sort, &c);
                //c.list2::print(p);
            }
            else if(res == 4 && n_name == 1){
                char* s = o_name;
                if(flag_hesh == 0)
                {
                    if(a.r_hesh() != read_status::success)
                        return -1;
                    flag_hesh = 1;
                    a.list2::merge(123,a.list2::get_length());
                }
                if(c_name == condition::like)
                    res = a.list2::task4(s, h[i], p, 0, f_del, sort, &c);
                else
                    res = a.list2::task4(s, h[i], p, 1, f_del, sort, &c);
            }
        }
        else if(op2 == operation::none)
        {
            int j = 0, l = 0;
            if(op1 == operation::lor)
                l = 1;
            if(n_name == 0)
            {
                if(n_group == 1)
                {
                    j = i;
                    i = n_phone;
                    res = apply(i);
                    if(res < 0) {
                        printf("Ошибка в сборке\n\n");
                        continue;
                    }
                }
                else{
                    j = n_group;
                    res = apply(j);
                    if(res < 0) {
                        printf("Ошибка в сборке\n\n");
                        continue;
                    }
                }
                if(flag_vector == 0)
                {
                    if(a.r_vector() != read_status::success)
                        return -1;
                    flag_vector = 1;
                }
                res = 0;
                if(o_group < 0 || o_group >= 1000)
                    continue;
                if(j == 2 && l == 0)
                {
                    res = d_g.data[o_group]->list2::task5(o_phone, f[i], o_group, f[j],  p, l, f_del, sort, &b);
                }
                else if((j == 1 || j == 4) && l == 0){
                    int i_dr = 0;
                    for(;i_dr < o_group; i_dr++)
                        res += d_g.data[i_dr]->list2::task5(o_phone, f[i], o_group, f[j],  p, l, f_del, sort, &b);
                    if(j == 4)
                        res += d_g.data[i_dr]->list2::task5(o_phone, f[i], o_group, f[j],  p, l, f_del, sort, &b);
                }
                else if((j == 0 || j == 3) && l == 0){
                    int i_dr = o_group;
                    if(j == 3)
                        res = d_g.data[i_dr]->list2::task5(o_phone, f[i], o_group, f[j],  p, l, f_del, sort, &b);
                    for(i_dr = i_dr + 1;i_dr < 1000; i_dr++)
                        res += d_g.data[i_dr]->list2::task5(o_phone, f[i], o_group, f[j],  p, l, f_del, sort, &b);
                }
                else {
                    res = a.list2::task5(o_phone, f[i], o_group, f[j],  p, l, f_del, sort, &c);
                }
            }
            else if(n_phone == 0)
            {
                if(n_name == 1)
                {
                    j = i;
                    i = n_group;
                    res = apply(i); 
                    if(res < 0) {
                        printf("Ошибка в сборке\n\n");
                        continue;
                    }
                }
                else{
                    j = n_name;
                    res = apply(j); 
                    if(res < 0) {
                        printf("Ошибка в сборке\n\n");
                        continue;
                    }
                }
                char* s = o_name;
                if(flag_hesh == 0)
                {
                    if(a.r_hesh() != read_status::success)
                        return -1;
                    flag_hesh = 1;
                    a.list2::merge(123,a.list2::get_length());
                }
                res = 0;
                if(o_group < 0 || o_group >= 1000)
                    continue;
                if(i == 2 && l == 0)
                {
                    if(c_name == condition::nlike)
                        res = d_g.data[o_group]->list2::task6(o_group, f[i], s, h[j], p, 1, l, f_del, sort, &b);
                    else if(c_name == condition::like)
                        res = d_g.data[o_group]->list2::task6(o_group, f[i], s, h[j], p, 0, l, f_del, sort, &b);
                    else
                        res = d_g.data[o_group]->list2::task6(o_group, f[i], s, g[j], p, 0, l, f_del, sort, &b);
                }
                else if((i == 1 || i == 4) && l == 0){
                    int i_dr = 0;
                    for(;i_dr < o_group; i_dr++)
                    {
                        if(c_name == condition::nlike)
                            res += d_g.data[i_dr]->list2::task6(o_group, f[i], s, h[j], p, 1, l, f_del, sort, &b);
                        else if(c_name == condition::like)
                            res += d_g.data[i_dr]->list2::task6(o_group, f[i], s, h[j], p, 0, l, f_del, sort, &b);
                        else
                            res += d_g.data[i_dr]->list2::task6(o_group, f[i], s, g[j], p, 0, l, f_del, sort, &b);
                    }
                    if(i == 4)
                    {
                        if(c_name == condition::nlike)
                            res += d_g.data[i_dr]->list2::task6(o_group, f[i], s, h[j], p, 1, l, f_del, sort, &b);
                        else if(c_name == condition::like)
                            res += d_g.data[i_dr]->list2::task6(o_group, f[i], s, h[j], p, 0, l, f_del, sort, &b);
                        else
                            res += d_g.data[i_dr]->list2::task6(o_group, f[i], s, g[j], p, 0, l, f_del, sort, &b);
                    }
                }
                else if((i == 0 || i == 3) && l == 0){
                    int i_dr = o_group;
                    if(i == 3)
                    {
                        if(c_name == condition::nlike)
                            res = d_g.data[i_dr]->list2::task6(o_group, f[i], s, h[j], p, 1, l, f_del, sort, &b);
                        else if(c_name == condition::like)
                            res = d_g.data[i_dr]->list2::task6(o_group, f[i], s, h[j], p, 0, l, f_del, sort, &b);
                        else
                            res = d_g.data[i_dr]->list2::task6(o_group, f[i], s, g[j], p, 0, l, f_del, sort, &b);
                    }
                    for(i_dr = i_dr + 1;i_dr < 1000; i_dr++)
                    {
                        if(c_name == condition::nlike)
                            res += d_g.data[i_dr]->list2::task6(o_group, f[i], s, h[j], p, 1, l, f_del, sort, &b);
                        else if(c_name == condition::like)
                            res += d_g.data[i_dr]->list2::task6(o_group, f[i], s, h[j], p, 0, l, f_del, sort, &b);
                        else
                            res += d_g.data[i_dr]->list2::task6(o_group, f[i], s, g[j], p, 0, l, f_del, sort, &b);
                    }
                }
                else {
                    if(c_name == condition::nlike)
                        res = a.list2::task6(o_group, f[i], s, h[j], p, 1, l, f_del, sort, &c);
                    else if(c_name == condition::like)
                        res = a.list2::task6(o_group, f[i], s, h[j], p, 0, l, f_del, sort, &c);
                    else
                        res = a.list2::task6(o_group, f[i], s, g[j], p, 0, l, f_del, sort, &c);
                }
            }
            else if(n_group == 0)
            {
                if(n_name == 1)
                {
                    j = i;
                    i = n_phone;
                    res = apply(i); 
                    if(res < 0) {
                        printf("Ошибка в сборке\n\n");
                        continue;
                    }
                }
                else{
                    j = n_name;
                    res = apply(j); 
                    if(res < 0) {
                        printf("Ошибка в сборке\n\n");
                        continue;
                    }
                }
                if(flag_hesh == 0)
                {
                    if(a.r_hesh() != read_status::success)
                        return -1;
                    flag_hesh = 1;
                    if(flag_vector == 1)
                        a.list2::merge(123,a.list2::get_length());
                }
                if(flag_vector == 0)
                {
                    if(a.r_vector() != read_status::success)
                        return -1;
                    flag_vector = 1;
                }
              //  printf("Ola %d %d %d %d\n", l, sort, i, j);
                char* s = o_name;
                if(c_name == condition::nlike)
                    res = a.list2::task7(o_phone, f[i], s, h[j], p, 1, l, f_del, sort, &c);
                else if(c_name == condition::like)
                    res = a.list2::task7(o_phone, f[i], s, h[j], p, 0, l, f_del, sort, &c);
                else
                    res = a.list2::task7(o_phone, f[i], s, g[j], p, 0, l, f_del, sort, &c);
            }
        }
        else{
            int j = 0, k = 0, l = 0;
            if(op2 == operation::lor)
                l = 1;
            if(n_group == 1) {
                j = i;
                i = n_phone;
                res = apply(i); 
                if(res < 0) {
                    printf("Ошибка в сборке\n\n");
                    continue;
                }
                k = n_name;
                res = apply(k); 
                if(res < 0) {
                    printf("Ошибка в сборке\n\n");
                    continue;
                }
            }
            else if(n_name == 1){
                k = i;
                j = n_group;
                res = apply(j); 
                if(res < 0) {
                    printf("Ошибка в сборке\n\n");
                    continue;
                }
                i = n_phone;
                res = apply(i); 
                if(res < 0) {
                    printf("Ошибка в сборке\n\n");
                    continue;
                }
            }
            else{
                j = n_group;
                res = apply(j); 
                if(res < 0) {
                    printf("Ошибка в сборке\n\n");
                    continue;
                }
                k = n_name;
                res = apply(k); 
                if(res < 0) {
                    printf("Ошибка в сборке\n\n");
                    continue;
                }
            }
            char* s = o_name;
            if(flag_hesh == 0)
            {
                if(a.r_hesh() != read_status::success)
                    return -1;
                flag_hesh = 1;
                if(flag_vector == 1)
                    a.list2::merge(123,a.list2::get_length());
            }
            if(flag_vector == 0)
            {
                if(a.r_vector() != read_status::success)
                    return -1;
                flag_vector = 1;
            }
            res = 0;
            if(o_group < 0 || o_group >= 1000)
                continue;
            if(j == 2 && l == 0)
            {
                if(c_name == condition::nlike)
                    res = d_g.data[o_group]->list2::task8(o_phone, f[i], o_group, f[j], s, h[k], p, 1, l, f_del, sort, &b);
                else if(c_name == condition::like)
                    res = d_g.data[o_group]->list2::task8(o_phone, f[i], o_group, f[j], s, h[k], p, 0, l, f_del, sort, &b);
                else
                    res = d_g.data[o_group]->list2::task8(o_phone, f[i], o_group, f[j], s, g[k], p, 0, l, f_del, sort, &b);
            }
            else if((j == 1 || j == 4) && l == 0){
                int i_dr = 0;
                for(;i_dr < o_group; i_dr++)
                {
                    if(c_name == condition::nlike)
                        res += d_g.data[i_dr]->list2::task8(o_phone, f[i], o_group, f[j], s, h[k], p, 1, l, f_del, sort, &b);
                    else if(c_name == condition::like)
                        res += d_g.data[i_dr]->list2::task8(o_phone, f[i], o_group, f[j], s, h[k], p, 0, l, f_del, sort, &b);
                    else
                        res += d_g.data[i_dr]->list2::task8(o_phone, f[i], o_group, f[j], s, g[k], p, 0, l, f_del, sort, &b);
                }
                if(j == 4)
                {
                    if(c_name == condition::nlike)
                        res += d_g.data[i_dr]->list2::task8(o_phone, f[i], o_group, f[j], s, h[k], p, 1, l, f_del, sort, &b);
                    else if(c_name == condition::like)
                        res += d_g.data[i_dr]->list2::task8(o_phone, f[i], o_group, f[j], s, h[k], p, 0, l, f_del, sort, &b);
                    else
                        res += d_g.data[i_dr]->list2::task8(o_phone, f[i], o_group, f[j], s, g[k], p, 0, l, f_del, sort, &b);
                }
            }
            else if((j == 0 || j == 3) && l == 0){
                int i_dr = o_group;
                if(j == 3)
                {
                    if(c_name == condition::nlike)
                        res = d_g.data[i_dr]->list2::task8(o_phone, f[i], o_group, f[j], s, h[k], p, 1, l, f_del, sort, &b);
                    else if(c_name == condition::like)
                        res = d_g.data[i_dr]->list2::task8(o_phone, f[i], o_group, f[j], s, h[k], p, 0, l, f_del, sort, &b);
                    else
                        res = d_g.data[i_dr]->list2::task8(o_phone, f[i], o_group, f[j], s, g[k], p, 0, l, f_del, sort, &b);
                }
                for(i_dr = i_dr + 1;i_dr < 1000; i_dr++)
                {
                    if(c_name == condition::nlike)
                        res += d_g.data[i_dr]->list2::task8(o_phone, f[i], o_group, f[j], s, h[k], p, 1, l, f_del, sort, &b);
                    else if(c_name == condition::like)
                        res += d_g.data[i_dr]->list2::task8(o_phone, f[i], o_group, f[j], s, h[k], p, 0, l, f_del, sort, &b);
                    else
                        res += d_g.data[i_dr]->list2::task8(o_phone, f[i], o_group, f[j], s, g[k], p, 0, l, f_del, sort, &b);
                }
            }
            else {
                if(c_name == condition::nlike)
                    res = a.list2::task8(o_phone, f[i], o_group, f[j], s, h[k], p, 1, l, f_del, sort, &c);
                else if(c_name == condition::like)
                    res = a.list2::task8(o_phone, f[i], o_group, f[j], s, h[k], p, 0, l, f_del, sort, &c);
                else
                    res = a.list2::task8(o_phone, f[i], o_group, f[j], s, g[k], p, 0, l, f_del, sort, &c);
            }
        }
		if(res < 0){
            printf("Unknown error\n\n");
			continue;
        }
		Res += res;
	}
    a.delete_list();
    d_g.data_base::delete_data();
    return Res;
}

int command::task_phone(int& i){
    if(c_phone == condition::ge)
        i = 0;
    if(c_phone == condition::le)
        i = 1;
    if(c_phone == condition::eq)
        i = 2;
    if(c_phone == condition::gt)
        i = 3;
    if(c_phone == condition::lt)
        i = 4;
    if(c_phone == condition::ne)
        i = 5;
    return 1;
}

int command::task_group(int& i){
    if(c_group == condition::ge)
        i = 0;
    if(c_group == condition::le)
        i = 1;
    if(c_group == condition::eq)
        i = 2;
    if(c_group == condition::gt)
        i = 3;
    if(c_group == condition::lt)
        i = 4;
    if(c_group == condition::ne)
        i = 5;
    return 2;
}

int command::task_name(int& i){
    if(c_name == condition::ge)
        i = 0;
    if(c_name == condition::le)
        i = 1;
    if(c_name == condition::eq)
        i = 2;
    if(c_name == condition::gt)
        i = 3;
    if(c_name == condition::lt)
        i = 4;
    if(c_name == condition::ne)
        i = 5;
    return 3;
}

condition command::operations(char* x){
	if(!x)
		return condition::none;
    if(!((x[1] == '\0') || (x[2] == '\0')))
        return condition::none;
    if(x[1] == '\0'){
        if(x[0] == '>')
            return condition::ge;
        if(x[0] == '<')
            return condition::le;
        if(x[0] == '=')
            return condition::eq;
        return condition::none;
    }
    if(x[1]){
        if((x[0] == '>') && (x[1] == '='))
            return condition::gt;
        if((x[0] == '<') && (x[1] == '='))
            return condition::lt;
        if((x[0] == '<') && (x[1] == '>'))
            return condition::ne;
        if(strcmp(x,"like") == 0)
        	return condition::like;
        return condition::none;
    }
    return condition::none;

}
