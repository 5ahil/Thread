//Program not working
#include<bits/stdc++.h>
#define t_id this_thread::get_id
#define t_slp(x) this_thread::sleep_for(chrono::milliseconds(x))
using namespace std;
void func(thread&t){
    cout<<"Thread: "<<t_id()<<endl;
    t.join();
}
int main(){
    thread t1,t2;
    t1 = thread(func,ref(t2));
    t2 = thread(func,ref(t1));
}