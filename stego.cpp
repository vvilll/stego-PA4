#include "stego.h"

void openFileIn(std::fstream &file,std::string infile)
{
    file.open(infile, std::ios::in | std::ios::binary);
    if(!file){
        std::cout << "Error opening NIC file\n";
        exit(1);
    }
}

void openFileOut(std::fstream &file,std::string outfile)
{
    file.open(outfile, std::ios::out | std::ios::binary);
    if(!file){
        std::cout << "Error opening NIC file\n";
        exit(1);
    }
}

void checkBMP(std::fstream &file)
{
    char rMagic[2];
    file.read(rMagic,2);
    if(rMagic[0]=='B'&&rMagic[1]=='M'){
        std::cout << "It is a bmp\n";
    }else{
        std::cout<<"It is not a bmp file\n";
        exit(1);
    }
}

void checkCompr(std::fstream &file)
{
    int32_t compr;
    file.seekg(30L, std::ios::beg);
    file.read(reinterpret_cast<char*>(&compr),4);
    if(compr==0){
        std::cout<<"file no compression\n";
    }else{
        std::cout<<"file has compression endcoding will not work\n";
        exit(1);
    }
}

int32_t findPixel(std::fstream &file)
{
    int32_t start;
    file.seekg(10L,std::ios::beg);
    file.read(reinterpret_cast<char*>(&start),4);
    return start;
}

std::string getUserMsg(unsigned int space)
{
    std::string message=" ";
    std::cout << "Please enter your message: ";
    getline(std::cin, message);
    std::string newMessage;
    while(message.size()>(space/8)){
        std::cout <<"Message to big. Please reduce the size: ";
        std::cin >> newMessage;
        message=newMessage;
    }
    return message;
}

void writeMsg(std::fstream &inFile,std::fstream &outFile,std::string msg)
{
    int mSize=msg.size();
    for(int i=0;i<mSize;i++){
        int8_t chunk=0;
        char sec = msg[i];
        for(int i=0;i<8;i++){
            inFile.read(reinterpret_cast<char*>(&chunk),1);
            if((sec & 1)==0){
                chunk &= ~1;
                outFile.write(reinterpret_cast<char*>(&chunk),1);
            }else{
                chunk |= 1;
                outFile.write(reinterpret_cast<char*>(&chunk),1);
            }
            sec=sec>>1;
        }
    }  
}

std::string readMsg(std::fstream &inFile,int16_t sSize)
{
    std::string secret="";
    for(int i=0;i<sSize;i++){
        int8_t byte=0;
        int8_t mask=1;
        char temp=0;
        for(int x=0;x<8;x++){
            inFile.read(reinterpret_cast<char*>(&byte),1);
            if((byte & 1)==0){
                mask=mask<<1;
            }else{
                temp+=mask;
                mask=mask<<1;
            }
        }
        secret+=temp;
    }
}
