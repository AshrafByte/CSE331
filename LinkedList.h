//
// Created by Hamad on 2/11/2024.
//
#pragma once
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;

    Node(int d)
    {
        data = d;
        next = nullptr;
    }
};

class LinkedList
{
public:
    Node *head;
    int length;

    LinkedList() : head(nullptr), length(0) {}

    bool empty()
    {
        return (head == nullptr);
    }

    int getLength()
    {
        return length;
    }

    void push_front(int d)
    {
        Node *newNode = new Node(d);
        newNode->next = head;
        head = newNode;
        length++;
    }

    void pop_front()
    {
        head = head->next;
        length--;
    }

    void push_back(int d)
    {
        if (empty())
            head = new Node(d);

        Node *current = head;
        while (current->next)
            current = current->next;
        current->next = new Node(d);

        length++;
    }

    void pop_back()
    {
        if (empty())
            return;

        Node dummy(0);
        dummy.next = head;

        Node *current = &dummy;
        while (current->next->next)
            current = current->next;

        delete current->next;
        current->next = nullptr;
        head = dummy.next;

        length--;
    }

    Node *getMin(Node *start)
    {
        Node *minNode = start;
        while (start)
        {
            if (start->data < minNode->data)
                minNode = start;
            start = start->next;
        }
        return minNode;
    }

    Node *min(Node *n1, Node *n2) { return n1->data < n2->data ? n1 : n2; }

    Node *getMinNode(Node *start)
    {
        if (start->next == nullptr)
            return start;

        return min(start, getMinNode(start->next));
    }

    void selectionSort(Node *start)
    {
        if (start == nullptr)
            return;

        swap(start->data, getMinNode(start)->data);
        selectionSort(start->next);
    }
    void selectionSort() { selectionSort(head); }

    void rearrange(Node *start)
    {
        if (start->next == nullptr)
            return;

        if (start->data > start->next->data)
            swap(start->data, start->next->data);

        rearrange(start->next);
    }
    void bubbleSort()
    {
        int listLength = getLength() - 1;
        while (listLength--)
            rearrange(head);
    }

    void sortWithIndex()
    {
        LinkedList temp;
        while (!empty())
        {
            auto [index , value] = getMinWithIndex();
            deleteNodeWithIndex(index);
            temp.push_back(value);
        }
        head = temp.head;
    }
    pair<int, int> getMinWithIndex()
    {
        int minValue = head->data;
        int minIndex = 0;
        Node *current = head;

        int index = 0;
        while (current != nullptr)
        {
            if (current->data < minValue)
            {
                minValue = current->data;
                minIndex = index;
            }
            index++;
            current = current->next;
        }
        return {minIndex, minValue};
    }
    void deleteNodeWithIndex(int index)
    {
        if (index == 0)
        {
            this->pop_front();
            return;
        }

        Node *beforeTarget = head;
        for (int i = 0; i < index - 1; i++)
            beforeTarget = beforeTarget->next;

        Node *target = beforeTarget->next;
        beforeTarget->next = target->next;
    }

    void print()
    {
        for (auto current = head ; current != nullptr ; current = current->next)
            cout << current->data << " ";

        cout << "\n";
    }
    Node * find(int data)
    {
        for (Node * current = head ; current != nullptr ; current = current->next)
            if (current->data == data)
                return current;
        return nullptr;
    }
};
