# Cash Flow Minimization Problem Solver

## Problem Statement

In a group of friends, multiple people spend money for each other during a trip. After the trip, all expenses need to be settled.

Instead of settling every transaction one by one, we simplify all debts and reduce the number of transactions so that everyone ends with zero balance.



## Idea

We first calculate the net balance of each person.

This converts the problem from many transactions into a simple balance sheet.

- Negative balance → person needs to pay
- Positive balance → person needs to receive
- Zero balance → already settled



## Approach

### Step 1: Calculate Net Balance
For each transaction:
A pays B amount X

- A decreases by X
- B increases by X



### Step 2: Separate People
We divide people into:

- Debtors (negative balance)
- Creditors (positive balance)



### Step 3: Greedy Matching
We match one debtor with one creditor and settle minimum possible amount.

We repeat until all balances become zero.


## Why This Works

- Net balance removes all indirect transactions
- Each step reduces at least one active person
- Ensures minimum number of transactions
- Always produces a valid solution



## Complexity

Time: O(n log n)  
Space: O(n)



# Examples (Given by Teacher)



## Example 1

### Input
Tom → Jerry 1000  
Jerry → Spike 1000  
Spike → Tom 500  

### Net Balance
Tom = -500  
Jerry = 0  
Spike = +500  

### Output
Tom pays Spike 500  



## Example 2

### Input
Alice → Bob 4000  
Bob → Charlie 2000  
Charlie → David 1000  
David → Alice 500  

### Net Balance
Alice = -3500  
Bob = +2000  
Charlie = +1000  
David = +500  

### Output
Alice pays Bob 2000  
Alice pays Charlie 1000  
Alice pays David 500  

## Conclusion

This solution converts a complex network of transactions into a simple balance system and uses a greedy approach to minimize the number of transfers required to settle all debts.