//
// Created by Hamad on 2/11/2024.
//

#ifndef STACK_H
#define STACK_H
#include <assert.h>


using namespace std;
class Stack
{
private:
    int data[1000];
    int size;

public:
    Stack() : size(0) {}
    void push(int d)
    {
        data[size] = d;
        size++;
    }

    void pop()
    {
        size--;
    }

    int top() {return data[size-1];}
    bool empty() {return size == 0;}

    bool isEqual(Stack other)
    {
        Stack temp;
        bool equal = true;
        while (!this->empty() && !other.empty() )
        {
            if (this -> top() != other.top())
            {
                equal = false;
                break;
            }
            temp.push(this->top());
            this->pop();
            other.pop();
        }
        fillFrom(temp);
        return equal;
    }

    void fillFrom(Stack temp)
    {
        while (!temp.empty())
        {
            push(temp.top());
            temp.pop();
        }
    }

    void print ()
    {
        Stack temp;
        while (!empty())
        {
            cout << top() << " ";
            temp.push(top());
            pop();
        }
        fillFrom(temp);
        cout << "\n";
    }

};



#endif //STACK_H
