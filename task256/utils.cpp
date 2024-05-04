#include "utils.h"
#include "constants.h"

#include <iostream>
#include <regex>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

void task() {
	regex valid_input("^[01]$");
	string input;
	char in_option, out_option;

	do {
		do {
			cout << "������� '0' ��� ����� � �������, '1' ��� ����� �� �����: ";
			getline(cin, input);
		} while (!regex_match(input, valid_input));
		in_option = input[0];

		do {
			cout << "������� '0' ��� ������ �� �������, '1' ��� ������ � ����: ";
			getline(cin, input);
		} while (!regex_match(input, valid_input));
		out_option = input[0];

		char* dataBuffer = nullptr;

		if (in_option == '0') {
			if (!readFromConsole(dataBuffer) ) {
				delete[] dataBuffer;
				continue;
			}
		}
		else if (in_option == '1'){
			if (!readFromFile(constants::input, dataBuffer)) {
				delete[] dataBuffer;
				continue;
			}

		}

		int firstCommaPos{ -1 };
		int lastCommaPos{ -1 };

		findCommas(dataBuffer, firstCommaPos, lastCommaPos);

		if (out_option == '0') {
			printConsole(firstCommaPos, lastCommaPos);
		}
		else if(out_option =='1')
		{
			writeToFile(constants::output, firstCommaPos, lastCommaPos);
		}

		delete[] dataBuffer;
		dataBuffer = nullptr;


		if (in_option == '0') {
			do {
				cout << "������� '0' ��� ������� ���������, '1' ��� ���������� ���������: ";
				getline(cin, input);
			} while (!regex_match(input, valid_input));
			in_option = input[0];

		}

	} while (in_option != '1');
}


bool readFromFile(const char* filename, char*& buffer) {
	ifstream file(filename, ios::binary | ios::ate);
	if (!file.is_open()) {
		cout << "������ ��� �������� ����� � �������� �������" << endl;
		return false;
	}
	streamsize size = file.tellg();
	file.seekg(0, ios::beg);

	buffer = new (nothrow) char[size + 1];
	if (buffer == nullptr) {
		cout << "�� ������� �������� ������ ��� ������ �����" << endl;
		file.close();
		return false;
	}

	if (!file.read(buffer, size)) {
		cout << "������ ��� ������ �����" << endl;
		delete[] buffer;
		buffer = nullptr;
		file.close();
		return false;
	}

	buffer[size] = '\0';
	file.close();
	return true;
}

bool readFromConsole(char*& buffer) {
	cout << "������� ������: ";
	string input;
	getline(cin, input);

	buffer = new (nothrow) char[input.length() + 1];
	if (buffer == nullptr) {
		cout << "�� ������� �������� ������ ��� ����� ������" << endl;
		return false;
	}
	strcpy_s(buffer, sizeof(input), input.c_str());
	return true;
}

void printConsole(int& firstCommaPos, int& lastCommaPos) {
	if (firstCommaPos != -1) {
		std::cout << "����� ������� ������ �������: " << firstCommaPos + 1 << std::endl;
		std::cout << "����� ������� ��������� �������: " << lastCommaPos + 1 << std::endl;
	}
	else
	{
		std::cout << "������� �����������!!!" << std::endl;
	}
}

void writeToFile(const char* output, int& firstCommaPos, int& lastCommaPos) {
	ofstream outputFile(output);
	if (!outputFile.is_open()) {
		cout << "������ ��� �������� ����� ��� ������" << endl;
	}
	else {

		if (firstCommaPos != -1) {
			outputFile << "����� ������� ������ �������: " << firstCommaPos + 1 << std::endl;
			outputFile << "����� ������� ��������� �������: " << lastCommaPos + 1 << std::endl;
		}
		else
		{
			outputFile << "������� �����������!!!" << std::endl;
		}
	}
	outputFile.close();
}

void findCommas(const char* data, int& firstCommaPos, int& lastCommaPos) {
	
	for (int i{ 0 };  data[i] != '\0'; i++) {
		if (data[i] == ',') {
			if (firstCommaPos == -1) firstCommaPos = i;
			lastCommaPos = i;
		}
	}
}