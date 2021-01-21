//	Program Name:		Job Scheduler
//	Programmer Name:	Husam Alsheikh
//	Description:		Simulates a single CPU system that schedules jobs using Round Robin Scheduling Algorithm
//	Date Created:		09/27/2020

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "ProcessList.h"
#include "CPU.h"
#include "IODevice.h"
#include "ReadyQueue.h"
#include "IOQueue.h"

using namespace std;

void createProcessList(ProcessList &processList, string inputPath);
void simulation(ProcessList processList, int& simTime, int timeQuantum, string outputPath, string outputLogPath);

//	Description:	Main of the program
//	Pre-Condition:	none
//	Post-Condition:	Takes in user input then runs program
void main() {
	ProcessList processList;

	string inputPath;
	string outputPath;
	string outputLogPath;
	int simTime = 0;
	int timeQuantum;

	cout << "Please enter file path for output file: ";
	getline(cin, outputPath);

	cout << "Please enter file path for input file: ";
	getline(cin, inputPath);

	ifstream temp(inputPath);

	//	Data Validation
	if (!temp.good()) {	//	If file path is invalid
		cout << "\n\tError - Invalid Input File, file path does not exist, terminating program!" << endl;
		exit(0);
	}
	if (temp.peek() == ifstream::traits_type::eof()) {	//	If file is empty
		cout << "\n\tError - Invalid Input File, file empty, terminating program" << endl;
		exit(0);
	}

	cout << "Please enter file path for output log file: ";
	getline(cin, outputLogPath);

	cout << "Please enter quantum number: ";
	cin >> timeQuantum;

	//	Data Validation
	if (timeQuantum < 1) {	//	If quantum number is invalid
		cout << "\n\tError - Invalid Quantum number, quantum number cannot be less than 1, terminating program!" << endl;
		exit(0);
	}

	cout << "\n\nTimeQuantum = " << timeQuantum << endl;

	createProcessList(processList, inputPath);
	simulation(processList, simTime, timeQuantum, outputPath, outputLogPath);

	system("pause");
}

//	Description:	Function to read in input file and create list of processes
//	Pre-Condition:	Pass by reference for list of processes, input file path
//	Post-Condition:	Reads input file and creates list of jobs
void createProcessList(ProcessList &processList, string inputPath) {
	ifstream input;
	string line;
	string temp;

	int processID = -1;
	int arrivalTime = 0;
	int cpuBursts = 0;
	int ioBursts = 0;
	int ascending = 0;

	struct Node event;

	input.open(inputPath);
	input.clear();

	while (getline(input, line)) {
		processID++;

		istringstream iss(line);

		iss >> temp;	//	arrival time
		arrivalTime = stoi(temp);

		iss >> temp;	//	number of total cpu bursts and io bursts
		cpuBursts = stoi(temp);
		ioBursts = cpuBursts - 1;

		//	Data Validation
		if (cpuBursts < 1) {	//	If invalid number of CPU bursts
			cout << "\n\tError - Invalid Data, CPU bursts cannot be less than 1, terminating program!" << endl;
			exit(0);
		}

		event.bursts.clear();

		cout << arrivalTime << " " << cpuBursts << " ";

		for (int x = 0; x < cpuBursts + ioBursts; x++) {
			event.arrivalTime = arrivalTime;
			event.type = 1;
			event.processID = processID;

			iss >> temp;

			event.bursts.push_back(stoi(temp));

			cout << temp << " ";

			//	Data Validation
			if (arrivalTime < ascending) {	//	If new arrival time number < previous arrival time number
				cout << "\n\tError - Invalid File Data, jobs not in ascending arrival time, terminating program!" << endl;
				exit(0);
			}
			ascending = arrivalTime;

			if (x == (cpuBursts + ioBursts) - 1) {
				//	Data Validation
				if (cpuBursts != (event.bursts.size()) - ioBursts) {	//	If wrong number of CPUbursts
					cout << "\n\tError - Invalid Data, CPU bursts < CPU burst number, program terminating!" << endl;
					exit(0);
				}
				if (ioBursts != (event.bursts.size() - cpuBursts)) {	//	If wrong number of IObursts
					cout << "\n\tError - Invalid Data, IO bursts < IO burst number, program termination!" << endl;
				}
			}
		}

		cout << endl;
		processList.enqueue(event);
	}

	input.close();
}

