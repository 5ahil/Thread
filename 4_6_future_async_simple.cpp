#include<bits/stdc++.h>
using namespace std;
void fun1(){
    cout<<"fun1\n";
}

int main(){
    future<void> future_result = async(fun1);
    cout<<"doing other task\n";
    future_result.get();
    cout<<"done\n";
}