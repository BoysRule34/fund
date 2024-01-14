// Fund3.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include <chrono> 
#include <fstream>
#include <sstream>

using namespace std;

class FullName {
public:
	string surname;
	string name;
	string patronymic;

	FullName() {
		surname = "";
		name = "";
		patronymic = "";
	}

	FullName(string p_surname, string p_name, string p_patronymic) {
		surname = p_surname;
		name = p_name;
		patronymic = p_patronymic;
	}

	string toString() {
		return surname + ";" + name + ";" + patronymic + ";";
	}

	int compareTo(FullName a) {
		if (a.surname > surname)
			return -1;
		else if (a.surname == surname && a.name > name)
			return -1;
		else if (a.surname == surname && a.name == name && a.patronymic > patronymic)
			return -1;
		else if (a.surname == surname && a.name == name && a.patronymic == patronymic)
			return 0;
		else
			return 1;
	}

};

class Date {
public:
	int day;
	int month;
	int year;

	Date() {
		day = 0;
		month = 0;
		year = 0;
	}

	Date(int p_day, int p_month, int p_year) {
		day = p_day;
		month = p_month;
		year = p_year;
	}

	string toString() {
		return to_string(day) + ";" + to_string(month) + ";" + to_string(year) + ";";
	}

	int compareTo(Date a) {
		if (a.year < year)
			return -1;
		else if (a.year == year && a.month < month)
			return -1;
		else if (a.year == year && a.month == month && a.day < day)
			return -1;
		else if (a.year == year && a.month == month && a.day == day)
			return 0;
		else
			return 1;
	}
};

class Key {
public:
	Date keyOne;
	FullName  keyTwo;
	int lineNumber;

	Key() {
		keyOne = Date();
		keyTwo = FullName();
		lineNumber = -1;
	}

	Key(Date p_keyOne, FullName p_keyTwo) {
		keyOne = p_keyOne;
		keyTwo = p_keyTwo;
		lineNumber = -1;
	}

	Key(Date p_keyOne, FullName  p_keyTwo, int p_lineNumber) {
		keyOne = p_keyOne;
		keyTwo = p_keyTwo;
		lineNumber = p_lineNumber;
	}

	int compareTo(Key a) {
		if (a.keyOne.compareTo(keyOne) > 0)
			return -1;
		else if (a.keyOne.compareTo(keyOne) == 0 && a.keyTwo.compareTo(keyTwo) > 0)
			return -1;
		else if (a.keyOne.compareTo(keyOne) == 0 && a.keyTwo.compareTo(keyTwo) == 0)
			return 0;
		else
			return 1;
	}

	string toString() {
		string s1(50 - keyOne.toString().size(), ' ');
		string s2(100 - keyTwo.toString().size(), ' ');
		return keyOne.toString() + " " + s1 + keyTwo.toString() + (lineNumber < 0 ? "" : s2 + " " + to_string(lineNumber));
	}

};

Key parseToKey(string a) {
	Key key;
	if (a.length() != 0) {
		int i = 0;
		string day = "";
		while (i < a.length() && a[i] != ';') {
			day += a[i];
			i++;
		}
		i++;
		string month = "";
		while (i < a.length() && a[i] != ';') {
			month += a[i];
			i++;
		}
		i++;
		string year = "";
		while (i < a.length() && a[i] != ';') {
			year += a[i];
			i++;
		}
		Date date = Date(stoi(day), stoi(month), stoi(year));

		i++;
		while (i < a.length() && a[i] == ' ')
			i++;
		
		string surname = "";
		while (i < a.length() && a[i] != ';') {
			surname += a[i];
			i++;
		}
		i++;
		string name = "";
		while (i < a.length() && a[i] != ';') {
			name += a[i];
			i++;
		}
		i++;
		string patronymic = "";
		while (i < a.length() && a[i] != ';') {
			patronymic += a[i];
			i++;
		}
		FullName fullName = FullName(surname, name, patronymic);
		key = Key(date, fullName);
	}
	return key;
}

void shakerSort(Key a[], int n) {
	bool flag = true;
	int right = 0;
	int left = n - 1;
	Key swap;

	while (flag) {
		flag = false;
		for (int i = right; i < left; ++i) {
			if (a[i].compareTo(a[i + 1]) > 0) {
				swap = a[i];
				a[i] = a[i + 1];
				a[i + 1] = swap;
				flag = true;
			}
		}
		--left;
		if (!flag) {
			for (int i = left - 1; i >= right; --i) {
				if (a[i].compareTo(a[i + 1]) > 0) {
					swap = a[i];
					a[i] = a[i + 1];
					a[i + 1] = swap;
					flag = true;
				}
			}
			++right;
		}
	}
}

