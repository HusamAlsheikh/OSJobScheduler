//	Program Name:		Job Scheduler
//	Programmer Name:	Husam Alsheikh
//	Description:		Simulates a single CPU system that schedules jobs using Round Robin Scheduling Algorithm
//	Date Created:		09/27/2020

#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int arrivalTime;
	int type;
	int processID;

	int readyWait = 0;
	int ioWait = 0;

	vector<int> bursts;

	Node* next;
};

class ProcessList {	//	PriorityQueue
private:
	vector <Node> priorityQueue;
	int size;

public:
	ProcessList();

	int getSize();

	void enqueue(struct Node event);

	void heapify();

	void deleteNode();

	bool empty();

	Node extractMin();
};