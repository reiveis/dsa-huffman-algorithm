#include <iostream>
#include <fstream>
#include "headers/Huffman/Huffman.h"

using namespace std;

int main() {
    Huffman huffmanAlgorithm = Huffman();

    bool quitOp = false;
    int choice;
    string data, path;
    while(!quitOp){
        cout << "===HUFFMAN ENCODING AND DECODING===" << endl;
        cout
            << "\tOptions" << endl
            << "\t1.\tEncode a message" << endl
            << "\t2.\tDecode a message" << endl
            << "\t3.\tHow to use" << endl
            << "\t4.\tExit Program" << endl;
        cout << "\tChoose an option :=";
        cin >> choice;

        switch(choice){
            case 1:
                cout << endl << "\tEncode a message/file into Huffman Code" << endl;
                cout
                    << endl << "\tWould you like to input your message through the terminal"
                    << endl << "\tor through a file?"
                    << endl << "\t1. Terminal\n\t2. File Input\n\tChoose an option :=";
                cin >> choice;
                if(choice == 1){
                    cout << "\n\tEnter text \n>";
                    cin.ignore();
                    getline(cin, data);
                    huffmanAlgorithm.encode(data);
                }
                else if(choice == 2){
                    cout << "\n\tEnter file path :=";
                    cin.ignore();
                    getline(cin, path);
                    ifstream InputFile;
                    try{
                        InputFile.open(path, ios::in | ios::binary);
                        char stream;
                        while(InputFile.get(stream)){
                            data += stream;
                        }
                        huffmanAlgorithm.encode(data);
                        InputFile.close();
                    }
                    catch(exception &e){
                        cout << "\nERROR: ";
                        cerr << e.what() << endl;
                    }
                }
                break;
            case 2:
                try{
                    string bin, key, binaryInputWithoutLength = "";
                    cout << "\tDecode a binary file" << endl;
                    cout << "\tEnter binary file path :=";
                    cin >> path;
                    ifstream BinaryFile(path, ios::in | ios::binary);

                    int keyBitLength, encodedBinaryLength;
                    char buffer[4];
                    for(int i=0; i<4; i++){
                        BinaryFile.get(buffer[i]);
                    }

                    // get integer value for those 4 bytes (use unsigned char to not get negative values), bitshift by bit level
                    keyBitLength = int((unsigned char)(buffer[0]) << 24 |
                                (unsigned char)(buffer[1]) << 16 |
                                (unsigned char)(buffer[2]) << 8 |
                                (unsigned char)(buffer[3]));

                    for(int i=0; i<4; i++){
                        BinaryFile.get(buffer[i]);
                    }

                    encodedBinaryLength = int((unsigned char)(buffer[0]) << 24 |
                                       (unsigned char)(buffer[1]) << 16 |
                                       (unsigned char)(buffer[2]) << 8 |
                                       (unsigned char)(buffer[3]));

                    cout << keyBitLength;
                    char curr;
                    while (BinaryFile.get(curr)){
                        for(int i=7; i>=0; i--){
                            binaryInputWithoutLength += to_string((curr >> i) & 1);
                        }
                    }

                    key = binaryInputWithoutLength.substr(0, keyBitLength);
                    bin = binaryInputWithoutLength.substr(keyBitLength, encodedBinaryLength);

                    string out = huffmanAlgorithm.decode(bin, key, keyBitLength);

                    cout << "\n\n\t--DECODED TEXT-- :: \n" << out << endl;

                    BinaryFile.close();
                }
                catch(exception &e){
                    cout << "\nERROR: ";
                    cerr << e.what() << endl;
                }
                break;
            case 3:
                cout << "\tHOW TO USE THIS PROGRAM\n\n";
                cout << "\t[ENCODING]"
                 << "\tChoose between giving a terminal input or a file input" <<endl
                 << "\tIf you chose file input, please provide an absolute path to the file" << endl
                 << "\t[DECODING]" << endl
                 << "\tProvide an absolute path for the binary file." << endl
                 << "\tOr, refer to the io folder (../io/FILENAME.bin)" << endl << endl;
                break;
            case 4:
                cout << "\n\tExiting program..." << endl;
                quitOp = true;
                break;
            default:
                cout << "\n\tInvalid choice! Please try again." << endl;
                break;
        }
    }

    return 0;
}