void heap(Key a[], int n, int i)
{
	int j = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	Key swap;

	if (left < n && a[left].compareTo(a[j]) > 0)
		j = left;
	if (right < n && a[right].compareTo(a[j]) > 0)
		j = right;

	if (j != i) {
		swap = a[i];
		a[i] = a[j];
		a[j] = swap;
		heap(a, n, j);
	}
	
}

void heapSort(Key a[], int n)
{
	Key swap;
	for (int i = n / 2 - 1; i >= 0; i--)
		heap(a, n, i);
	for (int i = n - 1; i >= 0; i--) {
		swap = a[i];
		a[i] = a[0];
		a[0] = swap;
		heap(a, i, 0);
	}
}

void printArray(Key a[], int n)
{
	Key empty = Key();
	for (int i = 0; i < n; i++)
		if (a[i].toString() != empty.toString())
			cout << a[i].toString() + "\n";
	cout << "\n";

}

void readFile(string url, Key a[], int n) {
	ifstream f;
	f.open(url);
	if (f.is_open()) {
		string line;
		int lineNumber = 1;
		Key key;
		while (getline(f, line) && n > lineNumber - 1) {
			key = parseToKey(line);
			key.lineNumber = lineNumber;
			a[lineNumber - 1] = key;
			lineNumber++;
		}
	}
	else {
		cout << "file not open";
	}
	f.close();
}

void readFile(string url, Key a[], Key b[], int n) {
	ifstream f;
	f.open(url);
	if (f.is_open()) {
		string line;
		int lineNumber = 1;
		Key key;
		while (getline(f, line) && n > lineNumber - 1) {
			key = parseToKey(line);
			key.lineNumber = lineNumber;
			a[lineNumber - 1] = key;
			b[lineNumber - 1] = key;
			lineNumber++;
		}
	}
	else {
		cout << "file not open";
	}
	f.close();
}

void writeInFile(string url1, string url2, Key a[], Key b[], int n) {
	ofstream f;
	string result;
	Key empty = Key();

	f.open(url1);
	result = "";

	auto heapBegin = chrono::steady_clock::now();
	heapSort(a, n);
	auto heapEnd = chrono::steady_clock::now();
	auto heapElapsed_ms = chrono::duration_cast <chrono::milliseconds>(heapEnd - heapBegin);
	for (int i = 0; i < n; i++)
		if (a[i].toString() != empty.toString()) {
			result = a[i].toString() + "\n";
			f << result;
		}
	f << "The time: " << heapElapsed_ms.count() << " ms\n";
	f.close();

	f.open(url2);
	result = "";

	auto shakerBegin = chrono::steady_clock::now();
	shakerSort(b, n);
	auto shakerEnd = chrono::steady_clock::now();
	auto shakerElapsed_ms = chrono::duration_cast <chrono::milliseconds>(shakerEnd - shakerBegin);
	for (int i = 0; i < n; i++)
		if (b[i].toString() != empty.toString()) {
			result = b[i].toString() + "\n";
			f << result;
		}
	f << "The time: " << shakerElapsed_ms.count() << " ms\n";
	f.close();
}

void random(Key a[], Key b[], int n) {
	FullName fullName;
	Date date;
	for (int i = 0; i < n; i++) {
		date = Date(rand() % 100, rand() % 100, rand() % 100);
		fullName = FullName(to_string(rand() % 100), to_string(rand() % 100), to_string(rand() % 100));
		a[i] = Key(date, fullName);
		b[i] = Key(date, fullName);
	}
}

void bestShaker(Key a[], Key b[], int n) {
	FullName fullName;
	Date date;
	for (int i = 0; i < n; i++) {
		date = Date(i, i, i);
		fullName = FullName(to_string(i), to_string(i), to_string(i));
		a[n - 1 - i] = Key(date, fullName);
		b[n - 1 - i] = Key(date, fullName);
	}
}

void worstShaker(Key a[], Key b[], int n) {
	FullName fullName;
	Date date;
	for (int i = 0; i < n; i++) {
		date = Date(i, i, i);
		fullName = FullName(to_string(i), to_string(i), to_string(i));
		a[i] = Key(date, fullName);
		b[i] = Key(date, fullName);
	}
}

int main()
{
	auto begin = chrono::steady_clock::now();
	const int n = 500;
	Key* a = new Key[n];
	Key* b = new Key[n];

	//random(a, b, n);
	//worstShaker(a, b, n);
	//bestShaker(a, b, n);
	readFile("stableTest.txt", a, b, n);
	//readFile("input.txt", a, b, n);
	writeInFile("heapOutput.txt", "shakerOutput.txt", a, b, n);
	auto end = chrono::steady_clock::now();
	auto elapsed_ms = chrono::duration_cast <chrono::milliseconds>(end - begin);
	std::cout << "The wihout swap program time: " << elapsed_ms.count() << " ms\n";
}

