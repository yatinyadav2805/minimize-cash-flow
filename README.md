# Cash Flow Minimization Problem Solver

## Problem Statement

After a trip where friends spent money on behalf of each other, simplify all debts and determine the minimum number of transactions required to settle all balances completely.

### Requirements
- Every person's final balance must become zero
- The total amount paid and received remains correct
- The number of money transfers must be minimized

---

## Solution Strategy

### Algorithm Overview

The solution uses a **greedy matching algorithm** with the following approach:

1. **Calculate Net Balance**: For each person, compute their total balance
   - Negative balance → Person needs to pay money
   - Positive balance → Person needs to receive money
   - Zero balance → Already settled

2. **Separate into Debtors and Creditors**: Split people into two groups
   - Debtors: People with negative balance (owe money)
   - Creditors: People with positive balance (should receive money)

3. **Greedy Matching**: Match debtors with creditors
   - Repeatedly pair the person who owes the most with the person who should receive the most
   - Each transaction settles at least one person completely
   - Continue until all balances are zero

4. **Output**: Return the minimized set of transactions

### Complexity Analysis

- **Time Complexity**: O(n log n) where n is the number of unique people
- **Space Complexity**: O(n) for storing balances and transactions

### Why This Works

- Each transaction settles at least one person completely, ensuring we don't create unnecessary intermediate transactions
- The maximum number of transactions needed is n-1 (where n is the number of people with non-zero balance)
- The greedy approach directly matches payers with receivers, avoiding unnecessary chains of payments

---

## Examples

### Example 1

**Input:**
```
Tom owes Jerry 1000
Jerry owes Spike 1000
Spike owes Tom 500
```

**Net Balances:**
- Tom: -500 (owes)
- Jerry: 0 (settled)
- Spike: +500 (should receive)

**Output:** 1 transaction
```
Tom pays Spike 500
```

### Example 2

**Input:**
```
Alice owes Bob 4000
Bob owes Charlie 2000
Charlie owes David 1000
David owes Alice 500
```

**Net Balances:**
- Alice: -3500
- Bob: +2000
- Charlie: +1000
- David: +500

**Output:** 3 transactions
```
Alice pays Bob 2000
Alice pays Charlie 1000
Alice pays David 500
```

---

## Building and Running

### Prerequisites
- C++17 compatible compiler (clang++ or g++)
- make (optional, can compile manually)

### Using Makefile

```bash
# Build the project
make

# Run the program
make run

# Clean build artifacts
make clean
```

### Manual Compilation

```bash
clang++ -std=c++17 -Wall -Wextra -O2 -o minimize_cash_flow main.cpp
./minimize_cash_flow
```

---

## File Structure

```
pep/
├── main.cpp           # Main implementation with test cases
├── Makefile           # Build configuration
├── README.md          # This file
└── .gitignore         # Git ignore rules
```

---

## Key Features

✅ **Optimal Solution**: Minimizes the number of transactions needed
✅ **Well Documented**: Comprehensive comments and strategy documentation
✅ **Test Cases**: Includes examples from the problem statement
✅ **Efficient**: O(n log n) time complexity
✅ **Scalable**: Handles up to 10^4 transactions with amounts up to 10^9

---

## Implementation Notes

- The solution handles large amounts (up to 10^9) using `long long` data type
- Unique person names are stored in an unordered_map for O(1) lookups
- The greedy matching approach guarantees a valid solution with minimal transactions
- Multiple valid minimized solutions may exist; this implementation returns one valid solution

---

## Author

Solution for Cash Flow Minimization Problem

Date: May 29, 2026
