Cash Flow Minimization Problem Solver
Problem Statement

In a group of friends, multiple people spend money on behalf of others during a trip. After the trip, all expenses must be settled.

Instead of settling every transaction one by one, we simplify all debts and reduce the number of transactions so that everyone ends with a zero balance.

 Idea

We convert all transactions into a net balance system.

Negative balance → Person needs to pay money
Positive balance → Person needs to receive money
Zero balance → Already settled

This reduces a complex transaction graph into a simple balance sheet.

 Algorithm / Logic Flow
Step 1: Input Processing

Take list of transactions:

A pays B amount X
Step 2: Compute Net Balance
Create a hashmap (unordered_map)
For each transaction:
subtract X from payer
add X to receiver

After this step, every person has a final net balance.

Step 3: Classify People

Divide all people into 3 groups:

Debtors → balance < 0
Creditors → balance > 0
Settled → balance = 0 (ignored)
Step 4: Greedy Settlement Process

While both debtors and creditors exist:

Pick one debtor
Pick one creditor

Compute:

settlement = min(|debtor balance|, creditor balance)

Create transaction:

debtor → creditor
Update balances:
Reduce debtor’s debt
Reduce creditor’s credit
Remove person if balance becomes zero
Step 5: Output
Return all generated transactions
These represent the minimum number of transfers required
Core Logic
We do NOT follow original transaction chains
We first compute net balance
Then we greedily settle maximum possible amount in each step
This ensures minimum transactions
 Data Structures Used
unordered_map → store net balances (O(1) access)
vector → store final transactions
Greedy two-pointer style matching
 Complexity Analysis
Time Complexity: O(n log n)
Space Complexity: O(n)
 Examples
Example 1
Input

Tom → Jerry 1000
Jerry → Spike 1000
Spike → Tom 500

Net Balance
Tom = -500
Jerry = 0
Spike = +500
Output

Tom pays Spike 500

Example 2
Input

Alice → Bob 4000
Bob → Charlie 2000
Charlie → David 1000
David → Alice 500

Net Balance
Alice = -3500
Bob = +2000
Charlie = +1000
David = +500
Output

Alice pays Bob 2000
Alice pays Charlie 1000
Alice pays David 500

 Conclusion

This solution efficiently converts multiple complex transactions into a simplified system using net balance calculation and greedy matching. It ensures all debts are settled with the minimum number of transactions possible.
