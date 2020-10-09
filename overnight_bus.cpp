#include<bits/stdc++.h>
using namespace std;
bool reached = false;
int dist_covered =0;
int dist_to_destination = 10;
void keep_driving(){
   while(true){
      this_thread::sleep_for(chrono::milliseconds(1000));
      dist_covered++;
   }
}
void keep_awake_all_night(){
   while(dist_covered<dist_to_destination){
      cout<<"Am I there?\n";
      this_thread::sleep_for(chrono::milliseconds(1000));
   }
   cout<<"Yes! you are at "<<dist_covered<<"\n";
}
void set_alarm(){
   while(dist_covered<dist_to_destination){
      cout<<"Setting alarm for 10 seconds\n";
      this_thread::sleep_for(chrono::milliseconds(10000));
   }
   cout<<"Hey! wake-up. You are at "<<dist_covered<<endl;
}
int main(){
   thread t1(keep_awake_all_night);
   thread t2(set_alarm);
   keep_driving();
   t1.join();
   t2.join();
}
