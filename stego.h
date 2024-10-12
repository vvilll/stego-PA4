#ifndef STEGO_H
#define STEGO_H
#include <iostream>
#include <fstream>

void openFileIn(std::fstream &file, std::string infile);
void openFileOut(std::fstream &file,std::string outfile);
void checkBMP(std::fstream &file);
void checkCompr(std::fstream &file);
int32_t findPixel(std::fstream &file);
std::string getUserMsg(unsigned int space);
void writeMsg(std::fstream &infile,std::fstream &oufile,std::string msg);
std::string readMsg(std::fstream &infile, int16_t sSize);

#endif