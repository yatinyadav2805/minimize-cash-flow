# Quick Start Guide

## Clone/Navigate to Project
```bash
cd /Users/yatin/Desktop/pep
```

## Build the Project
```bash
make
```

## Run the Program
```bash
make run
```

Or directly:
```bash
./minimize_cash_flow
```

## Expected Output
The program will display 3 test cases with:
- Input transactions
- Optimized (minimized) transactions
- Transaction count reduction

Example:
```
Example 1:
Input Transactions: 3
Output Transactions: 1
Reduction: 3 → 1
```

## Clean Build Artifacts
```bash
make clean
```

## View Documentation
- **README.md** - Problem overview and solution strategy
- **STRATEGY.md** - Detailed algorithm explanation
- **IMPLEMENTATION.md** - Code walkthrough and details
- **PROJECT_SUMMARY.md** - Complete project overview

## Solution Approach
1. Calculate net balance for each person
2. Separate into debtors and creditors
3. Greedily match largest debtor with largest creditor
4. Output minimized transaction list

Time: O(n log n) | Space: O(n)

---

✅ All test cases pass  
✅ Ready for submission  
✅ Git history included
