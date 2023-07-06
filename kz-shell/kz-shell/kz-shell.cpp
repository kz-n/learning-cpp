#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <stdlib.h>

#include "command.h"

#include "sysinfo.h"
#include "diskinfo.h"
using namespace std;

string shell();

void loadCommands();

vector<Command> commands = {};
string version = "1.0";



void loadCommands() {
    Command exitCommand("exit", []() {exit(0); });
    Command helpCommand("help", []() {
        cout << "kz-shell v" << version << endl;
        cout << "Available Commands: ";
        string cmds = "";
        for (Command cmd : commands) {
            cmds += cmd.name + " ";
        }
        cout << cmds << endl;
        });
    
    Command sysinfoCommand("sysinfo", []() {commandSysinfo cmdSysinfo; cmdSysinfo.exec(); });
    Command diskinfoCommand("diskinfo", []() {commandDiskinfo cmdDiskinfo; cmdDiskinfo.exec(); });
    commands = { exitCommand, helpCommand, sysinfoCommand, diskinfoCommand };
} 

int main() {
    loadCommands();
    while (true) {
        string shellResult = shell();
        for (Command cmd : commands) {
            if (cmd.name == shellResult) cmd.execute();
            
        }
    }
    return 0;
}

string shell() {
    printf("$ ");
    string input;
    getline(std::cin, input);
    return input;
}
