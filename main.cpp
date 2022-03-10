#include <bits/stdc++.h>
#include "Decryptor.h"
using namespace std;

int main() {
    string line;
    getline(cin, line);

    IDecryptor *decryptor = DecryptorFactory::makeDecryptor(line);

    string filename;
    cin>> filename;

    cout<<decryptor->decrypt(filename);

    return 0;
}