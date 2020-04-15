#include <iostream>

using namespace std;

class List
{
public:
	List(string b);
	~List();
    string a;
    List* next;
    List* prev;
};

List::List(string b)
{
    a = b;
    next = NULL;
    prev = NULL;
}

List::~List()
{
}

List* head = NULL;
List* tail = NULL;

void add_start(string b)
{
    List* temp = new List(b);
    temp->next = head;
    if (head != NULL)
        head->prev = temp;
    head = temp;
}

void add_end(string b)
{
    List* temp = new List(b);
    if (head == NULL)
    {
        temp->next = head;
        head = temp;
    }
    else
    {
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        tail->next = temp;
        temp->prev = tail;
    }
}

void remove_num(int num)
{
    int k = 1;
    if (head != NULL)
    {
        tail = head;
        while (tail->next != NULL || k != num)
        {
            tail = tail->next;
            k++;
        }
        if (k == num)
        {
            List* temp_1 = tail->prev;
            List* temp_2 = tail->next;
            if (temp_1 != NULL)
                temp_1->next = temp_2;
            if (temp_2 != NULL)
                temp_2->prev = temp_1;
            delete(tail);
        }
    }
}

void remove_all()
{
    tail = head;
    while (tail != NULL)
    {
        head = head->next;
        delete(tail);
        tail = head;
    }
}

void show()
{
    tail = head;
    while (tail != NULL)
    {
        cout << tail->a;
        tail = tail->next;
    }
}

int main()
{
    while (true)
    {
        int action;
        cin >> action;
        if (action == 1)
        {
            string k;
            cin >> k;
            add_start(k);
        }
        else if (action == 2)
        {
            string k;
            cin >> k;
            add_end(k);
        }
        else if (action == 3)
        {
            int num;
            cin >> num;
            remove_num(num);
        }
        else if (action == 4)
        {
            remove_all();
        }
        else if (action == 5)
        {
            show();
        }
    }
    return 0;
}