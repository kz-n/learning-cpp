#include<functional>
#include<string>
#include<iostream>
#include "sysinfo.h"

#include "utility.h"
#include "hwid2.h"

// std::function<void()>
void commandSysinfo::exec() {
	HardwareId HWID{};
	std::string cpuName;
	int cpuCores, cpuThreads;

	cpuName = convertToString(&HWID.CPU.Name);
	cpuCores = HWID.CPU.Cores;
	cpuThreads = HWID.CPU.Threads;

	std::cout << "CPU: " << cpuCores << "x" << cpuName << " " << cpuThreads << "T." << std::endl;
	std::cout << convertToString(&HWID.System.OSName) << " " << convertToString(&HWID.System.OSVersion) << std::endl;

	std::cout << std::endl;

	for (int i = 0; i < HWID.GPU.size(); i++) {
		std::cout << "GPU " << i << ":" << std::endl;
		std::wcout << L"Name:\t\t\t" << HWID.GPU.at(i).Name << std::endl;
		std::wcout << L"Driver Version:\t\t" << HWID.GPU.at(i).DriverVersion << std::endl;
		std::wcout << L"Memory:\t\t\t" << HWID.GPU.at(i).Memory << L" MB" << std::endl;
		std::wcout << L"Resolution:\t\t" << HWID.GPU.at(i).XResolution << L"x" << HWID.GPU.at(i).YResolution << std::endl;
		std::wcout << L"Refresh Rate:\t\t" << HWID.GPU.at(i).RefreshRate << std::endl;

		if (i + 1 < HWID.GPU.size()) { std::wcout << std::endl; }
	}

}