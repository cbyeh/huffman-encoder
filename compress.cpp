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
    // Initiate all vector to 0.
    vector<int> ascii_count(HCTree::TABLE_SIZE, 0);
    // Proceed to read bytes.
    while ((nextByte = input.get()) != EOF) {
        ascii_count[nextByte]++;
//        cout << nextByte << endl; // 67
//        cout << nextChar << endl; // C
    }
    // If file is empty, don't write anything.
    input.seekg(0, ios::end);
    if (input.tellg() == 0) {
        return EXIT_SUCCESS;
    }
    input.clear();
    input.seekg(0);
    // Write to our header the frequencies.
    for (int count : ascii_count) {
        output << count << endl;
    }
    // Encode our tree.
    HCTree* ht = new HCTree();
    ht->build(ascii_count); // TODO: if no tree, close
    // Write to our header the encoded file.
    input.clear();
    input.seekg(0);
    while ((nextByte = input.get()) != EOF) {
        nextChar = (unsigned char) nextByte;
        ht->encode(nextChar, output);
//         output << ht->getCode(nextChar);
    }
    delete ht;
    return EXIT_SUCCESS;
}