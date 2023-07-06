#include <string>
#include <functional>
#include <iostream>
#include "command.h"
Command::Command(std::string n, std::function<void()> c) {
    name = n; execute = c;
}