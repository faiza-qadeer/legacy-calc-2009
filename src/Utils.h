#ifndef UTILS_H
#define UTILS_H

#include "Loan.h"

/**
 * @brief Reads configuration defaults (e.g. interest, years) from config.txt.
 *
 * Supported keys:
 *  - default_interest=<number>
 *  - default_years=<integer>
 *
 * @param in LoanInput to fill with default values if not overridden by CLI.
 */
void readConfig(LoanInput &in);

/**
 * @brief Parses command-line arguments into LoanInput.
 *
 * Recognized flags:
 *  - -cp  : calculate monthly payment
 *  - -a   : loan amount
 *  - -i   : annual interest rate in percent
 *  - -n   : number of months
 *
 * @param argc Argument count.
 * @param argv Argument values.
 * @param in LoanInput to populate.
 * @return true on success, false on invalid/negative values or unknown flags.
 */
bool parseArgs(int argc, char* argv[], LoanInput &in);

#endif
