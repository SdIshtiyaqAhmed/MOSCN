#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

// Function to calculate the number of redundant bits required
int calculateRedundantBits(int m) {
    int r = 0;
    while (pow(2, r) < m + r + 1) {
        r++;
    }
    return r;
}

// Function to insert the redundant bits into the correct positions (1, 2, 4, 8, ...)
void insertRedundantBits(string &data, int r) {
    int n = data.length();
    string result = "";
    int j = 0;
    int dataIndex = 0;

    // Insert redundant bits at positions 1, 2, 4, 8, ...
    for (int i = 0; i < n + r; i++) {
        if ((i + 1) == pow(2, j)) {
            result += '0'; // Placeholder for parity bits
            j++;
        } else {
            result += data[dataIndex++];
        }
    }

    // Update the original data with the inserted bits
    data = result;
}

// Function to calculate and set the parity bits using even parity logic
void calculateParityBits(string &data, int r) {
    int n = data.length();

    // Calculate parity bits for positions 1, 2, 4, 8, ...
    for (int i = 0; i < r; i++) {
        int pos = pow(2, i) - 1;
        int parity = 0;

        // Check bits that contribute to the current parity bit
        for (int j = 0; j < n; j++) {
            if ((j + 1) & (pos + 1)) {
                parity ^= data[j] - '0';
            }
        }

        // Set the calculated parity bit (even parity)
        data[pos] = (parity % 2 == 0) ? '0' : '1';
    }
}

// Function to detect errors at the receiver side and find the erroneous bit
int detectError(const string &data, int r) {
    int n = data.length();
    int errorPos = 0;

    // Check parity for each redundant bit
    for (int i = 0; i < r; i++) {
        int pos = pow(2, i) - 1;
        int parity = 0;

        // Check bits that contribute to the current parity bit
        for (int j = 0; j < n; j++) {
            if ((j + 1) & (pos + 1)) {
                parity ^= data[j] - '0';
            }
        }

        // If parity is odd, it indicates an error in the bit
        if (parity % 2 != 0) {
            errorPos += (pos + 1);
        }
    }

    return errorPos;
}

int main() {
    string data;
    cout << "Enter the binary data string: ";
    cin >> data;

    int m = data.length(); // The number of data bits
    int r = calculateRedundantBits(m); // Calculate the number of redundant bits required

    // Insert the redundant bits into the data string
    insertRedundantBits(data, r);

    // Calculate and set the parity bits
    calculateParityBits(data, r);

    // Display the final data packet to be transmitted
    cout << "\nThe data packet to be sent is: ";
    for (char bit : data) {
        cout << bit << " ";
    }
    cout << endl;

    // Simulate receiver side: detect and correct errors
    int errorPos = detectError(data, r);

    if (errorPos == 0) {
        cout << "Correct data packet received\n";
    } else {
        cout << "Error detected at position: " << errorPos << endl;

        // Correct the error by flipping the erroneous bit
        data[errorPos - 1] = (data[errorPos - 1] == '0') ? '1' : '0';

        cout << "Corrected data packet: ";
        for (char bit : data) {
            cout << bit << " ";
        }
        cout << endl;
    }

    return 0;
}