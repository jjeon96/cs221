/*---------------------------------------------------------------------
                  Driver program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
using namespace std;



void print(Queue q)
{ q.display(cout); }

int main(void)
{
   Queue q1;
	 Queue q3;
   cout << "Queue created.  Empty? " << boolalpha << q1.empty() << endl;

   cout << "How many elements to add to the queue? ";
   int numItems;
   cin >> numItems;
   for (int i = 1; i <= numItems; i++)
      q1.enqueue(100*i);

	//This is to Test merge_two_queues when q1.empty
 	for (int i = 1; i <= 10; i++)
	    q3.enqueue(110*i);


	 int moveNum;
	 cout << "What value do you want to move front ?" <<endl;
	 cin >> moveNum;
	 q1.move_to_front(moveNum);
   cout << "Contents of queue q1 (via  print):\n";
   print(q1);
   cout << endl;


	 	//This is to Test merge_two_queues when q1.empty
	 cout << "Contents of queue q3 (via  print):\n";
	 print(q3);
	 cout << endl;
	 q1.merge_two_queues(q3);
     cout << "Merge queue 1 and queue 3" << endl;
	 cout << "Contents of queue q1 after merging(via  print):\n";
	 print(q1);
	 cout << endl;
	 cout << "Contents of queue q3 after merging(via  print):\n";
	 print(q3);
	 cout << endl;
	 //

    // This is to Test merge_two_queues when both queues are empty
    Queue q4;
    cout << "Queue q4 is created. Empty?" << boolalpha << q4.empty() << endl;
    q3.merge_two_queues(q4);
    cout << "Merge queue q3 and queue q4" << endl;
    cout << "Contents of queue q3 after merging (via print):\n";
    print(q3);

    // This is to Test merge_two_queues when the two queues contain the same numbers;
    Queue q5;
    for (int i = 1; i <= numItems; i++)
        q5.enqueue(100*i);
    Queue q6;
    for (int i = 1; i <= numItems; i++)
        q6.enqueue(100*i);
    cout << "Queue q5 and Queue q6 have been created" << endl;
    cout << "Contents of queue q5 (via  print):\n";
    print(q5);
    cout << "Contents of queue q6 (via  print):\n";
    print(q6);
    cout << "Merge two queues and print the contents of Queue q5" << endl;
    q5.merge_two_queues(q6);
    print(q5);
    cout<<endl;


   Queue q2;
   q2 = q1;
   cout << "Contents of queue q2 after q2 = q1 (via  print):\n";
   print(q2);
   cout << endl;

   cout << "Queue q2 empty? " << q2.empty() << endl;

   cout << "Front value in q2: " << q2.front() << endl;


    // while q2 is not empty, keep removing the front of the queue
   while (!q2.empty())
   {
     cout << "Remove front -- Queue contents: ";
     q2.dequeue();
     q2.display(cout);
   }
   cout << "Queue q2 empty? " << q2.empty() << endl;
   cout << "Front value in q2?" << endl << q2.front() << endl;
   cout << "Trying to remove front of q2: " << endl;
   q2.dequeue();
   //system("PAUSE");
   return 0;
}
