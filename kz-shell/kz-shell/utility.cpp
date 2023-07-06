#include <iostream>
#include <string>
#include "utility.h"

std::string convertToString(std::wstring* w) {
	std::string result;
	for (char x : *w) {
		result += x;
	}
	return result;
}