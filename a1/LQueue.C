/*--- LQueue.cpp ----------------------------------------------------------
This file implements LQueue member functions.
From:  "ADTs, Data Structures, and Problem Solving with C++", 2nd edition
by Larry Nyhoff
-------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

#include "LQueue.h"

//--- Definition of Queue constructor
Queue::Queue()
: myFront(0), myBack(0)
{}

  //--- Definition of Queue copy constructor
  Queue::Queue(const Queue & original)
  {
    myFront = myBack = 0;
    if (!original.empty())
    {
      // Copy first node
      myFront = myBack = new Queue::Node(original.front());

      // Set pointer to run through original's linked list
      Queue::NodePointer origPtr = original.myFront->next;
      while (origPtr != 0)
      {
        myBack->next = new Queue::Node(origPtr->data);
        myBack = myBack->next;
        origPtr = origPtr->next;
      }
    }
  }

  //--- Definition of Queue destructor
  Queue::~Queue()
  {
    // Set pointer to run through the queue
    Queue::NodePointer prev = myFront,
    ptr;
    while (prev != 0)
    {
      ptr = prev->next;
      delete prev;
      prev = ptr;
    }
  }

  //--- Definition of assignment operator
  const Queue & Queue::operator=(const Queue & rightHandSide)
  {
    if (this != &rightHandSide)         // check that not q = q
    {
      this->~Queue();                  // destroy current linked list
      if (rightHandSide.empty())       // empty queue
      myFront = myBack = 0;
      else
      {                                // copy rightHandSide's list
      // Copy first node
      myFront = myBack = new Queue::Node(rightHandSide.front());

      // Set pointer to run through rightHandSide's linked list
      Queue::NodePointer rhsPtr = rightHandSide.myFront->next;
      while (rhsPtr != 0)
      {
        myBack->next = new Queue::Node(rhsPtr->data);
        myBack = myBack->next;
        rhsPtr = rhsPtr->next;
      }
    }
  }
  return *this;
}

//--- Definition of empty()
bool Queue::empty() const
{
  return (myFront == 0);
}

//--- Definition of enqueue()
void Queue::enqueue(const QueueElement & value)
{
  Queue::NodePointer newptr = new Queue::Node(value);
  if (empty())
  myFront = myBack = newptr;
  else
  {
    myBack->next = newptr;
    myBack = newptr;
  }
}

//--- Definition of display()
void Queue::display(ostream & out) const
{
  Queue::NodePointer ptr;
  for (ptr = myFront; ptr != 0; ptr = ptr->next)
  out << ptr->data << "  ";
  out << endl;
}

//--- Definition of front()
QueueElement Queue::front() const
{
  if (!empty())
  return (myFront->data);
  else
  {
    return 0;
  }
}

//--- Definition of dequeue()
void Queue::dequeue()
{
  if (!empty())
  {
    Queue::NodePointer ptr = myFront;
    myFront = myFront->next;
    delete ptr;
    if (myFront == 0)     // queue is now empty
    myBack = 0;
  }
  else
  cerr << "*** Queue is empty -- can't remove a value ***\n";
}
void Queue::move_to_front(const QueueElement& value)
{ //END must be edited
  if(empty())
  return;
  Queue::NodePointer curr = myFront;
  if(myFront->data == value) {
    return;
  }
  while (curr->next != myBack->next){
    if (curr->next->data == value){
      Queue::NodePointer temp = curr->next;
      curr->next = curr->next->next;
      temp->next = myFront;
      myFront = temp;
      if (myFront == myBack)
        myBack = curr;
      return;
    }
    curr = curr->next;
  }
}
void Queue::merge_two_queues(Queue & other)
{
  if (other.empty())
  return;
  if (empty()) {
    myFront = other.myFront;
    myBack = other.myBack;
    other.myFront = other.myBack = 0;
    return;
  }
  NodePointer curr = other.myFront;
  while (curr != other.myBack->next) {
    other.myFront = curr->next;
    if (myFront->data >= curr->data) {
      curr->next = myFront;
      myFront = curr;
    }
    else {
      NodePointer currQ1 = myFront;
      while (currQ1->next != myBack->next) {
        if (currQ1->next->data >= curr->data) {
          NodePointer temp = currQ1->next;
          currQ1->next = curr;
          currQ1->next->next = temp;
          break;
        }
        currQ1 = currQ1->next;
      }
      if (curr->next == other.myFront) {
        myBack->next = curr;
        myBack = curr;
      }
    }
    if(other.empty()){
      break;
    }
    curr = other.myFront;
  }
  other.myFront = other.myBack = 0;
}
