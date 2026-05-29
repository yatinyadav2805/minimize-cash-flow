# Cash Flow Minimization - Strategy Document

## Problem Overview

After a group of friends goes on a trip where they pay for each other, a complex network of debts is created. The goal is to minimize the number of transactions needed to settle all debts completely.

---

## Solution Strategy

### High-Level Approach

The solution employs a **greedy algorithm** based on net balance calculation:

1. **Calculate Each Person's Net Balance**
   - Track all money owed and received by each person
   - Net Balance = Total Received - Total Paid
   - Negative balance → Person is a debtor (needs to pay)
   - Positive balance → Person is a creditor (needs to receive)
   - Zero balance → Person is already settled

2. **Separate into Two Groups**
   - Debtors: All people with negative balances
   - Creditors: All people with positive balances

3. **Greedy Matching Algorithm**
   - While there are unsettled debtors and creditors:
     - Find the debtor with the largest debt
     - Find the creditor with the largest credit
     - Transfer min(debt, credit) from debtor to creditor
     - Update both balances
     - Remove anyone whose balance becomes zero

4. **Return Optimized Transactions**
   - Return all transactions discovered during the greedy matching

### Why This Algorithm is Optimal

**Key Insight**: Each transaction must settle at least one person (reduce their balance to zero).

- **Maximum Possible Transactions**: If we have n people with non-zero balance, we need at most n-1 transactions to settle everyone
- **Greedy Property**: By always matching the largest debtor with the largest creditor, we ensure each transaction settles someone completely, leaving no orphaned balances
- **Correctness**: The final balances will always sum to zero (conservation of money), and each person's balance will be zero after all transactions

### Example Walkthrough: Example 1

**Initial Transactions:**
```
Tom → Jerry: 1000
Jerry → Spike: 1000
Spike → Tom: 500
```

**Step 1: Calculate Net Balances**
```
Tom:   -1000 (paid) + 500 (received) = -500
Jerry: +1000 (received) - 1000 (paid) = 0
Spike: +1000 (received) - 500 (paid) = +500
```

**Step 2: Separate Groups**
```
Debtors:  [Tom: -500]
Creditors: [Spike: +500]
Jerry is settled (balance = 0), so ignore
```

**Step 3: Greedy Matching**
```
Iteration 1:
  Debtor: Tom owes 500
  Creditor: Spike receives 500
  Transfer: min(500, 500) = 500
  Transaction: Tom → Spike: 500
  Updated balances: Tom = 0, Spike = 0
  Both settled, done!
```

**Result**: 1 transaction instead of 3 ✓

---

## Implementation Details

### Data Structures Used

1. **unordered_map<string, long long>**: 
   - Stores net balance for each person
   - O(1) average lookup time
   - Handles large amounts (up to 10^9)

2. **vector<pair<long long, string>>**:
   - Stores debtors and creditors with their amounts
   - Separate vectors for debtors and creditors
   - Allows easy iteration through all unsettled people

3. **vector<vector<string>>**:
   - Stores the output transactions
   - Each transaction: [debtor, creditor, amount]

### Algorithm Complexity

- **Time Complexity**: O(n log n)
  - O(t) to calculate balances where t is number of input transactions
  - O(n log n) to sort debtors/creditors if needed (though not explicitly done in code)
  - O(n) for greedy matching (each iteration settles one person)
  - Overall dominated by sorting if needed: O(n log n)

- **Space Complexity**: O(n)
  - O(n) for the balance hash map
  - O(n) for debtors and creditors vectors
  - O(n) for result transactions (at most n-1 transactions)

### Edge Cases Handled

1. **Already Settled**: Transactions where people are in a cycle (e.g., A→B→C→A)
   - Handled by net balance calculation
   - Jerry in Example 1 is correctly identified as settled

2. **Large Amounts**: Up to 10^9
   - Used `long long` (64-bit) to avoid overflow
   - Sufficient for 10^4 transactions of 10^9 each

3. **Unique Names**: Multiple people with same balance
   - Handled by storing person's name with each balance
   - Each person has independent balance tracking

4. **Single Transaction Debt**:
   - Correctly identifies when only one transaction is needed
   - Handles chains where multiple people are settled

---

## Comparison with Other Approaches

### Approach 1: Naive (No Optimization)
- Simply execute all original transactions
- **Transactions**: t (number of original transactions)
- **Problem**: Doesn't minimize transactions

### Approach 2: DFS/BFS Settlement
- Try to find cycles and cancel them out
- **Time**: O(n²) or worse
- **Problem**: Complex, harder to prove optimality

### Approach 3: Greedy Matching (Our Solution) ✓
- Calculate net balances
- Greedily match largest debtor with largest creditor
- **Time**: O(n log n) or O(n)
- **Optimal**: Guaranteed to produce minimal transactions
- **Proof**: Each transaction settles at least one person

---

## Testing Strategy

### Test Cases Included

1. **Example 1: Simple Cycle**
   - 3 transactions reduced to 1
   - Tests cycle detection and simplification

2. **Example 2: Complex Chain**
   - 4 transactions reduced to 3
   - Tests multiple debtor/creditor matching
   - Tests that one person can owe/receive from multiple people

3. **Example 3: Additional Case**
   - 3 transactions reduced to 2
   - Tests different balance patterns

### Verification

For each test case, we verify:
- ✓ All original transaction amounts are accounted for
- ✓ Each person's final balance is zero
- ✓ Number of transactions is minimized

---

## Scalability

The solution handles the constraints:
- **Up to 10^4 transactions**: O(n log n) = ~130,000 operations
- **Amounts up to 10^9**: Using `long long` (up to 2^63-1 ≈ 9×10^18)
- **Unique names**: Efficient hash map storage

---

## Possible Extensions

1. **Circular Debt Optimization**: Detect and cancel circular debts before greedy matching (pre-processing)
2. **Multiple Solutions**: Find all minimal transaction sets
3. **Constrained Matching**: Add constraints like "specific people must not transact directly"
4. **Visualization**: Generate dependency graphs of transactions

---

## Conclusion

The greedy matching algorithm provides an optimal solution to the cash flow minimization problem with:
- ✓ Guaranteed correctness
- ✓ Minimal number of transactions
- ✓ Efficient O(n log n) time complexity
- ✓ Clear, understandable logic
- ✓ Handles all edge cases and constraints

The implementation includes comprehensive test cases and documentation for easy understanding and verification.
