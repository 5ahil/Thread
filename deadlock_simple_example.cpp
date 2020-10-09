#include<bits/stdc++.h>
using namespace std;
mutex m1,m2;
void m1m2(){
   lock_guard<mutex>l1(m1);
   cout<<this_thread::get_id()<<" has acquired lock on m1\n";
   this_thread::sleep_for(chrono::milliseconds(1000));

   cout<<this_thread::get_id()<<" waiting to acquire lock on m2\n";
   lock_guard<mutex>l2(m2);
   cout<<this_thread::get_id()<<" finished execution\n";
}
void m2m1(){
   lock_guard<mutex>l1(m2);
   cout<<this_thread::get_id()<<" has acquired lock on m2\n";
   this_thread::sleep_for(chrono::milliseconds(1000));

   cout<<this_thread::get_id()<<" waiting to acquire lock on m1\n";
   lock_guard<mutex>l2(m1);
   cout<<this_thread::get_id()<<" finished execution\n";
}
int main(){
   thread t1(m1m2);this_thread::sleep_for(chrono::milliseconds(100));
   thread t2(m2m1);
   t1.join();
   t2.join();
}
