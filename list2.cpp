#include "record.hpp"
#include "list2_node.hpp"
#include "list2.hpp"
#include <stdio.h>
#include <cstring>
#include "command.hpp"
using namespace std;
#define LEN 1234

void list2::delete_list()
{
    list2_node*curr, *next;
    for(curr = head; curr; curr = next)
    { 
        next = curr->next; 
        delete curr;
    }
    head = nullptr;
}

void list2::delete_vectors()
{
    if(!vectors)
        return;
    for(int i = 0; i < l && vectors[i]; i++)
        delete [] vectors[i];
    delete [] vectors;
    vectors = nullptr;
}

int list2::print_vectors(const ordering * p)
{
    int len = 0;
    if(!vectors)
        return 0;
    for(int i = 0; i < l && vectors[i]; i++)
        for(int j = 0; j < k_massiv; j++)
        {
            if(vectors[i][j] == nullptr)
                continue;
            printf("vectors[%d][%d] = ", i, j);
            vectors[i][j]->print(p);
            len++;
        }
    printf("\n");
    return len;
}

int list2::print_len()
{
    int len = 0;
    for(int i = 0; i < l && vectors[i]; i++)
        for(int j = 0; j < k_massiv; j++)
        {
            if(vectors[i][j] == nullptr)
                continue;
            len++;
        }
    printf("\n");
    return len;
}

int list2::print(const ordering * p)
{
    int i = 0;
    list2_node *curr;
    for(curr = head; curr; curr = curr->next)
    {
        i++;
        curr->record::print(p);
    }
    return i;
}
int list2::print()
{
    int i = 0;
    list2_node *curr;
    for(curr = head; curr; curr = curr->next)
    {
        i++;
        curr->record::print_r();
    }
    return i;
}
int list2::get_length()
{
    list2_node *curr;
    int i = 0;
    for(curr = head; curr; curr = curr -> next)
        i++;
    return i;
}
read_status list2::read(FILE*fp)
{
    int i = 1;
    list2_node buf;
    list2_node *curr, *tail;
    if((buf.read(fp)) != read_status::success)
        return read_status::eof;
    head = new list2_node;
    if(!head)
        return read_status::memory;
    *head = (list2_node&&)buf;
    curr = head;
    while(buf.read(fp) == read_status::success)
    {
        tail = new list2_node;
        if(!tail)
        {
            delete_list();
            return read_status::memory;
        }
        *tail = (list2_node&&)buf;
        curr->next = (tail);
        tail->prev = curr;
        curr = tail; 
        i++;
    }
    if(!feof(fp))
    {
        delete_list();
        return read_status::eof;
    }
    merge(123,i);
    return read_status::success;
}

void list2::open_file(int k_n, int k_m, int M)
{
    k_massiv = k_m;
    k_name = k_n;
    m = M;
}

int list2::number_hesh(const char* s)
{
    if(s[0] != '\0')
    {
        int i = (int)s[0] - 32;
        if(k_name == 1)
            return i;
        if(s[1] != '\0'){
            i = 95 * i + ((int)s[1] - 32);
            if(k_name == 2)
                return i;
            if(s[2] != '\0'){
                i = i * 95 + ((int)s[2] - 32);
                if(k_name == 3)
                    return i;
                if(s[3] != '\0'){
                    i = i * 95 + (int)s[3] - 32;
                    return i;
                }
                else
                    return i;
            }
            else
                return i;
        }
        else
            return i;
    }
    else
        return 0;
}

read_status list2::r_hesh()
{
    int i = 1, j = 0, a = 0, a_new = 0, n = 0;
    list2_node* curr1 = nullptr;
    while(i < k_name)
    {
        i++;
        a_hesh *= 95;
    }
    len_hesh = new int[a_hesh];
    i = 0;
    while(i < a_hesh){
        len_hesh[i] = 0;
        i++;
    }
    n = get_length();
//printf("%d %d %d %d %d\n", n, l_hesh, a_hesh, m, l_hesh * a_hesh * m);
    while(n >= l_hesh * a_hesh * m)
        l_hesh *= 2;
    hesh = new list2_node*** [a_hesh]{};
    if(head == nullptr)
        return read_status::memory;
    merge(2, n);
    auto curr = head;
    curr1 = head;
    i = 0; j = 0;
    while(i < a_hesh){
        hesh[i] = nullptr;
        i++;
    }
    i = 0;
    a = number_hesh(head->get_name());
    hesh[a] = new list2_node** [l_hesh]{};
    len_hesh[a] = l_hesh;
    while(curr)
    {
        a_new = number_hesh(curr->get_name());
        if(a == a_new) 
        {
            if(j >= m) 
            {
                j = 0;
                i++;
            }
            if(i >= len_hesh[a_new]) {
                for(int i_new = 0; i_new < len_hesh[a_new] && hesh[a_new][i_new]; i_new++)
                    delete [] hesh[a_new][i_new];
                delete [] hesh[a_new];
                hesh[a_new] = nullptr;
                len_hesh[a_new] *= 2;
                hesh[a_new] = new list2_node** [len_hesh[a_new]]{};
                i = 0; 
                while(i < len_hesh[a_new])
                {
                    hesh[a_new][i] = nullptr;
                    i++;
                }
                j = 0; i = 0;
                hesh[a_new][i] = new list2_node* [m]{};
                list2_node* curr2 = curr1;
                while(curr2 != curr){
                    if(j >= m) {
                        j = 0;
                        i++;
                        hesh[a_new][i] = new list2_node* [m]{};
                    }
                    hesh[a_new][i][j] = curr2;
                    j++;
                    curr2 = curr2->next;
                }
                if(j >= m) {
                    j = 0;
                    i++;
                    hesh[a_new][i] = new list2_node* [m]{};
                }
                hesh[a_new][i][j] = curr;
                j++;
                int J = j;
                while(J < m){
                    hesh[a_new][i][J] = nullptr;
                    J++;
                }
            }
            else {
                if(j == 0)
                {
                    hesh[a][i] = new list2_node* [m]{};
                    int J = j + 1;
                    while(J < m){
                        hesh[a_new][i][J] = nullptr;
                        J++;
                    }
                }
                hesh[a][i][j] = curr;
                j++;
            }
        }
        else{
            i = 0;
            j = 0;
            curr1 = curr;
            hesh[a_new] = new list2_node** [l_hesh]{};
            len_hesh[a_new] = l_hesh;
            while(i < l_hesh)
            {
                hesh[a_new][i] = nullptr;
                i++;
            }
            i = 0;
            hesh[a_new][i] = new list2_node* [m]{};
            hesh[a_new][0][0] = curr;
            j = 1;
            while(j < m){
                hesh[a_new][0][j] = nullptr;
                j++;
            }
            j = 1;
        }
        a = a_new;
        curr = curr->next;
    }
    return read_status::success;
}

void list2::delete_hesh()
{
    if(!hesh)
        return;
    for(int i = 0; i < a_hesh; i++){
        if(!hesh[i])
            continue;
        for(int j = 0; j < len_hesh[i] && hesh[i][j]; j++)
            delete [] hesh[i][j];
        delete [] hesh[i];
    }
    delete [] hesh;
    hesh = nullptr;
}

int list2::print_hesh(const ordering * p)
{
    int len = 0;
    if(!hesh)
        return 0;
    for(int i = 0; i < a_hesh; i++){
        if(!hesh[i])
            continue;
        for(int j = 0; j < len_hesh[i] && hesh[i][j]; j++)
        {
            for(int z = 0; z < m; z++)
            {
                if(hesh[i][j][z] == nullptr)
                    continue;
                printf("hesh[%d][%d][%d]\n", i, j, z);
                hesh[i][j][z]->print(p);
                len++;
            }
        }
    }
    printf("\n");
    return len;
}

