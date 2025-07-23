#include <iostream>
using namespace std;
class Singleton {
private:
    int a,b;
    static Singleton* instance;  // Static pointer to the single instance

    // Private constructor to prevent direct instantiation
    Singleton() {
        cout << "Singleton created\n";
    }

public:
    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Static method to access the singleton instance
    static Singleton* getInstance() {
        if (!instance) {
            instance = new Singleton();
        }
        return instance;
    }

    void doSomething() {
        cout<<a<<" "<<b<<endl;
    }
    void assign(int a,int b){
        this->a=a;
        this->b=b;
    }
};

// Initialize static member
Singleton* Singleton::instance = nullptr;

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();
    
    s1->assign(1,2);
    s2->assign(3,4);
    
    s1->doSomething();
    s2->doSomething();

    cout<<"Same instance? "<<(s1 == s2)<<"\n";

    return 0;
}
