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
    // Initiate all vector to 0.
    vector<int> ascii_count(HCTree::TABLE_SIZE, 0);
    // Proceed to read bytes, assuming valid file.
    int firstVals = 0;
    string line = "";
    while (firstVals < HCTree::TABLE_SIZE) {
        getline(input, line);
        int count = stoi(line);
        ascii_count[firstVals] = count;
        firstVals++;
    }
    // Build tree and decode the encoded string.
    HCTree* ht = new HCTree();
    ht->build(ascii_count); // TODO: if no tree, close
    unsigned char nextByte;
    while (input.tellg() != EOF) {
        nextByte = (unsigned char) ht->decode(input);
        if (nextByte != 0) { // For extra character at end.
            output << nextByte;
        } else {
            break;
        }
    }
    delete ht;
    return EXIT_SUCCESS;
}