read_status list2::r_vector()
{
    int n = 0;
    n = get_length();
    while(n >= l*k_massiv)
        l *= 2;
    vectors = new list2_node** [l]{};
    vectors[0] = new list2_node*[k_massiv]{};
    if(head == nullptr)
        return read_status::memory;
    merge(123, n);
    auto curr = head;
    int i = 0, j = 0;
    while(curr && i < l)
    {
        if(j >= k_massiv) {
            i++;
            vectors[i] = new list2_node*[k_massiv]{};
            j = 0;
        }
        vectors[i][j] = curr;
        j++;
        curr = curr->next;
    }
    while(j < k_massiv){
        vectors[i][j] = nullptr;
        j++;
    }
    i++;
    while(i < l){
        vectors[i] = nullptr;
        i++;
    }
    return read_status::success;
}
// group = 3, phone = 1, name = 2;
int list2::srav(int i, list2_node* currmin, list2_node* curr)
{
    if(i == 1 || i/10 == 1 || i/100 == 1)
    {
        if(currmin->get_phone() > curr->get_phone())
            return 1;
        if(i == 123)
        {
            if((currmin->get_phone() == curr->get_phone()  && strcmp(currmin->get_name(), curr->get_name()) == 0 && currmin->get_group() > curr->get_group()) || (currmin->get_phone() == curr->get_phone()  && strcmp(currmin->get_name(), curr->get_name()) > 0))
                return 1;
            return 0;
        }
        if(i == 132)
        {
            if((currmin->get_phone() == curr->get_phone() && currmin->get_group() == curr->get_group() && strcmp(currmin->get_name(), curr->get_name()) > 0 ) || (currmin->get_phone() == curr->get_phone()  && currmin->get_group() > curr->get_group()))
                return 1;
            return 0;
        }
        if(i == 12)
        {
            if((currmin->get_phone() == curr->get_phone()  && strcmp(currmin->get_name(), curr->get_name()) > 0))
                return 1;
            return 0;
        }
        if(i == 13)
        {
            if((currmin->get_phone() == curr->get_phone() && currmin->get_group() > curr->get_group()))
                return 1;
            return 0;
        }
        return 0;
    }
    if(i == 2 || i/10 == 2 || i/100 == 2)
    {
        if(strcmp(currmin->get_name(), curr->get_name()) > 0)
            return 1;
        if(i == 213)
        {
            if((currmin->get_phone() == curr->get_phone()  && strcmp(currmin->get_name(), curr->get_name()) == 0 && currmin->get_group() > curr->get_group()) || (currmin->get_phone() > curr->get_phone()  && strcmp(currmin->get_name(), curr->get_name()) == 0))
                return 1;
            return 0;
        }
        if(i == 231)
        {
            if((currmin->get_phone() > curr->get_phone() && currmin->get_group() == curr->get_group() && strcmp(currmin->get_name(), curr->get_name()) == 0 ) || (strcmp(currmin->get_name(), curr->get_name()) == 0  && currmin->get_group() > curr->get_group()))
                return 1;
            return 0;
        }
        if(i == 21)
        {
            if((currmin->get_phone() > curr->get_phone()  && strcmp(currmin->get_name(), curr->get_name()) == 0))
                return 1;
            return 0;
        }
        if(i == 23)
        {
            if((strcmp(currmin->get_name(), curr->get_name()) == 0 && currmin->get_group() > curr->get_group()))
                return 1;
            return 0;
        }
        return 0;
    }
    if(i == 3 || i/10 == 3 || i/100 == 3)
    {
        if(currmin->get_group() > curr->get_group())
            return 1;
        if(i == 321)
        {
            if((currmin->get_phone() > curr->get_phone()  && strcmp(currmin->get_name(), curr->get_name()) == 0 && currmin->get_group() == curr->get_group()) || (currmin->get_group() == curr->get_group()  && strcmp(currmin->get_name(), curr->get_name()) > 0))
                return 1;
            return 0;
        }
        if(i == 312)
        {
            if((currmin->get_phone() == curr->get_phone() && currmin->get_group() == curr->get_group() && strcmp(currmin->get_name(), curr->get_name()) > 0 ) || (currmin->get_phone() > curr->get_phone()  && currmin->get_group() == curr->get_group()))
                return 1;
            return 0;
        }
        if(i == 32)
        {
            if((currmin->get_group() == curr->get_group()  && strcmp(currmin->get_name(), curr->get_name()) > 0))
                return 1;
            return 0;
        }
        if(i == 31)
        {
            if((currmin->get_phone() > curr->get_phone() && currmin->get_group() == curr->get_group()))
                return 1;
            return 0;
        }
        return 0;
    }
    return 0;
}


void list2::merge(int i, int n)
{
    list2_node *curr, *curr1, *n_curr,*curr_next, *curr_next1;
    list2 a;
    int k_len = 1, j = 0,len1 = 0, len2 = 0;
    n *= 2;
    if(!head || !(head->next))
        return;
    a.head = nullptr;
    curr1 = head->next;
    while(k_len * 2  < n)
    {
        j = 0;
        len1 = 0;
        len2 = 0;
        curr = head;
        curr1 = head;
        while(j < k_len && curr1->next)
        {
            curr1 = curr1->next;
            j++;
        }
        curr_next = curr->next;
        curr_next1 = curr1->next;
        while(curr1 && curr)
        {
            if(srav(i, curr,curr1) > 0)
            {
                if(!a.head)
                {
                    a.head = curr1;
                    a.head->prev = nullptr;
                    n_curr = a.head;
                    n_curr->next = nullptr;
                    curr1 = curr_next1;
                    if(curr1)
                        curr_next1 = curr1->next;
                }
                else
                {
                    n_curr->next = curr1;
                    curr1->prev = n_curr;
                    n_curr = n_curr->next;
                    n_curr->next = nullptr;
                    curr1 = curr_next1;
                    if(curr1)
                        curr_next1 = curr1->next;
                }
                len2++;
            }
            else
            {
                if(!a.head)
                {
                    a.head = curr;
                    a.head->prev = nullptr;//
                    n_curr = a.head;
                    n_curr->next = nullptr;
                    curr = curr_next;
                    if(curr)
                        curr_next = curr->next;
                }
                else
                {
                    n_curr->next = curr;
                    curr->prev = n_curr; 
                    n_curr = n_curr->next;
                    n_curr->next = nullptr;
                    curr = curr_next;
                    if(curr)
                        curr_next = curr->next;
                }
                len1++;
            }
            if (len1 == k_len || len2 == k_len || !curr1)
            {
                while(len1 < k_len && curr)
                {
                    n_curr->next = curr;
                    curr->prev = n_curr;
                    n_curr = n_curr->next;
                    curr = curr_next;
                    if(curr)
                        curr_next = curr->next;
                    len1++;
                }
                while(len2 < k_len && curr1)
                {
                    n_curr->next = curr1;
                    curr1->prev = n_curr;
                    n_curr = n_curr->next;
                    curr1 = curr_next1;
                    if(curr1)
                        curr_next1 = curr1->next;
                    len2++;
                }
                n_curr->next = nullptr;
            }
            if(len1 == k_len && len2 == k_len) {
                curr = curr1;
                j = 0;
                while(j < k_len && curr1 && curr1->next) {
                    curr1 = curr1->next;
                    j++;
                }
                if(curr)
                    curr_next = curr->next;
                if(curr1)
                    curr_next1 = curr1->next;
                len1 = 0;
                len2 = 0;
            }
            j = 0;
        }
        head = a.head;
        a.head = nullptr;
        k_len *= 2;
    }
    return;
}

void list2::isert_2(char* s, int a, int b){
    head = new list2_node;
    head->record::init(s, b,a);
    head->next = nullptr;
    head->prev = nullptr;
    if(!hesh && !vectors)
    {
        r_hesh();
        r_vector();
    }
    else{
        int i = number_hesh(s);
        if(!hesh[i])
        {
            int j = 0;
            hesh[i] = new list2_node** [l_hesh]{};
            len_hesh[i] = l_hesh;
            while(j < l_hesh){
                hesh[i][j] = nullptr;
                j++;
            }
            j = 0;
            hesh[i][0] = new list2_node* [m]{};
            hesh[i][0][0] = head;
            while(j < m){
                hesh[i][0][j] = nullptr;
                j++;
            }
        }
        else
            hesh[i][0][0] = head;
        vectors[0][0] = head;
    }
}

int list2::find_record(char *s, int ph, int gr) {
    for (list2_node *curr_c = head; curr_c; curr_c = curr_c->next)
        if (curr_c->get_phone() == ph && curr_c->get_group() == gr && strcmp(curr_c->get_name(), s) == 0)
            return 1;
    return 0;
}

