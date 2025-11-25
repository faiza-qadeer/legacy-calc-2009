#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// Data structure for input arguments
struct LoanInput {
    double amount = 0.0;      // -a
    double annualRate = 0.0;  // -i
    int months = 0;           // -n
    bool calcPayment = false; // -cp
};

// Parse CLI arguments like: -cp -a 100000 -i 12 -n 360
bool parseArgs(int argc, char* argv[], LoanInput &in) {
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "-cp") {
            in.calcPayment = true;
        }
        else if (arg == "-a" && i + 1 < argc) {
            in.amount = stod(argv[++i]);
        }
        else if (arg == "-i" && i + 1 < argc) {
            in.annualRate = stod(argv[++i]);
        }
        else if (arg == "-n" && i + 1 < argc) {
            in.months = stoi(argv[++i]);
        }
        else {
            cerr << "❌ Unknown or incomplete argument: " << arg << endl;
            return false;
        }
    }

    if (!in.calcPayment) {
        cerr << "❌ Error: You must specify a calculation type (e.g., -cp)" << endl;
        return false;
    }
    if (in.amount <= 0 || in.months <= 0) {
        cerr << "❌ Error: Amount (-a) and Months (-n) must be > 0" << endl;
        return false;
    }

    return true;
}

// EMI (Monthly Payment) calculation using real amortization formula
double calculateMonthlyPayment(const LoanInput &in) {
    double monthlyRate = in.annualRate / 12.0 / 100.0;

    // Zero interest case
    if (monthlyRate == 0.0) {
        return in.amount / in.months;
    }

    // EMI formula
    double factor = pow(1 + monthlyRate, in.months);
    return in.amount * (monthlyRate * factor) / (factor - 1);
}

int main(int argc, char* argv[]) {
    LoanInput in;

    if (!parseArgs(argc, argv, in)) {
        cout << "\nUsage:\n"
             << "  " << argv[0] << " -cp -a AMOUNT -i INTEREST -n MONTHS\n\n"
             << "Example:\n"
             << "  " << argv[0] << " -cp -a 100000 -i 12 -n 360\n\n";
        return 1;
    }

    // Do calculation
    double payment = calculateMonthlyPayment(in);

    cout << "\n===== Loan Calculation Result =====\n";
    cout << "Loan Amount:         " << in.amount << endl;
    cout << "Interest Rate:       " << in.annualRate << "% annually" << endl;
    cout << "Loan Duration:       " << in.months << " months" << endl;
    cout << "------------------------------------\n";
    cout << "Monthly Payment:     " << payment << endl;
    cout << "====================================\n\n";

    return 0;
}
