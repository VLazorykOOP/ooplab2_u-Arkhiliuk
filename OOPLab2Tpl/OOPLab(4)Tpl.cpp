#include <bitset>
#include <cstring>
#include <iostream>

bool getNePar(int num) {
  bool res = false;
  num >>= 1;
  for (int i = 0; i < 15; i += 2) {
    if ((num >> i) & 1) {
      res = !res;
    }
  }
  return res;
}

bool getPar(int num) {
  bool res = false;
  for (int i = 0; i < 15; i += 2) {
    if ((num >> i) & 1) {
      res = !res;
    }
  }
  return res;
}

int main() {
  char words[100][3];
  char inputWord[3];
  int encrypted[100];
  int N = 0;
  std::cout << "Input \"q\" to stop" << std::endl;
  do {
    std::cout << "Input word (max 2 letters): ";
    std::cin >> inputWord;
    strncpy(words[N++], inputWord, 2);
    words[N - 1][2] = '\0';
    std::cout << "You entered: " << words[N - 1] << std::endl;
    encrypted[N - 1] = 0;
   // std::cout << inputWord[0] << std::endl;
    std::cout << std::bitset<32>(inputWord[0]) << std::endl;
    encrypted[N - 1] |= inputWord[0];
    std::cout << std::bitset<32>(encrypted[N - 1]) << std::endl;
    encrypted[N - 1] <<= 8;
    std::cout << std::bitset<32>(encrypted[N - 1]) << std::endl;
    encrypted[N - 1] |= inputWord[1];
    std::cout << std::bitset<32>(encrypted[N - 1]) << std::endl;
    bool par = getPar(encrypted[N - 1]);
    bool nepar = getNePar(encrypted[N - 1]);
    encrypted[N - 1] <<= 1;
    encrypted[N - 1] |= nepar;
    encrypted[N - 1] <<= 1;
    encrypted[N - 1] |= par;
  } while (inputWord[0] != 'q');

  for (int i = 0; i < N; i++) {
    std::cout << "Word: " << words[i] << std::endl;
    std::cout << "Bitset: " << std::bitset<32>(encrypted[i]) << std::endl;
    bool par = encrypted[i] & 1;
    bool nepar = encrypted[i] >> 1 & 1;
    char second = encrypted[i] >> 2 & 255;
    std::cout << "Decrypted second char: " << std::bitset<8>(second)
              << std::endl;
    char first = encrypted[i] >> 10 & 255;
    std::cout << "Decrypted first char: " << std::bitset<8>(first) << std::endl;

    std::cout << "Decrypted: " << first << second << std::endl;
    bool checkPar = getPar(encrypted[i] >> 2);
    bool checkNePar = getNePar(encrypted[i] >> 2);
    if (par != checkPar)
      std::cout << "Par bit not matched" << std::endl;
    if (nepar != checkNePar)
      std::cout << "NePar bit not matched" << std::endl;
  }

  return 0;
}