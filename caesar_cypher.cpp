// -------------------------------------------------------------------------------
// Name:        Graph Analysis
//
// Author:      Julian Gherghel
// -------------------------------------------------------------------------------
//
// Caesar Cypher implementation in C++
// both encoding and decoding. The key is an integer from 1 to 25. This cipher 
// rotates the letters of the alphabet (A to Z). The encoding replaces each letter 
// with the 1st to 25th next letter in the alphabet (wrapping Z to A). So key 2
// encrypts "HI" to "JK", but key 20 encrypts "HI" to "BC". This simple 
// "monoalphabetic substitution cipher" provides almost no security, because an 
// attacker who has the encoded message can either use frequency analysis to 
// guess the key, or just try all 25 keys.

#include <iostream>
#include <sstream>

const std::string encrypt ( const std::string plainText, int key )
{
    std::stringstream cipherStream;
    int x;
    for ( auto &c : plainText ) {
        x = c + key;
        if ( c >= 'A' && c <= 'Z' ) {
            x =  ( x  > 'Z') ? ( 'A' + (x - 1) - 'Z') : x ;

        } else if ( c >= 'a' && c <= 'z' ) {
            x =  ( x  > 'z') ? ( 'a' + (x - 1) - 'z') : x ;
        }
        cipherStream << char(x);
    }
    return cipherStream.str();
}

const std::string decrypt ( const std::string cipherText, int key )
{
    std::stringstream plainStream;
    int x;
    for ( auto &c : cipherText ) {
        x = c - key;
        if ( c >= 'A' && c <= 'Z' ) {
            x =  ( x  < 'A') ? ( 'Z' -('A'- (x + 1))) : x ;

        } else if ( c >= 'a' && c <= 'z' ) {
            x =  ( x  < 'a') ? ( 'z' - ('a' - (x + 1))) : x ;
        }
        plainStream << char(x);
    }
    return plainStream.str();
}

int main()
{
    std::cout << "----Caesar Cipher ----\n"
              << "What would you like to do?\n"
              << "1. Encrypt a plain text\n"
              << "2. Decrypt a cipher text\n"
              << "Enter a choice:";
    int choice, key;
    std::string plainText, cipherText;
    std::cin >> choice;
    switch(choice) {
        case 1 :
        {
            std::cout << "Enter plain text:";
            std::cin >> plainText;
            std::cout << "Enter key ( 1 - 25 ):";
            std::cin >> key;
            cipherText = encrypt(plainText, key);
            std::cout << "Plain Text: " << plainText
                      << " ---> "
                      << "Cipher Text: " << cipherText
                      << std::endl;
            break;
        }
        case 2 :
        {
            std::cout << "Enter cipher text:";
            std::cin >> cipherText;
            std::cout << "Enter key ( 1 - 25 ):";
            std::cin >> key;
            plainText = decrypt(cipherText, key);
            std::cout << "Cipher Text: " << cipherText
                      << " ---> "
                      <<  "Plain Text: " << plainText
                      << std::endl;
            break;
        }
        default:
            std::cout << "Invalid Choice\n";
            break;
    }

    return 0;
}