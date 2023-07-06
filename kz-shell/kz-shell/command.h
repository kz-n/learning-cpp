#pragma once
#include <iostream>
#include <functional>
#include <string>
class Command {
public:
    std::string name;
    std::function<void()> execute;
    Command(std::string n, std::function<void()> c);

};
