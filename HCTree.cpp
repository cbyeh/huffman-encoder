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
    while (q.size() > 1) {
        n0 = q.top();
        q.pop();
        n1 = q.top();
        q.pop();
        root = new HCNode(n0->count + n1->count, '\0');
        if (n0->c0 == nullptr && n0->c1 == nullptr) {
            leaves[n0->symbol] = n0;
        }
        if (n1->c0 == nullptr && n1->c1 == nullptr) {
            leaves[n1->symbol] = n1;
        }
        root->c0 = n0;
        root->c1 = n1;
        q.push(root);
    }
    // Get the codes for our leaves.
    HCNode* curr;
    HCNode* prev;
    for (HCNode* leaf : leaves) {
        string code;
        curr = leaf;
        while (curr->p != nullptr) {
            prev = curr;
            curr = curr->p;
            if (curr->c0 == prev) {
                code.insert(0, "0"); // Prepend.
            } else {
                code.insert(0, "1");
            }
        }
        codes[leaf->symbol] = code;
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
    out << codes[symbol];
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

}

/*int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    auto ht = new HCTree();
    ht->build(vec);
}*/



HCTree::~HCTree() {

}
