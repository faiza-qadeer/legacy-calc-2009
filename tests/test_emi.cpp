#include "gtest/gtest.h"
#include "../src/Loan.h"
#include "../src/Utils.h"
#include <cmath>

// Normal EMI calculation test
TEST(LoanTest, NormalEmiCalculation) {
    LoanInput in;
    in.amount = 100000;
    in.annualRate = 12;
    in.months = 360;
    in.calcPayment = true;

    long double payment = calculateMonthlyPayment(in);
    EXPECT_NEAR((double)payment, 1028.61, 1.0);
}

// Invalid loan amount
TEST(LoanTest, InvalidAmountFails) {
    LoanInput in;

    char* argv[] = {
        (char*)"calc",
        (char*)"-cp",
        (char*)"-a",
        (char*)"-5000",  // invalid
        (char*)"-i",
        (char*)"10",
        (char*)"-n",
        (char*)"12"
    };
    int argc = 9;

    bool ok = parseArgs(argc, argv, in);
    EXPECT_FALSE(ok);
}

// Large tenure should not overflow
TEST(LoanTest, LargeTenureNoOverflow) {
    LoanInput in;
    in.amount = 250000;
    in.annualRate = 7.5;
    in.months = 1200; // 100 years
    in.calcPayment = true;

    long double p = calculateMonthlyPayment(in);

    EXPECT_TRUE(std::isfinite((double)p));
    EXPECT_GT((double)p, 0);
}
