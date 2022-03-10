#include <bits/stdc++.h>
using namespace std;

#ifndef DECRYPTORPROJECT_DECRYPTORMODES_H
#define DECRYPTORPROJECT_DECRYPTORMODES_H

static string BinToStr(string binary){

    stringstream sstream(binary);
    string op;

    while(sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        op += c;
    }

    return op;
}

static string TxtToBin(string cuv) {
    string binstr = "";

    for (char& _char : cuv) {
        binstr +=bitset<8>(_char).to_string();
    }

    return binstr;
}

class IDecryptorModes {
public:
    virtual string DecrTxt() = 0;
    virtual string DecrBlk() = 0;
};

class Rotatie: public IDecryptorModes {
private:
    int nrRot;
    string txt1;
public:
    Rotatie(int nrRot, const string &text);

    string DecrTxt();
    string DecrBlk();

    const string &getText() const;
};

class Cezar: public IDecryptorModes  {
private:
    int reduces;
    string txt2;
public:
    Cezar(int red, const string &text);

    string DecrTxt();
    string DecrBlk();

    const string &getText() const;
};

class XOR: public IDecryptorModes {
private:
    char chr;
    string chr1;
    string txt3;
public:
    XOR(char ch1, const string &text);

    XOR(const string &character1, const string &text);

    string DecrTxt();
    string DecrBlk();
};

class Invers: public IDecryptorModes{
private:
    string text;
public:
    Invers(const string &text);

    string DecrTxt();
    string DecrBlk();
};

#endif //DECRYPTORPROJECT_DECRYPTORMODES_H