int list2::isert_(char* s, int a, int b) // o_name, o_group, o_phone
{
    int i = 0, j = 0, i_n = 0, j_n = 0, flag = 0;
    list2_node* curr, *curr_new, *curr2, *curr_dop, *CURR = nullptr;
    for(i = 0; i < l && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() < b; i++);
    if(i > 0)
        i--;
    CURR = new list2_node;
    CURR->init(s, b, a);
    while(vectors[i] && (vectors[i][j] == nullptr || (vectors[i][j]->get_phone() <= b && vectors[i][j]->next))){
        if(vectors[i][j] && strcmp(s, vectors[i][j]->get_name()) == 0 && vectors[i][j]->get_phone() == b && vectors[i][j]->get_group() == a)
        {
            delete CURR;
            return 0;
        }
        if(vectors[i][j] && srav(123, CURR, vectors[i][j]) == 0)
            break;
        j++;
        if(j >= k_massiv)
        {
            i++;
            j = 0;
        }
        if(i * j >= (l - 1) * (k_massiv - 1) || i >= l)
        {
            delete_vectors();
            l *= 2;
            vectors = new list2_node** [l]{};
            curr = head;
            i_n = 0;
            j_n = 0;
            vectors[0] = new list2_node*[k_massiv]{};
            list2_node* curr1 = nullptr;
            while(curr && i_n < l)
            {
                if(j_n >= k_massiv)
                {
                    i_n++;
                    vectors[i_n] = new list2_node*[k_massiv]{};
                    j_n = 0;
                }
                vectors[i_n][j_n] = curr;
                j_n++;
                curr1 = curr;
                curr = curr->next;
            }
            curr1->next = CURR;
            CURR->prev = curr1;
            CURR->next = nullptr;
            vectors[i_n][j_n] = CURR;
            j_n++;
            if(j_n >= k_massiv)
            {
                i_n++;
                vectors[i_n] = new list2_node*[k_massiv]{};
                j_n = 0;
            }
            while(j_n < k_massiv)
            {
                vectors[i_n][j_n] = nullptr;
                j_n++;
            }
            i_n++;
            while(i_n < l)
            {
                vectors[i_n] = nullptr;
                i_n++;
            }
            flag = 1;
            break;
        }
        if(flag == 0 && !vectors[i])
        {
            CURR->next = nullptr;
            if(i > 0)
                CURR->prev = vectors[i-1][k_massiv-1];
            vectors[i] = new list2_node*[k_massiv]{};
            vectors[i][0] = CURR;
            j = 1;
            while(j < k_massiv){
                vectors[i][j] = nullptr;
                j++;
            }
            flag = 1;
            break;
        }
    }
    list2_node *dop1 = vectors[i][j], *dop2 = vectors[i][j];
    if(vectors[i][j] && vectors[i][j]->get_phone() < b && vectors[i][j]->next == nullptr)
    {
        i_n = i;
        j_n = j;
        j++;
        if(j >= k_massiv){
            i++;
            j = 0;
        }
        if(i * j >= (l - 1) * (k_massiv - 1) || i >= l){
            delete_vectors();
            l *= 2;
            vectors = new list2_node** [l]{};
            curr = head;
            i_n = 0;
            j_n = 0;
            vectors[0] = new list2_node*[k_massiv]{};
            list2_node* curr1 = nullptr;
            while(curr && i_n < l){
                if(j_n >= k_massiv){
                    i_n++;
                    vectors[i_n] = new list2_node*[k_massiv]{};
                    j_n = 0;
                }
                vectors[i_n][j_n] = curr;
                j_n++;
                curr1 = curr;
                curr = curr->next;
            }
            curr1->next = CURR;
            CURR->prev = curr1;
            CURR->next = nullptr;
            vectors[i_n][j_n] = CURR;
            j_n++;
            if(j_n >= k_massiv){
                i_n++;
                vectors[i_n] = new list2_node*[k_massiv]{};
                j_n = 0;
            }
            while(j_n < k_massiv){
                vectors[i_n][j_n] = nullptr;
                j_n++;
            }
            i_n++;
            while(i_n < l){
                vectors[i_n] = nullptr;
                i_n++;
            }
            flag = 1;
        }
        if(flag == 0 && !vectors[i]){
            CURR->next = nullptr;
            if(i > 0)
                CURR->prev = vectors[i-1][k_massiv-1];
            vectors[i] = new list2_node*[k_massiv]{};
            vectors[i][0] = CURR;
            j = 1;
            while(j < k_massiv){
                vectors[i][j] = nullptr;
                j++;
            }
            flag = 1;
        }
        if(flag == 0){
            vectors[i_n][j_n]->next = CURR;
            CURR->prev = vectors[i_n][j_n];
            vectors[i][j] = CURR;
        }
        flag = 1;
    }
    curr2 = nullptr;
    if(flag == 0)
    {
        if(i == 0 && j == 0)
        {
            i_n = 0;
            j_n = 0;
            CURR->next = vectors[i][j];
            vectors[i][j]->prev = CURR;
            vectors[i_n][j_n] = CURR;
            head = CURR;
        }
        else if(j == 0)
        {
            if(i > 0)
                i_n = i - 1;
            j_n = k_massiv - 1;
        }
        else
        {
            i_n = i;
            j_n = j - 1;
        }
        if(vectors[i_n][j_n] == nullptr)
        {
            CURR->next = vectors[i][j];
            if(vectors[i][j]->prev == nullptr)
            {
                vectors[i][j]->prev = CURR;
                head = CURR;
            }
            else
            {
                curr2 = vectors[i][j]->prev;
                vectors[i][j]->prev = CURR;
                curr2->next = CURR;
                CURR->prev = curr2;
            }
            vectors[i_n][j_n] = CURR;
            flag = 1;
        }
        if(flag == 0 && (i != 0 || j != 0))
        {
            if(!vectors[i_n][j_n])
                return 0;
            curr2 = vectors[i_n][j_n]->next;
            CURR->prev = vectors[i_n][j_n];
            vectors[i_n][j_n]->next = CURR;
            CURR->next = curr2;
            if(curr2)
                curr2->prev = CURR;
            vectors[i][j] = CURR;
        }
        j++;
        if(dop1 == nullptr)
            flag = 1;
        for(;i < l && flag == 0 && vectors[i]; i++)
        {
            for(; j < k_massiv; j++){
                if(vectors[i][j] == nullptr){
                    vectors[i][j] = dop1;
                    flag = 1;
                    break;
                }
                dop2 = vectors[i][j];
                vectors[i][j] = dop1;
                dop1 = dop2;
            }
            j = 0;
        }
        if(flag == 0 && (i * j >= (l - 1) * (k_massiv - 1) || i >= l))
        {
            delete_vectors();
            l *= 2;
            vectors = new list2_node** [l]{};
            curr = head;
            i_n = 0;
            j_n = 0;
            vectors[0] = new list2_node*[k_massiv]{};
            while(curr && i_n < l)
            {
                if(j_n >= k_massiv)
                {
                    i_n++;
                    vectors[i_n] = new list2_node*[k_massiv]{};
                    j_n = 0;
                }
                vectors[i_n][j_n] = curr;
                j_n++;
                curr = curr->next;
            }
            if(j_n >= k_massiv)
            {
                i_n++;
                vectors[i_n] = new list2_node*[k_massiv]{};
                j_n = 0;
            }
            curr_new = dop1;
            vectors[i_n][j_n] = curr_new;
            j_n++;
            if(j_n >= k_massiv)
            {
                i_n++;
                vectors[i_n] = new list2_node*[k_massiv]{};
                j_n = 0;
            }
            while(j_n < k_massiv)
            {
                vectors[i_n][j_n] = nullptr;
                j_n++;
            }
            i_n++;
            while(i_n < l)
            {
                vectors[i_n] = nullptr;
                i_n++;
            }
            flag = 1;
        }
        if(flag == 0 && !vectors[i])
        {
            dop1->next = nullptr;
            if(i > 0)
                dop1->prev = vectors[i-1][k_massiv-1];
            vectors[i] = new list2_node*[k_massiv]{};
            vectors[i][0] = dop1;
            j = 1;
            while(j < k_massiv){
                vectors[i][j] = nullptr;
                j++;
            }
            flag = 1;
        }
    }
    i = 0; j = 0; flag = 0;
    int as = number_hesh(s);
    if(!hesh[as])
    {
        hesh[as] = new list2_node** [l_hesh]{};
        hesh[as][i] = new list2_node* [m]{};
        len_hesh[as] = l_hesh;
        hesh[as][0][0] = CURR;
    }
    else
    {
        curr2 = hesh[as][0][0];
        curr = hesh[as][0][0];
        curr_dop = curr2;
        for(i = 0; i < len_hesh[as] && flag == 0; i++)
        {
            if(!hesh[as][i])
            {
           //     printf("priv2\n");
                hesh[as][i] = new list2_node* [m]{};
                hesh[as][i][0] = CURR;
                flag = 1;
                break;
            }
            for(j = 0; j < m; j++)
            {
                if(hesh[as][i][j] == nullptr)
                {
                    if(j == 0 && !hesh[as][i])
                        hesh[as][i] = new list2_node* [m]{};
                    hesh[as][i][j] = CURR;
                    flag = 1;
                    break;
                }
                curr = hesh[as][i][j];
            }
        }
        if(flag == 0)
        {
            if(i >= len_hesh[as]) {
                for(int i_new = 0; i_new <= len_hesh[as] && hesh[as][i_new]; i_new++)
                    delete [] hesh[as][i_new];
                if(hesh[as])
                    delete [] hesh[as];
                hesh[as] = nullptr;
                len_hesh[as] *= 2;
                hesh[as] = new list2_node** [len_hesh[as]]{};
                i = 0; 
                while(i < len_hesh[as]){
                    hesh[as][i] = nullptr;
                    i++;
                }
                j = 0; i = 0;
                hesh[as][i] = new list2_node* [m]{};
                list2_node* curr2 = curr_dop;
                while(curr2 != curr){
                    if(j >= m) {
                        j = 0;
                        i++;
                        hesh[as][i] = new list2_node* [m]{};
                    }
                    hesh[as][i][j] = curr2;
                    j++;
                    curr2 = curr2->next;
                }
                if(j >= m) {
                    j = 0;
                    i++;
                    hesh[as][i] = new list2_node* [m]{};
                }
                hesh[as][i][j] = CURR;
                j++;
            }
        }
    }
    return 1;
}

void list2::plus(list2_node* curr1)
{
//curr1->print_r();
    if(!head){
        head = new list2_node;
        if(!head)
            return;
        head->init(curr1->get_name(), curr1->get_phone(), curr1->get_group()); 
        return;
    }
    list2_node* new_head;
    new_head = new list2_node;
    if(!new_head)
    {
        delete_list();
        return;
    }
    new_head->init(curr1->get_name(), curr1->get_phone(), curr1->get_group()); 
    new_head->next = (head);
    head->prev = new_head;
    head = new_head;
}

void list2::delete_spisoc(list2_node* head2, int flag)
{
    int j = 0, i = 0, z = 0;
    list2_node* curr = head2, *curr_prev, *curr_next, *curr2 = head2;
//    for (list2_node *pr = head2; pr; pr = pr->next)
//        pr->print_r();
    while(curr2)
    {
//        printf("hi2\n");
//curr2->print_r();
        if(!hesh)
            break;
        if(curr2 == nullptr)
            break;
        if(flag > 0 && flag != curr2->get_group()){
//            curr2 = nullptr;
            break;
        }
        i = number_hesh(curr2->get_name());
//printf("%d %d\n", i, len_hesh[i]);
        if (!hesh[i])
            break;
        for(j = 0; j < len_hesh[i] && hesh[i][j]; j++){
//            for(z = 0; z < m; z++)
//                if (hesh[i][j][z]) hesh[i][j][z]->print_r();
            for(z = 0; z < m; z++)
            {
                if(hesh[i][j][z] == nullptr)
                    continue;
//                printf("hi\n");
//hesh[i][j][z]->print_r();
                if(curr2 && curr2->get_phone() == hesh[i][j][z]->get_phone() && curr2->get_group() == hesh[i][j][z]->get_group() && strcmp(curr2->get_name(), hesh[i][j][z]->get_name()) == 0){
//curr2->print_r();
//printf("deleted\n");
                    if(!vectors)
                    {
//printf("here\n");
                        curr_prev = hesh[i][j][z]->prev;
                        curr_next = hesh[i][j][z]->next;
                        if(curr_prev)
                            curr_prev->next = curr_next;
                        else
                            head = curr_next;
                        if(curr_next)
                            curr_next->prev = curr_prev;
                        curr2 = curr2->next;
                        delete hesh[i][j][z];
                    }
                    else
                        curr2 = curr2->next;
//if (curr2) {curr2->print_r();
//if (curr2->next) curr2->next->print_r();
//}
                    hesh[i][j][z] = nullptr;
                    break;
                }
            }
        }
    }
//    printf("hi3\n");
    if(!vectors && !hesh)
    {
//printf("l123\n");
        curr2 = head2; list2_node *curr1 = head; i = 0;
        for(curr = head; curr && head && curr2; curr = curr->next){
            if(i == 1)
                curr = head;
            i = 0;
            if(flag > 0 && flag != curr2->get_phone())
                return;
            if(curr && curr->get_phone() == curr2->get_phone() && curr->get_group() == curr2->get_group() && strcmp(curr->get_name(), curr2->get_name()) == 0){
                if(curr == head)
                {
                    head = curr->next;
                    delete curr;
                    curr = head;
                    curr1 = head;
                    i = 1;
                }
                else{
                    curr1->next = curr->next;
                    if(curr->next)
                        (curr->next)->prev = curr1;
                    delete curr;
                    curr = curr1;
                }
                curr2 = curr2->next;
            }
            curr1 = curr;
        }
        if(i == 1 && curr2)
        {
            curr = head;
            if(curr->get_phone() == curr2->get_phone() && curr->get_group() == curr2->get_group() && strcmp(curr->get_name(), curr2->get_name()) == 0) {
                head = curr->next;
                delete curr;
            }
        }
        return;
    }
    if(!vectors)
        return;
    curr = head2;
//    printf("hi3\n");
//    for ( ; curr; curr = curr->next)
//        curr->print_r();
    curr = head2;

    int del_flag = 0;
//    while (curr) {

    for ( ; curr; curr = curr->next) {
        del_flag = 0;
        for(int i = 0; i < l && vectors[i] && curr; i++)
        {
//    printf("l1233 %d %d\n", flag, k_massiv);
    //curr->print_r();
            for(j = 0; j < k_massiv && curr; j++){
                if(vectors[i][j] == nullptr)
                    continue;
//    printf("vectors[%d][%d]:\n", i,j);
//    vectors[i][j]->print_r();
                if(flag > 0 && flag != curr->get_group()) {
                    del_flag = 1;
                    break;
                }
                if(curr && curr->get_phone() == vectors[i][j]->get_phone() && curr->get_group() == vectors[i][j]->get_group() && strcmp(curr->get_name(), vectors[i][j]->get_name()) == 0){
//    curr->print_r();
//    printf("deletedfn\n");
                    curr_prev = vectors[i][j]->prev;
                    curr_next = vectors[i][j]->next;
                    if(curr_prev)
                        curr_prev->next = curr_next;
                    else
                        head = curr_next;
                    if(curr_next)
                        curr_next->prev = curr_prev;
//                    curr = curr->next;
//    if (curr) curr->print_r();
                    delete vectors[i][j];
                    vectors[i][j] = nullptr;
                    del_flag = 1;
                    break;
                }
            }
            if (del_flag) break;
        }
    }

//    }
}

