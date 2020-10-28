#include<iostream>
#include"pqueue.h"
#include"cust.h"
using namespace std;
// Simple constructor 
Pqueue :: Pqueue()
{
        m_head = NULL;
}
// Simple destructor 
Pqueue :: ~Pqueue()
{
        while (m_head)
        {
                Node *tmp = m_head;
                m_head = m_head -> m_next;
                delete tmp;
        }

}
// A function that will return the length in int type of the current list 
int Pqueue :: length()
{
        int x = 0;
        Node *cur = m_head;
        while(cur)
        {
                x++;
                cur = cur -> m_next;
        }
        return x;
}
// Function that will return 1 if the list is empty, and 0 otherwise. 
bool Pqueue :: empty()
{
        if( m_head == NULL )
        {
                return 1;
        }
        else
        {
                return 0;
        }
}
// Will look at the current list and return the first priority of the list
int Pqueue :: first_priority()
{
        Node *cur = m_head;
        int x = 0;
        if(empty())
        {
                return -1;
        }
        else
        {
                x = cur -> m_prior;
                return x;
        }

}
// Enqueue function which will put the element on the list, and sort it according to priority 
void Pqueue :: enqueue(Cust *cust, int prior)
{
        // If the list is empty, run this code block 
        if(!m_head || prior < m_head -> m_prior)
        {
                m_head = new Node( cust, prior, m_head);
        }
        else
        {
                Node *ptr = m_head;
                Node *temp = m_head;
                // moves to either the end of the list, or the place in the list where the object would go
                while(ptr->m_next != NULL && prior >= ptr -> m_prior)
                {
                        temp = ptr;
                        ptr = ptr-> m_next;
                }
                // Block of code which will replace two list objects that are out of order    
                if(prior < ptr->m_prior)
                {
                        Node* cur = new Node(cust,prior,NULL);
                        temp ->m_next = cur;
                        cur -> m_next = ptr;
                        return;
                }
                // Conditional statement to add an object to the list at the end 
                if(ptr -> m_next == NULL)
                {
                        ptr -> m_next = new Node(cust, prior, ptr->m_next);
                        return; 
                }

        }

}
// Will iterate through the list, and call the print function on every item in said list 
void Pqueue :: print()
{
        Node *cur = m_head;
        while(cur)
        {
                cur -> m_cust -> print(cout);
                cur = cur-> m_next;
        }
}
// removes item from the front of the list, and returns it 
Cust* Pqueue :: dequeue()
{
        Cust* pop;
        Node* old;
        if(empty())
        {
                return NULL;
        }
        else
        {
                pop = m_head -> m_cust;
                old = m_head;
                m_head = m_head -> m_next;
                delete old;
                return pop;
        }
}


