#include <bits/stdc++.h>
using namespace std;
class func{
   int data;
public:
   func(int data_){
      data = data_;
   }
   void operator()(){
      cout<<"function object\n";
   }
};
class thread_guard{
   thread &t1;
public:
   explicit thread_guard(thread&t):t1(t){}
   ~thread_guard(){
      if(t1.joinable()){
         t1.join();
      }
   }
   thread_guard(thread_guard const&)=delete;
   thread_guard& operator=(thread_guard const&) =delete;
};
int main() {
   int some_state = 0;
   func my_func(some_state);
   thread t(my_func);
   thread_guard tg(t);
   cout<<"Some random statement\n";
}