//	Description:	Function to run job scheduler simulation
//	Pre-Condition:	List of processes, pass by reference of simulationTime, timeQuantum, output file path, and outputLog file path
//	Post-Condition:	Runs simulation of job scheduler
void simulation(ProcessList processList, int& simTime, int timeQuantum, string outputPath, string outputLogPath) {
	ofstream output;
	ofstream outputLog;

	CPU cpu;
	IODevice ioDevice;
	ReadyQueue readyQ;
	IOQueue ioQ;

	bool IO_Idle = true;
	bool CPU_Idle = true;
	double cpuUtilization = 0;
	int simulationR = 0;	//	Flag to keep the simulation going

	Node event;
	Node temp;

	output.open(outputPath, ios::out);
	outputLog.open(outputLogPath, ios::out);

	while (!processList.empty() || (!CPU_Idle && !IO_Idle) || simulationR == 1) {	//	While list of processes is not empty and CPU and IO are not IDLE
		simTime++;
		event = processList.extractMin();
		
		if (simTime < event.arrivalTime) {
			//	print nothing happened to log file
			outputLog << simTime << ": " << "No event" << endl;
		}

		readyQ.incrementWait();
		ioQ.incrementWait();

		for (int x = 0; x <= processList.getSize(); x++) {
			if (event.arrivalTime <= simTime) {
				switch (event.type) {
				case 1:	//	ARRIVAL
					//	Create a new process and place it in the ready queue
					outputLog << simTime << ": " << "start of " << simTime << ": P" << event.processID;
					outputLog << " Arrives - new process - enters readyQ - CPU burst of " << event.bursts[0] << endl;

					output << simTime << ": P" << event.processID << " Arrives - new process changes state to Ready";

					readyQ.enqueue(event);
					break;

				case 2:	//	PREEMPTION
					//	Put the current process in the ready queue
					outputLog << simTime << ": " << "start of " << simTime << ": P" << event.processID;
					outputLog << " Preempted from CPU - moved into readyQ - CPU burst of " << event.bursts[0] << endl;

					output << simTime << ": P" << event.processID << " preempted - changes state from Running to Ready" << endl;

					CPU_Idle = true;
					readyQ.enqueue(event);
					break;

				case 3:	//	IO REQUEST
					//	Free CPU and move the current process into IO queue
					outputLog << simTime << ": " << "start of " << simTime << ": P" << event.processID;
					outputLog << " CPU burst complete - moved into IO Queue (Blocked) - IO Bursts of " << event.bursts[0] << endl;

					output << simTime << ": P" << event.processID << " CPU changes state from Running to Blocked" << endl;

					CPU_Idle = true;
					ioQ.enqueue(event);
					break;

				case 4:	//	IO DONE
					//	Free IO and put the process in the ready queue
					outputLog << simTime << ": " << "start of " << simTime << ": P" << event.processID;
					outputLog << " IO burst complete  - Move into readyQ - CPU burst of " << event.bursts[0] << endl;

					output << simTime << ": P" << event.processID << " changes state from Blocked to Ready" << endl;

					IO_Idle = true;
					readyQ.enqueue(event);
					break;

				case 5:	//	TERMINATION
					//	Free up CPU, update statistics of entire simulation
					outputLog << simTime << ": " << "start of " << simTime << ": P" << event.processID;
					outputLog << " Terminated - No more bursts remain" << endl;

					output << simTime << ": P" << event.processID << " change state from Running to Terminate" << endl;

					cout << "\nJob: " << event.processID << " terminated: Turn Around Time = " << (simTime - event.arrivalTime);
					cout << ", Wait Time = " << event.readyWait << ", IO Wait Time = " << event.ioWait << endl << endl;

					CPU_Idle = true;
					break;
				}

				readyQ.incrementWait();
				ioQ.incrementWait();

				processList.deleteNode();
				event = processList.extractMin();
			}
		}

		readyQ.incrementWait();
		ioQ.incrementWait();	

		if (CPU_Idle && !readyQ.empty()) {	//	dispatch a process by removing first process from ready queue
			//	maybe create a function in main to do so
			outputLog << simTime << ": " << " start of " << simTime << ": ";
			outputLog << " CPU empty - move P" << readyQ.getProcessID() << " from readyQ into CPU - CPU burst of " << readyQ.getBurst() << endl;

			output << simTime << ": P" << readyQ.getProcessID() << " changes state from Ready to Running" << endl;
			
			CPU_Idle = false;
			cpu.dispatch(readyQ.dequeue(), simTime);

			readyQ.incrementWait();
			ioQ.incrementWait();
		}

		if (IO_Idle && !ioQ.empty()) {	//	dispatch a process by removing first process from io queue
			//	maybe create a function in main to do so
			outputLog << simTime << ": P" << " start of " << simTime << ": ";
			outputLog << " IO empty - move " << ioQ.getProcessID() << " from IO Queue into IO - IO burst of " << ioQ.getBurst() << endl;

			output << simTime << ": P" << ioQ.getProcessID() << " changes state from Ready to Blocked" << endl;

			IO_Idle = false;
			ioDevice.dispatch(ioQ.dequeue(), simTime);

			readyQ.incrementWait();
			ioQ.incrementWait();
		}

		// End of time unit
		if (!cpu.empty()) {
			temp = cpu.process(simTime, timeQuantum);

			if (temp.processID != -1) {
				outputLog << simTime << ": " << "end of " << simTime << ": " << temp.processID;
				outputLog << " CPU burst complete - Moved into event list" << endl;

				processList.enqueue(temp);
			}
		}
		if (!ioDevice.empty()) {
			temp = ioDevice.process(simTime);

			if (temp.processID != -1) {
				outputLog << simTime << ": " << "end of " << simTime << ": " << temp.processID;
				outputLog << " IO burst complete - Moved into event list" << endl;

				processList.enqueue(temp);
			}
		}

		if (simTime % 5 == 0) {	//	print status every 5 simulation times
			outputLog << "\nCPU: " << cpu.status(CPU_Idle) << "\t\tIO: " << ioDevice.status(IO_Idle);
			outputLog << "\t\tReadyQ: " << readyQ.status() << "\t\tIOQueue: " << ioQ.status() << endl << endl;
			
			//	Visual Represention
			cout << "\nCPU: " << cpu.status(CPU_Idle) << "\t\tIO: " << ioDevice.status(IO_Idle);
			cout << "\t\tReadyQ: " << readyQ.status() << "\t\tIOQueue: " << ioQ.status() << endl << endl;
		}

		if (!CPU_Idle) {
			cpuUtilization++;
		}

		simulationR = 0;
		if (!CPU_Idle || !IO_Idle) {
			simulationR = 1;
		}
	}

	cpuUtilization = (cpuUtilization / simTime) * 100;

	cout << "Results for Quantum " << timeQuantum;
	cout << ", CPU Utilization: " << (int)round(cpuUtilization) << "%" << endl;

	cout << "" << endl;

	output.close();
	outputLog.close();
}