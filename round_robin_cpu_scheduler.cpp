#include <iostream>
#include<stdio.h>

using namespace std;

void readyfun(int *temp_arrival, int &timer, int &rear, int *ready_q, int &size, bool &flag1, int &front, int &n)
{
    for(int j = 0; j < size; j++){
        timer += 1;
        for(int i = 0; i < n; i++) 
        {
            if(temp_arrival[i] == timer)
            {
               rear++;
               ready_q[rear] = i;
            }
        }
    }
    if(flag1 == true){
        rear++;
        ready_q[rear] = ready_q[front];
    }
}

void processing(int *temp_arrival, int *temp_brust, int &timer, int &rear, int *ready_q, int &front, int &n, int &qt, 
 int *compeletion_time)      //Processing the process in ready queue    
{
bool flag1,check = true;
int temp, z;
while(check)
{   
    if(temp_brust[ready_q[front]] > qt)
    {
        flag1 = true;
        temp_brust[ready_q[front]] = temp_brust[ready_q[front]] - qt;
        cout<<"P"<<(ready_q[front]+1)<<" ";
        temp_arrival[ready_q[front]] = 9999;
        readyfun(temp_arrival, timer, rear, ready_q, qt, flag1, front, n);
      for(int i = 0; i < n; i++)
        {
        if(temp_arrival[i] != 9999 || rear != front){
          front++;    //rear++;
          if(ready_q[front] == 0){
            int min=99999;
            for(int j = 0; j < n; j++)                            //Searching for min arrival time
              if(min > temp_arrival[j])
              {  
                min = temp_arrival[j];
                z = j;
              } 
            ready_q[front] = z;
        }
          break;
        }
        else if(i == n-1 && temp_arrival[i] == 9999)
        {
            rear = -1;
            front = 0;
            cout<<"All Process Completed"<<endl;
        }
        }
    }
    else
    {
        flag1 = false;
        temp = temp_brust[ready_q[front]];
        temp_brust[ready_q[front]] = temp_brust[ready_q[front]] - temp;
        cout<<"P"<<(ready_q[front]+1)<<" ";
        compeletion_time[ready_q[front]] = timer + temp;
        temp_arrival[ready_q[front]] = 9999;
        readyfun(temp_arrival, timer, rear, ready_q, temp, flag1, front, n);
        for(int i = 0; i < n; i++)
        {
        if(temp_arrival[i] != 9999 || rear != front){
          front++;
          if(ready_q[front] == 0){
            int min=99999;
            for(int j = 0; j < n; j++)                            //Searching for min arrival time
              if(min > temp_arrival[j])
              {  
                min = temp_arrival[j];
                z = j;
              } 
            ready_q[front] = z;
        }
          break;
        }
        else if(i == n-1 && temp_arrival[i] == 9999)
        {
            rear = -1;
            front = 0;
            cout<<"All Process Completed"<<endl<<endl;
        }
        }
    }
    if(rear != -1)
    check = true;
    else 
    check = false;
}
}

void print_function(int *arrival, int *brust, int *compeletion_time, int &n)
{
  int tat[n], wt[n], sum_tat = 0, sum_wt = 0;
  cout<<"Turnaround Time for Process:"<<endl;
  for(int i =0 ;i < n; i++)
    {
      cout<<"P"<<i+1<<" : "<<compeletion_time[i] - arrival[i]<<endl;
      tat[i] = compeletion_time[i] - arrival[i];
      sum_tat = sum_tat + tat[i];
    }
  cout<<endl<<"Wating Time for Process:"<<endl;
  for(int i =0 ;i < n; i++)
    {
      cout<<"P"<<i+1<<" : "<<tat[i] - brust[i]<<endl;
      wt[i] = compeletion_time[i] - arrival[i];
      sum_wt = sum_wt + wt[i];
    }
  cout<<endl<<"Average TAT : "<<sum_tat/n<<endl;
  cout<<"Average WT : "<<sum_wt/n<<endl;
}
//driver code
int main()
{
    int n,qt, timer = 0, maxProccessIndex = 0,front = 0, rear = -1, temp_timer=0, z,j,i;
    cout << "\nEnter the time quanta : ";
    cin>>qt;
    cout << "\nEnter the number of processes : ";
    cin>>n;
    int arrival[n], temp_arrival[n], brust[n], ready_q[100], temp_brust[n], compeletion_time[n];
    cout << "\nEnter the arrival time of the processes : "; //Taking entry for Arrival time of all processes
    for(int i = 0; i < n; i++){
        cin>>arrival[i];
        temp_arrival[i] = arrival[i];
    }
    cout << "\nEnter the burst time of the processes : ";  //Taking entry for Brust time of all processes
    for(int i = 0; i < n; i++){
        cin>>brust[i];
        temp_brust[i] = brust[i];
    }
    int min=99999;
    for(j = 0; j < n; j++)                            //Searching for min arrival time
        if(min > temp_arrival[j])
        {  
          min = temp_arrival[j];
          z = j;
        }  
    //cout<<z<<endl;
    //cout<<temp_arrival[z]<<" "<<min<<endl;
    //for(int s=0;s<n;s++)
    //cout<<temp_arrival[s]<<endl;
    for(i = 0; i < 1000; i++)
    {
    if(timer == min)
    {
      rear++;
      ready_q[rear] = z;                                //Adding process in ready queue  
      cout<<"Gantt Chart->  ";
      processing(temp_arrival, temp_brust, timer, rear, ready_q, front, n, qt, compeletion_time);       
      break;
    }    
    timer++;       
    }  
   // for(int s=0;s<n;s++)
   // cout<<ready_q[s]<<endl;
   print_function(arrival, brust, compeletion_time, n);
}

