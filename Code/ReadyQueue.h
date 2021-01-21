//	Program Name:		Job Scheduler
//	Programmer Name:	Husam Alsheikh
//	Description:		Simulates a single CPU system that schedules jobs using Round Robin Scheduling Algorithm
//	Date Created:		09/27/2020

#pragma once
#include <iostream>
#include "ProcessList.h"

using namespace std;

class ReadyQueue {	//	Linked List
private:
	Node* head;

public:
	ReadyQueue();

	void enqueue(Node event);

	Node* dequeue();

	string getProcessID();
	
	string getBurst();

	string status();

	void incrementWait();

	bool empty();
};