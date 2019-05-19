#include "BitInputStream.hpp"

/** Fill the buffer, read one byte from the input stream */
void BitInputStream::fill() {
    buf = in.get(); // read one byte from istream to bitwise buffer
    nbits = 0; // No bits have been read from bitwise buffer
}

/** Read the next bit from the bit buffer.
 * Fill the buffer from the input stream first if needed.
 * @return 1 if the bit read is 1, 0 if bit read is 0.
 */
int BitInputStream::readBit() {
    // Fill bitwise buffer if there are no more unread bits.
    if (nbits == CHAR_BIT) {
        fill();
    }
    // Get the next unread bit from the bitwise buffer, increment and return.
    unsigned int nextBit = (buf >> nbits) & 1;
    nbits++;
    return nextBit;
}

/** Read the amount of characters from our bit buffer. */
unsigned int BitInputStream::readInt() {
    unsigned int numCharacters = 0;
    int bit;
    for (int i = 0; i < sizeof(int) * CHAR_BIT; i++) {
        bit = readBit();
        numCharacters |= bit << i;
    }
    return numCharacters;
}

/** Read the next byte from the bit buffer. */
byte BitInputStream::readByte() {
    byte character = 0;
    int bit;
    for (int i = 0; i < CHAR_BIT; i++) {
        bit = readBit();
        character |= bit << i;
    }
    return character;
}