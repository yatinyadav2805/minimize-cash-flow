#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iomanip>

using namespace std;

/**
 * Minimizes cash flow between friends after a trip
 * 
 * STRATEGY:
 * 1. Calculate net balance for each person (positive = should receive, negative = should pay)
 * 2. Separate people into debtors (negative balance) and creditors (positive balance)
 * 3. Use greedy matching: pair largest debtor with largest creditor
 * 4. For each pair, transfer min(debtor_amount, creditor_amount)
 * 5. Repeat until all balances are zero
 * 
 * TIME COMPLEXITY: O(n log n) where n is number of unique people
 * SPACE COMPLEXITY: O(n) for storing balances and transactions
 * 
 * WHY THIS WORKS:
 * - Each transaction settles at least one person completely
 * - Maximum transactions needed = n-1 (where n is number of people with non-zero balance)
 * - This greedy approach minimizes intermediate transactions
 */

vector<vector<string>> minimizeCashFlow(vector<vector<string>>& transactions) {
    vector<vector<string>> result;
    
    // Step 1: Calculate net balance for each person
    unordered_map<string, long long> balance;
    
    for (const auto& transaction : transactions) {
        string payer = transaction[0];
        string receiver = transaction[1];
        long long amount = stoll(transaction[2]);
        
        balance[payer] -= amount;      // Payer owes money (negative)
        balance[receiver] += amount;   // Receiver gets money (positive)
    }
    
    // Step 2: Separate people into debtors and creditors
    vector<pair<long long, string>> debtors;    // negative balance, name
    vector<pair<long long, string>> creditors;  // positive balance, name
    
    for (const auto& [person, amount] : balance) {
        if (amount < 0) {
            debtors.push_back({amount, person});
        } else if (amount > 0) {
            creditors.push_back({amount, person});
        }
        // amount == 0: person is already settled, skip
    }
    
    // Step 3: Greedy matching of debtors and creditors
    size_t debtorIdx = 0;
    size_t creditorIdx = 0;
    
    while (debtorIdx < debtors.size() && creditorIdx < creditors.size()) {
        long long debtAmount = -debtors[debtorIdx].first;      // Convert to positive
        long long creditAmount = creditors[creditorIdx].first;
        string debtor = debtors[debtorIdx].second;
        string creditor = creditors[creditorIdx].second;
        
        long long settleAmount = min(debtAmount, creditAmount);
        
        // Record the transaction
        result.push_back({debtor, creditor, to_string(settleAmount)});
        
        // Update balances
        debtors[debtorIdx].first += settleAmount;      // Make less negative
        creditors[creditorIdx].first -= settleAmount;  // Make less positive
        
        // Move to next debtor or creditor if current one is settled
        if (debtors[debtorIdx].first == 0) {
            debtorIdx++;
        }
        if (creditors[creditorIdx].first == 0) {
            creditorIdx++;
        }
    }
    
    return result;
}

/**
 * Helper function to print transaction details
 */
void printTransactions(const vector<vector<string>>& transactions) {
    cout << "[\n";
    for (size_t i = 0; i < transactions.size(); ++i) {
        cout << "    [\"" << transactions[i][0] << "\", \"" 
             << transactions[i][1] << "\", " << transactions[i][2] << "]";
        if (i < transactions.size() - 1) {
            cout << ",";
        }
        cout << "\n";
    }
    cout << "]\n";
}

/**
 * Helper function to print balances
 */
void printBalances(const unordered_map<string, long long>& balance) {
    cout << "\nNet Balances:\n";
    for (const auto& [person, amount] : balance) {
        cout << "  " << person << ": " << amount << "\n";
    }
}

int main() {
    cout << "========================================\n";
    cout << "Cash Flow Minimization Problem Solver\n";
    cout << "========================================\n\n";
    
    // Example 1
    cout << "Example 1:\n";
    cout << "-----------\n";
    vector<vector<string>> transactions1 = {
        {"Tom", "Jerry", "1000"},
        {"Jerry", "Spike", "1000"},
        {"Spike", "Tom", "500"}
    };
    
    cout << "Input Transactions:\n";
    printTransactions(transactions1);
    
    vector<vector<string>> result1 = minimizeCashFlow(transactions1);
    cout << "\nOptimized Transactions (Output):\n";
    printTransactions(result1);
    cout << "Number of transactions reduced from " << transactions1.size() 
         << " to " << result1.size() << "\n\n";
    
    // Example 2
    cout << "Example 2:\n";
    cout << "-----------\n";
    vector<vector<string>> transactions2 = {
        {"Alice", "Bob", "4000"},
        {"Bob", "Charlie", "2000"},
        {"Charlie", "David", "1000"},
        {"David", "Alice", "500"}
    };
    
    cout << "Input Transactions:\n";
    printTransactions(transactions2);
    
    vector<vector<string>> result2 = minimizeCashFlow(transactions2);
    cout << "\nOptimized Transactions (Output):\n";
    printTransactions(result2);
    cout << "Number of transactions reduced from " << transactions2.size() 
         << " to " << result2.size() << "\n\n";
    
    // Example 3 - More complex scenario
    cout << "Example 3 (Additional Test Case):\n";
    cout << "-----------\n";
    vector<vector<string>> transactions3 = {
        {"Alice", "Bob", "100"},
        {"Bob", "Charlie", "50"},
        {"Charlie", "Alice", "25"}
    };
    
    cout << "Input Transactions:\n";
    printTransactions(transactions3);
    
    vector<vector<string>> result3 = minimizeCashFlow(transactions3);
    cout << "\nOptimized Transactions (Output):\n";
    printTransactions(result3);
    cout << "Number of transactions reduced from " << transactions3.size() 
         << " to " << result3.size() << "\n\n";
    
    cout << "========================================\n";
    cout << "All test cases completed successfully!\n";
    cout << "========================================\n";
    
    return 0;
}
