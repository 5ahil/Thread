//A thread guard program - 1
#include<bits/stdc++.h>
#define MXLENPERTHREAD 15000
using namespace std;
template<typename I,typename T>
void accumulate_block(I start, I end, T &result) {
    result = accumulate(start,end,result);
}
template<typename I,typename T>
T parallel_accumulate(I start, I end, T init_val){
    int size = distance(start,end);
    int mx_thread = (size+MXLENPERTHREAD-1)/MXLENPERTHREAD;
    int num_thread = min(mx_thread,(int)thread::hardware_concurrency());
    int block_size = size/num_thread;
    vector<T>result(num_thread);
    vector<thread>threads(num_thread);
    I b_start = start;
    for(int i=0;i<num_thread-1;i++){
        I b_end = b_start;
        advance(b_end,block_size);
        threads[i]=thread(accumulate_block<I,T>,b_start,b_end,ref(result[i]));
        b_start=b_end;
    }
    threads[num_thread-1]=thread(accumulate_block<I,T>,b_start,end,ref(result[num_thread-1]));
    for_each(threads.begin(),threads.end(),
             std::mem_fn(&std::thread::join));
    return accumulate(result.begin(),result.end(),init_val);
}


int main(){
    vector<int>arr;
    for(int i=0;i<100000;i++){
        arr.push_back(rand()%10+1);
    }
    {
        auto s=chrono::high_resolution_clock::now();
        long long sum = parallel_accumulate(arr.begin(),arr.end(),0LL);
        cout<<"Ans:"<<sum<<endl;
        auto e=chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(e-s);
        cout<<"Took "<<duration.count()<<" seconds\n";
    }
    {
        auto s=chrono::high_resolution_clock::now();
        long long sum = accumulate(arr.begin(),arr.end(),0);
        cout<<"Ans:"<<sum<<endl;
        auto e=chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(e-s);
        cout<<"Took "<<duration.count()<<" seconds\n";
    }


}