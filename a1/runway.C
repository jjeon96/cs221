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
  bool isLanding1 = false;
  bool isTakingoff1 = false;
  int planeID = 1000;
  int landingTime;
  int takeOffTime;
  int landingRate;
  int takeOffRate;
  int simulationDuration;
  int simulationTime = 0;
  int maxlandingQSize = 0;
  int maxtakeOffQSize = 0;
  int countDown1 = -1;
  float totalLandingWait = 0;
  float totalTakeoffWait = 0;
  int totalLandingPlane = 0;
  int totalTakeoffPlane = 0;

  int numOfRunways = 0;

  cout << "bowen<221> runway" <<endl;
  cout << "Enter:" << endl;
  while (numOfRunways != 1 && numOfRunways != 2) {
  cout << "  How many runways do you want to use? (currently 1 or 2):  ";
  cin >> numOfRunways;
  }
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
  switch (numOfRunways) {
    // CASE OF USING TWO RUNWAYS
    case 2:
    {
  cout << "There are two runways available" <<endl;
  cout << "one of the runway may shut down due to the bad condition" <<endl;
  int timeToReopen;
  cout << "  How long will it take to reopen a closed runway ?";
  cin  >> timeToReopen;
  cout << endl;


  Queue landingQ2;
  Queue takeOffQ2;
  int countDown2 = -1;
  bool isrunway1Available = true;
  bool isrunway2Available = true;
  bool runway1PendingClose = false;
  bool runway2PendingClose = false;
  bool isLanding2 = false;
  bool isTakingoff2 = false;
  int runwayReopen = -1;

  //         -> program should continue until there is no more planes
  //            in both landing and takeoff queues.
  //       BELOW checks time < simulationDuration
  //

  while (simulationTime <= simulationDuration || !landingQ1.empty() || !takeOffQ1.empty() || !landingQ2.empty() || !takeOffQ2.empty()){
    cout << "Time = " << simulationTime << endl;

    // INFORM THAT THERE WILL BE NO MORE ENQUEING
    if(simulationTime == simulationDuration)
      cout << "No new takeoffs or landings will be generated." << endl;

    //
      countDown1--;
      countDown2--;

    // check if the plane in action has finished landing/taking off, then dequeue that plane.
    if (countDown1 == 0) {
      if (isLanding1 == true) {
        landingQ1.dequeue() ;
        totalLandingPlane++;
        int size = sizeOfQ(landingQ1);
        isLanding1 = false;
        cout << "Landing complete from Runway1; " << size << " in landing queue1" << endl;
      }
      if (isTakingoff1 == true){
        takeOffQ1.dequeue();
        totalTakeoffPlane++;
        int size = sizeOfQ(takeOffQ1);
        isTakingoff1 = false;
        cout << "Takeoff complete from Runway1; " << size << " in takeOff queue1" << endl;
      }

    }
    if (countDown2 == 0) {
      if (isLanding2 == true) {
        landingQ2.dequeue();
        totalLandingPlane++;
        int size = sizeOfQ(landingQ2);
        isLanding2 = false;
        cout << "Landing complete from Runway2; " << size << " in landing queue2" << endl;
      }
      if (isTakingoff2 == true){
        takeOffQ2.dequeue();
        totalTakeoffPlane++;
        int size = sizeOfQ(takeOffQ2);
        isTakingoff2 = false;
        cout << "Takeoff complete from Runway2; " << size << " in takeOff queue2" << endl;
      }
    }
    // if one of the runways close down, merge the landing/takeoff queues into the runway that still functions

    if (runway1PendingClose && countDown1 <=0) {
      cout << "Runway 1 has been shut down. Queues will be merged to runway 2" << endl;

      cout << "Planes before shut down: " << endl;
      cout << "   Planes in landingQ1: ";
      print(landingQ1);
      cout << "   Planes in landingQ2: ";
      print(landingQ2);
      cout << "   Planes in takeOffQ1: ";
      print(takeOffQ1);
      cout << "   Planes in takeOffQ2: ";
      print(takeOffQ2);
      landingQ2.merge_two_queues(landingQ1);
      takeOffQ2.merge_two_queues(takeOffQ1);
      cout << "Planes after shut down: " << endl;
      cout << "   Planes in landingQ1: ";
      print(landingQ1);
      cout << "   Planes in landingQ2: ";
      print(landingQ2);
      cout << "   Planes in takeOffQ1: ";
      print(takeOffQ1);
      cout << "   Planes in takeOffQ2: ";
      print(takeOffQ2);
      isrunway1Available = false;
      runway1PendingClose = false;
      runwayReopen = timeToReopen;
    }
    if (runway2PendingClose && countDown2 <= 0) {
      cout << "Runway 2 has been shut down. Queues will be merged to runway 1"<< endl;
      cout << "Planes before shut down: " << endl;
      cout << "   Planes in landingQ1: ";
      print(landingQ1);
      cout << "   Planes in landingQ2: ";
      print(landingQ2);
      cout << "   Planes in takeOffQ1: ";
      print(takeOffQ1);
      cout << "   Planes in takeOffQ2: ";
      print(takeOffQ2);
      landingQ1.merge_two_queues(landingQ2);
      takeOffQ1.merge_two_queues(takeOffQ2);
      cout << "Planes after shut down: " << endl;
      cout << "   Planes in landingQ1: ";
      print(landingQ1);
      cout << "   Planes in landingQ2: ";
      print(landingQ2);
      cout << "   Planes in takeOffQ1: ";
      print(takeOffQ1);
      cout << "   Planes in takeOffQ2: ";
      print(takeOffQ2);
      isrunway2Available = false;
      runway2PendingClose = false;
      runwayReopen = timeToReopen;
    }



    // check the time remaining until the closed runway will be able to reopen

    if (runwayReopen > 0) {
      if (!isrunway1Available) {
        if (runwayReopen <= 10)
        cout << "Runway1 will reopen in " << runwayReopen << " minutes" << endl;
        else if (runwayReopen % 10 == 0)
        cout << "Runway1 will reopen in " << runwayReopen << " minutes" << endl;
      }
      if (!isrunway2Available) {
        if (runwayReopen <= 10)
        cout << "Runway2 will reopen in " << runwayReopen << " minutes" << endl;
        else if (runwayReopen <= 10)
        cout << "Runway2 will reopen in " << runwayReopen << " minutes" << endl;
      }
      runwayReopen--;
    }
    // when the timeToReopen hits 0, open the closed runway and inform that both runways can function.

    if (runwayReopen == 0) {
      cout << "Both Runways are running now" << endl;
      runwayReopen = -1;
      isrunway1Available = true;
      isrunway2Available = true;
    }



    if (isrunway1Available && isrunway2Available && !runway1PendingClose && !runway2PendingClose) {
      int randNum = rand() % 60;
      if (randNum < 1) {
        if (randNum % 2 == 1) {
            cout << "Runway 1 will shut down after this current landing or takeoff." << endl;
            cout << "Landing & takeoff queues in runway 1 will be merged to runway 2" << endl;
            runway1PendingClose = true;
          }
        else {
            cout << "Runway 2 will shut down after this current landing or takeoff." << endl;
            cout << "Landing & takeoff queues in runway 2 will be merged to runway 1" << endl;
            runway2PendingClose = true;
          }
        }
      }

    //GENERATION PART
    // Add planes to landing/ takeoff queue in the two runways

    while (simulationTime < simulationDuration) {
      if (rand() % 60 < landingRate){
        cout << "Plane " << planeID << " wants to land; ";
        if (isrunway1Available && isrunway2Available && !runway1PendingClose && !runway2PendingClose) {
          if (sizeOfQ(landingQ1) < sizeOfQ(landingQ2)) {
            landingQ1.enqueue(planeID);
            int size1 = sizeOfQ(landingQ1);
            int size2 = sizeOfQ(landingQ2);
            if (maxlandingQSize < size1)
              maxlandingQSize = size1;
            cout << "added to the landing queue1;" <<endl;
            cout << size1 << " in landing queue1" << endl;
            cout << size2 << " in landing queue2" << endl;
            planeID++;
          }

          else if (sizeOfQ(landingQ1) > sizeOfQ(landingQ2)) {
            landingQ2.enqueue(planeID);
            int size1 = sizeOfQ(landingQ1);
            int size2 = sizeOfQ(landingQ2);
            if (maxlandingQSize < size2)
              maxlandingQSize = size2;
            cout << "added to the landing queue2;" <<endl;
            cout << size1 << " in landing queue1" << endl;
            cout << size2 << " in landing queue2" << endl;
            planeID++;
          }
          else {
            if (sizeOfQ(takeOffQ1) <= sizeOfQ(takeOffQ2)) {

                landingQ1.enqueue(planeID);
                int size1 = sizeOfQ(landingQ1);
                int size2 = sizeOfQ(landingQ2);
                if (maxlandingQSize < size1)
                  maxlandingQSize = size1;
                cout << "added to the landing queue1;" <<endl;
                cout << size1 << " in landing queue1" << endl;
                cout << size2 << " in landing queue2" << endl;
                planeID++;
            }
            else {
                landingQ2.enqueue(planeID);
                int size1 = sizeOfQ(landingQ1);
                int size2 = sizeOfQ(landingQ2);
                if (maxlandingQSize < size2)
                  maxlandingQSize = size2;
                cout << "added to the landing queue2;" <<endl;
                cout << size1 << " in landing queue1" << endl;
                cout << size2 << " in landing queue2" << endl;
                planeID++;
            }
          }
        }

        else if (!isrunway2Available || runway2PendingClose) {
            landingQ1.enqueue(planeID);
            int size1 = sizeOfQ(landingQ1);
            if (maxlandingQSize < size1)
              maxlandingQSize = size1;
            cout << "added to the landing queue1;"<< endl;
            cout << size1 << " in landing queue1" << endl;
            planeID++;
        }
        else if (!isrunway1Available || runway1PendingClose) {
            landingQ2.enqueue(planeID);
            int size2 = sizeOfQ(landingQ2);
            if (maxlandingQSize < size2)
              maxlandingQSize = size2;
            cout << "added to the landing queue2;"<< endl;
            cout << size2 << " in landing queue2" << endl;
            planeID++;
        }

      }
      if (rand() % 60 < takeOffRate) {
        cout << "Plane " << planeID << " wants to take off; ";
        if (isrunway1Available && isrunway2Available && !runway1PendingClose && !runway2PendingClose) {
          if (sizeOfQ(takeOffQ1) < sizeOfQ(takeOffQ2)) {
            takeOffQ1.enqueue(planeID);

            int size1 = sizeOfQ(takeOffQ1);
            int size2 = sizeOfQ(takeOffQ2);
            if (maxtakeOffQSize < size1)
              maxtakeOffQSize = size1;

            cout << "added to the takeoff queue1;"<<endl;
            cout << size1 << " in takeoff queue1" << endl;
            cout << size2 << " in takeoff queue2" << endl;
            planeID++;
          }

          else if (sizeOfQ(takeOffQ1) > sizeOfQ(takeOffQ2)){
            takeOffQ2.enqueue(planeID);

            int size1 = sizeOfQ(takeOffQ1);
            int size2 = sizeOfQ(takeOffQ2);
            if (maxtakeOffQSize < size2)
              maxtakeOffQSize = size2;
            cout << "added to the takeoff queue2;"<<endl;
            cout << size1 << " in takeoff queue1" << endl;
            cout << size2 << " in takeoff queue2" << endl;
            planeID++;
          }
          else {
            if(sizeOfQ(landingQ1) <= sizeOfQ(landingQ2)) {
              takeOffQ1.enqueue(planeID);

              int size1 = sizeOfQ(takeOffQ1);
              int size2 = sizeOfQ(takeOffQ2);
              if (maxtakeOffQSize < size1)
                maxtakeOffQSize = size1;

              cout << "added to the takeoff queue1;"<<endl;
              cout << size1 << " in takeoff queue1" << endl;
              cout << size2 << " in takeoff queue2" << endl;
              planeID++;
            }
            else {
                takeOffQ2.enqueue(planeID);

                int size1 = sizeOfQ(takeOffQ1);
                int size2 = sizeOfQ(takeOffQ2);
                if (maxtakeOffQSize < size2)
                  maxtakeOffQSize = size2;
                cout << "added to the takeoff queue2;"<<endl;
                cout << size1 << " in takeoff queue1" << endl;
                cout << size2 << " in takeoff queue2" << endl;
                planeID++;
            }

          }
        }

        else if (!isrunway2Available || runway2PendingClose) {
            takeOffQ1.enqueue(planeID);
            int size1 = sizeOfQ(takeOffQ1);
            if (maxtakeOffQSize < size1)
              maxtakeOffQSize = size1;
            cout << "added to the takeoff queue1;" << endl;
            cout << size1 << " in takeoff queue1" << endl;
            planeID++;
        }
        else if (!isrunway1Available || runway1PendingClose) {
            takeOffQ2.enqueue(planeID);
            int size2 = sizeOfQ(takeOffQ2);
            if (maxtakeOffQSize < size2)
              maxtakeOffQSize = size2;
            cout << "added to the takeoff queue2;" << endl;
            cout << size2 << " in takeoff queue2" << endl;
            planeID++;
        }
      }
      break;
    }

    // CHECK IF THE RUNWAY IS AVAILABE AND IF SO, LET THE MOST PRIOR PLANE TO RUN
    // give priority to the planes in the landing queues

    if (countDown1 <= 0 && isrunway1Available) {
      if (!landingQ1.empty()) {
        cout<< "Landing from runway1: Plane " << landingQ1.front()<< endl;
        countDown1 = landingTime;
        isLanding1 = true;
      }
      else if(!takeOffQ1.empty()) {
        cout<< "Taking off from runway1: Plane " << takeOffQ1.front() << endl;
        countDown1 = takeOffTime;
        isTakingoff1 = true;
        }
      }
      if (countDown2 <= 0 && isrunway2Available) {
        if (!landingQ2.empty()) {
          cout<< "Landing from runway2: Plane " << landingQ2.front()<< endl;
          countDown2 = landingTime;
          isLanding2 = true;
        }
        else if(!takeOffQ2.empty()) {
          cout<< "Taking off from runway2: Plane " << takeOffQ2.front() << endl;
          countDown2 = takeOffTime;
          isTakingoff2 = true;
          }
        }

      // THIS IS TO KEEP TRACK OF TOTAL WAIT PER TIME FOR EACH QUEUE
      totalLandingWait += sizeOfQ(landingQ1) + sizeOfQ(landingQ2);
      totalTakeoffWait += sizeOfQ(takeOffQ1) + sizeOfQ(takeOffQ2);
      simulationTime++;
    }
    break;
  }
  // CASE OF USING ONE RUNWAY

  case 1: {
    cout << "There are only one runway available" <<endl;
    while (simulationTime <= simulationDuration || !landingQ1.empty() || !takeOffQ1.empty()){
      cout << "Time = " << simulationTime << endl;

      // INFORM THAT THERE WILL BE NO MORE ENQUEING
      if(simulationTime == simulationDuration)
        cout << "No new takeoffs or landings will be generated." << endl;

      //countDown ALWAYS DECREMENT
      countDown1--;

      // check if the plane in action has finished landing/taking off, then dequeue that plane.
      if (countDown1 == 0) {
        if (isLanding1 == true) {
          landingQ1.dequeue();
          totalLandingPlane++;
          int size = sizeOfQ(landingQ1);
          isLanding1 = false;
          cout << "Landing complete; " << size << " in landing queue" << endl;
          if (!landingQ1.empty()) {
            int ID;
            cout << "In landing Queue, there are plane with ID: ";
            print(landingQ1);
            cout << "Is there any plane in emergency to land?"<< endl;
            cin >> ID;
            landingQ1.move_to_front(ID);
          }
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
          if (maxtakeOffQSize < size)
            maxtakeOffQSize = size;
          cout << size << " in takeoff queue" << endl;
          planeID++;
        }
        break;
      }

      // CHECK IF THE RUNWAY IS AVAILABE AND IF SO, LET THE MOST PRIOR PLANE TO RUN
      if (countDown1 <= 0) {
        if (!landingQ1.empty()) {
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
      break;
    }
  }

  cout << "Maximum number of planes in landing queue was: " << maxlandingQSize << endl;
  cout << "Average minutes spent waiting to land:  " << ((totalLandingWait - (totalLandingPlane * landingTime))/totalLandingPlane) << endl;
  cout << "Maximum number of planes in takeoff queue was: " << maxtakeOffQSize << endl;
  cout << "Average minutes spent waiting to take off:  " << ((totalTakeoffWait - (totalTakeoffPlane * takeOffTime))/totalTakeoffPlane) << endl;

  return -1;
}
