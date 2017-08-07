#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LQueue.h"

using namespace std;


void print(Queue q) {
 q.display(cout);
}

int sizeOfQ(Queue q) {
 Queue temp;
 int size = 0;
 while (!q.empty()) {
   temp.enqueue(q.front());
   q.dequeue();
   size++;
 }
 q = temp;
 return size;
}

int main(){
 srand(time(NULL));
 Queue landingQ1;
 Queue takeOffQ1;
 int planeID = 1000;
 int landingTime;
 int takeOffTime;
 int landingRate;
 int takeOffRate;
 int simulationDuration;

 cout << "bowen<221> runway" <<endl;
 cout << "Enter:" << endl;
 cout << "  Time for a plane to land (in minutes):  ";
 cin >> landingTime;
 cout << "  Time for a plane to takeOff (in minutes):  ";
 cin >> takeOffTime;
 cout << "  Landing rate (planes per hour):  ";
 cin >> landingRate;
 cout << "  Takeoff rate (planes per hour):  ";
 cin >> takeOffRate;
 cout << "  How long to run the simulation (in minutes):  ";
 cin >> simulationDuration;
 cout << endl;

 int simulationTime = 0;
 int maxlandingQSize = 0;
 int maxTakeOffQSize = 0;
 int countDown1 = -1;
 bool isLanding1 = false;
 bool isTakingoff1 = false;
 float totalLandingWait = 0;
 float totalTakeoffWait = 0;
 int totalLandingPlane = 0;
 int totalTakeoffPlane = 0;
 // TODO: for loop below should be implemented
 //         -> program should continue until there is no more planes
 //            in both landing and takeoff queues.
 //       BELOW only checks time < simulationDuration
 //       17/01/27 Ro: Basic setup for enqueing landing and takeoff queues is finished

 while (simulationTime <= simulationDuration || !landingQ1.empty() || !takeOffQ1.empty()){
   cout << "Time = " << simulationTime << endl;

   // INFORM THAT THERE WILL BE NO MORE ENQUEING
   if(simulationTime == simulationDuration)
     cout << "No new takeoffs or landings will be generated." << endl;

   //countDown ALWAYS DECREMENT
   countDown1--;

   // CHECK COMPLETE :
   if (countDown1 == 0) {
     if (isLanding1 == true) {
       landingQ1.dequeue();
       totalLandingPlane++;
       int size = sizeOfQ(landingQ1);
       isLanding1 = false;
       cout << "Landing complete; " << size << " in landing queue" << endl;
     }
     if (isTakingoff1 == true){
       takeOffQ1.dequeue();
       totalTakeoffPlane++;
       int size = sizeOfQ(takeOffQ1);
       isTakingoff1 = false;
       cout << "Takeoff complete; " << size << " in takeoff queue" << endl;

     }
   }

   //GENERATION PART
   while (simulationTime < simulationDuration) {
     if (rand() % 60 < landingRate){
       landingQ1.enqueue(planeID);
       cout << "Plane " << planeID << " wants to land; ";
       cout << "added to the landing queue;";
       int size = sizeOfQ(landingQ1);
       if (maxlandingQSize < size)
         maxlandingQSize = size;
       cout << size << " in landing queue" << endl;
       planeID++;

     }
     if (rand() % 60 < takeOffRate) {
       takeOffQ1.enqueue(planeID);
       cout << "Plane " << planeID << " wants to take off; ";
       cout << "added to the takeoff queue;";
       int size = sizeOfQ(takeOffQ1);
       if (maxTakeOffQSize < size)
         maxTakeOffQSize = size;
       cout << size << " in takeoff queue" << endl;
       planeID++;
     }
     break;
   }

   // CHECK IF THE RUNWAY IS AVAILABE AND IF SO, LET THE MOST PRIOR PLANE TO RUN
   if (countDown1 <= 0) {
     if (!landingQ1.empty()) {
       int ID;
       cout << "In landing Queue, there are plande with ID: ";
       print(landingQ1);
       cout << "Is there any plane in emergency to land?"<< endl;
       cin >> ID;
       landingQ1.move_to_front(ID);
       cout<< "Landing: Plane " << landingQ1.front()<< endl;
       countDown1 = landingTime;
       isLanding1 = true;
     }
     else if(!takeOffQ1.empty()) {
       cout<< "Taking off: Plane " << takeOffQ1.front() << endl;
       countDown1 = takeOffTime;
       isTakingoff1 = true;
       }
     }

     // THIS IS TO KEEP TRACK OF TOTAL WAIT PER TIME FOR EACH QUEUE
     totalLandingWait += sizeOfQ(landingQ1);
     totalTakeoffWait += sizeOfQ(takeOffQ1);
     simulationTime++;

   }

 cout << "Maximum number of planes in landing queue was: " << maxlandingQSize << endl;
 cout << "Average minutes spent waiting to land:  " << ((totalLandingWait - (totalLandingPlane * landingTime))/totalLandingPlane) << endl;
 cout << "Maximum number of planes in takeoff queue was: " << maxTakeOffQSize << endl;
 cout << "Average minutes spent waiting to take off:  " << ((totalTakeoffWait - (totalTakeoffPlane * takeOffTime))/totalTakeoffPlane) << endl;

 return -1;
}
