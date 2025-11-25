#include "Loan.h"
#include <cmath>

/**
 * @brief Implementation of EMI calculation using long double.
 */
long double calculateMonthlyPayment(const LoanInput &in) {
    long double monthlyRate = in.annualRate / 12.0L / 100.0L;

    if (monthlyRate == 0.0L) {
        return in.amount / static_cast<long double>(in.months);
    }

    long double factor = std::pow(1.0L + monthlyRate,
                                  static_cast<long double>(in.months));

    return in.amount * (monthlyRate * factor) / (factor - 1.0L);
}
