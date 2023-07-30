#ifndef __PROGTEST__
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <openssl/evp.h>
#include <openssl/rand.h>

// For testing
//#include <bitset>


#endif /* __PROGTEST__ */

bool check_hash(const unsigned char* hashOfGeneratedMsg, int bits)
{
    int i = 0;
    while (bits > 0 && i < 64)
    {
        if (hashOfGeneratedMsg[i] > (0xff >> (bits - 8 >= 0 ? 8 : bits)))
            return true;
        bits -= 8;
        ++i;
    }
    return false;
}


int findHash(int bits, char** message, char** hash)
{
    if (bits > 512 || bits < 0 || message == nullptr || hash == nullptr)
        return 0;

    unsigned char hashOfGeneratedMsg[64];
    unsigned char generatedMsg[64];

    // Initialization of SHA-512
    auto context = EVP_MD_CTX_new();
    if (context == nullptr)
        return 0;
    EVP_MD_CTX_init(context);

    const auto algorithm = EVP_sha512();
    if ( algorithm == nullptr )
    {
        EVP_MD_CTX_free(context);
        return 0;
    }

    size_t msgLen;
    do {
        for (int i = 0; i < 64; ++i)
            generatedMsg[i] = rand() % 256;
        msgLen = sizeof(generatedMsg);
        if ( !EVP_DigestInit_ex(context, algorithm, nullptr) )
        {
            EVP_MD_CTX_free(context);
            return 0;
        }
        if ( !EVP_DigestUpdate(context, generatedMsg, msgLen) )
        {
            EVP_MD_CTX_free(context);
            return 0;
        }
        if ( !EVP_DigestFinal_ex(context, hashOfGeneratedMsg, nullptr) )
        {
            EVP_MD_CTX_free(context);
            return 0;
        }
    } while (check_hash(hashOfGeneratedMsg, bits));

    EVP_MD_CTX_free(context);

//      For testing

//    std::bitset<8> binary1(hashOfGeneratedMsg[0]);
//    std::bitset<8> binary2(hashOfGeneratedMsg[1]);
//    std::bitset<8> binary3(hashOfGeneratedMsg[2]);
//    std::bitset<8> binary4(hashOfGeneratedMsg[3]);
//
//    std::cout << "Binary representation - " << binary1.to_string() << ' ' << binary2.to_string() << ' ' << binary3.to_string() << ' ' << binary4.to_string() << '\n';


    char* msgHex = (char*) malloc(2 * msgLen + 1);
    char* hashHex = (char*) malloc(2 * 64 + 1);

    for (size_t i = 0; i < msgLen; i++)
        sprintf(&msgHex[2 * i], "%02x", generatedMsg[i]);
    msgHex[2 * msgLen] = '\0';

    for (int i = 0; i < 64; i++)
        sprintf(&hashHex[2 * i], "%02x", hashOfGeneratedMsg[i]);
    hashHex[2 * 64] = '\0';

    *message = msgHex;
    *hash = hashHex;

    return 1;
}

int findHashEx (int bits, char ** message, char ** hash, const char * hashFunction) {
    /* TODO or use dummy implementation */
    return 1;
}

#ifndef __PROGTEST__

int checkHash(int bits, char * hexString) {
    return 1;
}

int main (void) {
    char * message, * hash;

    findHash(21, &message, &hash);
    free(message);
    free(hash);

//    assert(findHash(0, &message, &hash) == 1);
//    assert(message && hash && checkHash(0, hash));
//    free(message);
//    free(hash);
//    assert(findHash(1, &message, &hash) == 1);
//    assert(message && hash && checkHash(1, hash));
//    free(message);
//    free(hash);
//    assert(findHash(2, &message, &hash) == 1);
//    assert(message && hash && checkHash(2, hash));
//    free(message);
//    free(hash);
//    assert(findHash(3, &message, &hash) == 1);
//    assert(message && hash && checkHash(3, hash));
//    free(message);
//    free(hash);
//    assert(findHash(-1, &message, &hash) == 0);
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

