#include "HCNode.hpp"
#include <climits>

class BitOutputStream {
private:
    byte buf; // One byte buffer of bits.
    int nbits; // How many bits have been written to buf.
    ostream& out; // Reference to the output stream to use.

public:
    /** Constructor, clear buffer and bit counter. */
    BitOutputStream(ostream & os) : out(os), buf(0), nbits(0) {}

    /** Send the buffer to the output stream, and clear it */
    void flush();

    /** Write the least significant bit of the argument to
     * the bit buffer, and increment the bit buffer index.
     * But flush the buffer first, if it is full.
     */
    void writeBit(unsigned int bit);

    /** Write a (4) byte int in bits */
    void writeInt(unsigned int num);

    /** Write a (8) bit symbol in bits */
    void writeByte(byte symbol);

    /** Make sure we get the last byte in */
    void pad();
};