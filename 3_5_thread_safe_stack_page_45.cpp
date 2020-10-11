#include<bits/stdc++.h>
using namespace std;
struct empty_stack: std::exception{
    const char*what() const throw();
};

template<typename T>
class threadsafe_stack{
    stack<T> data;
    mutable mutex m;
public:
    threadsafe_stack(){}
    threadsafe_stack(threadsafe_stack &other){
        lock_guard<mutex> lg(m);
        data = other.data;
    }
    threadsafe_stack &operator= (const threadsafe_stack&) = delete;
    void push(T val){
        lock_guard<mutex> lg(m);
        data.push(val);
    }
    shared_ptr<T> pop(){
        lock_guard<mutex> lg(m);
        if(data.empty()) throw empty_stack();
        shared_prt<T> const res(make_shared<T>(data.top()));
        data.pop();
        return res;
    }
    void pop(T &val){
        lock_guard<mutex>lg(m);
        if(data.empty()) throw empty_stack();
        val = data.top();
        data.pop();
    }
    bool empty(){
        lock_guard<mutex>lg(m);
        return data.empty();
    }
};

int main(){
    
}