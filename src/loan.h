#ifndef LOAN_H
#define LOAN_H

#include <string>

/**
 * @brief Holds parsed loan input parameters.
 */
struct LoanInput {
    long double amount = 0.0L;      /**< Principal loan amount. */
    long double annualRate = 0.0L;  /**< Annual interest rate in percent. */
    int months = 0;                 /**< Loan duration in months. */
    bool calcPayment = false;       /**< Whether to calculate monthly payment. */
};

/**
 * @brief Calculates the monthly payment (EMI) for a loan.
 *
 * Uses the standard amortization formula:
 *   EMI = P * (r * (1 + r)^n) / ((1 + r)^n - 1)
 *
 * @param in LoanInput containing amount, annualRate and months.
 * @return long double Monthly payment amount.
 */
long double calculateMonthlyPayment(const LoanInput &in);

#endif
