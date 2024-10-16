

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool checkSecret(string secret) {
    for (char c : secret) { //splti up string by char
        if (!isalpha(c)) { //if char isnt alphabetic return false
            return false;
        }
    }
    return true; //valid if all characters are alphabetic or if it's empty
}

string generateKey(string str, string key) {
    string generatedKey;
    int keyIndex = 0;
    
    string keyCheck = key.empty() ? "default" : key; //checks if the secret is empty. If it is, use a default key "default", otherwise use the key (secret)
                                                     //originally, was gonna use plaintext/ciphertext as the default key but that wasnt working
    for (char c : str) { //split up string by char
        if (isalpha(c)) { //checks if char is alphabetic
            generatedKey += keyCheck[keyIndex % keyCheck.size()];
            keyIndex++;
        } else {
            generatedKey += c; //keep nonalphabetic characters
        }
    }

    return generatedKey;
}

//encrypt plaintext
string cipherText(string plain_text, string key) {
    string cipher_text;
    
    for (int i = 0; i < plain_text.size(); i++) { //while i < plaintext size
        char plain_char = plain_text[i]; //iterate through char of plaintext and key
        char key_char = key[i];
        
        if (isalpha(plain_char)) { //alphabetic check
            char base = isupper(plain_char) ? 'A' : 'a'; //checks if the chars are uppercase or lowercase and matches it based on whichever it is
            char key_base = isupper(key_char) ? 'A' : 'a';
            cipher_text += ((plain_char - base + (key_char - key_base))) % 26 + base;
        } else {
            cipher_text += plain_char; //keep special characters as is
        }
    }

    return cipher_text;
}

//decrypt ciphertext
string plainText(string cipher_text, string key) {
    string plain_text;
    
    for (int i = 0; i < cipher_text.size(); i++) { //while i < ciphertext size
        char cipher_char = cipher_text[i]; //iterate through char of plaintext and key
        char key_char = key[i];
        
        if (isalpha(cipher_char)) { //alphabetic check
            char base = isupper(cipher_char) ? 'A' : 'a'; //checks if the chars are uppercase or lowercase and matches it based on whichever it is
            char key_base = isupper(key_char) ? 'A' : 'a';
            plain_text += (cipher_char - base - (key_char - key_base) + 26) % 26 + base;
        } else {
            plain_text += cipher_char; //leave special characters as is
        }
    }

    return plain_text;
}

int main() {
    string plaintext;
    string secret;
    string key;
    string ciphertext;
    
    while (true) {
        string choice;
        cout << "\nPlease make your choice:" << endl;
        cout << "1 - Encrypt the message." << endl;
        cout << "2 - Decrypt the message." << endl;
        cout << "Exit on any other input." << endl;
        getline(cin, choice);

        if (choice == "1") { //encrypting
            cout << "Enter your non-encrypted message: ";
            getline(cin, plaintext);
            cout << "Enter the secret (either an empty value or alphabetic letters): "; //cannot do something like "The City", either leave it empty or be in one word
            getline(cin, secret);

            if (!checkSecret(secret) || (secret.size() < 4 && !secret.empty())) {  //if secret has than 4 letters or if secret contains invalid characters
                cout << "Invalid secret" << endl;
                continue;
            }

            key = generateKey(plaintext, secret);
            ciphertext = cipherText(plaintext, key);
            cout << "Encrypted message: " << ciphertext << endl;

        } else if (choice == "2") {//decrypt
            cout << "Enter your encrypted message: ";
            getline(cin, ciphertext);
            cout << "Enter the secret (either an empty value or alphabetic letters): "; //cannot do something like "The City", either leave it empty or be in one word
            getline(cin, secret);

            if (!checkSecret(secret) || (secret.size() < 4 && !secret.empty())) { //if secret has than 4 letters or if secret contains invalid characters
                cout << "Invalid secret" << endl;
                continue;
            }

            key = generateKey(ciphertext, secret);
            plaintext = plainText(ciphertext, key);
            cout << "Decrypted message: " << plaintext << endl;

        } else {
            cout << "Goodbye";
            //exit
            break;
        }
    }

    return 0;
}
