#include "gtest/gtest.h"
#include "../Loan.h"
#include "../Utils.h"
#include <cmath>

// Normal EMI calculation test
TEST(LoanTest, NormalEmiCalculation) {
    LoanInput in;
    in.amount = 100000.0L;
    in.annualRate = 12.0L;
    in.months = 360;
    in.calcPayment = true;

    long double payment = calculateMonthlyPayment(in);

    EXPECT_NEAR((double)payment, 1028.61, 1.0);
}

TEST(LoanTest, InvalidNegativeAmountRejected) {
    LoanInput in;

    char prog[] = "calc";
    char cp[]   = "-cp";
    char a[]    = "-a";
    char neg[]  = "-1000";
    char* argv[] = { prog, cp, a, neg };
    int argc = sizeof(argv) / sizeof(argv[0]);

    bool ok = parseArgs(argc, argv, in);

    EXPECT_FALSE(ok);
}

TEST(LoanTest, LargeTenureNoOverflow) {
    LoanInput in;
    in.amount = 500000.0L;
    in.annualRate = 7.5L;
    in.months = 1200; // 100 years
    in.calcPayment = true;

    long double payment = calculateMonthlyPayment(in);

    EXPECT_TRUE(isfinite((double)payment));
}
