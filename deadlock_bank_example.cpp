#include<bits/stdc++.h>
using namespace std;
class Account{
public:
  double balance;
  string name;
  mutex m;
   Account(){};
   Account(double _amount, string _name):balance(_amount),name(_name){}
   Account(Account const&) = delete;
   Account& operator =(Account const&) = delete;
   void withdraw(double amount){
      lock_guard<mutex>lg(m);
      balance-=amount;
   }
   void deposit(double amount){
      lock_guard<mutex>lg(m);
      balance += amount;
   }
   void transfer(Account&ac1, Account&ac2, double amount){
      lock_guard<mutex>lg1(ac1.m);
      cout<<"Locked for "<<ac1.name<<" acquired by thread: "<<this_thread::get_id()<<endl;
      this_thread::sleep_for(chrono::milliseconds(2000));
      cout<<"Thread :"<<this_thread::get_id()<<" is waiting to acquire lock on "<<ac2.name<<endl;
      lock_guard<mutex>lg2(ac2.m);
      ac1.balance -= amount;
      ac2.balance += amount;
      cout<<"Tranfer of amount "<<amount << " done from "<<ac1.name<<" to "<<ac2.name<<endl;
   }
};

int main(){
   Account ac;
   Account ac1(200, "Sahil");
   Account ac2(300, "Asim");
   thread t1(&Account::transfer,&ac, ref(ac1),ref(ac2), 50);
   thread t2(&Account::transfer,&ac, ref(ac2),ref(ac1), 100);
   t1.join();
   t2.join();
}
