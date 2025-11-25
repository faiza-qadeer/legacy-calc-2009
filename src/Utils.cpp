#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readConfig(LoanInput &in) {
    ifstream file("config.txt");
    if (!file) {
        return; 
    }

    string key;
    char eq;
    long double value;

    while (file >> key >> eq >> value) {
        if (key == "default_interest") {
            in.annualRate = value;
        } else if (key == "default_years") {
            in.months = static_cast<int>(value) * 12;
        }
    }
}

bool parseArgs(int argc, char* argv[], LoanInput &in) {
    readConfig(in);

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "-cp") {
            in.calcPayment = true;
        }
        else if (arg == "-a" && i + 1 < argc) {
            in.amount = stold(argv[++i]);
            if (in.amount <= 0.0L) {
                cerr << "Error: Loan amount (-a) must be > 0.\n";
                return false;
            }
        }
        else if (arg == "-i" && i + 1 < argc) {
            in.annualRate = stold(argv[++i]);
            if (in.annualRate < 0.0L) {
                cerr << "Error: Interest rate (-i) cannot be negative.\n";
                return false;
            }
        }
        else if (arg == "-n" && i + 1 < argc) {
            in.months = stoi(argv[++i]);
            if (in.months <= 0) {
                cerr << "Error: Number of months (-n) must be > 0.\n";
                return false;
            }
        }
        else {
            cerr << "Error: Unknown or incomplete argument: " << arg << "\n";
            return false;
        }
    }

    return true;
}

