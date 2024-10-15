/**
 * @file main.cpp
 * @author William Wotherspoon
 * @brief stegonography program for bmp files
 * @date 2024-10-13
 */
#include <iostream>
#include <fstream>
#include "stego.h"

int main(int argc, char *argv[])
{
    bool encode=false;
    bool decode=false;
    std::string inputFile= " ";
    std::string outputFile= " ";
    for(int i=0;i<argc;i++){
        if(((argv[i])[0]=='-') && ((argv[i])[1]=='d')){
            decode=true;
        }
        if(((argv[i])[0]=='-') && ((argv[i])[1]=='e')){
            encode=true;
        }
        if(((argv[i])[0]=='-') && ((argv[i])[1]=='f')){
            inputFile=argv[i+1];
        }
        if(((argv[i])[0]=='-') && ((argv[i])[1]=='o')){
            outputFile=argv[i+1];
        }
    }
 
    if(encode){
        //open real file
        std::fstream rFile;
        openFileIn(rFile,inputFile);
        //check if bmp
        checkBMP(rFile);
        //check if compression
        checkCompr(rFile);
        //create secret file
        std::fstream wFile;
        openFileOut(wFile,outputFile);
        //finds the beginning of the pixel array
        int32_t start=findPixel(rFile);

        //write header into new file;
        int16_t fChunk;
        int8_t tChunk;
        rFile.seekg(0, std::ios::beg);
        rFile.read(reinterpret_cast<char*>(&tChunk),2);
        wFile.write(reinterpret_cast<char*>(&tChunk),2);
        for(int i=2;i<start;i+=4){
            rFile.read(reinterpret_cast<char*>(&fChunk),4);
            wFile.write(reinterpret_cast<char*>(&fChunk),4);  
        }

        //space available for message
        unsigned int space=0;
        rFile.seekg(2, std::ios::beg);
        rFile.read(reinterpret_cast<char*>(&space),4);
        space-=start;

        //User Message
        std::string message=getUserMsg(space);
        int16_t mSize=message.size();
        //write size of message into file
        wFile.seekp(6,std::ios::beg);
        wFile.write(reinterpret_cast<char*>(&mSize),4);

        //write message to image
        rFile.seekg(start,std::ios::beg);
        wFile.seekp(start,std::ios::beg);
        writeMsg(rFile,wFile,message);
        //add rest of image
        while(rFile.peek() != EOF){
            int8_t chunk=0;
            rFile.read(reinterpret_cast<char*>(&chunk),1);
            wFile.write(reinterpret_cast<char*>(&chunk),1);
        }
        wFile.close();
        rFile.close();
        std::cout<<"Message Encoded.\n";
    }

    if(decode)
    {
        //open Secret file
        std::fstream secFile;
        openFileIn(secFile,inputFile);
        checkBMP(secFile);
        checkCompr(secFile);

        //finds the beginning of the pixel array
        int32_t start=findPixel(secFile);

        //read the size of message from 
        int16_t secSize=0;
        secFile.seekg(6,std::ios::beg);
        secFile.read(reinterpret_cast<char*>(&secSize),4);
        if(secSize<=0){
            std::cout <<"There is no secret\n";
            exit(1);
        }
        
        //read message from image
        secFile.seekg(start,std::ios::beg);
        std::string secret=readMsg(secFile,secSize);
        std::cout<<"The secret is: "<<secret<<"\n";
        secFile.close();
    }
}