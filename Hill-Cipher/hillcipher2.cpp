#include <iostream>
#include <windows.h>
using namespace std;

void keyInput(int key[][3]){
    int cons = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << "Masukkan key[" << i+1 << "][" << j+1 << "] : ";
            cin >> key[i][j];
        }
    }}

void keyOutput(int key[][3]){
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << key[i][j] << "  ";}
        cout << endl;
    }
}


string Encrypt(int key[][3], string text){
    // ascii dec range 65 ... 90 (ascii for A to Z)
    // ascii dec range 97 ... 122 (ascii for a to z)
    string encrypted;
    int con[3];
    int con2 = 0;
    int z = 0;
    if(text.length()%3 == 0){
        z = text.length()/3;
    }else{
        z = (text.length()/3) + 1;
    }
    for(int i = 0; i < z; i++){
        con[0] = 23;con[1] = 23;con[2] = 23;
        for(int j = 0; j < 3; j++){ // alphabet -> ASCII number
            if((int)text[j + (i*3)] >= 97 && (int)text[j + (i*3)] <= 122) {  // alfabet kecil
                con[j] = (int)text[j + (i*3)] - 97;
                cout << text[j + (i*3)] << " = " << con[j] << endl;
            }else if((int)text[j + (i*3)] >= 65 && (int)text[j + (i*3)] <= 90) {  // alfabet kapital
                con[j] = (int)text[j + (i*3)] - 65;
            }else if(isblank(text[j + (i*3)])){
                con[j] = 23;
            }}
        for(int j = 0; j < 3; j++){// Calculation
            cout << (key[j][0]*con[0] + key[j][1]*con[1] + key[j][2]*con[2])%26 << "    ";
            con2 = ((key[j][0]*con[0] + key[j][1]*con[1] + key[j][2]*con[2])%26) + 65;
            encrypted += (char)con2;
        }
        cout << endl;
        
    }
    return encrypted;}

// string Decrypt(int key[][3], string text){
//     // ascii dec range 65 ... 90 (ascii for A to Z)
//     // ascii dec range 97 ... 122 (ascii for a to z)
//     string decrypted;
//     int con[3];
//     int con2 = 0;
//     int inv[3][3];



//     for(int i = 0; i < text.length()/3; i++){
//         for(int j = 0; j < 3; j++){ // alphabet -> ASCII number
//             if((int)text[j + (i*3)] >= 97 && (int)text[j + (i*3)] <= 122) {  // alfabet kecil
//                 con[j] = (int)text[j + (i*3)] - 97;
//                 cout << text[j + (i*3)] << " = " << con[j + (i*3)] << endl;
//             }else if((int)text[j + (i*3)] >= 65 && (int)text[j + (i*3)] <= 90) {  // alfabet kapital
//                 con[j] = (int)text[j + (i*3)] - 65;
//             }}
//         for(int j = 0; j < 3; j++){// Calculation
//             cout << (key[j][0]*con[0] + key[j][1]*con[1] + key[j][2]*con[2])%26 << "    ";
//             con2 = ((key[j][0]*con[0] + key[j][1]*con[1] + key[j][2]*con[2])%26) + 65;
//             decrypted += (char)con2;}
//     }
//     return decrypted;
// }
void elCheck(int key[][3], string text){
    int det = 0;
    det += (key[0][0]*key[1][1]*key[2][2]);
    det += (key[0][1]*key[1][2]*key[2][0]);
    det += (key[0][2]*key[1][0]*key[2][1]);
    det -= (key[0][2]*key[1][1]*key[2][0]);
    det -= (key[0][1]*key[1][0]*key[2][2]);
    det -= (key[0][0]*key[1][2]*key[2][1]);
    int result = min(det, 26);
    while (result > 0) {
        if (det % result == 0 && 26 % result == 0) {
            break;
        }
        result--;
    }
    cout << "\nDeterminant mod 26 = " << result << endl;
    if(result != 1){
        cout << "Matrix is not inversible mod 26\n";
    }else{
        cout << "Can be Decrypted\n";
        // Decrypt(key, text);
    }
}
int main(){
    string text;
    int resp;
    int key[3][3];

    cout << "\nMasukkan text : ";
    getline(cin, text);

    cout << "\nMasukkan kunci : \n";
    keyInput(key);

    cout << "Hasil Enkripsi : " << endl << Encrypt(key, text) << endl;
    elCheck(key, text);
    // cout << Decrypt(key, text);
    // keyOutput(key);
}