int list2::strcmp_4 (const char *s1, const char *s2, int a1, int a2)
{
    int i = 0;
    while((s1[i]) && (i < k_name) && (s1[i] == s2[i]))
        i++;
    if(i == k_name)
        return a1 - a2;
    return s1[i]-s2[i];
}


int list2::task1(int k, int (*cmp)(int, int),const ordering * p, int f_del, int sort, list2* a)
{
    int res = 0, i = 0, j = 0;
    list2_node *curr1 = a->head,*tail;
    if(!vectors)
        return 0;
    list2 arr2;
    if(cmp == f1 || cmp == f3 || cmp == f4)
    {
        for(i = 0; i < l && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() < k; i++);
        if(i > 0)
            i--;
    }
    if(cmp == f1)
    {
        for(i = 0; i < l && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() <= k; i++);
        if(i > 0)
            i--;
    }
    while(a->head && curr1->next)
        curr1 = curr1->next;
    for( ; i < l && vectors[i]; i++)
    {
        if((cmp == f2 || cmp == f3 || cmp == f5) && vectors[i][0] && vectors[i][0]->get_phone() > k)
        {
            break;
        }
        if(cmp == f2 && vectors[i][0] && vectors[i][0]->get_phone() == k)
            break;
        for(j = 0; j < k_massiv; j++){
            if(!vectors[i])
                break;
            if(vectors[i][j] == nullptr)
                continue;
            if((*cmp)(vectors[i][j]->get_phone(), k) > 0){
                if(f_del == 1)
                {
                    if(!a->head)
                    {
                        a->head = new list2_node;
                        arr2.plus(vectors[i][j]);
                        a->head->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                        curr1 = a->head;
                    }
                    else
                    {
                        tail = new list2_node;
                        if(!tail)
                            a->delete_list();
                        arr2.plus(vectors[i][j]);
                        tail->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                        curr1->next = (tail);
                        tail->prev = curr1;
                        curr1 = tail;
                    }
                    res++;
                }
                else
                {
                    if(sort)
                        arr2.plus(vectors[i][j]);
                    else
                        vectors[i][j]->record::print(p);
                    res++;
                }
            }

        }
    }
    if(f_del)
    {
        arr2.merge(123, res);
        delete_spisoc(arr2.head);
        res = 0;
    }
    else if(sort){
        arr2.merge(sort, res);
        arr2.print(p);
    }
    return res;
}

int list2::task2(int k, int (*cmp)(int, int),const ordering * p, int f_del, int sort, list2* a)
{
    int res = 0;
    list2_node *curr, *curr1 = a->head, *tail;
    list2 arr2;
    while(a->head && curr1->next)
        curr1 = curr1->next;
    for(curr = head; curr; curr = curr->next){
        if((*cmp)(curr->get_group(), k) > 0) {
            if(f_del == 1)
            {
                if(!a->head)
                {
                    a->head = new list2_node;
                    arr2.plus(curr);
                    a->head->init(curr->get_name(), curr->get_phone(), curr->get_group());
                    curr1 = a->head;
                }
                else
                {
                    tail = new list2_node;
                    if(!tail)
                        a->delete_list();
                    arr2.plus(curr);
                    tail->init(curr->get_name(), curr->get_phone(), curr->get_group());
                    curr1->next = (tail);
                    tail->prev = curr1;
                    curr1 = tail;
                }
                res++;
            }
            else
            {
                if(sort)
                    arr2.plus(curr);
                else
                    curr->record::print(p);
                res++;
            }
        }
    }
    if(f_del)
    {
        arr2.merge(123, res);
        delete_spisoc(arr2.head);
        res = 0;
    }
    else if(sort)
    {
        arr2.merge(sort, res);
        arr2.print(p);
    }
    return res;
}

int list2::task3(char* k, int (*cmp)(const char*, char*),const ordering * p, int f_del, int sort, list2* arr)
{
    int res = 0, i = 0, j = 0, a = 0, z = 0;
    list2_node *curr1 = arr->head,*tail;
    list2 arr2;
    if(!hesh)
        return 0;
    a = number_hesh(k);
    if(cmp == g1 || cmp == g4 || cmp == g3)
        i = a;
    while(arr->head && curr1->next)
        curr1 = curr1->next;
    for( ; i < a_hesh && hesh[i]; i++)
    {
        if(cmp == g3 && i != a)
            break;
        if((cmp == g2 || cmp == g5) && i > a)
            break;
        for(j = 0; j < len_hesh[i] && hesh[i][j]; j++){
            for(z = 0; z < m; z++)
            {
                if(!hesh[i])
                    break;
                if(hesh[i][j][z] == nullptr)
                    continue;
                if((*cmp)(hesh[i][j][z]->get_name(), k) == 0){
                    if(f_del == 1)
                    {
                        if(!arr->head)
                        {
                          //  printf("Ola45\n");
                            arr->head = new list2_node;
                            arr2.plus(hesh[i][j][z]);
                            arr->head->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                            curr1 = arr->head;
                        }
                        else
                        {
                        //    printf("Ola345\n");
                            tail = new list2_node;
                            if(!tail)
                                arr->delete_list();
                            arr2.plus(hesh[i][j][z]);
                            tail->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                            curr1->next = (tail);
                            tail->prev = curr1;
                            curr1 = tail;
                        }
                        res++;
                    }
                    else
                    {
                        if(sort)
                            arr2.plus(hesh[i][j][z]);
                        else
                            hesh[i][j][z]->record::print(p);
                        res++;
                    }
                }
            }
        }
    }
    if(f_del)
    {
        arr2.merge(123, res);
        delete_spisoc(arr2.head);
        res = 0;
    }
    else if(sort){
        arr2.merge(sort, res);
        arr2.print(p);
    }
    return res;
}


int list2::task4(char* k, int (*cmp)(const char*, char*),const ordering * p, int flag, int f_del, int sort, list2* a)
{
    int res = 0;
    list2_node *curr, *curr1 = a->head, *tail;
    while(a->head && curr1->next)
        curr1 = curr1->next;
    list2 arr2;
    for(curr = head; curr && head; curr = curr->next){
        if((*cmp)(curr->get_name(), k) == 0){
            if(flag == 0)
            {
                if(f_del == 1)
                {
                    if(!a->head)
                    {
                        a->head = new list2_node;
                        arr2.plus(curr);
                        a->head->init(curr->get_name(), curr->get_phone(), curr->get_group());
                        curr1 = a->head;
                    }
                    else
                    {
                        tail = new list2_node;
                        if(!tail)
                            a->delete_list();
                        arr2.plus(curr);
                        tail->init(curr->get_name(), curr->get_phone(), curr->get_group());
                        curr1->next = (tail);
                        tail->prev = curr1;
                        curr1 = tail;
                    }
                }
                else
                {
                    if(sort)
                        arr2.plus(curr);
                    else
                        curr->record::print(p);
                }
                res++;
            }
        }
        else if(flag == 1){
            if(f_del == 1)
            {
                if(!a->head)
                {
                    a->head = new list2_node;
                    arr2.plus(curr);
                    a->head->init(curr->get_name(), curr->get_phone(), curr->get_group());
                    curr1 = a->head;
                }
                else
                {
                    tail = new list2_node;
                    if(!tail)
                        a->delete_list();
                    arr2.plus(curr);
                    tail->init(curr->get_name(), curr->get_phone(), curr->get_group());
                    curr1->next = (tail);
                    tail->prev = curr1;
                    curr1 = tail;
                }
            }
            else
            {
                if(sort)
                    arr2.plus(curr);
                else
                    curr->record::print(p);
            }
            res++;
        }
    }
    if(f_del)
    {
        arr2.merge(123, res);
        delete_spisoc(arr2.head);
        res = 0;
    }
    else if(sort)
    {
        arr2.merge(sort, res);
        arr2.print(p);
    }
    return res;
}

