#include<iostream>
#include <string>

using namespace std;

string moveLeft(string num, int shift){
    char copy0 = num[0];
    char copy1 = num[1];
    for(int i=0; i<num.size(); i++){
        if(i+shift >= num.size()){
            num[i] = copy0;
            num[i+1] = copy1;
            return num;
        }
        else num[i] = num[i+shift];
    }
    return num;
}

string dec2bin(unsigned n){
    const int size=sizeof(n)*8;
    std::string res;
    bool s=0;
    for (int a=0;a<size;a++){
        bool bit=n>>(size-1);
        if (bit)
            s=1;
        if (s)
            res.push_back(bit+'0');
        n<<=1;
    }
    if (!res.size())
        res.push_back('0');
    if(res.size() == 1) return "000" + res;
    else if(res.size() == 2) return "00" + res;
    else if(res.size() == 3) return "0" + res;
    return res;
}

int main(){
    //MATRIXES
    int keyStartPermutationTable [64] =
    {
        57,	49,	41,	33,	25,	17,	9, 1,	58,	50,	42,	34,	26,	18,
        10,	2,	59,	51,	43,	35,	27, 19,	11,	3,  60,	52,	44,	36,
        63,	55,	47,	39,	31,	23,	15, 7,	62,	54,	46,	38,	30,	22,
        14,	6,	61,	53,	45,	37,	29, 21,	13,	5,	28,	20,	12,	4
    };

    int keyCpPermutationTable [48] =
    {
        14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
    };

    int startPermutation [64] =
    {
        58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
    };

    int rightPermutation [48] =
    {
        32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
    };

    int rightPermutationEnd [32] =
    {
        16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25
    };

    int sBox [8][4][16]{
        {
            {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
            {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
            {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
            {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
        },{
            {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
            {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
            {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
            {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
        },{
            {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
            {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
            {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
            {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
        },{
            {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
            {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
            {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
            {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
        },{
            {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
            {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
            {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
            {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
        },{
            {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
            {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
            {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
            {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
        },{
            {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
            {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
            {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
            {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
        },{
            {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
            {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
            {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
            {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11},
        }
    };

    int permutationEnd [64] ={
        40,     8,   48,    16,    56,   24,    64,   32,
        39,     7,   47,    15,    55,   23,    63,   31,
        38,     6,   46,    14,    54,   22,    62,   30,
        37,     5,   45,    13,    53,   21,    61,   29,
        36,     4,   44,    12,    52,   20,    60,   28,
        35,     3,   43,    11,    51,   19,    59,   27,
        34,     2,   42,    10,    50,   18,    58,   26,
        33,     1,   41,     9,    49,   17,    57,   25
    };

    //KEYS GENERATOR
    string keyString = "0001001100110100010101110111100110011011101111001101111111110001";
    string keyAfterPermutation;
    string keyLeft;
    string keyRight;
    string keyLeftRight;
    string finalKey [17];

    keyAfterPermutation = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    keyLeft = "xxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    keyRight = "xxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    keyLeftRight = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

    for(int i=0, j=0; i<56; i++){
        keyAfterPermutation[i] = keyString[keyStartPermutationTable[i]-1];
    }

    for(int i=0; i<56; i++){
        if(i<28) keyLeft[i] = keyAfterPermutation[i];
        else keyRight[i-28] = keyAfterPermutation[i];
    }

    for(int r=0; r<17; r++){
        finalKey[r] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

        if(r == 1 || r == 2 || r == 9 || r == 16){
            keyLeft = moveLeft(keyLeft, 1);
            keyRight = moveLeft(keyRight, 1);
        }
        else if(r == 0);
        else{
            keyLeft = moveLeft(keyLeft, 2);
            keyRight = moveLeft(keyRight, 2);
        }

        keyLeftRight = keyLeft + keyRight;

        for(int i=0; i<48; i++){
            finalKey[r][i] = keyLeftRight[keyCpPermutationTable[i]-1];
        }
    }

    //ENCRYPTION
    string messageInput = "0000000100100011010001010110011110001001101010111100110111101111";
    string message = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    string messageLeft = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    string messageRight = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    string messageRightLong = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    string messageRightOutput = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

    for(int i=0; i<64; i++){
        message[i] = messageInput[startPermutation[i]-1];
    }

    for(int i=0; i<64; i++){
        if(i<32) messageLeft[i] = message[i];
        else messageRight[i-32] = message[i];
    }

    for(int r=1; r<17; r++){
        for(int i=0; i<48; i++){
            messageRightLong[i] = messageRight[rightPermutation[i]-1];
        }

        for(int i=0; i<48; i++){
            if((messageRightLong[i] == finalKey[r][i])) messageRightLong[i] = '0';
            else messageRightLong[i] = '1';
        }

        string partMessageRight [8];
        int row, column;
        int res [8];
        int j=0;
        for(int i=0; i<48; i++){
            if(i%6 == 0 && i != 0) j++;
            partMessageRight[j] += messageRightLong[i];
        }

        string messageRightCopy = messageRight;
        messageRight = "";
        for(int i=0; i<8; i++){
            string rowString = "";
            rowString += partMessageRight[i][0];
            rowString += partMessageRight[i][5];
            int row = std::stoi(rowString, nullptr, 2);

            string columnString = "";
            columnString += partMessageRight[i][1];
            columnString += partMessageRight[i][2];
            columnString += partMessageRight[i][3];
            columnString += partMessageRight[i][4];
            int column = std::stoi(columnString, nullptr, 2);

            res[i] = sBox[i][row][column];
            messageRight += dec2bin(res[i]);
        }

        for(int i=0; i<32; i++)messageRightOutput[i] = messageRight[rightPermutationEnd[i]-1];
        messageRight = "";

        for(int i=0; i<32; i++){
            if((messageRightOutput[i] == messageLeft[i])) messageRight += '0';
            else messageRight += '1';
        }
        messageLeft = messageRightCopy;
    }

    string outputMessage = messageLeft + messageRight;
    string finalMessage = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    for(int i=0; i<64; i++){
            finalMessage[i] = outputMessage[permutationEnd[i]-1];
    }
    cout<<"WIADOMOSC:    "<<messageInput<<endl<<"KLUCZ:        "<<keyString<<endl<<"ZASZYFROWANE: "<<finalMessage<<endl;
    return 0;
}
