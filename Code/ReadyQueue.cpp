//	Program Name:		Job Scheduler
//	Programmer Name:	Husam Alsheikh
//	Description:		Simulates a single CPU system that schedules jobs using Round Robin Scheduling Algorithm
//	Date Created:		09/27/2020

#include <iostream>
#include <string>
#include "ReadyQueue.h"
#include "ProcessList.h"

using namespace std;

//	Description:	Constructor function to initialize head to null
//	Pre-Condition:	none
//	Post-Condition:	Instantiates object of class
ReadyQueue::ReadyQueue() {
	head = nullptr;
}

//	Description:	Class member function to enqueue event to queue
//	Pre-Condition:	Node of the event to enqueue
//	Post-Condition:	Enqueues node to queue
void ReadyQueue::enqueue(Node event) {
	Node* current = head;
	Node* temp = new Node();
	
	temp->arrivalTime = event.arrivalTime;
	temp->type = event.type;
	temp->processID = event.processID;
	temp->bursts = event.bursts;
	temp->readyWait = event.readyWait;
	temp->ioWait = event.ioWait;

	if (head == nullptr) {
		head = temp;

		return;
	}

	while (current->next != nullptr) {
		current = current->next;
	}

	current->next = temp;
	temp->next = nullptr;
}

//	Description:	Class member function to dequeue event from queue
//	Pre-Condition:	none
//	Post-Condition:	Dequeues node from queue
Node* ReadyQueue::dequeue() {
	Node* temp = head;

	head = temp->next;

	return temp;
}

//	Description:	Class getter function to get processID of top event in queue
//	Pre-Condition:	none
//	Post-Condition:	Return processID of top event
string ReadyQueue::getProcessID() {
	return to_string(head->processID);
}

//	Description:	Class getter function to get burst number of top event in queue
//	Pre-Condition:	none
//	Post-Condition:	Return burst number of top event
string ReadyQueue::getBurst() {
	return to_string(head->bursts[0]);
}

//	Description:	Class member function to get processID of top event
//	Pre-Condition:	none
//	Post-Condition:	Return processID of top event as string, return empty if ReadyQ is empty
string ReadyQueue::status() {
	if (empty()) {
		return "empty";
	}

	return "P" + to_string(head->processID);
}

//	Description:	Class member function to increment ready wait time of all events
//	Pre-Condition:	none
//	Post-Condition:	Increments ready wait time for all events in queue
void ReadyQueue::incrementWait() {
	if (!empty()) {
		Node* current = head;

		while (current->next != nullptr) {
			current = current->next;
			current->readyWait++;
		}
	}
}

//	Description:	Class member function to check if queue is empty
//	Pre-Condition:	none
//	Post-Condition:	Returns true if queue is empty, false otherwise
bool ReadyQueue::empty() {
	if (head == nullptr) {
		//	queue is empty
		return true;
	}

	return false;
}