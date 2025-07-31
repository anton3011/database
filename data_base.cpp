#include "data_base.hpp"
#include "record.hpp"
#include "list2_node.hpp"
#include "list2.hpp"
#include <stdio.h>
#include <cstring>
#include "command.hpp"
using namespace std;
#define LEN 1234

void data_base::delete_data()
{
    if(!data)
        return;
    for(int i = 0; i < d_len_group; i++)
        delete data[i];
    if(data)
        delete [] data;
    data = nullptr;
}

void data_base::free_data()
{
    if(!data)
        return;
    for(int i = 0; i < d_len_group; i++)
    {
        if(data[i]->head)
        {
            data[i]->delete_hesh();
            data[i]->delete_vectors();
            data[i]->delete_list();
        }
        data[i]->head=nullptr;
    }
}

void data_base::fill(list2 *a)
{
    data = new list2* [d_len_group];
    for(int i = 0;i < d_len_group; i++)
    {
        data[i] = new list2;
        data[i]->head = nullptr;
    }
    r_data(a);
}

void data_base::r_data(list2 *b)
{
    int a = 0;
    list2_node *curr = nullptr, *head2 = b->head;
    for(int i = 0;i < d_len_group; i++)
    {
        data[i]->k_massiv = b->k_massiv;
        data[i]->k_name = b->k_name;
        data[i]->m = b->m;
    }
    while(head2)
    {
        a = head2->get_group();
        if(a < 0 || a >= d_len_group)
        {
            head2 = head2->next;
            continue;
        }
        if(!data[a]->head)
        {
            data[a]->head = new list2_node;
            data[a]->head->record::init(head2->get_name(), head2->get_phone(),head2->get_group());
            head2 = head2->next;
            data[a]->head->next = nullptr;
            data[a]->head->prev = nullptr;
        }
        else
        {
            curr = new list2_node;
            if(!curr)
            {
                delete_data();
                return;
            }
            curr->record::init(head2->get_name(), head2->get_phone(),head2->get_group());
            head2 = head2->next;
            curr->next = (data[a]->head);
            data[a]->head->prev = curr;
            data[a]->head = curr;
        }       
    }
    for(int i = 0;i < d_len_group; i++)
    {
        if(data[i]->head)
        {
            data[i]->r_hesh();
            data[i]->r_vector();
        }
    }
    return;
}

void data_base::print_data(const ordering * p){
    for(int i = 0; i < d_len_group; i++)
    {
        if(data[i]->head)
        {
            printf("hesh[%d]\n", i);
            data[i]->list2::print_vectors(p);
            printf("hesh2[%d]\n", i);
            data[i]->list2::print_hesh(p);
        }
    }
}

void data_base::delete_spisoc1(list2_node* head2, list2 *arr)
{
(void)arr;
    int a = 0;
    list2_node *head2_next = head2;
    while(head2)
    {
        head2_next = head2;
        a = head2->get_group();
        if(a <= 0 || a > d_len_group)
        {
            head2 = head2->next;
            continue;
        }
//        data[a]->list2::delete_spisoc(head2, a);
        while(head2_next && a == head2_next->get_group()) {
            head2_next = head2_next->next;
        }
        data[a]->list2::delete_spisoc(head2, a);
//        arr->list2::delete_spisoc(head2, a);
        head2 = head2_next;
    }
}
