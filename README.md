# Cash Flow Minimization Problem Solver

## Problem Statement

A group of friends spends money for each other during a trip. After the trip, all expenses need to be settled.

Instead of doing multiple individual payments, we simplify all debts and reduce the number of transactions so that everyone ends with zero balance.



## Idea

We convert all transactions into a net balance system.

- Negative balance → person needs to pay money  
- Positive balance → person needs to receive money  
- Zero balance → already settled  

This reduces a complex transaction graph into a simple balance system.



## Algorithm / Logic Flow

### Step 1: Input Transactions
Each transaction is of form:
A pays B amount X



### Step 2: Compute Net Balance
- Create a hashmap (unordered_map)
- For each transaction:
  - subtract amount from payer
  - add amount to receiver



### Step 3: Classify People
- If balance < 0 → Debtor
- If balance > 0 → Creditor
- If balance = 0 → Ignore



### Step 4: Greedy Settlement
While debtors and creditors exist:
- Pick one debtor
- Pick one creditor
- Settle minimum possible amount
- Update balances
- Remove settled persons



### Step 5: Output
Return minimized list of transactions where all balances become zero.



## Core Logic

- Ignore original transaction chain  
- Convert everything into net balance  
- Use greedy matching to settle maximum amount each time  
- This ensures minimum number of transactions  



## Data Structures Used

- unordered_map → store net balances  
- vector → store final transactions  



## Complexity

- Time Complexity: O(n log n)  
- Space Complexity: O(n)  



## Examples

### Example 1
Tom → Jerry 1000  
Jerry → Spike 1000  
Spike → Tom 500  

Output:
Tom pays Spike 500  



### Example 2
Alice → Bob 4000  
Bob → Charlie 2000  
Charlie → David 1000  
David → Alice 500  

Output:
Alice pays Bob 2000  
Alice pays Charlie 1000  
Alice pays David 500  




## Conclusion

This project minimizes cash flow using net balance calculation and a greedy approach to reduce the number of transactions efficiently.