#include"cust.h"
#include<assert.h>
using namespace std;
// Constructor for cust object,  
Cust :: Cust(string w, string x, int y, int z)
{
        name = w;
        if(x == "robber")
        {
                shop = 1;
        }
        else 
        {
                shop = 0;
        }
        time = y;
        items = z;
        d_time = time +(items*2);

}
Cust:: ~Cust()
{
}
// Getter function for the time 
int Cust :: gettime()
{
        return time;
}
// Set the customers current time 
void Cust :: settime(int x)
{
        time = x;
}
// Returns the amount of items that the current customer has 
int Cust :: getitems()
{
        return items;
}
// Returns the name of the current customer 
string Cust :: getname()
{
        return name;
}
// Returns the boolean value for the robber 
bool Cust :: getshop()
{
        return shop;
}
// Prints the customer and all of its values, mostly for debug 
void Cust :: print(ostream &os)
{
        os << "name: "<< name << "Shop or Rob: " << shop << " Arrival: " << time << " Items: " << items << endl;
}
// entered message, will run if the assert statement is true
void Cust ::entered ( ostream & os , int clock )
{
        assert ( clock == time );
        os << clock << ": " << name << " entered store" << endl ;
}
// The bought staement, prints the paid message to the output file. 
void Cust :: bought_items(ostream &os, int clock, int checker)
{
        if(items <2)
        {
        os << clock << ": " << name << " paid $" << items *3 << " for " << items << " item to checker " << checker << endl;  
        }
        else 
        {
        os << clock << ": " << name << " paid $" << items *3 << " for " << items << " items to checker " << checker << endl;
        }
}
//  The done statement, for the current customer.
void Cust :: doneshop(ostream &os, int clock)
{
        os << clock << ": " << name << " done shopping" << endl;
}
// The stole message, similar to the bought statement but for stealing. 
void Cust :: stole(ostream &os, int clock, int cash, int checker)
{
        if(items < 2)
        {
                os << clock << ": " << name << " stole $" << cash << " and " << items << " item from checker " << checker << endl;
        }
        else 
        {
                os << clock << ": " << name << " stole $" << cash << " and " << items << " items from checker " << checker << endl;

        }

}
// Prints the started checking out message to the outputfile
void Cust :: start_check(ostream &os, int clock, int checker)
{
        assert (clock == time);
        os << clock << ": " << name << " started checkout with checker " << checker <<endl;
}
