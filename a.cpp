#include "record.hpp"
#include "list2_node.hpp"
#include "list2.hpp"
#include "command.hpp"
#include <time.h>
#include <iostream>
using namespace std;
#define LEN 1234

int main(int argc,char* argv[])
{
    const char* name1 = 0;
    double t;
    int Res = 0;
    if(argc != 2)
    {
        printf("Usage %s file\n",argv[0]);
        return 1;
    }
    name1 = argv[1];
    FILE*fp;
    FILE * kp;
    if(!(fp = fopen(name1, "r")))
    {
        printf("Cannot open %s\n",name1);
        return 2;
    }
    const char * config_name = "config.txt";
    char buf[LEN];
    fprintf((stderr), "Exe = %s\n", argv[0]);
    strcpy(buf, argv[0]);
    char * fname = strrchr (buf, '/');
    if(fname != nullptr)
    {
        fname[0] = '/';
        fname[1] = '\0';
        strcat(buf, config_name);
    }
    else
        strcpy(buf, config_name);
    fprintf(stderr, "Config path = %s\n", buf);
    if(!(kp = fopen(buf, "r")))
    {
        fprintf(stderr, "Cannot open file %s\n", buf);
        return 1;
    }
    int number = 0, k_n = 0, k_m = 0, M = 0;
    char *s = nullptr;
    while(fgets(buf, LEN, kp))
    {
        if(buf[0] == '\n' || buf[0] == '#')
            continue;
        int i = 0;
        while(buf[i] == ' ' || buf[i] == '\t')
            i++;
        if(buf[i] == '\n' || buf[i] == '\0')
            continue;
        s = buf;
        s = strtok(s, " \t\n");
        if(buf == nullptr){
            fclose(kp);
            return 1;
        }
        if(proverka(s) != true){
            fclose(kp);
            return 1;
        }
        if(number == 0)
        {
            k_m = stoi(s);
            number++;
            continue;
        }
        if(number == 1)
        {
            k_n = stoi(s);
            number++;
            continue;
        }
        M = stoi(s);
        break;
    }
    if(k_n <= 0 || k_m <= 0 || M <= 0)
    {
        fclose(kp);
        return 1;
    }
    fclose(kp);
    command qq;
    t = clock();
    Res = qq.sbor(fp, k_n, k_m, M);
    t = (clock() - t)/CLOCKS_PER_SEC;
    if(Res < 0)
    {
        switch(Res)
        {
            case -1:
                printf("Ошибка в чтении файла\n");
                break;
            case -2:
                printf("Ошибка в запросе или в командах\n");
                break;
            case -3:
                printf("Ошибка в сборке\n");
                break;
            default:
                printf("Unknown error in  %s\n", name1);
        }
        fclose(fp);
        return 2;
    }
    printf ("%s : Result = %d Elapsed = %.2f\n",argv[0], Res, t);
    fclose(fp);
    return 0;
}