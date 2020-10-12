#include<bits/stdc++.h>
#define t_id this_thread::get_id
#define t_slp(x) this_thread::sleep_for(chrono::milliseconds(x))
using namespace std;

mutex m;

template<typename T>
class Item{
    queue<T> itemList;
    mutex m;
    condition_variable cv;
    const unsigned int size = 10;
public:
    Item(){}
    void addItem(T x){
        while(true){
            unique_lock<mutex>ul(m);
            cv.wait(ul,[this]{return itemList.size()<size;});
            itemList.push(x);
            ul.unlock();
            cv.notify_one();
            return ;
        }
    }
    T removeItem(){
        while(true){
            unique_lock<mutex>ul(m);
            cv.wait(ul,[this]{return itemList.size()>0;});
            T temp = itemList.front();
            itemList.pop();
            ul.unlock();
            cv.notify_one();
            return temp;
        }
    }
};

template<typename T>
class Producer{
    Item<T> &item;
public:
    Producer(Item<T>&item_):item(item_){}
    void run(){
        while(true){
            T num = (T)(rand()%10+1);
            cout<<"Producing item "<<num<<'\n';
            item.addItem(num);
            t_slp(300);
        }
    }
};

template<typename T>
class Consumer{
    Item<T> &item;
public:
    Consumer(Item<T>&item_):item(item_){}
    void run(){
        while(true){
            T num = item.removeItem();
            cout<<"Consuming item "<<num<<'\n';
            t_slp(500);
        }
    }
};

int main(){
    Item<int> item;
    Producer<int>p(item);
    Consumer<int>c(item);
    thread producer_thread(&Producer<int>::run,&p);
    thread consumer_thread(&Consumer<int>::run,&c);
    producer_thread.join();
    consumer_thread.join();
}
