#include <iostream>
#include <windows.h>
using namespace std;

void keyInput(int key[][2]){
    int cons = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cout << "Masukkan key[" << i+1 << "][" << j+1 << "] : ";
            cin >> key[i][j];
        }
    }}

void keyOutput(int key[][2]){
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cout << key[i][j] << "  ";}
        cout << endl;
    }
}
int** inverse(int key[][2]){
    int inv[2][2];int invKey[2][2];
    inv[0][0]=(int)(key[1][1]);
	inv[0][1]=(int)((-1) * key[0][1]);
	inv[1][0]=(int)((-1) * key[1][0]);
	inv[1][1]=(int)(key[0][0]);
    int det = (key[0][0]*key[1][1]) - (key[0][1]*key[1][0]);
    int detInv = 0;
    int flag = 0;
    
    for (int i = 0; i < 26; i++){
        flag = (det * i) % 26;
        if (flag < 0){
        	flag = flag + 26;
		}
        if (flag == 1){
            detInv = i;
        }
    }
	for(int i=0 ; i<2 ; i++)
		for(int j=0 ; j<2 ; j++){
			if ( inv[i][j] < 0 ) {
				int tempNumber = inv[i][j]*detInv;
			    invKey[i][j] = ((tempNumber%26) + 26)%26;
			}
			else{
				invKey[i][j] = (inv[i][j]*detInv%26);
			}
            cout << "test= " << invKey[i][j] << endl;
		}
    
    int** array2D = 0;
      array2D = new int*[2];
      for (int h = 0; h < 2; h++){
            array2D[h] = new int[2];
            for (int w = 0; w < 2; w++){
                  array2D[h][w] = invKey[h][w];
            }
      }   
    return array2D;
}

string Encrypt(int key[][2], string text){
    // ascii dec range 65 ... 90 (ascii for A to Z)
    // ascii dec range 97 ... 122 (ascii for a to z)
    string encrypted;
    int con[2];
    int con2 = 0;
    int z = 0;
    if(text.length()%2 == 0){
        z = text.length()/2;
    }else{
        z = (text.length()/2) + 1;
    }
    for(int i = 0; i < z; i++){
        con[0] = 23;con[1] = 23;
        for(int j = 0; j < 2; j++){ // alphabet -> ASCII number
            if((int)text[j + (i*2)] >= 97 && (int)text[j + (i*2)] <= 122) {  // alfabet kecil
                con[j] = (int)text[j + (i*2)] - 97;
            }else if((int)text[j + (i*2)] >= 65 && (int)text[j + (i*2)] <= 90) {  // alfabet kapital
                con[j] = (int)text[j + (i*2)] - 65;
            }else if(isblank(text[j + (i*2)])){
                con[j] = 23;
            }}
        for(int j = 0; j < 2; j++){// Calculation
            con2 = ((key[j][0]*con[0] + key[j][1]*con[1])%26) + 65;
            encrypted += (char)con2;
        }
    }
    return encrypted;}

string Decrypt(int key[][2], string text){
    // ascii dec range 65 ... 90 (ascii for A to Z)
    // ascii dec range 97 ... 122 (ascii for a to z)
    string decrypted;
    int con[2];
    int con2 = 0;
    
    int** invKey = inverse(key);
    int z = 0;
    if(text.length()%2 == 0){
        z = text.length()/2;
    }else{
        z = (text.length()/2) + 1;
    }
    for(int i = 0; i < z; i++){
        con[0] = 23;con[1] = 23;
        for(int j = 0; j < 2; j++){ // alphabet -> ASCII number
            if((int)text[j + (i*2)] >= 97 && (int)text[j + (i*2)] <= 122) {  // alfabet kecil
                con[j] = (int)text[j + (i*2)] - 97;
            }else if((int)text[j + (i*2)] >= 65 && (int)text[j + (i*2)] <= 90) {  // alfabet kapital
                con[j] = (int)text[j + (i*2)] - 65;
            }else if(isblank(text[j + (i*2)])){
                con[j] = 23;
            }}
        for(int j = 0; j < 2; j++){// Calculation
            con2 = ((invKey[j][0]*con[0] + invKey[j][1]*con[1])%26) + 65;
            decrypted += (char)con2;
        }
        
    }
    return decrypted;}



