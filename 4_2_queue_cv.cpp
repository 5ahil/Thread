#include<bits/stdc++.h>
#define t_id this_thread::get_id
#define t_slp(x) this_thread::sleep_for(chrono::milliseconds(x))
using namespace std;
template<typename T>
class threadsafe_queue{
    queue<T>data_queue;
    mutex m;
    condition_variable cv;
    public:
    threadsafe_queue(){}
    threadsafe_queue(threadsafe_queue& const other){
        lock_guard<mutex> lg(other.m);
        data_queue = other.data_queue;
    }
    void push(T val){
        lock_guard<mutex> lg(m);
        data_queue.push(val);
        cv.notify();
    }
    bool try_pop(T &val){
        lock_guard<mutex> lg(m);
        if(data_queue.empty())retrun false;
        val = data_queue.front();
        data_queue.pop();
        return true;
    }
    shared_ptr<T> try_pop(){
        lock_guard<mutex> lg(m);
        if(data_queue.empty())retrun NULL;
        shared_ptr<T> result(make_shared<T>(move(data.front)));
        data_queue.pop();
        return result;
    }
    bool wait_and_pop(T &val){
        unique_lock<mutex>ul(m);
        cv.wait(ul, []{return !data_queue.empty();});
        val = data_queue.front();
        data_queue.pop();
        return true;
    }
    shared_ptr<T> wait_and_pop(){
        unique_lock<mutex>ul(m);
        cv.wait(ul, []{return !data_queue.empty();});
        shared_ptr<T> result(make_shared<T>(move(data.front)));
        data_queue.pop();
        return result;
    }
};

int main(){

}