int list2::task5(int a, int (*cmp1)(const int, int), int b, int (*cmp2)(const int, int), const ordering * p, int l_or, int f_del, int sort, list2* arr){
    int res = 0, i = 0, j = 0;
    list2_node *curr1 = arr->head,*tail;
    list2 arr2;
    if(!vectors)
        return 0;
    if(cmp1 == f1 || cmp1 == f3 || cmp1 == f4)
    {
        for(i = 0; i < l  && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() < a; i++);
        if(i > 0)
            i--;
    }
    if(cmp1 == f1)
    {
        for(i = 0; i < l  && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() <= a; i++);
        if(i > 0)
            i--;
    }
    while(arr->head && curr1->next)
        curr1 = curr1->next;
    for( ; i < l && vectors[i]; i++)
    {
        if((cmp1 == f2 || cmp1 == f3 || cmp1 == f5)  && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() > a)
            break;
        if(cmp1 == f2  && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() == a)
            break;
        for(j = 0; j < k_massiv; j++){
            if(!vectors[i])
                break;
            if(vectors[i][j] == nullptr)
                continue;
            if(l_or == 0){
                if((*cmp1)(vectors[i][j]->get_phone(), a) > 0 && (*cmp2)(vectors[i][j]->get_group(), b) > 0){
                    if(f_del == 1)
                    {
                        if(!arr->head)
                        {
                            arr->head = new list2_node;
                            arr2.plus(vectors[i][j]);
                            arr->head->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                            curr1 = arr->head;
                        }
                        else
                        {
                            tail = new list2_node;
                            if(!tail)
                                arr->delete_list();
                            arr2.plus(vectors[i][j]);
                            tail->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                            curr1->next = (tail);
                            tail->prev = curr1;
                            curr1 = tail;
                        }
                    }
                    else {
                        if(sort)
                            arr2.plus(vectors[i][j]);
                        else
                            vectors[i][j]->record::print(p);
                    }
                    res++;
                }
            }
            else{
                if((*cmp1)(vectors[i][j]->get_phone(), a) > 0 || (*cmp2)(vectors[i][j]->get_group(), b) > 0){
                    if(f_del == 1)
                    {
                        if(!arr->head)
                        {
                            arr->head = new list2_node;
                            arr2.plus(vectors[i][j]);
                            arr->head->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                            curr1 = arr->head;
                        }
                        else
                        {
                            tail = new list2_node;
                            if(!tail)
                                arr->delete_list();
                            arr2.plus(vectors[i][j]);
                            tail->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                            curr1->next = (tail);
                            tail->prev = curr1;
                            curr1 = tail;
                        }
                    }
                    else
                    {
                        if(sort)
                            arr2.plus(vectors[i][j]);
                        else
                            vectors[i][j]->record::print(p);
                    }
                    res++;
                }
            }
        }
    }
    if(f_del)
    {
        arr2.merge(123, res);
        delete_spisoc(arr2.head);
        res = 0;
    }
    else if(sort)
    {
        arr2.merge(sort, res);
        arr2.print(p);
    }
    return res;
}

int list2::task6(int b, int (*cmp2)(const int, int), char* c, int (*cmp3)(const char*, char*), const ordering * p, int flag, int l_or, int f_del, int sort, list2* arr){
    int res = 0, i = 0, j = 0, a = 0, z = 0, FLAG = 0;
    list2_node *curr1 = arr->head,*tail, *curr;
    list2 arr2;
    if(!hesh)
        return 0;
    while(arr->head && curr1->next)
        curr1 = curr1->next;
    if((cmp3 != g1 && cmp3 != g2 && cmp3 != g3 && cmp3 !=g4 && cmp3 != g5) || (l_or == 1))
    {
        FLAG = 1;
        for(curr = head; curr && head; curr = curr->next){
            if(l_or == 0)
            {
                if(flag == 0 && (*cmp3)(curr->get_name(), c) == 0 && (*cmp2)(curr->get_group(), b) > 0){
                    if(f_del == 1)
                    {
                        if(!arr->head)
                        {
                            arr->head = new list2_node;
                            arr2.plus(curr);
                            arr->head->init(curr->get_name(), curr->get_phone(), curr->get_group());
                            curr1 = arr->head;
                        }
                        else
                        {
                            tail = new list2_node;
                            if(!tail)
                                arr->delete_list();
                            arr2.plus(curr);
                            tail->init(curr->get_name(), curr->get_phone(), curr->get_group());
                            curr1->next = (tail);
                            tail->prev = curr1;
                            curr1 = tail;
                        }
                        res++;
                    }
                    else
                    {
                        if(sort)
                            arr2.plus(curr);
                        else
                            curr->record::print(p);
                        res++;
                    }
                }
                else if(flag == 1 && (*cmp3)(curr->get_name(), c) != 0 && (*cmp2)(curr->get_group(), b) > 0){
                    if(f_del == 1)
                    {
                        if(!arr->head)
                        {
                            arr->head = new list2_node;
                            arr2.plus(curr);
                            arr->head->init(curr->get_name(), curr->get_phone(), curr->get_group());
                            curr1 = arr->head;
                        }
                        else
                        {
                            tail = new list2_node;
                            if(!tail)
                                arr->delete_list();
                            arr2.plus(curr);
                            tail->init(curr->get_name(), curr->get_phone(), curr->get_group());
                            curr1->next = (tail);
                            tail->prev = curr1;
                            curr1 = tail;
                        }
                        res++;
                    }
                    else
                    {
                        if(sort)
                            arr2.plus(curr);
                        else
                            curr->record::print(p);
                        res++;
                    }
                }
            }
            else{
                if(flag == 0 && ((*cmp3)(curr->get_name(), c) == 0 || (*cmp2)(curr->get_group(), b) > 0)){
                    if(f_del == 1)
                    {
                        if(!arr->head)
                        {
                            arr->head = new list2_node;
                            arr2.plus(curr);
                            arr->head->init(curr->get_name(), curr->get_phone(), curr->get_group());
                            curr1 = arr->head;
                        }
                        else
                        {
                            tail = new list2_node;
                            if(!tail)
                                arr->delete_list();
                            arr2.plus(curr);
                            tail->init(curr->get_name(), curr->get_phone(), curr->get_group());
                            curr1->next = (tail);
                            tail->prev = curr1;
                            curr1 = tail;
                        }
                        res++;
                    }
                    else
                    {
                        if(sort)
                            arr2.plus(curr);
                        else
                            curr->record::print(p);
                        res++;
                    }
                }
                else if(flag == 1 && ((*cmp3)(curr->get_name(), c) != 0 || (*cmp2)(curr->get_group(), b) > 0)){
                    if(f_del == 1)
                    {
                        if(!arr->head)
                        {
                            arr->head = new list2_node;
                            arr2.plus(curr);
                            arr->head->init(curr->get_name(), curr->get_phone(), curr->get_group());
                            curr1 = arr->head;
                        }
                        else
                        {
                            tail = new list2_node;
                            if(!tail)
                                arr->delete_list();
                            arr2.plus(curr);
                            tail->init(curr->get_name(), curr->get_phone(), curr->get_group());
                            curr1->next = (tail);
                            tail->prev = curr1;
                            curr1 = tail;
                        }
                        res++;
                    }
                    else
                    {
                        if(sort)
                            arr2.plus(curr);
                        else
                            curr->record::print(p);
                        res++;
                    }
                }

            }
        }
    }
    if(FLAG == 0)
    {
        a = number_hesh(c);
        if(cmp3 == g1 || cmp3 == g4 || cmp3 == g3)
            i = a;
        for( ; i < a_hesh && hesh[i]; i++)
        {
            if(cmp3 == g3 && i != a)
                break;
            if((cmp3 == g2 || cmp3 == g5) && i > a)
                break;
            for(j = 0; j < len_hesh[i] && hesh[i][j]; j++){
                for(z = 0; z < m; z++)
                {
                    if(!hesh[i])
                        break;
                    if(hesh[i][j][z] == nullptr)
                        continue;
                    if(l_or == 0)
                    {
                        if(flag == 0 && (*cmp3)(hesh[i][j][z]->get_name(), c) == 0 && (*cmp2)(hesh[i][j][z]->get_group(), b) > 0){
                            if(f_del == 1)
                            {
                                if(!arr->head)
                                {
                                    arr->head = new list2_node;
                                    arr2.plus(hesh[i][j][z]);
                                    arr->head->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1 = arr->head;
                                }
                                else
                                {
                                    tail = new list2_node;
                                    if(!tail)
                                        arr->delete_list();
                                    arr2.plus(hesh[i][j][z]);
                                    tail->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1->next = (tail);
                                    tail->prev = curr1;
                                    curr1 = tail;
                                }
                                res++;
                            }
                            else
                            {
                                if(sort)
                                    arr2.plus(hesh[i][j][z]);
                                else
                                    hesh[i][j][z]->record::print(p);
                                res++;
                            }
                        }
                        else if(flag == 1 && (*cmp3)(hesh[i][j][z]->get_name(), c) != 0 && (*cmp2)(hesh[i][j][z]->get_group(), b) > 0){
                            if(f_del == 1)
                            {
                                if(!arr->head)
                                {
                                    arr->head = new list2_node;
                                    arr2.plus(hesh[i][j][z]);
                                    arr->head->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1 = arr->head;
                                }
                                else
                                {
                                    tail = new list2_node;
                                    if(!tail)
                                        arr->delete_list();
                                    arr2.plus(hesh[i][j][z]);
                                    tail->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1->next = (tail);
                                    tail->prev = curr1;
                                    curr1 = tail;
                                }
                                res++;
                            }
                            else
                            {
                                if(sort)
                                    arr2.plus(hesh[i][j][z]);
                                else
                                    hesh[i][j][z]->record::print(p);
                                res++;
                            }
                        }
                    }
                    else{
                        if(flag == 0 && ((*cmp3)(hesh[i][j][z]->get_name(), c) == 0 || (*cmp2)(hesh[i][j][z]->get_group(), b) > 0)){
                            if(f_del == 1)
                            {
                                if(!arr->head)
                                {
                                    arr->head = new list2_node;
                                    arr2.plus(hesh[i][j][z]);
                                    arr->head->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1 = arr->head;
                                }
                                else
                                {
                                    tail = new list2_node;
                                    if(!tail)
                                        arr->delete_list();
                                    arr2.plus(hesh[i][j][z]);
                                    tail->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1->next = (tail);
                                    tail->prev = curr1;
                                    curr1 = tail;
                                }
                                res++;
                            }
                            else
                            {
                                if(sort)
                                    arr2.plus(hesh[i][j][z]);
                                else
                                    hesh[i][j][z]->record::print(p);
                                res++;
                            }
                        }
                        else if(flag == 1 && ((*cmp3)(hesh[i][j][z]->get_name(), c) != 0 || (*cmp2)(hesh[i][j][z]->get_group(), b) > 0)){
                            if(f_del == 1)
                            {
                                if(!arr->head)
                                {
                                    arr->head = new list2_node;
                                    arr2.plus(hesh[i][j][z]);
                                    arr->head->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1 = arr->head;
                                }
                                else
                                {
                                    tail = new list2_node;
                                    if(!tail)
                                        arr->delete_list();
                                    arr2.plus(hesh[i][j][z]);
                                    tail->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1->next = (tail);
                                    tail->prev = curr1;
                                    curr1 = tail;
                                }
                                res++;
                            }
                            else
                            {
                                if(sort)
                                    arr2.plus(hesh[i][j][z]);
                                else
                                    hesh[i][j][z]->record::print(p);
                                res++;
                            }
                        }

                    }
                }
            }
        }
    }
    if(f_del)
    {
        arr2.merge(123, res);
        delete_spisoc(arr2.head);
        res = 0;
    }
    else if(sort)
    {
        arr2.merge(sort, res);
        arr2.print(p);
    }
    return res;
}

