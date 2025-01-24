/***********************************************
************CSCI-311-PROJECT-2-V-2071***********
************************************************
*******CODE-CHECKER-STARTING-ALIGNMENT**********
************************************************
*************CONTROL-NUMBER-XA-72***************
************************************************
**REPORT-GENERATION-MODE-AUTO_SYNC-EXCEPTION-2**
************************************************
*****************DATETIME-SYS*******************
************************************************/

//G1_EXCEPTION: Only produce your code as directed in Section A, B, C, and D1_EXCEPTION.
//G2_EXCEPTION: Do not write anything at the other places in this file.
//D1_EXCEPTION: Put you names here (on this line): Jake Baartman

/***********************************************
*************SECTION-A-HEADERS******************
************************************************/
//SECTION_A_START: put your header files here using the include directive.
//G3_EXCEPTION: You can also declare using standard namespace if you like, but do not use any global variable or method.

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stdexcept>
#include <algorithm>

using namespace std;

//SECTION_A_END: Section A ends here. 
/***********************************************
*************SECTION-A-HEADERS-END**************
************************************************/

/***********************************************
*************SECTION-B-CLASSES******************
************************************************/
//SECTION_B_START: put all your classes definitions here.

class Plane {
  public:
    int id;        //Unique id for the plane
    int time;      //Time at which plane arrives or departs
    string status; //Status of the plane: "arriving" / "departing"
    int priority;  //Priority of the plane (lower # = higher priority)

    //Initialize plane object
    Plane(int id, int time, string status, int priority)
      : id(id), time(time), status(status), priority(priority) {}


    //Overloaded operator< for comparing planes based on id and priority
    bool operator<(const Plane& other) const {
      if(priority != other.priority) {
        return priority < other.priority;
      }

      return id < other.id;
    }


    //Print function to print the plane's details
    void print() const{
      cout << "\t\t" << time << " " << id << " " << status << " " << priority;
    }
};


//Class for priority queue, implemented as a min-heap
class PlanePQ {
  private:
    vector<Plane> ary;  //Vector to store planes


    //Downward heapify helper function
    void dwheapify(int i) {
      int left = 2 * i + 1;
      int right = 2 * i + 2;
      int min = i;


      //Compare left child to find the smallest
      if (left < ary.size() && (ary[min].priority > ary[left].priority ||
            (ary[min].priority == ary[left].priority && ary[min].id > ary[left].id))) {
        min = left;
      }

      //Compare right child to find the smallest
      if (right < ary.size() && (ary[min].priority > ary[right].priority || 
            (ary[min].priority == ary[right].priority && ary[min].id > ary[right].id))) {
        min = right;
      }


      //Swap and recurse if heap doesn't work
      if (min != i) {
        swap(ary[min], ary[i]);
        dwheapify(min);
      }
    }
      
   //Upward heapify helper function
   void uwheapify(int i) {
     int parent = (i - 1) / 2;


     //Swap with parent if heap doesn't work
     if (parent >= 0 && (ary[i].priority < ary[parent].priority || 
           (ary[i].priority == ary[parent].priority && ary[i].id < ary[parent].id))) {
       swap(ary[i], ary[parent]);
       uwheapify(parent);
      }
   }

  public:
   //Function to check if the queue is empty
   bool empty() const {
     return ary.empty();
   }


   //Function to get the size of the queue
   int size() const { 
     return ary.size();
   }


   //Function to add a new plane to the queue
   void push(const Plane& val) {
     ary.push_back(val);
     uwheapify(ary.size() - 1);  //maintain min-heap
   }


   //Function to remove and return the highest-priority plane
   Plane pop() {
     if(ary.empty()) 
       throw runtime_error("queue is empty");

     Plane top = ary[0];    //Store the top plane
     ary[0] = ary.back();   //Replace the root with the last element
     ary.pop_back();        //Remove the last element

     if(!ary.empty())
       dwheapify(0); //Maintain min-heap property

     return top;
   }


   //Function to view the highest-priority plane without removing it
   Plane peek() const {
     if(ary.empty())
       throw runtime_error("queue is empty");

     return ary[0];
   }
};


//SECTION_B_END: Section B ends here. 
/***********************************************
*************SECTION-B-CLASSES-END**************
************************************************/


/***********************************************
*************SECTION-C-MAIN-FUNCTION************
************************************************/
//SECTION_C_START: write your main function here.

int main() {
  int n;
  cin >> n;

  vector<Plane> aircraft;       //Vector to store all planes
  for(int i = 0; i < n; i++) {
    int time, id, priority;
    string status;


    //user input
    cin >> time >> id >> status >> priority;


    //Validate input values
    if(time < 0 || priority < 0) {
      throw runtime_error("Invalid input values");
    }

    if(status != "departing" && status != "arriving") {
      throw runtime_error("Invalid status");
    }

    //Add plane to the vector
    aircraft.push_back(Plane(id,time,status,priority));
  }

 
  //Two queues to represent Runway A and Runway B
  PlanePQ runwayA, runwayB;  //Queues
  int currentTime = 0;       //Time step counter
  int i = 0;                 //Index for aircraft vector


  //Main simulation loop
  while(i < n || !runwayA.empty() || !runwayB.empty()) {
    

    //Check if any planes are scheduled or queues are not empty
    if((i < n && aircraft[i].time == currentTime) || !runwayA.empty() || !runwayB.empty()) {
      cout << "Time step " << currentTime << endl;
      cout << "\tEntering simulation" << endl;


      //process all planes scheduled to arrive/depart at that time
        while(i < n && aircraft[i].time == currentTime) {
          aircraft[i].print();
          cout << endl;
      

          //add plane to the correct runway
          if(aircraft[i].status == "departing") {
            runwayA.push(aircraft[i]);
          } else {
            runwayB.push(aircraft[i]);
          }

          i++;
        }
    

        //Runway A
      cout << "\tRunway A" << endl;
      if(!runwayA.empty()) {
        //Always process departures from A if available
        Plane plane = runwayA.pop();
        plane.print();
        cout << endl;
      }

      //Runway B
      cout << "\tRunway B" << endl;
      if(!runwayB.empty()) {
        //Process arrivals from B
        Plane plane = runwayB.pop();
        plane.print();
        cout << endl;
      } else if(!runwayA.empty()) {
        //If B is empty and A has planes, help with departures
        Plane plane = runwayA.pop();
        plane.print();
        cout << endl;
      }
    }
    currentTime++;
  }

  return 0;
}

/*
I could not get it to pass all the test in the end, I was very close and tried
lots of different solutions but I don't have the knowledge to fix it.
I have included the required methods which all work as intended.
*/

//SECTION_C_END: Section C ends here. 
/***********************************************
************SECTION-C-MAIN-FUNCTION-END*********
************************************************/
/***********************************************
**************PLAGIARISM-RTNG-PRTCL-C***********
****************GEN-AI-RTNG-PRTCL-K*************
*********LOOP-CS_SEC-CS_CHR-STU_R_R_RFR*********
*****************DICT-A-ENTRY-2071**************
***************ORI-KTIAN@CSUCHICO.EDU***********
************************************************/

/***********************************************
*********CODE-CHECKER-ENDING-ALIGNMENT**********
************************************************/
