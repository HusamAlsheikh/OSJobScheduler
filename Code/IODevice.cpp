//	Program Name:		Job Scheduler
//	Programmer Name:	Husam Alsheikh
//	Description:		Simulates a single CPU system that schedules jobs using Round Robin Scheduling Algorithm
//	Date Created:		09/27/2020

#include <iostream>
#include <string>
#include "IODevice.h"

//	Description:	Constructor function to initialize processID to an invalid value
//	Pre-Condition:	none
//	Post-Condition:	Instantiates object of class
IODevice::IODevice() {
	event.processID = -1;
}

//	Description:	Class member function that will dispatch the job to the IO device
//	Pre-Condition:	Node of the event to be dispatched, and simulation time at function call
//	Post-Condition:	Dispatches event to IO device to be processed
void IODevice::dispatch(Node* temp, int simTime) {
	event.arrivalTime = temp->arrivalTime;
	event.processID = temp->processID;
	event.bursts = temp->bursts;
	event.type = temp->type;
	event.readyWait = temp->readyWait;
	event.ioWait = temp->ioWait;
	event.next = nullptr;

	timeEntered = simTime;
}

//	Description:	Class member function that will process the job
//	Pre-Condition:	Simulation time at function call
//	Post-Condition:	Processes event as an IO device simulation
Node IODevice::process(int simTime) {
	Node temp;
	temp.processID = -1;
	temp.type = 0;

	if (event.bursts.size() % 2 == 0) {
		if (((simTime - timeEntered) + 1) == event.bursts[0]) {
			event.type = 4;
			event.bursts.erase(event.bursts.begin());

			if (event.bursts.size() == 0) {
				event.type = 5;
			}

			return event;
		}
	}

	return temp;
}

//	Description:	Class member function to return job number
//	Pre-Condition:	Boolean value to check if IO is running or not
//	Post-Condition:	Returns job number or returns empty if IO is not running
string IODevice::status(bool IO_Idle) {
	if (IO_Idle) {
		return "empty";
	}

	return "P" + to_string(event.processID);
}

//	Description:	Class member function to check whether IO is empty or not
//	Pre-Condition:	none
//	Post-Condition:	Return true if IO is empty, false otherwise
bool IODevice::empty() {
	if (event.processID == -1) {
		return true;
	}

	return false;
}