#ifndef CUST_H
#define CUST_H
#include<iostream>
using namespace std;
class Cust
{
        private:
                string name;
                bool shop;
                int time;
                int items;
                int d_time;
                int c_time;
        public: 
                Cust();
                ~Cust();
                void entered(ostream &os,int clock); 
                void bought_items(ostream &os, int clock, int checker);
                void start_check(ostream &os, int clock, int checker);
                Cust(string name, string shop, int time, int items);
                void doneshop(ostream &os, int clock);
                void print(ostream &os);
                void stole(ostream &os, int clock, int cash, int checker);
                int gettime();
                void settime(int x);
                int getitems();
                bool getshop();
                string getname();
               
};

#endif
