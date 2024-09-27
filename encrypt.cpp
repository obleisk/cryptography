#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Function to generate a random 8-character string
string generateRandomString(size_t length) {
    const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string result;
    result.resize(length);

    for (size_t i = 0; i < length; ++i) {
        result[i] = chars[rand() % chars.size()];
    }

    return result;
}

// Function to XOR a chunk of data with a key string
void xorWithKey(string& chunk, const string& key) {
    for (size_t i = 0; i < chunk.size(); ++i) {
        chunk[i] ^= key[i % key.size()];
    }
}

int main() {
    // Seed random number generator
    srand(static_cast<unsigned>(time(0)));

    // File name to be processed
    string filename = "input.txt"; // Change to your file name

    // Generate a random 8-character string
    string key = generateRandomString(8);

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

    cout << "File processing completed. Random key used: " << key << endl;

    return 0;
}
