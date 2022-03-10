#include <bits/stdc++.h>
#include "DecryptorMethods.h"

#ifndef DECRYPTORPROJECT_DECRYPTOR_H
#define DECRYPTORPROJECT_DECRYPTOR_H

class IDecryptor {
public:
    virtual string decrypt(string const &filename) = 0;
};

class BasicDcry: public IDecryptor{
private:
    string DecrTxtM, DecrBlM, chrBl;
    char  chrTxt;
    int nrTxt, nrBl;
    char block[8];
    string storedText, dataText;
public:
    BasicDcry(const string &decrTxtM, const string &decrBlM, char chTxt,
              string chBl, int numTxt, int numBl);

    string decrypt(string const &filename) override;
    void DcryTxt();
    void DcryBl();
    
};

class DecryptorFactory {
public:
    static IDecryptor *makeDecryptor(string const &desc);
};

#endif //DECRYPTORPROJECT_DECRYPTOR_H
