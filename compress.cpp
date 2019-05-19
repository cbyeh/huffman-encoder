#include <algorithm>
#include "HCTree.hpp"

int main(int argc, char** argv) {
    // Check for appropriate arguments. Does not account for invalid files.
    const int NUM_ARGS = 3;
    if (argc != NUM_ARGS) {
        cout << "Invalid number of arguments" << endl <<
        "Usage: ./compress <infile filename> <outfile filename>." << endl;
        return EXIT_FAILURE;
    }
    // Error "checking" done. Proceed with program.
    const string INFILE = argv[1];
    const string OUTFILE = argv[2];
    ifstream input;
    ofstream output;
    input.open(INFILE, ios_base::binary);
    output.open(OUTFILE, ios_base::app);
    unsigned char nextChar;
    int nextByte;
    // If file is empty, don't write anything.
    input.seekg(0, ios::end);
    if (input.tellg() == 0) {
        return EXIT_SUCCESS;
    }
    input.clear();
    input.seekg(0);
    // Initiate all vector to 0.
    vector<int> ascii_count(HCTree::TABLE_SIZE, 0);
    unsigned int numCharacters = 0;
    unsigned int numUniqueChars = 0;
    // Proceed to read bytes, and count number of characters.
    while ((nextByte = input.get()) != EOF) {
        ascii_count[nextByte]++;
        numCharacters++;
    }
    // Get our number of unique characters */
    for (int count : ascii_count) {
        if (count > 0) {
            numUniqueChars++;
        }
    }
    // Encode our tree.
    BitOutputStream bitOut = BitOutputStream(output);
    HCTree* ht = new HCTree();
    ht->build(ascii_count);
    // Write our header: count and pre-order traversal of tree.
    ht->writeHeader(bitOut, numCharacters, numUniqueChars);
    // Write our encoding.
    input.clear();
    input.seekg(0);
    while ((nextByte = input.get()) != EOF) {
        nextChar = (unsigned char) nextByte;
        ht->encode(nextChar, bitOut);
    }
    // Padding for last.
    ht->pad(bitOut);
    delete ht;
    return EXIT_SUCCESS;
}