int list2::task7(int a, int (*cmp1)(const int, int), char* c, int (*cmp3)(const char*, char*), const ordering * p, int flag, int l_or, int f_del, int sort, list2* arr){
    int res = 0, i = 0, j = 0, as = 0, z = 0;
    list2_node *curr1 = arr->head, *tail;
    list2 arr2;
    while(arr->head && curr1->next)
        curr1 = curr1->next;
    if((cmp3 != g1 && cmp3 != g2 && cmp3 != g3 && cmp3 !=g4 && cmp3 != g5) || (l_or == 1))
    {
       // printf("this1\n");
        if(!vectors)
            return 0;
        if(cmp1 == f1 || cmp1 == f3 || cmp1 == f4)
        {
            for( ; i < l && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() < a; i++);
            if(i > 0)
                i--;
        }
        if(cmp1 == f1)
        {
            for(i = 0; i < l && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() <= a; i++);
            if(i > 0)
                i--;
        }
        for( ; i < l && vectors[i]; i++)
        {
            if((cmp1 == f2 || cmp1 == f3 || cmp1 == f5) && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() > a)
                break;
            if(cmp1 == f2 && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() == a)
                break;
            for(j = 0; j < k_massiv; j++){
                if(!vectors[i])
                    break;
                if(vectors[i][j] == nullptr)
                    continue;
                if(l_or == 0)
                {
                    if(flag == 0 && (*cmp3)(vectors[i][j]->get_name(), c) == 0 && (*cmp1)(vectors[i][j]->get_phone(), a) > 0){
                        if(f_del == 1)
                        {
                            if(!arr->head)
                            {
                                arr->head = new list2_node;
                                arr2.plus(vectors[i][j]);
                                arr->head->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1 = arr->head;
                            }
                            else
                            {
                                tail = new list2_node;
                                if(!tail)
                                    arr->delete_list();
                                arr2.plus(vectors[i][j]);
                                tail->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1->next = (tail);
                                tail->prev = curr1;
                                curr1 = tail;
                            }
                            res++;
                        }
                        else
                        {
                            if(sort)
                                arr2.plus(vectors[i][j]);
                            else
                                vectors[i][j]->record::print(p);
                            res++;
                        }
                    }
                    else if(flag == 1 && (*cmp3)(vectors[i][j]->get_name(), c) != 0 && (*cmp1)(vectors[i][j]->get_phone(), a) > 0){
                        if(f_del == 1)
                        {
                            if(!arr->head)
                            {
                                arr->head = new list2_node;
                                arr2.plus(vectors[i][j]);
                                arr->head->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1 = arr->head;
                            }
                            else
                            {
                                tail = new list2_node;
                                if(!tail)
                                    arr->delete_list();
                                arr2.plus(vectors[i][j]);
                                tail->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1->next = (tail);
                                tail->prev = curr1;
                                curr1 = tail;
                            }
                            res++;
                        }
                        else
                        {
                            if(sort)
                                arr2.plus(vectors[i][j]);
                            else
                                vectors[i][j]->record::print(p);
                            res++;
                        }
                    }
                }
                else{
                    if(flag == 0 && ((*cmp3)(vectors[i][j]->get_name(), c) == 0 || (*cmp1)(vectors[i][j]->get_phone(), a) > 0)){
                        if(f_del == 1)
                        {
                            if(!arr->head)
                            {
                                arr->head = new list2_node;
                                arr2.plus(vectors[i][j]);
                                arr->head->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1 = arr->head;
                            }
                            else
                            {
                                tail = new list2_node;
                                if(!tail)
                                    arr->delete_list();
                                arr2.plus(vectors[i][j]);
                                tail->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1->next = (tail);
                                tail->prev = curr1;
                                curr1 = tail;
                            }
                            res++;
                        }
                        else
                        {
                            if(sort)
                                arr2.plus(vectors[i][j]);
                            else
                                vectors[i][j]->record::print(p);
                            res++;
                        }
                    }
                    else if(flag == 1 && ((*cmp3)(vectors[i][j]->get_name(), c) != 0 || (*cmp1)(vectors[i][j]->get_phone(), a) > 0)){
                        if(f_del == 1)
                        {
                            if(!arr->head)
                            {
                                arr->head = new list2_node;
                                arr2.plus(vectors[i][j]);
                                arr->head->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1 = arr->head;
                            }
                            else
                            {
                                tail = new list2_node;
                                if(!tail)
                                    arr->delete_list();
                                arr2.plus(vectors[i][j]);
                                tail->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1->next = (tail);
                                tail->prev = curr1;
                                curr1 = tail;
                            }
                            res++;
                        }
                        else
                        {
                            if(sort)
                                arr2.plus(vectors[i][j]);
                            else
                                vectors[i][j]->record::print(p);
                            res++;
                        }
                    }

                }
            }
        }
    }
    else
    {
      //  printf("this2\n");
        if(!hesh)
            return 0;
        as = number_hesh(c);
        if(cmp3 == g1 || cmp3 == g4 || cmp3 == g3)
            i = as;
        for( ; i < a_hesh && hesh[i]; i++)
        {
            if(cmp3 == g3 && i != as)
                break;
            if((cmp3 == g2 || cmp3 == g5) && i > as)
                break;
            for(j = 0; j < len_hesh[i] && hesh[i][j]; j++){
                for(z = 0; z < m; z++)
                {
                    if(!hesh[i])
                        break;
                    if(hesh[i][j][z] == nullptr)
                        continue;
                    if(l_or == 0)
                    {
                        if(flag == 0 && (*cmp3)(hesh[i][j][z]->get_name(), c) == 0 && (*cmp1)(hesh[i][j][z]->get_phone(), a) > 0){
                            if(f_del == 1)
                            {
                                if(!arr->head)
                                {
                                    arr->head = new list2_node;
                                    arr2.plus(hesh[i][j][z]);
                                    arr->head->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1 = arr->head;
                                }
                                else
                                {
                                    tail = new list2_node;
                                    if(!tail)
                                        arr->delete_list();
                                    arr2.plus(hesh[i][j][z]);
                                    tail->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1->next = (tail);
                                    tail->prev = curr1;
                                    curr1 = tail;
                                }
                                res++;
                            }
                            else
                            {
                                if(sort)
                                    arr2.plus(hesh[i][j][z]);
                                else
                                    hesh[i][j][z]->record::print(p);
                                res++;
                            }
                        }
                        else if(flag == 1 && (*cmp3)(hesh[i][j][z]->get_name(), c) != 0 && (*cmp1)(hesh[i][j][z]->get_phone(), a) > 0){
                            if(f_del == 1)
                            {
                                if(!arr->head)
                                {
                                    arr->head = new list2_node;
                                    arr2.plus(hesh[i][j][z]);
                                    arr->head->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1 = arr->head;
                                }
                                else
                                {
                                    tail = new list2_node;
                                    if(!tail)
                                        arr->delete_list();
                                    arr2.plus(hesh[i][j][z]);
                                    tail->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1->next = (tail);
                                    tail->prev = curr1;
                                    curr1 = tail;
                                }
                                res++;
                            }
                            else
                            {
                                if(sort)
                                    arr2.plus(hesh[i][j][z]);
                                else
                                    hesh[i][j][z]->record::print(p);
                                res++;
                            }
                        }
                    }
                    else{
                    //    printf("why\n");
                        if(flag == 0 && ((*cmp3)(hesh[i][j][z]->get_name(), c) == 0 || (*cmp1)(hesh[i][j][z]->get_phone(), a) > 0)){
                            if(f_del == 1)
                            {
                                if(!arr->head)
                                {
                                    arr->head = new list2_node;
                                    arr2.plus(hesh[i][j][z]);
                                    arr->head->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1 = arr->head;
                                }
                                else
                                {
                                    tail = new list2_node;
                                    if(!tail)
                                        arr->delete_list();
                                    arr2.plus(hesh[i][j][z]);
                                    tail->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1->next = (tail);
                                    tail->prev = curr1;
                                    curr1 = tail;
                                }
                                res++;
                            }
                            else
                            {
                                if(sort)
                                    arr2.plus(hesh[i][j][z]);
                                else
                                    hesh[i][j][z]->record::print(p);
                                res++;
                            }
                        }
                        else if(flag == 1 && ((*cmp3)(hesh[i][j][z]->get_name(), c) != 0 || (*cmp1)(hesh[i][j][z]->get_phone(), a) > 0)){
                            if(f_del == 1)
                            {
                                if(!arr->head)
                                {
                                    arr->head = new list2_node;
                                    arr2.plus(hesh[i][j][z]);
                                    arr->head->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1 = arr->head;
                                }
                                else
                                {
                                    tail = new list2_node;
                                    if(!tail)
                                        arr->delete_list();
                                    arr2.plus(hesh[i][j][z]);
                                    tail->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1->next = (tail);
                                    tail->prev = curr1;
                                    curr1 = tail;
                                }
                                res++;
                            }
                            else
                            {
                                if(sort)
                                    arr2.plus(hesh[i][j][z]);
                                else
                                    hesh[i][j][z]->record::print(p);
                                res++;
                            }
                        }
                    }
                }
            }
        }
    }
    if(f_del)
    {
//        printf("delete\n");
        arr2.merge(123, res);
//        arr2.print(p);
//        printf("delete\n");
        delete_spisoc(arr2.head);
        res = 0;
    }
    else if(sort)
    {
        arr2.merge(sort, res);
        arr2.print(p);
    }
    return res;
}

