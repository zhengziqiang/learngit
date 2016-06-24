     #include <iostream>  
    #include <string>  
    #define MAX 100  
    using namespace std;  
    class Book             //class是类型构造子  
    {  
    public:  
        int id;  
        string name;  
        string publisher;  
        Book() : id(0), number(0),name(""),publisher(""){};  
        void addBook(int a_id,string a_name)  
        {  
            id=a_id;      
            name=a_name;  
        }  
        void deleteBook(Book &boo)  
        {  
            boo.id=0;  
            boo.number=0;  
        }  
    private:  
        int number;   
    }  
    int main()  
    {  
        int i = 101;  
        int &newId = i;     //int类型的引用  
        Book books[MAX];  
        Book *bookA = new Book();  //产生一个复合对象引用  
          
        string pub[] = {"Buaa","TsingHua","PeiKing"};   //值构造子  
        string *otherPub = new string("ChinaMachine");  //new是引用构造子，产生一个符合对象引用  
        for(size_t i = 0 ; i < sizeof(books) ; i++)    //sizeof是类型选择子  
        books[i].addBook(i,"aa");  
        newId = bookA->id;        //->引用选择子   
        bookA->name = "bb";         
        books[0].publisher = pub[0];     //[]是值选择子  
        books[1].publisher = *otherPub;   //右操作数 复合递引用  
        string bookAName = bookA->name;    //->是选择+递引用  
        string DefaultBookName = books[0].name;   //.是值选择子  
        delete otherPub;  
    }  
