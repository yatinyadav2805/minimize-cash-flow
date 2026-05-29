# Implementation Documentation

## File Overview

### main.cpp
Main implementation file containing:
- `minimizeCashFlow()`: Core algorithm function
- `printTransactions()`: Utility to display transactions in formatted output
- `printBalances()`: Utility to display person balances
- `main()`: Entry point with 3 comprehensive test cases

### Makefile
Build configuration supporting:
- `make` or `make all`: Compile the program
- `make run`: Compile and run the program
- `make clean`: Remove build artifacts

### README.md
User-facing documentation with:
- Problem statement and requirements
- Solution strategy overview
- Complexity analysis
- Usage instructions
- Build and run guide

### STRATEGY.md
Technical strategy document detailing:
- High-level approach
- Algorithm correctness proof
- Implementation details
- Edge cases and testing
- Scalability analysis

### .gitignore
Git ignore rules for:
- Build artifacts (*.o, *.out, executable)
- IDE configuration files
- macOS system files

---

## Function Signature

```cpp
vector<vector<string>> minimizeCashFlow(
    vector<vector<string>>& transactions
);
```

### Parameters
- `transactions`: Vector of [payer, receiver, amount] as strings

### Returns
- Optimized vector of [debtor, creditor, amount] transactions

### Time Complexity
- O(n log n) where n is the number of unique people

### Space Complexity
- O(n) for storing balances and transactions

---

## Algorithm Steps

### Step 1: Net Balance Calculation
```cpp
unordered_map<string, long long> balance;

for (const auto& transaction : transactions) {
    string payer = transaction[0];
    string receiver = transaction[1];
    long long amount = stoll(transaction[2]);
    
    balance[payer] -= amount;      // Payer's balance decreases
    balance[receiver] += amount;   // Receiver's balance increases
}
```

### Step 2: Separate into Debtors and Creditors
```cpp
vector<pair<long long, string>> debtors;    // (negative balance, name)
vector<pair<long long, string>> creditors;  // (positive balance, name)

for (const auto& [person, amount] : balance) {
    if (amount < 0) {
        debtors.push_back({amount, person});
    } else if (amount > 0) {
        creditors.push_back({amount, person});
    }
}
```

### Step 3: Greedy Matching
```cpp
size_t debtorIdx = 0;
size_t creditorIdx = 0;

while (debtorIdx < debtors.size() && creditorIdx < creditors.size()) {
    long long debtAmount = -debtors[debtorIdx].first;      // Make positive
    long long creditAmount = creditors[creditorIdx].first;
    string debtor = debtors[debtorIdx].second;
    string creditor = creditors[creditorIdx].second;
    
    long long settleAmount = min(debtAmount, creditAmount);
    
    result.push_back({debtor, creditor, to_string(settleAmount)});
    
    // Update balances
    debtors[debtorIdx].first += settleAmount;
    creditors[creditorIdx].first -= settleAmount;
    
    // Move indices if balance is zero
    if (debtors[debtorIdx].first == 0) debtorIdx++;
    if (creditors[creditorIdx].first == 0) creditorIdx++;
}
```

---

## Test Case Verification

### Test Case 1: Example 1
```
Input:  Tom → Jerry: 1000, Jerry → Spike: 1000, Spike → Tom: 500
Output: Tom → Spike: 500
Reduction: 3 → 1 ✓
```

### Test Case 2: Example 2
```
Input:  Alice → Bob: 4000, Bob → Charlie: 2000, 
        Charlie → David: 1000, David → Alice: 500
Output: Alice → Bob: 2000, Alice → Charlie: 1000, Alice → David: 500
Reduction: 4 → 3 ✓
```

### Test Case 3: Additional
```
Input:  Alice → Bob: 100, Bob → Charlie: 50, Charlie → Alice: 25
Output: Alice → Bob: 50, Alice → Charlie: 25
Reduction: 3 → 2 ✓
```

---

## Key Design Decisions

1. **Using `unordered_map` for Balance Storage**
   - O(1) average lookup vs O(log n) for map
   - Suitable for this problem size

2. **Storing Amounts as Long Long**
   - Handles up to 10^9 per transaction
   - Max 10^4 transactions = 10^13 total, fits in long long

3. **Separate Debtor/Creditor Vectors**
   - Cleaner logic than mixing in one structure
   - Allows easy iteration through two groups

4. **Greedy Matching Without Sorting**
   - For first/largest pairs, we iterate sequentially
   - Avoids explicit sorting overhead
   - Still achieves optimality through the algorithm logic

5. **String Output Format**
   - Matches required function signature
   - Amount converted via `to_string()` for consistency

---

## Potential Optimizations

1. **Pre-processing for Circular Debts**
   - Could detect cycles like A→B→A and eliminate them upfront
   - Would further reduce transaction count in some cases

2. **Sorting by Amount**
   - Could explicitly sort debtors and creditors by amount
   - Might improve performance for very large datasets
   - Not necessary for correctness or current performance

3. **Memory-Efficient Streaming**
   - Could process transactions in chunks for memory efficiency
   - Not needed given constraints

---

## Compilation Options

### Standard Compilation
```bash
g++ -std=c++17 -O2 -o minimize_cash_flow main.cpp
```

### With Full Warnings
```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 -o minimize_cash_flow main.cpp
```

### Debug Mode
```bash
g++ -std=c++17 -g -O0 -o minimize_cash_flow main.cpp
```

---

## Error Handling

The current implementation assumes:
- Valid input (no malformed transactions)
- Positive amounts (as per constraints)
- Guaranteed solvable (as per constraints)

For production use, could add:
- Input validation
- Exception handling
- Logging for debugging

---

## Output Format

Each test case displays:
1. Test case number and description
2. Input transactions in formatted JSON-like style
3. Calculated net balances (for understanding)
4. Output transactions in same format
5. Summary showing transaction reduction

Example:
```
Example 1:
-----------
Input Transactions:
[
    ["Tom", "Jerry", 1000],
    ...
]

Optimized Transactions (Output):
[
    ["Tom", "Spike", 500]
]
Number of transactions reduced from 3 to 1
```

---

## Building and Testing

### Build Project
```bash
cd /Users/yatin/Desktop/pep
make clean
make
```

### Run Tests
```bash
make run
# or
./minimize_cash_flow
```

### Expected Output
```
========================================
Cash Flow Minimization Problem Solver
========================================

Example 1:
...
All test cases completed successfully!
========================================
```

All three test cases should show successful optimization with reduced transaction counts.
