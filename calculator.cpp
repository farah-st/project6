#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

// Calculator class
class Calculator {
private:
    vector<string> history; // Stores calculation history

public:
    // Function to perform calculations
    double calculate(double num1, double num2, char op) {
        double result = 0.0;
        switch (op) {
            case '+': result = num1 + num2; break;
            case '-': result = num1 - num2; break;
            case '*': result = num1 * num2; break;
            case '/': 
                if (num2 != 0) result = num1 / num2; 
                else {
                    cout << "Error: Division by zero!" << endl;
                    return 0;
                }
                break;
            default:
                cout << "Invalid operator!" << endl;
                return 0;
        }
        // Store result in history
        string entry = to_string(num1) + " " + op + " " + to_string(num2) + " = " + to_string(result);
        history.push_back(entry);
        return result;
    }

    // Display calculation history
    void displayHistory() {
        if (history.empty()) {
            cout << "No calculations performed yet." << endl;
            return;
        }
        cout << "Calculation History:" << endl;
        for (const auto &entry : history) {
            cout << entry << endl;
        }
    }

    // Save history to a file
    void saveHistoryToFile(const string &filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto &entry : history) {
                file << entry << endl;
            }
            file.close();
            cout << "History saved to " << filename << endl;
        } else {
            cout << "Error: Unable to open file." << endl;
        }
    }

    // Load history from a file
    void loadHistoryFromFile(const string &filename) {
        ifstream file(filename);
        string line;
        if (file.is_open()) {
            cout << "Previous Calculation History:" << endl;
            while (getline(file, line)) {
                cout << line << endl;
                history.push_back(line);
            }
            file.close();
        } else {
            cout << "No previous history found." << endl;
        }
    }
};

int main() {
    Calculator calc;
    string filename = "history.txt";
    calc.loadHistoryFromFile(filename); // Load previous calculations

    char choice;
    do {
        double num1, num2;
        char op;

        cout << "\nSimple Calculator\n";
        cout << "Enter first number: ";
        while (!(cin >> num1)) {  // Input validation
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter a number: ";
        }

        cout << "Enter operator (+, -, *, /): ";
        cin >> op;

        cout << "Enter second number: ";
        while (!(cin >> num2)) {  // Input validation
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter a number: ";
        }

        // Perform calculation
        double result = calc.calculate(num1, num2, op);
        cout << "Result: " << result << endl;

        // Ask user for next action
        cout << "\nOptions:\n";
        cout << "1. View History\n";
        cout << "2. Save History\n";
        cout << "3. New Calculation\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == '1') {
            calc.displayHistory();
        } else if (choice == '2') {
            calc.saveHistoryToFile(filename);
        }

    } while (choice != '4');

    cout << "Exiting program. Goodbye!" << endl;
    return 0;
}