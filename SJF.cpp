#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
class Process {
public:
	int pid;
	int priority;
	int arrivalTime;
	vector<string> bursts;

	Process(int pid, int priority, int arrivalTime, const vector<string>& bursts)
    	: pid(pid), priority(priority), arrivalTime(arrivalTime), bursts(bursts) {}
};


void sjfScheduling(vector<Process>& processes) {
	cout << "SJF Scheduling:" << endl;
	for (const Process& process : processes) {
    	cout << "Process " << process.pid << ": Arrival Time=" << process.arrivalTime << " ";
    	for (const string& burst : process.bursts) {
        	cout << burst << " ";
    	}
    	cout << endl;
	}
}

vector<Process> readInputFile(const string& filename) {
	vector<Process> processes;
	ifstream file(filename);
	if (!file.is_open()) {
    	cerr << "Error opening file: " << filename << endl;
    	exit(EXIT_FAILURE);
	}
	int numProcesses, quantumValue;
	file >> numProcesses >> quantumValue;
	for (int i = 0; i < numProcesses; ++i) {
    	int pid, priority, arrivalTime;
    	file >> pid >> priority >> arrivalTime;
    	vector<string> bursts;
    	string burst;
    	while (file >> burst && burst != "-1") {
        	bursts.push_back(burst);
    	}
    	processes.emplace_back(pid, priority, arrivalTime, bursts);
	}
	file.close();
	return processes;
}

int main() {
	vector<Process> processes = readInputFile("input.dat");
	sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
    	return p1.bursts.size() < p2.bursts.size();
	});
	sjfScheduling(processes);
	return 0;
}