void elCheck(int key[][2], string text){
    int det = 0;
    det += (key[0][0]*key[1][1]);
    det -= (key[0][1]*key[1][0]);
    int result = min(det%26, 26);
    while (result > 0) {
        if (det % result == 0 && 26 % result == 0) {
            break;
        }
        result--;
    }
    cout << "\nGCD 26 = " << result << endl;
    if(result != 1){
        cout << "Matrix is not inversible mod 26\n";
    }else{
        cout << "Can be Decrypted\n";
        cout << "Hasil Enkripsi : " << endl << Decrypt(key, text) << endl;
    }}
void keySearch(int key[][2], string text, string text2){
    int con[2][2];
    int con2[2][2];
    int z = 0;
    if(text.length()%2 == 0){
        z = text.length()/2;
    }else{
        z = (text.length()/2) + 1;
    }
    for(int i = 0; i < 2; i++){
        con[0][0] = 23;con[1][0] = 23;con[0][1] = 23;con[1][1] = 23;
        for(int j = 0; j < 2; j++){ // alphabet -> ASCII number
            if((int)text[j + (i*2)] >= 97 && (int)text[j + (i*2)] <= 122) {  // alfabet kecil
                con[j][i] = (int)text[j + (i*2)] - 97;
            }else if((int)text[j + (i*2)] >= 65 && (int)text[j + (i*2)] <= 90) {  // alfabet kapital
                con[j][i] = (int)text[j + (i*2)] - 65;
            }else if(isblank(text[j + (i*2)])){
                con[j][i] = 23;
            }
    }}
    for(int i = 0; i < 2; i++){
        con2[0][0] = 23;con2[1][0] = 23;con2[0][1] = 23;con2[1][1] = 23;
        for(int j = 0; j < 2; j++){ // alphabet -> ASCII number
            if((int)text2[j + (i*2)] >= 97 && (int)text2[j + (i*2)] <= 122) {  // alfabet kecil
                con2[j][i] = (int)text2[j + (i*2)] - 97;
            }else if((int)text2[j + (i*2)] >= 65 && (int)text2[j + (i*2)] <= 90) {  // alfabet kapital
                con2[j][i] = (int)text2[j + (i*2)] - 65;
            }else if(isblank(text2[j + (i*2)])){
                con2[j][i] = 23;
            }}
    }
    int** conI = inverse(con);
    int con3[2][2];
    con3[0][0] = ((con2[0][0]*conI[0][0] + con2[0][1]*conI[1][0])%26);
    
    con3[0][1] = ((con2[0][0]*conI[0][1] + con2[0][1]*conI[1][1])%26);
    con3[1][0] = ((con2[1][0]*conI[0][0] + con2[1][1]*conI[1][0])%26);
    con3[1][1] = ((con2[1][0]*conI[0][1] + con2[1][1]*conI[1][1])%26);

    keyOutput(con3);
}
int main(){
    string text;string text2;
    int resp = 0;
    int key[2][2];

    cout << "\nMenu : ";
    cout << "\n1. Enkripsi text ";
    cout << "\n2. Dekripsi text ";
    cout << "\n3. Cari Key ";
    cin >> resp;
    switch(resp) {
        case 1:
            cout << "\nMasukkan text : ";
            cin >> text;

            cout << "\nMasukkan kunci : \n";
            keyInput(key);

            cout << "Hasil Enkripsi : " << endl << Encrypt(key, text) << endl;
            break;
        case 2:
            cout << "\nMasukkan text : ";
            cin >> text;

            cout << "\nMasukkan kunci : \n";
            keyInput(key);

            elCheck(key, text);
            break;
        case 3:
            cout << "\nMasukkan text sebelum enkripsi: ";
            cin >> text;

            cout << "\nMasukkan text setelah enkripsi: ";
            cin >> text2;

            keySearch(key, text, text2);
            break;
        default:
            cout << "Respon tidak sesuai";
}
}