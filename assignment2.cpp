#include<iostream>
using namespace std;
class A{
    int v1;
protected:
int v2;
public:
A():v1(0),v2(0){
    cout<<"default constructor";
}
A(int v1,int v2):v1(v1),v2(v2);
{
    cout<<"A parametrised const called";
}
void displayA(){
    cout<<v1<<v2;
}
~A(){
    cout<<"A destructor";
};
int main(){
    A a1;
    A a2(5,10);
    cout<<a1.v1;
    cout<<a2.v2;
    a1.displayA();
    a2.displayA();
}
}