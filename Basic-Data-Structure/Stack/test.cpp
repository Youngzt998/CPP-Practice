# include <iostream>
# include "MyStack.hpp"
using namespace std;

int main()
{

    MyStack<int> stack;
    stack.push(1);
    stack.push(2);
    cout << stack.getSize() <<'\n';

    int* i = stack.pop();
    int* j = stack.pop();
    cout << (stack.isEmpty()? "yes":"no");

    return 0;
}