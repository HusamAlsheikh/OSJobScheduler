//	Program Name:		Job Scheduler
//	Programmer Name:	Husam Alsheikh
//	Description:		Simulates a single CPU system that schedules jobs using Round Robin Scheduling Algorithm
//	Date Created:		09/27/2020

#pragma once
#include <iostream>
#include "ProcessList.h"

using namespace std;

class IODevice {
private:
	Node event;
	int timeEntered;

public:
	IODevice();

	void dispatch(Node* temp, int simTime);

	Node process(int simTime);

	string status(bool IO_Idle);

	bool empty();
};