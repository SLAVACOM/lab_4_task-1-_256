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
			cout << "Введите '0' для ввода с консоли, '1' для ввода из файла: ";
			getline(cin, input);
		} while (!regex_match(input, valid_input));
		in_option = input[0];

		do {
			cout << "Введите '0' для вывода в консоль, '1' для вывода в файл: ";
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

		if (dataBuffer != nullptr) {
			int firstCommaPos{ -1 }, lastCommaPos{ -1 };
			findCommas(dataBuffer, firstCommaPos, lastCommaPos);
			if (out_option == '0') printConsole(firstCommaPos, lastCommaPos);
			else if (out_option == '1')	writeToFile(constants::output, firstCommaPos, lastCommaPos);
		}
		if (in_option == '0') {
			do {
				cout << "Введите '0' для повтора программы, '1' для завершения программы: ";
				getline(cin, input);
			} while (!regex_match(input, valid_input));
			in_option = input[0];
		}
		delete[] dataBuffer;
	} while (in_option != '1');
}


bool readFromFile(const char* filename, char*& buffer) {
	ifstream file(filename, ios::binary | ios::ate);
	if (!file.is_open()) {
		cout << "Ошибка при открытии файла с входными данными" << endl;
		return false;
	}
	streamsize size = file.tellg();
	file.seekg(0, ios::beg);

	buffer = new char[size + 1];
	if (buffer == nullptr) {
		cout << "Не удалось выделить память для чтения файла" << endl;
		file.close();
		return false;
	}

	if (!file.read(buffer, size)) {
		cout << "Ошибка при чтении файла" << endl;
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
	cout << "Введите данные: ";
	string input;

	getline(cin, input);
	buffer = new char[input.length() + 1];

	strcpy_s(buffer, input.length() + 1, input.c_str());
	return true;
}

void printConsole(int& firstCommaPos, int& lastCommaPos) {
	if (firstCommaPos != -1) {
		cout << "Номер позиции первой запятой: " << firstCommaPos + 1 << std::endl;
		cout << "Номер позиции последней запятой: " << lastCommaPos + 1 << std::endl;
	}
	else cout << "Запятые отсутствуют!!!" << std::endl;
}

void writeToFile(const char* output, int& firstCommaPos, int& lastCommaPos) {
	ofstream outputFile(output);
	if (!outputFile.is_open()) cout << "Ошибка при открытии файла для записи" << endl;
	else {
		if (firstCommaPos != -1) {
			outputFile << "Номер позиции первой запятой: " << firstCommaPos + 1 << std::endl;
			outputFile << "Номер позиции последней запятой: " << lastCommaPos + 1 << std::endl;
		}
		else outputFile << "Запятые отсутствуют!!!" << std::endl;
		outputFile.close();
	}
}

void findCommas(const char* data, int& firstCommaPos, int& lastCommaPos) {
	for (int i{ 0 };  data[i] != '\0'; i++) {
		if (data[i] == ',') {
			if (firstCommaPos == -1) firstCommaPos = i;
			lastCommaPos = i;
		}
	}
}