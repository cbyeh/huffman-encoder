#include "HCTree.hpp"

int main(int argc, char** argv) {
// Check for appropriate arguments. Does not account for invalid files.
    const int NUM_ARGS = 3;
    if (argc != NUM_ARGS) {
        cout << "Invalid number of arguments" << endl <<
             "Usage: ./uncompress <infile filename> <outfile filename>." << endl;
        return EXIT_FAILURE;
    }
    // Error "checking" done. Proceed with program.
    const string INFILE = argv[1];
    const string OUTFILE = argv[2];
    ifstream input;
    ofstream output;
    input.open(INFILE, ios_base::binary);
    output.open(OUTFILE, ios_base::app);
    // If file is empty, don't write anything.
    input.seekg(0, ios::end);
    if (input.tellg() == 0) {
        return EXIT_SUCCESS;
    }
    input.clear();
    input.seekg(0);
    // Get the number of characters for out output.
    BitInputStream bitIn = BitInputStream(input);
    unsigned int numCharacters = bitIn.readInt();
    cout << numCharacters << endl;
    unsigned int numUniqueChars = bitIn.readInt();
    cout << numUniqueChars << endl;
    // Build our tree from encoding.
    HCTree* ht = new HCTree();
    ht->buildFromEncoding(bitIn, numUniqueChars);
    // Output to our file. Deconstruct and return success.
    unsigned char nextByte;
    for (int i = 0; i < numCharacters; i++) {
//    while (input.tellg() != EOF) {
        nextByte = (unsigned char) ht->decode(bitIn);
        if (nextByte != 0) { // For extra character at end.
            output << nextByte;
        } else {
            break;
        }
    }
    delete ht;
    return EXIT_SUCCESS;
}