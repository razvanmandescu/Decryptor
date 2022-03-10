#include "Decryptor.h"

IDecryptor *DecryptorFactory::makeDecryptor (string const &desc) {
    string DecrTxtM, DecrBlm, chrBl = "g";
    char chrTxt = 'g';
    int nrTxt = -1, nrBl = -1;
    stringstream is(desc);
    string cuvxd;

    if (is >> cuvxd) {
        DecrTxtM = cuvxd;

        if (cuvxd == "ROTATIE" || cuvxd == "CEZAR")
            is >> nrTxt;
        else if (cuvxd == "XOR") is >> chrTxt;
    }

    if (is >> cuvxd) {
        DecrBlm = cuvxd;

        if (cuvxd == "ROTATIE" || cuvxd == "CEZAR")
            is >> nrBl;
        else if (cuvxd == "XOR") is >> chrBl;
    }

    return new BasicDcry(DecrTxtM, DecrBlm, chrTxt, chrBl, nrTxt,
                         nrBl);
}

BasicDcry::BasicDcry(const string &decrTxtM, const string &decrBlM,
                     char chTxt, string chBl, int numTxt,
                     int numBl) : DecrTxtM(decrTxtM), DecrBlM(decrBlM),
                                            chrTxt(chTxt), chrBl(chBl),
                                            nrTxt(numTxt), nrBl(numBl) {}

void copyf (char (&block)[8], char (&text)[1024], int idx){
    for(int i = 0; i < 8 ; i++){
        block[i] = text[idx + i];
    }
}

string strconvert(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}


string BasicDcry::decrypt(const string &filename) {

    ifstream fin(filename, ios::binary);

    string decryptedinfo;
    char text[1024];
    int indx = 0;

    fin.read(text, sizeof(text));
    while(true){
        copyf(block, text, indx);
        dataText = strconvert(block, 8);

        DcryBl();

        for(int i = 0; i < 6 ; i++){
            if(block[i] != '\0'){
                storedText += block[i];
            }
        }
        if(block[6]*8 > 0){
            indx = (int)block[6] * 8;
        } else break;
    }

    DcryTxt();

    return storedText;
}

void BasicDcry::DcryBl() {

    string data;
    if (DecrBlM == "NIMIC") return ;

    if (DecrBlM == "ROTATIE") {
        IDecryptorModes *decryptorMode = new Rotatie(nrBl, TxtToBin(dataText));
        data = decryptorMode->DecrBlk();
    }

    if (DecrBlM == "INVERSARE") {
        IDecryptorModes *decryptorMode = new Invers(dataText);
        data = decryptorMode->DecrBlk();
    }

    if (DecrBlM == "XOR"){
        IDecryptorModes *decryptorMode = new XOR(chrBl, dataText);
        data = decryptorMode->DecrBlk();
    }

    for (int i = 0; i < 8;i++){
        block[i] = data[i];
    }
}

void BasicDcry::DcryTxt() {
    if (DecrTxtM == "NIMIC") return ;

    if (DecrTxtM == "ROTATIE") {
        IDecryptorModes *decryptorMode = new Rotatie(nrTxt, storedText);
        storedText = decryptorMode->DecrTxt();
    }

    if (DecrTxtM == "CEZAR") {
        IDecryptorModes *decryptorMode = new Cezar(nrTxt, storedText);
        storedText = decryptorMode->DecrTxt();
    }

    if (DecrTxtM == "XOR"){
        IDecryptorModes *decryptorMode = new XOR(chrTxt, storedText);
        storedText = decryptorMode->DecrTxt();
    }
}

char XorBlocks(string text, int number){
    char val;
    val = text[number];
    number += 8;
    while (number < 64){
        char a = text[number];
        val = val ^ a;
        number += 8;
    }

    if (val == '\000')
        val = '0';

    if (val == '\001')
        val = '1';

    return val;
}

