#include<bits/stdc++.h>
using namespace std;
bool reached = false;
int dist_covered =0;
int dist_to_destination = 10;
condition_variable cv;
mutex m;
void keep_driving(){
   while(true){
      this_thread::sleep_for(chrono::milliseconds(1000));
      dist_covered++;
      if(dist_covered == dist_to_destination){
         cv.notify_one();
      }
   }
}
void ask_driver_to_wake_up(){
   unique_lock<mutex>ul(m);
   cv.wait(ul,[]{return dist_covered == dist_to_destination;});
   cout<<"Reached at "<<dist_covered<<endl;
}
int main(){
   thread driver(keep_driving);
   thread passenger(ask_driver_to_wake_up);
   driver.join();
   passenger.join();
}
