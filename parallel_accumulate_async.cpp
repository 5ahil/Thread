#include<bits/stdc++.h>
using namespace std;
int minnum =1000;
template<typename I>
long long parallel_accumulate(I start, I end){
    int len = distance(start, end);
    if(len<minnum){
        cout<<"returning result: "<<this_thread::get_id()<<endl;
        return accumulate(start, end, 0LL);
    }
    cout<<"dividing problem: "<<this_thread::get_id()<<endl;
    I mid = start;
    advance(mid, (len+1)/2);
    future <long long> f1= async(launch::deferred|launch::async,
                                 parallel_accumulate<I>,mid, end);
    long long sum = parallel_accumulate(start, mid);
    cout<<"summing result: "<<this_thread::get_id()<<endl;
    return sum + f1.get();

}

int main(){
    int n= 24000;
    vector<long long>a(24000);
    for(int i=0;i<n;i++){
        a[i] = rand()%7+2;
    }
    cout<<"Sum is "<<(long long)parallel_accumulate(a.begin(),a.end())<<endl;
}