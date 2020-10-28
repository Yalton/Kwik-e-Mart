#ifndef PQUEUE_H
#define PQUEUE_H
#include "cust.h"
using namespace std;
class Pqueue
{
        private:
                class Node
                {
                        public:
                                Node(Cust *ptr, int x, Node *next)
                                {
                                        m_cust = ptr;
                                        m_prior = x;
                                        m_next = next;
                                }
                                Cust* m_cust;
                                int m_prior;
                                Node* m_next;
                };
                Node* m_head;
        public:
                Pqueue();
                ~Pqueue();
                void print();
                void enqueue();
                void enqueue(Cust *m_cust, int prior);
                Cust* dequeue();
                int first_priority();
                bool empty();
                int length();

};
#endif

