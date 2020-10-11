#include<bits/stdc++.h>
using namespace std;
class SBO{
    int x;
public:

    mutable mutex m;
    SBO(){};
    SBO(int x_):x(x_){}
    SBO(SBO const&) = delete;
    SBO& operator =(SBO const&) = delete;

    void swap1(SBO &ac1, SBO &ac2){
        lock_guard<mutex>lg1(ac1.m);
        cout<<"Locked for "<<ac1.x<<" acquired by thread: "<<this_thread::get_id()<<endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout<<"Thread :"<<this_thread::get_id()<<" is waiting to acquire lock on "<<ac2.x<<endl;
        lock_guard<mutex>lg2(ac2.m);
        int t = ac1.x;
        ac1.x = ac2.x;
        ac2.x = t;
    }
};

int main(){
    SBO obj;
    SBO ac1(200);
    SBO ac2(300);
    thread t1(&SBO::swap1,&obj, ref(ac1),ref(ac2));
    thread t2(&SBO::swap1,&obj, ref(ac2),ref(ac1));
    t1.join();
    t2.join();
}
