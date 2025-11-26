#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to calculate the number of redundant bits needed
int calculateRedundantBits(int m) {
    int r = 0;
    while (pow(2, r) < m + r + 1) {
        r++;
    }
    return r;
}

// Function to insert redundant bits into the data bits
void insertRedundantBits(string &data, int r) {
    int n = data.length();
    int j = 0;
    string result = "";
    
    // Inserting redundant bits at positions 1, 2, 4, 8, ...
    for (int i = 0; i < n + r; i++) {
        if ((i + 1) == pow(2, j)) {
            result += '0'; // placeholder for parity bits
            j++;
        } else {
            result += data[i - j];
        }
    }
    data = result;
}

// Function to calculate parity bits for the data string
void calculateParityBits(string &data, int r) {
    int n = data.length();
    
    // Calculate parity bits at positions 1, 2, 4, 8, ...
    for (int i = 0; i < r; i++) {
        int pos = pow(2, i) - 1;
        int parity = 0;
        
        // Check the bits that contribute to the current parity bit
        for (int j = 0; j < n; j++) {
            if ((j + 1) & (pos + 1)) {
                parity ^= data[j] - '0';
            }
        }
        
        // Set the calculated parity bit
        data[pos] = (parity % 2 == 0) ? '0' : '1';
    }
}

// Function to detect errors at the receiver's side and identify the erroneous bit position
int detectError(string &data, int r) {
    int n = data.length();
    int errorPos = 0;
    
    // Check parity for each redundant bit
    for (int i = 0; i < r; i++) {
        int pos = pow(2, i) - 1;
        int parity = 0;
        
        // Check the bits that contribute to the current parity bit
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
    
    int m = data.length();
    int r = calculateRedundantBits(m); // Calculate number of redundant bits needed
    
    // Insert redundant bits into the data string
    insertRedundantBits(data, r);
    
    // Calculate and set the parity bits
    calculateParityBits(data, r);
    
    cout << "\nThe data packet to be sent is: ";
    for (char bit : data) {
        cout << bit << " ";
    }
    cout << endl;
    
    // Simulate receiver's side: detect and correct errors
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