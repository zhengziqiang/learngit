#include <string>  
#include<iostream>  
using namespace std;  
class Product  
{  
public:  
    virtual void use(){};  
};  
class ConcreteProductA :public Product  
{  
public:  
    void use()  
    {  
        cout << "使用A" << endl;  
    };  
};  
class ConcreteProductB:public Product  
{  
public:  
    void use()  
    {  
        cout << "使用B" << endl;  
    };  
};  
class Factory  
{  
public:  
    Product* Factory::createProduct(string proname){  
        if ("A" == proname)  
        {  
            return new ConcreteProductA();  
        }  
        else if ("B" == proname)  
        {  
            return new ConcreteProductB();  
        }  
        return  NULL;  
    }  
};  
int main()  
{  
    Product *P = NULL;  
    Product *Q = NULL;  
    Factory f;  
    P=f.createProduct("A");  
    Q = f.createProduct("B");  
    P->use();  
    Q->use();  
    return 0;  
}  
