/**
 * Christopher Yeh
 * cyeh@ucsd.edu
 * Implementation of a DictionaryTrie.
 * It is instantiated with a node representing the empty string.
 */

#include "HCTree.hpp"

/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION: root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs) {
    // Create our priority queue as a min-heap and add our freqs to it.
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> q;
    for (int i = 0; i < freqs.size(); i++) {
        if (freqs[i] != 0) {
            auto node = new HCNode(freqs[i], i);
            q.push(node);
        }
    }
    HCNode* n0;
    HCNode* n1;
    // Begin building the Huffman trie.
    if (q.size() == 1) { // File contains one character.
        root = new HCNode(1, q.top()->symbol);
        codes[root->symbol] = "0";
    }
    while (q.size() > 1) {
        n0 = q.top();
        q.pop();
        n1 = q.top();
        q.pop();
        root = new HCNode(n0->count + n1->count, '\0');
        // Set pointers.
        if (n0->c0 == nullptr && n0->c1 == nullptr) {
            leaves[n0->symbol] = n0;
        }
        if (n1->c0 == nullptr && n1->c1 == nullptr) {
            leaves[n1->symbol] = n1;
        }
        root->c0 = n0;
        n0->p = root;
        root->c1 = n1;
        n1->p = root;
        q.push(root);
    }
    // Get the codes for our leaves.
    HCNode* curr;
    HCNode* prev;
    for (HCNode* leaf : leaves) {
        string code;
        if (leaf != nullptr) {
            curr = leaf;
            while (curr->p != nullptr) {
                prev = curr;
                curr = curr->p;
                if (curr->c0 == prev) {
                    code.insert(0, "0"); // Prepend.
                } else {
                    code.insert(0, "1"); // Prepend.
                }
            }
            codes[leaf->symbol] = code;
//            cout << leaf->count << " : " << codes.at(leaf->symbol) << endl;
        }
    }
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
//void encode(byte symbol, BitOutputStream& out) const {

//}

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream& out) const {
    out << codes.at(symbol);
}

/**
 * Helper method to get the bits that symbol represents in the trie.
 * @param symbol
 * @return
 */
string HCTree::getCode(byte symbol) {
    return codes.at(symbol);
}


/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
//int decode(BitInputStream& in) const {
//}

/** Return the symbol coded in the next sequence of bits (represented as
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream& in) const {
    unsigned char nextByte;
    if (root == nullptr) { // Empty file case.
        return 0;
    }
    if (root->c0 == nullptr && root->c1 == nullptr) { // One character case.
        in.get();
        in.get();
        return root->symbol;
    }
    // Else we have a regular file.
    HCNode* curr = root;
    while (curr->c0 != nullptr && curr->c1 != nullptr) { // Not a leaf:
        nextByte = (unsigned char) in.get();
        if (nextByte == '0') {
            curr = curr->c0;
        } else if (nextByte == '1'){
            curr = curr->c1;
        } else {
            return 0;
        }
    }
    return curr->symbol;
}

/*int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    auto ht = new HCTree();
    ht->build(vec);
}*/



HCTree::~HCTree() {
    deleteAll(root);
}

void HCTree::deleteAll(HCNode *start) {
    HCNode* curr = start;
    if (curr == nullptr) {
        return;
    }
    deleteAll(curr->c0);
    deleteAll(curr->c1);
    delete curr;
}
