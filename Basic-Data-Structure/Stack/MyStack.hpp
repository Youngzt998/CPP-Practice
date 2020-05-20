# ifndef MYSTACK_HPP
# define MYSTACK_HPP

template<class T>
class MyStack
{
private:
    /* data */
    struct node
    {
        // cannot be "T data;", since T might not have a default constructor
        T* data;
        node *next;
        ~node() {delete data;}
    };

    node* top;
    int size;    
/*
   top
    |
   \ /
    [ data_n | next] -> [data_2 | next] -> ... -> [data_1 | next ]
       |                  |                         | 
      \ /                \ /                       \ /
       [...data...]       [...data...]              [...data...]     

    push(...): <-
    pop():     ->          
*/

public:
    MyStack(/* args */)
    {
        top = nullptr;
        size = 0;
    }
    ~MyStack()
    {
        while (top!=nullptr)
        {
            /* code */
            node* tmp = top;
            top = top -> next;
            delete tmp;
        }   
    }

    void push(T x)
    {
        node *tmp = new node;
        tmp -> data = new T(x);
        tmp -> next = top;
        top = tmp;
        size ++;
    }

    T* pop()
    {
        T* tmp = top -> data;
        top = top -> next;
        size --;
        return tmp;
    }

    int getSize()
    {
        return size;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }
};

// MyStack::MyStack(/* args */)
// {
// }

// MyStack::~MyStack()
// {
// }


# endif