#include <iostream>
#include "Loan.h"
#include "Utils.h"

using namespace std;

/**
 * @brief Entry point for the legacy loan calculator (refactored).
 */
int main(int argc, char* argv[]) {
    LoanInput in;

    if (!parseArgs(argc, argv, in)) {
        cout << "\nUsage:\n";
        cout << "  " << argv[0] << " -cp -a AMOUNT -i INTEREST -n MONTHS\n\n";
        cout << "Example:\n";
        cout << "  " << argv[0] << " -cp -a 100000 -i 12 -n 360\n\n";
        return 1;
    }

    if (!in.calcPayment) {
        cerr << "Error: No calculation selected. Use -cp to calculate payment.\n";
        return 1;
    }

    long double payment = calculateMonthlyPayment(in);

    cout << "\n===== Loan Calculation =====\n";
    cout << "Loan Amount:      " << in.amount      << "\n";
    cout << "Interest Rate:    " << in.annualRate  << " %\n";
    cout << "Months:           " << in.months      << "\n";
    cout << "-----------------------------\n";
    cout << "Monthly Payment:  " << payment        << "\n";
    cout << "=============================\n\n";

    return 0;
}
