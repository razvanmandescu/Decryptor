#include "DecryptorMethods.h"

Rotatie::Rotatie(int nrRot, const string &text) : nrRot(nrRot), txt1(text) {}

Cezar::Cezar(int red, const string &text) : reduces(red), txt2(text) {}

string Rotatie::DecrTxt() {
    rotate(txt1.begin(), txt1.begin() + nrRot, txt1.end());

    return txt1;
}

string Rotatie::DecrBlk() {
    rotate(txt1.begin(), txt1.begin() + nrRot, txt1.end());

    return BinToStr(txt1);
}

const string &Rotatie::getText() const {
    return txt1;
}

string Cezar::DecrTxt() {

    string rez;
    for (int i = 0; i < txt2.length(); i++) {
        if ((txt2[i] >= 'A' && txt2[i] <= 'Z') || (txt2[i] >= 'a' && txt2[i] <= 'z'))
            if (isupper(txt2[i]))
                rez += char(int(txt2[i] - reduces + 26 - 65) % 26 + 65);
            else
                rez += char(int(txt2[i] + 26 - reduces - 97) % 26 + 97);
        else rez += txt2[i];
    }

    return rez;
}

string Cezar::DecrBlk() {
    return "sgihdufci";
}

const string &Cezar::getText() const {
    return txt2;
}

XOR::XOR(char ch1, const string &text) : chr(ch1), txt3(text) {}

string XOR::DecrTxt() {
    string rettxt = txt3;

    for (int i = 0; i < txt3.size(); i++) {
        rettxt[i] = txt3[i] ^ chr;
    }

    return rettxt;
}

string returnSegment(int ix, int keyx, string binary){
    string toret;

    for (int i = ix; i < ix + keyx; i++)
        toret.push_back(binary[i]);

    return toret;
}

string xorfstr(string a, string b, int n){
    string ans = "";

    for (int i = 0; i < n; i++)
    {
        if (a[i] == b[i])
            ans += "0";
        else
            ans += "1";
    }

    return ans;
}

string XOR::DecrBlk() {
    string bin = TxtToBin(txt3);
    int key = chr1.size();
    string dcrinf;

    for (int i = 0; i < 64 / key; i++){
        string segm = returnSegment(i * key, key, bin);
        dcrinf.append(xorfstr(segm, chr1, key));
    }

    return BinToStr(dcrinf);
}

XOR::XOR(const string &character1, const string &text) : chr1(character1), txt3(text) {}

Invers::Invers(const string &text) : text(text) {}

string Invers::DecrTxt() {
    return "...";
}

string Invers::DecrBlk() {
    string binary = TxtToBin(text);
    reverse(binary.begin(), binary.end());

    return BinToStr(binary);
}
