#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to XOR a chunk of data with a key string
void xorWithKey(string& chunk, const string& key) {
    for (size_t i = 0; i < chunk.size(); ++i) {
        chunk[i] ^= key[i % key.size()];
    }
}

int main() {
    // File name to be processed
    string filename = "input.txt"; // Change to your file name

    // Take key as input from user
    string key;
    cout << "Enter the 8-character key: ";
    cin >> key;

    if (key.size() != 8) {
        cerr << "Invalid key length. Key must be exactly 8 characters." << endl;
        return 1;
    }

    // Open file for reading
    ifstream inputFile(filename, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Error opening file for reading." << endl;
        return 1;
    }

    // Read file content into a stringstream
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string fileContent = buffer.str();
    inputFile.close();

    // Process the file content in chunks of 8 characters
    size_t chunkSize = 8;
    for (size_t i = 0; i < fileContent.size(); i += chunkSize) {
        string chunk = fileContent.substr(i, chunkSize);
        xorWithKey(chunk, key);
        fileContent.replace(i, chunkSize, chunk);
    }

    // Write the modified content back to the file
    ofstream outputFile(filename, ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Error opening file for writing." << endl;
        return 1;
    }
    outputFile.write(fileContent.c_str(), fileContent.size());
    outputFile.close();

    cout << "File processing completed." << endl;

    return 0;
}