int list2::task8(int a, int (*cmp1)(const int, int), int b, int (*cmp2)(const int, int), char* c, int (*cmp3)(const char*, char*), const ordering * p, int flag, int l_or, int f_del, int sort, list2* arr)
{
    int res = 0, i = 0, j = 0, z = 0, as = 0;
    list2_node *curr1 = arr->head, *tail;
    while(arr->head && curr1->next)
        curr1 = curr1->next;
    list2 arr2;
    if((cmp3 != g1 && cmp3 != g2 && cmp3 != g3 && cmp3 !=g4 && cmp3 != g5) || (l_or == 1))
    {
        if(!vectors)
            return 0;
        if(cmp1 == f1 || cmp1 == f3 || cmp1 == f4)
        {
            for(i = 0; i < l && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() < a; i++);
            if(i > 0)
                i--;
        }
        if(cmp1 == f1)
        {
            for(i = 0; i < l && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() <= a; i++);
            if(i > 0)
                i--;
        }
        for( ; i < l && vectors[i]; i++)
        {
            if((cmp1 == f2 || cmp1 == f3 || cmp1 == f5) && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() > a)
                break;
            if(cmp1 == f2 && vectors[i] && vectors[i][0] && vectors[i][0]->get_phone() == a)
                break;
            for(j = 0; j < k_massiv; j++){
                if(!vectors[i])
                    break;
                if(vectors[i][j] == nullptr)
                    continue;
                if(l_or == 0)
                {
                    if(flag == 0 && (*cmp3)(vectors[i][j]->get_name(), c) == 0 && (*cmp1)(vectors[i][j]->get_phone(), a) > 0 && (*cmp2)(vectors[i][j]->get_group(), b) > 0){
                        if(f_del == 1)
                        {
                            if(!arr->head)
                            {
                                arr->head = new list2_node;
                                arr2.plus(vectors[i][j]);
                                arr->head->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1 = arr->head;
                            }
                            else
                            {
                                tail = new list2_node;
                                if(!tail)
                                    arr->delete_list();
                                arr2.plus(vectors[i][j]);
                                tail->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1->next = (tail);
                                tail->prev = curr1;
                                curr1 = tail;
                            }
                            res++;
                        }
                        else
                        {
                            if(sort)
                                arr2.plus(vectors[i][j]);
                            else
                                vectors[i][j]->record::print(p);
                            res++;
                        }
                    }
                    else if(flag == 1 && (*cmp3)(vectors[i][j]->get_name(), c) != 0 && (*cmp1)(vectors[i][j]->get_phone(), a) > 0 && (*cmp2)(vectors[i][j]->get_group(), b) > 0){
                        if(f_del == 1)
                        {
                            if(!arr->head)
                            {
                                arr->head = new list2_node;
                                arr2.plus(vectors[i][j]);
                                arr->head->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1 = arr->head;
                            }
                            else
                            {
                                tail = new list2_node;
                                if(!tail)
                                    arr->delete_list();
                                arr2.plus(vectors[i][j]);
                                tail->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1->next = (tail);
                                tail->prev = curr1;
                                curr1 = tail;
                            }
                            res++;
                        }
                        else
                        {
                            if(sort)
                                arr2.plus(vectors[i][j]);
                            else
                                vectors[i][j]->record::print(p);
                            res++;
                        }
                    }
                }
                else{
                    if(flag == 0 && ((*cmp3)(vectors[i][j]->get_name(), c) == 0 || (*cmp1)(vectors[i][j]->get_phone(), a) > 0 || (*cmp2)(vectors[i][j]->get_group(), b) > 0)){
                        if(f_del == 1)
                        {
                            if(!arr->head)
                            {
                                arr->head = new list2_node;
                                arr2.plus(vectors[i][j]);
                                arr->head->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1 = arr->head;
                            }
                            else
                            {
                                tail = new list2_node;
                                if(!tail)
                                    arr->delete_list();
                                arr2.plus(vectors[i][j]);
                                tail->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1->next = (tail);
                                tail->prev = curr1;
                                curr1 = tail;
                            }
                            res++;
                        }
                        else
                        {
                            if(sort)
                                arr2.plus(vectors[i][j]);
                            else
                                vectors[i][j]->record::print(p);
                            res++;
                        }
                    }
                    else if(flag == 1 && ((*cmp3)(vectors[i][j]->get_name(), c) != 0 || (*cmp1)(vectors[i][j]->get_phone(), a) > 0 || (*cmp2)(vectors[i][j]->get_group(), b) > 0)){
                        if(f_del == 1)
                        {
                            if(!arr->head)
                            {
                                arr->head = new list2_node;
                                arr2.plus(vectors[i][j]);
                                arr->head->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1 = arr->head;
                            }
                            else
                            {
                                tail = new list2_node;
                                if(!tail)
                                    arr->delete_list();
                                arr2.plus(vectors[i][j]);
                                tail->init(vectors[i][j]->get_name(), vectors[i][j]->get_phone(), vectors[i][j]->get_group());
                                curr1->next = (tail);
                                tail->prev = curr1;
                                curr1 = tail;
                            }
                            res++;
                        }
                        else
                        {
                            if(sort)
                                arr2.plus(vectors[i][j]);
                            else
                                vectors[i][j]->record::print(p);
                            res++;
                        }
                    }
                }
            }
        }
    }
    else
    {
        if(!hesh)
            return 0;
        as = number_hesh(c);
        i = as;
        if(cmp3 == g1 || cmp3 == g4 || cmp3 == g3)
            i = as;
        for( ; i < a_hesh && hesh[i]; i++)
        {
            if(cmp3 == g3 && i != as)
                break;
            if((cmp3 == g2 || cmp3 == g5) && i > as)
                break;
            for(j = 0; j < len_hesh[i] && hesh[i][j]; j++){
                for(z = 0; z < m; z++)
                {
                    if(!hesh[i])
                        break;
                    if(hesh[i][j][z] == nullptr)
                        continue;
                    if(l_or == 0)
                    {
                        if(flag == 0 && (*cmp3)(hesh[i][j][z]->get_name(), c) == 0 && (*cmp1)(hesh[i][j][z]->get_phone(), a) > 0 && (*cmp2)(hesh[i][j][z]->get_group(), b) > 0){
                            if(f_del == 1)
                            {
                                if(!arr->head)
                                {
                                    arr->head = new list2_node;
                                    arr2.plus(hesh[i][j][z]);
                                    arr->head->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1 = arr->head;
                                }
                                else
                                {
                                    tail = new list2_node;
                                    if(!tail)
                                        arr->delete_list();
                                    arr2.plus(hesh[i][j][z]);
                                    tail->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1->next = (tail);
                                    tail->prev = curr1;
                                    curr1 = tail;
                                }
                                res++;
                            }
                            else
                            {
                                if(sort)
                                    arr2.plus(vectors[i][j]);
                                else
                                    hesh[i][j][z]->record::print(p);
                                res++;
                            }
                        }
                        else if(flag == 1 && (*cmp3)(hesh[i][j][z]->get_name(), c) != 0 && (*cmp1)(hesh[i][j][z]->get_phone(), a) > 0 && (*cmp2)(hesh[i][j][z]->get_group(), b) > 0){
                            if(f_del == 1)
                            {
                                if(!arr->head)
                                {
                                    arr->head = new list2_node;
                                    arr2.plus(hesh[i][j][z]);
                                    arr->head->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1 = arr->head;
                                }
                                else
                                {
                                    tail = new list2_node;
                                    if(!tail)
                                        arr->delete_list();
                                    arr2.plus(hesh[i][j][z]);
                                    tail->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1->next = (tail);
                                    tail->prev = curr1;
                                    curr1 = tail;
                                }
                                res++;
                            }
                            else
                            {
                                if(sort)
                                    arr2.plus(hesh[i][j][z]);
                                else
                                    hesh[i][j][z]->record::print(p);
                                res++;
                            }
                        }
                    }
                    else{
                        if(flag == 0 && ((*cmp3)(hesh[i][j][z]->get_name(), c) == 0 || (*cmp1)(hesh[i][j][z]->get_phone(), a) > 0 || (*cmp2)(hesh[i][j][z]->get_group(), b) > 0)){
                            if(f_del == 1)
                            {
                                if(!arr->head)
                                {
                                    arr->head = new list2_node;
                                    arr2.plus(hesh[i][j][z]);
                                    arr->head->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1 = arr->head;
                                }
                                else
                                {
                                    tail = new list2_node;
                                    if(!tail)
                                        arr->delete_list();
                                    arr2.plus(hesh[i][j][z]);
                                    tail->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1->next = (tail);
                                    tail->prev = curr1;
                                    curr1 = tail;
                                }
                                res++;
                            }
                            else
                            {
                                if(sort)
                                    arr2.plus(hesh[i][j][z]);
                                else
                                    hesh[i][j][z]->record::print(p);
                                res++;
                            }
                        }
                        else if(flag == 1 && ((*cmp3)(hesh[i][j][z]->get_name(), c) != 0 || (*cmp1)(hesh[i][j][z]->get_phone(), a) > 0 || (*cmp2)(hesh[i][j][z]->get_group(), b) > 0)){
                            if(f_del == 1)
                            {
                                if(!arr->head)
                                {
                                    arr->head = new list2_node;
                                    arr2.plus(hesh[i][j][z]);
                                    arr->head->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1 = arr->head;
                                }
                                else
                                {
                                    tail = new list2_node;
                                    if(!tail)
                                        arr->delete_list();
                                    arr2.plus(hesh[i][j][z]);
                                    tail->init(hesh[i][j][z]->get_name(), hesh[i][j][z]->get_phone(), hesh[i][j][z]->get_group());
                                    curr1->next = (tail);
                                    tail->prev = curr1;
                                    curr1 = tail;
                                }
                                res++;
                            }
                            else
                            {
                                if(sort)
                                    arr2.plus(hesh[i][j][z]);
                                else
                                    hesh[i][j][z]->record::print(p);
                                res++;
                            }
                        }
                    }
                }
            }
        }
    }
    if(f_del)
    {
        arr2.merge(123, res);
        delete_spisoc(arr2.head);
        res = 0;
    }
    else if(sort)
    {
        arr2.merge(sort, res);
        arr2.print(p);
    }
    return res;
}

