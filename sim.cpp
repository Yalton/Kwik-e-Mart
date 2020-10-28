// All my includes and stuff 
#include<iostream>
#include<fstream>
#include<ctype.h>
#include"cust.h"
#include"pqueue.h"
using namespace std;
// debug variable i put in all my code, its more than useful, its essential 
bool DEBUG = false;
struct Checker 
{
        int cash = 250;
        int b_over = 0;
        int c_time=0;
        Cust *ptr;
};
// Cute little recursive function that uses a whole lot of isdigit()
bool is_int(char str[])
{
        // Returns if string is empty 
        if(*str == NULL)
        {
                return true;
        }
        // If there are still values on the string, run again with the pointer pointing to the next value 
        if(isdigit(*str))
        {
                return is_int(str +1);
        }
        // If is it not a digit, then return false
        else if(!isdigit(*str))
        {
                return false;
        }
}
// This gigantic function, which is essentially the block of the whole program, takes in 4 arguments, half of which are command line arguments 
void run_simulation ( Pqueue & arrival_queue , int num_checkers ,int break_duration , ostream &os)
{
        // Initialized the Shopping Queue"Sq", and the Line Queue "Lq 
        Pqueue Sq;
        Pqueue Lq;
        //Important bit of code, that determines how long the main loop will run 
        int num_customers = arrival_queue.length();
        Checker * checkers = new Checker [ num_checkers ];
        // A cout that is for any debbuger who might wanna edit this code 
        if(DEBUG == true)
        {
                cout <<"Arrival Queue has " <<arrival_queue.length() <<" impatient customers." <<endl;
        }
        // Error status in case not a single customer was passed into the arrival queue. 
        if(arrival_queue.empty() == 1)
        {
                cerr << "Error: Arrival Queue is empty" << endl;
                exit(1);
        }
        // First for loop, and the main one. Runs through all the other for loops until num_customers == 0
        for (int time =1; num_customers >0; time++)
        {
                // Mainly an error condition for me, so that the program will end before it gets to 500000+ time. 
                if(time >= 5000)
                {
                        cerr << "big boi issues" << endl;
                        exit(1);
                }
                // Nice little debug cout that will print the current time every five seconds. 
                if(DEBUG == true)
                {
                        if(time % 5 ==0)
                        {
                                cout << "In Sim-loop, time is: " << time << endl;
                        }
                }
                // When the customers arrival time is equal to the current time, do some stuff. 
                while(arrival_queue.first_priority() == time && !arrival_queue.empty())
                {
                        Cust *cust = arrival_queue.dequeue();
                        if(DEBUG == true)
                        {
                                cout <<"In arrival queue for, " << cust ->getname() << endl;
                        }
                        // Prints the entered the store message to tge output file, and increments time accordingly, aswell as putting the 
                        // customer on the Shopping Queue 
                        cust -> entered(os, time);
                        cust -> settime(time + (cust -> getitems()) *2 );
                        Sq.enqueue(cust, (time + (cust -> getitems() * 2)));
                }
                // When the shopping queue time is equal to the current time, do things
                while(Sq.first_priority() == time && !Sq.empty())
                {
                        // Takes the current customer off the front of the queue, prints the done shopping message to the output file, and 
                        // enqueues the customer onto the Line Queue 
                        Cust *cust = Sq.dequeue();
                        cust->doneshop(os, time);
                        Lq.enqueue(cust,1);
                }
                // Loop that will run if there are customers waiting in line to be checked out
                for(int i =0; i< num_checkers; i++)
                {
                        // Checks if the ptr is empty, and if the time is equal to the checkers checkout time. 
                        if(checkers[i].ptr != NULL &&  time == checkers[i].c_time)
                        {
                                // Checks to see if the recently dequeued customer is a robber or not. 
                                if(checkers[i].ptr ->getshop() == true)
                                {
                                        // Debug statement that will print the customers name and their items 
                                        if(DEBUG ==true)
                                        {
                                                cout << checkers[i].ptr -> getname() << " ooh he stealin." << endl;
                                        }
                                        // Prints the steal line to the output file, sets the checker cash to 0, and puts the checker
                                        // on break for the correct time. 
                                        checkers[i].ptr -> stole(os, time, checkers[i].cash,i);
                                        checkers[i].cash = 0;
                                        checkers[i].b_over = time + break_duration;
                                }
                                // If the customer is not a robber, this code block will run
                                else 
                                {
                                        // yet another debug staement to print the customers name and items 
                                        if(DEBUG == true)
                                        {
                                                cout << checkers[i].ptr -> getname() << " has "<< checkers[i].ptr ->getitems() << " items, and is at checker "<< i <<endl;
                                        }
                                        // Prints the bought items prompt to the output file, and updates the checkers cash 
                                        checkers[i].ptr -> bought_items(os,time,i);
                                        checkers[i].cash = checkers[i].cash + (checkers[i].ptr->getitems() *3);

                                }
                                // Statement that runs regardless of whether the shopper was a robebr or not, removed the current custome, 
                                // and sets the next customer toNULL
                                delete checkers[i].ptr;
                                checkers[i].ptr = NULL;
                                num_customers --;
                        }
                }
                // 4th for loop which will only run if the Line Queue is not empty, and will run until 
                // i == num_checkers 
                for(int i =0; !Lq.empty() && i < num_checkers; i++)
                {
                        // If the current checker is serving no customers, and the checker is not
                        // on break 
                        if( checkers[i].ptr ==  NULL && checkers[i].b_over <= time)
                        {
                                // Assign the first customer on the queue to the current checker 
                                checkers[i].ptr = Lq.dequeue();
                                // If the customer is a robber, run this block
                                if(checkers[i].ptr -> getshop() == true)
                                {
                                        // Calculates time the robber will be done, and sets the times accordingly. 
                                        checkers[i].c_time = time + (7);
                                        checkers[i].ptr -> settime(time);
                                }
                                // If the customer is not a robber, run this block 
                                else 
                                {
                                        // Calculates the time the shopper will be done, and sets the times accordingly 
                                        checkers[i].c_time = time + (checkers[i].ptr ->getitems());
                                        checkers[i].ptr -> settime(time);

                                }
                                // Prints the checkout message for the current customer, and sets the proper time. 
                        checkers[i].ptr -> start_check(os,time,i);
                        checkers[i].ptr -> settime(checkers[i].c_time);
                        } 
                }
                // The closing statement, will only run if the simulation is complete 
                if(num_customers == 0 && time > 0)
                {
                        // Iterates through all the checkers, and prints their cash
                        for(int i=0; i < num_checkers; i++)
                        {
                                // Debug statement, prints the same thing as the os statement, but to cout 
                                if(DEBUG == true)
                                {
                                        cout <<"registers[" << i<< "] = $" << checkers[i].cash << endl;
                                }
                                // Prints the cash of all the registers to the output file 
                                os <<"registers[" << i<< "] = $" << checkers[i].cash << endl;
                        }
                        // Debug statement, prints the same thing as the below os statement, but to cout 
                        if(DEBUG == true)
                        {
                                cout << "time = " << time+1 << endl;
                        }
                        // Writes the end time of the simlation to the file 
                        os << "time = " << time+1 << endl;
                        // Deletes all checkers
                delete [] checkers;
                }
        }
}
// Main of the program, takes in 4 arguments, Input file, checkers, checker break time, and output file 
int main(int argc, char *argv[])
{
        // Creates a Pq object to start the arrival_queue
        Pqueue Pq; 
        // If theres arent enough arguments, print this error statement, and end the program. 
        if (argc != 5)
        {
                cerr << "Error: invalid number of command line arguments." << endl;
                return 1;
        }
        // Opens the input file
        ifstream my_ifile(argv[3]);
        // if the input file could not be opened, print this Error message 
        if(!my_ifile)
        {
                cerr << "Error: could not open input file <" << argv[3] << ">." << endl;
                return 1; // error
        }
        // If the Number of checkers is zero or less, or is not a number; Run this block 
        if(atoi(argv[1]) < 0 || !is_int(argv[1]) )
        {
                cerr <<"Error: invalid number of checkers specified." << endl;
                return 1;
        }
        // If the checkers break time is less than zero, or not a digit, print this error message 
        if(atoi(argv[2]) <= -1 || !is_int(argv[2]))
        {
                cerr << "Error: invalid checker break duration specified." << endl;
                return 1; // error
        }
        // Initializes the temp variables to save the values for the customers
        string name_m = "0";
        string shop_m = "0";
        int time_m = 0;
        int items_m = 0;
        // Opens output file 
        ofstream  my_ofile(argv[4]);
        // if the output file could not be opened, print this error message 
        if(!my_ofile)
        {
                cerr << "Error: could not open output file <" << argv[4] << ">." << endl;
                return 1;
        }
        // Reads in from the file, until there is nothing left to read 
        while (my_ifile >> name_m)
        {
                // save all the customer values into their proper holder variables
                my_ifile >> shop_m;
                my_ifile >> time_m;
                my_ifile >> items_m;
                // Debug statement to confirim proper customer building 
                if(DEBUG == true)
                {
                        cout << "Building Customer: " << name_m <<endl;
                }
                // Create new object with values read in from the input file, enqueue that customer
                Cust *ptr = new Cust(name_m, shop_m, time_m, items_m);
                Pq.enqueue(ptr, time_m);
        }
        if(DEBUG == true)
        {
                Pq.print();
        }
        // Runs the main simulation, taking in the arrival_queue, the number of checkers, the break time, and the output file
        run_simulation(Pq, atoi(argv[1]),atoi(argv[2]), my_ofile);
        return 0;
}
