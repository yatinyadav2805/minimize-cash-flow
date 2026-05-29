#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>

using namespace std;

vector<vector<string>> minimizeCashFlow(vector<vector<string>>& transactions) {

 map<string, long long> balance;

    for (auto transaction : transactions) {

        string from = transaction[0];
        string to = transaction[1];
        long long amount = stoll(transaction[2]);

        balance[from] -= amount;
        balance[to] += amount;
    }

    vector<pair<string, long long>> debtors;
    vector<pair<string, long long>> creditors;

    for (auto person : balance) {

        string name = person.first;
        long long amount = person.second;

        if (amount < 0) {
            debtors.push_back({name, -amount});
        }

        else if (amount > 0) {
            creditors.push_back({name, amount});
        }
    }

    vector<vector<string>> result;

    int i = 0;
    int j = 0;

    while (i < debtors.size() && j < creditors.size()) {

        string debtorName = debtors[i].first;
        long long debtorAmount = debtors[i].second;

        string creditorName = creditors[j].first;
        long long creditorAmount = creditors[j].second;

        long long settledAmount = min(debtorAmount, creditorAmount);

        result.push_back({
            debtorName,
            creditorName,
            to_string(settledAmount)
        });

        debtors[i].second -= settledAmount;
        creditors[j].second -= settledAmount;

        if (debtors[i].second == 0) {
            i++;
        }

        if (creditors[j].second == 0) {
            j++;
        }
    }

    return result;
}

void printTransactions(vector<vector<string>>& transactions) {

    cout << "[\n";

    for (int i = 0; i < transactions.size(); i++) {

        cout << "    [\"" << transactions[i][0]
             << "\", \"" << transactions[i][1]
             << "\", " << transactions[i][2] << "]";

        if (i != transactions.size() - 1) {
            cout << ",";
        }

        cout << "\n";
    }

    cout << "]\n";
}

int main() {

    vector<vector<string>> transactions1 = {
        {"Tom", "Jerry", "1000"},
        {"Jerry", "Spike", "1000"},
        {"Spike", "Tom", "500"}
    };

    cout << "Example 1\n\n";

    cout << "Input:\n";
    printTransactions(transactions1);

    vector<vector<string>> answer1 = minimizeCashFlow(transactions1);

    cout << "\nOutput:\n";
    printTransactions(answer1);

    cout << "\n";

    vector<vector<string>> transactions2 = {
        {"Alice", "Bob", "4000"},
        {"Bob", "Charlie", "2000"},
        {"Charlie", "David", "1000"},
        {"David", "Alice", "500"}
    };

    cout << "Example 2\n\n";

    cout << "Input:\n";
    printTransactions(transactions2);

    vector<vector<string>> answer2 = minimizeCashFlow(transactions2);

    cout << "\nOutput:\n";
    printTransactions(answer2);

    return 0;
}