int list2::strcmp12(const char* s1, char* s2) //находит просто слова удовлетворяющие только спецсимволу "_"
{
    int j = 0, l = 0, i = 0;
    for(i = 0; s1[i] != '\0' && s2[j] != '\0'; i++) {
        if(s2[j] == '\\' && l == 0) {
            j++;
            l = 1;
        }
        if(l == 0 && s2[j] == '_')
            j++;
        else if(s1[i] != s2[j])
            return 1;
        else
            j++;
        l = 0;
    }
    if(s1[i] != '\0' || s2[j] != '\0')
        return 1;
    return 0;
}

int list2::func(char c, char* s, int& m) // вспогательная задача(для strmp34) для спецсимволов [n-m] and [^n-m]
{
    int j = 0;
    char c1, c2;
    if(s[++j] == '\\')
        j++;
    if(s[j] == '\0' || s[j] == '\n')
        return 1;
    if(!m)
        j++;
    if(s[j] == '\\')
        j++;
    c1 = s[j];
    j++;
    if(s[j] == '\0' || s[j] == '\n')
        return 1;
    if(s[++j] == '\\')
        j++;
    if(s[j] == '\0' || s[j] == '\n' || s[j+1] == '\0' || s[j] == '\n')
        return 1;
    c2 = s[j];
    j += 2;
    if(m == 1 && (c < (c1) || c > (c2)))
    {
        m = j;
        return 1;
    }
    if(m == 0 && (c >= (c1) && c <= (c2)))
    {
        m = j;
        return 1;
    }
    m = j;
    return 0;
}

int list2::strstr_1 (const char *s1, char *s2) //вспомогательная задача (для strmp34) смотрит с какого номера элемента слово s2 входит в слово s1
{
    int j = 0;
    for(int i = 0; s1[i]; i++)
    {
        bool inRange;
        char *s = s2;
        s--;
        j = -1;
        do
        {
            j++;
            s++;
            inRange = false;
            for(;*(s+1) && *s == '\\' ;s++)
            {
                s++;
                if(*s != s1[i+j])
                    return -1;
            }
            if(*s == '[')
            {
                int newpos;
                if(s[1] == '^')
                    newpos = 0;
                else
                    newpos = 1;

                int n = func(s1[i + j], s, newpos);
                if(n == 1)
                    continue;

                inRange = true;
                s += newpos - 1;
            }
        }
        while(s1[i + j] && (s1[i + j] == *s || *s == '_' || inRange));

        if(*s == '\0')
            return i;
}
    return -1;
}

int list2::strstr_2 (const char *s1, char *s2)//вспомогательная задача (для strmp34) входит слово s2 в s1, если известно, что оно должно совпадать с концом слова
{
    int j = strlen(s2) - 1;
    if(s2[j] == '\n')
        j--;
    int i = strlen(s1) - 1;
    if(s1[i] == '\n')
        i--;
    i++;
    j++;
    int m = 0;
    bool inRange;
    do{
        m = 0;
        i--;
        j--;
        inRange = false;
        for(;j > 0 && s2[j - 1] == '\\' ;j-=2) {
            if(s2[j] != s1[i])
                return -1;
            i--;
        }
        if(s2[j] == ']') {
            char c1, c2;
            if(j == 0)
                return -1;
            c2 = s2[--j];
            if(j == 0)
                return -1;
            if(s2[--j] == '\\')
                j--;
            j--;
            if(j <= 0)
                return -1;

            c1 = s2[j];
            if(s2[--j] == '\\')
                j--;
            if(j < 0)
                return -1;
            if(s2[j] == '^') {
                m = 1;
                j--;
            }
            if(m == 0 && (s1[i] < (c1) || s1[i] > (c2)))
                return -1;
            if(m == 1 && (s1[i] >= (c1) && s1[i] <= (c2)))
                return -1;
            inRange = true;
        }
    }
    while(i >= 0 && j >= 0 && (s1[i] == s2[j] || s2[j] == '_' || inRange));
    if(j < 0)
        return 0;
    return -1;
}

int list2::strcmp34(const char* s1, char* s2)//задача на все спецсиволы
{
    char buf[LEN];
    const char*s;
    s = s1;
    int l = 0, m = 0, j = 0, i = 0, k = 0, a = -1, n = 0;
    for(i = 0; s1[i] != '\0'; i++) {
        if(s2[j] == '\\' && l == 0){
            j++;
            l = 1;
        }
        while(l == 0 && s2[j] == '%') {
            m = 1;
            j++;
        }
        if(m == 1){
            while(s2[j] != '\0'){
                while(m == 1 && s2[j] == '%')
                    j++;
                m = 0;
                if(s2[j] == '\\' && l == 0 && s2[j + 1] == '%'){
                    j++;
                    l = 1;
                    m = 0;
                }
                if(l == 0 && s2[j] == '%')
                    break;
                buf[k++] = s2[j++];
            }
            buf[k] = '\0';
            if(buf[0] == '\0')
                return 0;
            while(a < i) {
                if(s2[j] == '\n' || s2[j] == '\0')
                {
                    a = strstr_2(s, buf);
                    if(a == -1)
                        return 1;
                    return 0;
                }
                else
                    a = strstr_1(s, buf);
                if(a == -1)
                    return 1;
                k += a;
                s = s + a;
            }
            i = k - 1;
            s = s1;
        }
        else {
            n = 0;
            if(l == 0 && s2[j] == '_')
                j++;
            else if(l == 0 && s2[j] == '[' && s2[j+1] == '^')
            {
                int newpos = 0;
                n = func(s1[i], s2+j, newpos);
                if(n == 1)
                    return 1;
                j += newpos;
            }
            else if(l == 0 && s2[j] == '[')
            {
                int newpos = 1;
                n = func(s1[i], s2+j, newpos);
                if(n == 1)
                    return 1;
                j += newpos;
            }
            else if(s1[i] != s2[j])
                return 1;
            else
                j++;
        }
        m = 0;
        l = 0;
        k = 0;
    }
    if(s1[i] == '\0')
        while(s2[j] == '%')
            j++;
    if(s2[j] != '\0' || s1[i] != '\0')
        return 1;
    return 0;
}

int list2::strcmp5(const char* s1, char* s2)//задача , работающая только со спецсимволом [n-m]
{
    int j = 0, l = 0, i, m = 0;
    char c1, c2;
    for(i = 0; s1[i] != '\0' && s2[j] != '\0'; i++)
    {
        if(s2[j] == '\\' && l == 0){
            j++;
            l = 1;
        }
        if(l == 0 && s2[j] == '[')
        {
            m = 1;
            if(s2[++j] == '\\')
                j++;
            c1 = s2[j];
            j++;
            if(s2[++j] == '\\')
                j++;
            c2 = s2[j];
            j += 2;
        }
        if(m == 1)
        {
            if(s1[i] < (c1) || s1[i] > (c2))
                return 1;
        }
        else if(s1[i] != s2[j])
            return 1;
        else
            j++;
        l = 0;
        m = 0;
    }
    if(s1[i] != '\0' || s2[j] != '\0')        
        return 1;
    return 0;
}

int list2::strcmp6(const char* s1, char* s2)//задача , работающая только со спецсимволом [^n-m]
{
    int j = 0, l = 0, i, m = 0;
    char c1, c2;
    for(i = 0; s1[i] != '\0' && s2[j] != '\0'; i++)
    {
        if(s2[j] == '\\' && l == 0){
            j++;
            l = 1;
        }
        if(l == 0 && s2[j] == '[')
        {
            m = 1;
            j++;
            if(s2[++j] == '\\')
                j++;
            c1 = s2[j];
            j++;
            if(s2[++j] == '\\')
                j++;
            c2 = s2[j];
            j += 2;
        }
        if(m == 1)
        {
            if(s1[i] >= (c1) && s1[i] <= (c2))
                return 1;
        }
        else if(s1[i] != s2[j])
            return 1;
        else
            j++;
        l = 0;
        m = 0;
    }
    if(s1[i] != '\0' || s2[j] != '\0')        
        return 1;
    return 0;
}
