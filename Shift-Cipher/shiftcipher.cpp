#include <iostream>
#include<windows.h>
using namespace std;


// ascii dec range 97 ... 122 (ascii for a to z)
string Encrypt(string text, int key) {
    string encrypted;

    for(int i=0; i< text.length(); i++) {
        int indexEncrypted;

        if((int)text[i] == 32) {
            indexEncrypted = (int)text[i];
        }else if((int)text[i] >= 97 && (int)text[i] <= 122) {  // alfabet kecil
            indexEncrypted = (int)text[i] + key;
            if(indexEncrypted > 122) {
                indexEncrypted -= 26;
            }
        }else if((int)text[i] >= 65 && (int)text[i] <= 90) {  // alfabet kapital
            indexEncrypted = (int)text[i] + key;
            if(indexEncrypted > 90) {
                indexEncrypted -= 26;
            }
        }
        encrypted += (char)indexEncrypted;
    }

    return encrypted;
}

// ascii dec range 32...126 
string Decrypt(string text, int key) {
    string decrypted;

    for(int i=0; i< text.length(); i++) {
        int indexDecrypted;

        if((int)text[i] == 32) {
            indexDecrypted = (int)text[i];
        }else if((int)text[i] >= 97 && (int)text[i] <= 122) {  // alfabet kecil
            indexDecrypted = (int)text[i] - key;
            if(indexDecrypted < 97) {
                indexDecrypted += 26;
            }
        }else if((int)text[i] >= 65 && (int)text[i] <= 90) {  // alfabet kapital
            indexDecrypted = (int)text[i] - key;
            if(indexDecrypted < 65) {
                indexDecrypted += 26;
            }
        }
        decrypted += (char)indexDecrypted;
    }

    return decrypted;
}

int main() {
    string text;
    int key;

    cout << "\nMasukkan text : ";
    getline(cin, text);

    cout << "\nMasukkan kunci : ";
    cin >> key;

    cout << "\n>> Encrypted Text : ";
    cout << Encrypt(text, key) << endl;// x + key

    cout << "\n>> Decrypted Text : ";
    cout << Decrypt(text, key) << endl;// x - key

    cout << Decrypt(Encrypt(text, key), key) << endl;// Hasil setelah enkripsi lalu didekripsi

}