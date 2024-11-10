#include <iostream>
#include "LinkedList.h"
#include "Stack.h"
#include "algorithms.h"
#include <stack>
using namespace std;

void testStack();
void testLinkedList();

int main()
{
   testLinkedList();
}


void testLinkedList()
{
   cout << "Testcase 1 :- \n";
   LinkedList list1,list2 ;
   int values1[] = {2,3,1};
   int values2[] = {2,3,1};
   for (auto data: values1)
      list1.push_front(data);

   for (auto data: values2)
      list2.push_front(data);

   list1.selectionSort();
   list1.print();

   list2.bubbleSort();
   list2.print();
   
}

void testStack()
{
   Stack s1;
   Stack s2;

   cout << "Testcase 1 :- \n";
   s1.push(1);
   s1.push(2);
   s1.push(3);
   s2.push(1);
   s2.push(2);
   s2.push(3);
   cout << s1.isEqual(s2) << "\n";
   s1.print();
   s2.print();

   cout << "==================================\n" ;

   cout << "Testcase 2 :- \n";
   s2.push(4);
   cout << s1.isEqual(s2) << "\n";
   s1.print();
   s2.print();

}