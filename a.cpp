
#include <iostream>

struct S{
    S(int value):value(value){
        std::cout<<"Constructor\n";
        p = new int();
        throw 23;
    }

    ~S(){
        delete p;
        std::cout<<"Destructor\n";
    }
private:
    int value; 
    int* p;
};


int gg__(){
    int temp =90;
    //throw 43;
    return temp;
}

int main(){
    try{
        
        S(static_cast<int>(gg__()));
    }

    catch(...){
        std::cout<<"we in catch\n";
    }

    return 0;
}