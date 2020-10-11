#include<bits/stdc++.h>
using namespace std;
class SBO{
    int x;
public:

    mutex m;
    SBO(){};
    SBO(int x_):x(x_){}
    SBO(SBO const&) = delete;
    SBO& operator =(SBO const&) = delete;

    void swap1(SBO &ac1, SBO &ac2){
        unique_lock<mutex>lg1(ac1.m,std::defer_lock);
        cout<<"Locke acquired by thread: "<<this_thread::get_id()<<endl;
        unique_lock<mutex>lg2(ac2.m,std::defer_lock);
        lock(lg1, lg2);
        int t = ac1.x;
        ac1.x = ac2.x;
        ac2.x = t;
        cout<<ac1.x<<" and "<<ac2.x<<endl;
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
