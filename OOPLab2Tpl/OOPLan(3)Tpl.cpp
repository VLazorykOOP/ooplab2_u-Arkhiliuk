#include <iostream>
#include <fstream>
#include <bitset>
#include <cstring>

using namespace std;

struct CharBit {
    short nomerRyadka : 2;
    short pos : 5;
    char ascii : 8;
    bool parity : 1;
};

bool parityBit(short num) {
    bool result = false;
    for (int i = 1; i < 14; i++) {
        if ((num >> i) & 1)
            result = !result;
    }
    return result;
}

int main() {
    cout << "1. Encode.\n2. Decode.\nChoose: ";
    int choose = 0;
    cin >> choose;
    switch (choose) {
    case 1: {
        char a[4][32];
        CharBit result[4][32];
        cin.ignore(32, '\n');
        for (int i = 0; i < 4; i++) {
            cin.getline(a[i], 32);
        }
        for (int i = 0; i < 4; i++) {
            if (strlen(a[i]) < 32) {
                for (int c = strlen(a[i]); c < 32; c++) {
                    a[i][c] = ' ';
                }
                a[i][31] = '\0';
            }
        }
        for (int i = 0; i < 4; i++) {
            cout << a[i] << ";" << endl;
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 32; j++) {
                short res = 0;
                result[i][j].ascii = a[i][j];
                result[i][j].nomerRyadka = i;
                result[i][j].pos = j;
                res |= result[i][j].nomerRyadka;
                res = res << 5;
                res |= result[i][j].pos;
                res = res << 8;
                res |= result[i][j].ascii;
                res = res << 1;
                result[i][j].parity = parityBit(res);
                res |= result[i][j].parity;
                cout << bitset<16>(res) << endl;


            }
        }
        ofstream resBinFile("/Users/admin/Documents/oop/lab2/lab2/out", ios::out | ios::binary);
        resBinFile.write((char*)&result, (4 * 32) * sizeof(CharBit));
    } break;
    case 2: {
        CharBit fromBinary[4][32];
        char result[4][32];
        std::ifstream input("/Users/admin/Documents/oop/lab2/lab2/out", ios::binary);
        input.read((char*)&fromBinary, 4 * 32 * sizeof(CharBit));
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 32; j++) {
                bool readParityBit = fromBinary[i][j].parity;
                char letter = fromBinary[i][j].ascii;
                int readRyadok = fromBinary[i][j].nomerRyadka;
                if (readRyadok != i) {
                    cout << "String position not matched" << endl;
                }
                int posSymbol = fromBinary[i][j].pos;
                if (posSymbol != j) {
                    cout << "Position symbol not matched" << endl;
                }
                cout << "Letter: " << letter << endl;
                result[i][j] = letter;
                short res = 0;
                res |= fromBinary[i][j].nomerRyadka;
                res = res << 5;
                res |= fromBinary[i][j].pos;
                res = res << 8;
                res |= fromBinary[i][j].ascii;
                res = res << 1;
                res |= fromBinary[i][j].parity;
                if (parityBit(res) != readParityBit) {
                    cout << "Parity bits not matched" << endl;
                }
                cout << bitset<16>(res) << endl;
            }

            cout << endl;
        }
        cout << "Result:" << endl;
        for (int i = 0; i < 4; i++) {
            cout << result[i] << ";" << endl;
        }
    } break;
    default: {
        cout << "Invalid input\n";
        return -1;
    }
    }
    return 0;
}
