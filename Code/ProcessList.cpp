//	Program Name:		Job Scheduler
//	Programmer Name:	Husam Alsheikh
//	Description:		Simulates a single CPU system that schedules jobs using Round Robin Scheduling Algorithm
//	Date Created:		09/27/2020

#include <iostream>
#include "ProcessList.h"

using namespace std;

//	Description:	Constructor function to initialize size to 0
//	Pre-Condition:	none
//	Post-Condition:	Instantiates object of class
ProcessList::ProcessList() {
	size = 0;
}

//	Description:	Class getter function to get size
//	Pre-Condition:	none
//	Post-Condition:	Returns size of queue
int ProcessList::getSize() {
	return size;
}

//	Description:	Class member function to enqueue a new event to queue
//	Pre-Condition:	Node of the event to be enqueued
//	Post-Condition:	Enqueues new node to list while sorting in order of arrival time
void ProcessList::enqueue(struct Node event) {
	struct Node temp;

	priorityQueue.resize(size + 1);

	priorityQueue[size].arrivalTime = event.arrivalTime;
	priorityQueue[size].type = event.type;
	priorityQueue[size].processID = event.processID;
	priorityQueue[size].bursts = event.bursts;
	priorityQueue[size].readyWait = event.readyWait;
	priorityQueue[size].ioWait = event.ioWait;

	int x = size;
	while (x >= 1) {
		if (priorityQueue[x / 2].arrivalTime > priorityQueue[x].arrivalTime) {
			temp = priorityQueue[x / 2];
			priorityQueue[x / 2] = priorityQueue[x];
			priorityQueue[x] = temp;

			x = x / 2;
		}
		else {
			break;
		}
	}

	size++;

	heapify();
}

//	Description:	Class member function that converts elements to heap
//	Pre-Condition:	none
//	Post-Condition:	Heapifies queue sorting the elements from min to largest
void ProcessList::heapify() {
	int x = 0;
	struct Node temp;

	while ((2 * x) < size - 1) {
		if ((2 * x) + 1 >= size - 1) {
			if (priorityQueue[x].arrivalTime > priorityQueue[2 * x].arrivalTime) {
				temp = priorityQueue[x];
				priorityQueue[x] = priorityQueue[2 * x];
				priorityQueue[2 * x] = temp;
				break;
			}
		}

		if (priorityQueue[x].arrivalTime > priorityQueue[2 * x].arrivalTime || priorityQueue[x].arrivalTime > priorityQueue[(2 * x) + 1].arrivalTime) {
			if (priorityQueue[2 * x].arrivalTime <= priorityQueue[(2 * x) + 1].arrivalTime) {
				temp = priorityQueue[2 * x];
				priorityQueue[2 * x] = priorityQueue[x];
				priorityQueue[x] = temp;

				x = 2 * x;
			}
			else if (priorityQueue[2 * x].arrivalTime > priorityQueue[(2 * x) + 1].arrivalTime) {
				temp = priorityQueue[(2 * x) + 1];
				priorityQueue[(2 * x) + 1] = priorityQueue[x];
				priorityQueue[x] = temp;

				x = (2 * x) + 1;
			}
		}
		else {
			break;
		}
	}
}

//	Description:	Class member function that deletes top node in heap
//	Pre-Condition:	none
//	Post-Condition:	Deletes top node from queue and decrements size
void ProcessList::deleteNode() {
	priorityQueue.erase(priorityQueue.begin());

	size--;

	heapify();
}

//	Description:	Class member function that checks if queue is empty
//	Pre-Condition:	none
//	Post-Condition:	Returns true if queue is empty, false otherwise
bool ProcessList::empty() {
	if (size == 0) {
		return true;
	}

	return false;
}

//	Description:	Class member function that will extract the minimum element from queue
//	Pre-Condition:	none
//	Post-Condition:	Returns top element from queue
Node ProcessList::extractMin() {
	Node temp;
	if (empty()) {
		temp.type = 0;
		temp.arrivalTime = INT_MAX;
		return temp;
	}

	struct Node min = priorityQueue[0];
	return min;
}