#include<bits/stdc++.h>
using namespace std;
template<typename T>
class trivial_thread_safe_stack{
   stack<T> stk;
   mutex m;
public:
   void push (T data){
      lock_guard<std::mutex> lg(m);
      stk.push(data);
   }
   void pop(){
      lock_guard<mutex> lg(m);
      stk.pop();
   }
   T& top(){
      lock_guard<mutex>lg(m);
      return stk.top();
   }
   // bool empty(){
   //    lock_guard<mutex>lg(m);
   //    return stk.empty();
   // }

};
int main(){

}
