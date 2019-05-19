#include "BitOutputStream.hpp"

/** Send the buffer to the output stream, and clear it */
void BitOutputStream::flush() {
    out.put(buf);  // Write the bitwise buffer to the ostream.
    out.flush(); // Flush the ostream (optional, slower to do it here)
    buf = 0;
    nbits = 0;
}

/** Write the least significant bit of the argument to
 * the bit buffer, and increment the bit buffer index.
 * But flush the buffer first, if it is full.
 */
void BitOutputStream::writeBit(unsigned int bit) {
    // Flush the buffer if full.
    if (nbits == CHAR_BIT) {
        flush();
    }
    // Write the least significant bit of i into the buffer at the current index.
    buf |= bit << nbits;
    // Increment index.
    nbits++;
}

/** Write a (4) byte int in bits */
void BitOutputStream::writeInt(unsigned int num) {
    unsigned int bit;
    for (int i = 0; i < sizeof(int) * CHAR_BIT; i++) {
        bit = (num >> i) & 1;
        writeBit(bit);
    }
}

/** Write a (8) bit symbol in bits */
void BitOutputStream::writeByte(byte symbol) {
    unsigned int bit;
    for (int i = 0; i < CHAR_BIT; i++) {
        bit = (symbol >> i) & 1;
        writeBit(bit);
    }
}

/** Make sure we get the last byte in */
void BitOutputStream::pad() {
    if (nbits == 0) {
        return;
    }
    while (nbits != CHAR_BIT) {
        buf |= 0 << nbits;
        nbits++;
    }
    flush();
}