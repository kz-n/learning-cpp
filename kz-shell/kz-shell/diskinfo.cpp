#include<functional>
#include<string>
#include<iostream>
#include "diskinfo.h"

#include "utility.h"
#include "hwid2.h"

void commandDiskinfo::exec() {
	HardwareId HWID{};
	for (int i = 0; i < HWID.Disk.size(); i++) {
		HardwareId::DiskObject& Disk{ HWID.Disk.at(i) };

		std::wcout << L"Drive: ";
		std::wcout << Disk.Name.substr(4, Disk.Name.size() - 4);
		std::wcout << L"\n---------------------\n";

		std::wcout << L"Model:\t\t\t" << Disk.Model << std::endl;
		std::wcout << L"Serial Number:\t\t" << Disk.SerialNumber << std::endl;
		std::wcout << L"Interface Type:\t\t" << Disk.Interface << std::endl;
		std::wcout << L"Size:\t\t\t" << Disk.Size << L" GB" << std::endl;
		std::wcout << L"Free Space:\t\t" << Disk.FreeSpace << L" GB" << std::endl;

		std::wcout << L"Media Type:\t\t" <<
			(HWID.Disk.at(i).MediaType == 4 ? L"SSD" :
				(HWID.Disk.at(i).MediaType == 3 ? L"HDD" : L"(null)")) << std::endl;

		std::wcout << L"Boot Drive:\t\t" << (Disk.IsBootDrive ? L"Yes" : L"No") << std::endl;

		if (Disk.Volumes.empty() == false) {
			for (int j = 0; j < Disk.Volumes.size(); j++) {
				std::wcout << std::endl;
				std::wcout << L"Volume " << j << std::endl << L"--------\n";
				std::wcout << L"Name:\t\t\t" << Disk.Volumes.at(j).Name << std::endl;
				std::wcout << L"Serial Number:\t\t" << std::hex << Disk.Volumes.at(j).SerialNumber << std::dec << std::endl;
				std::wcout << L"Size:\t\t\t" << Disk.Volumes.at(j).Size << L" GB" << std::endl;
				std::wcout << L"Free Space:\t\t" << Disk.Volumes.at(j).FreeSpace << L" GB" << std::endl;
				std::wcout << L"Drive Letter:\t\t" << Disk.Volumes.at(j).DriveLetter << std::endl;

				if (j + 1 == Disk.Volumes.size()) {
					std::wcout << std::endl;
				}
			}
		}
		else {
			std::wcout << L"Drive Letter:\t\t" << HWID.Disk.at(i).DriveLetter << std::endl;

			if (i + 1 != HWID.Disk.size()) {
				std::wcout << std::endl;
			}
		}
	}
}