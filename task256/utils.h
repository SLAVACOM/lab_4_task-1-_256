#pragma once


void task();

void findCommas(const char* data, int& firstCommaPos, int& lastCommaPos);

void printConsole(int& firstCommaPos, int& lastCommaPos);

void writeToFile(const char* output, int& firstCommaPos, int& lastCommaPos);

bool readFromFile(const char* filename, char*& buffer);

bool readFromConsole(char*& buffer);


