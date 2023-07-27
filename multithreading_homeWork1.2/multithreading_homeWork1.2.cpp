#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <random>
#include <execution>
#include <chrono>
#include <iomanip>

using namespace std;

void sumVector(const int size, const vector<int> &a, const vector<int> &b, vector<int> &c) {
	for (int i = 0; i < a.size(); i++) {
		c.at(i) = a.at(i) + b.at(i);
	}
}

void printTimeCalc(const int size, const int potok) {
	vector<thread>v;
	vector<int> a(size);
	vector<int> b(size);
	vector<int> c(size);
	// -capture
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < potok; i++) {
		v.push_back(thread(sumVector, size, ref(a), ref(b), ref(c)));
	}
	for (auto& t : v) {
		t.join();
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double, milli> time = end - start;
	cout << setw(13) << time.count() << "ms";
	//-end
}

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Количество аппаратных ядер - " << thread::hardware_concurrency() << endl;
	cout << setw(20) << 1000 << setw(16) << 10000 << setw(16) << 100000 << setw(16) << 1000000 << endl;

	cout << "1 поток: ";
	printTimeCalc(1000, 1);
	printTimeCalc(10000, 1);
	printTimeCalc(100000, 1);
	printTimeCalc(1000000, 1);
	cout << endl;

	cout << "2 поток: ";
	printTimeCalc(1000, 2);
	printTimeCalc(10000, 2);
	printTimeCalc(100000, 2);
	printTimeCalc(1000000, 2);
	cout << endl;

	cout << "4 поток: ";
	printTimeCalc(1000, 4);
	printTimeCalc(10000, 4);
	printTimeCalc(100000, 4);
	printTimeCalc(1000000, 4);
	cout << endl;

	cout << "8 поток: ";
	printTimeCalc(1000, 8);
	printTimeCalc(10000, 8);
	printTimeCalc(100000, 8);
	printTimeCalc(1000000, 8);
	cout << endl;

	cout << "16 поток:";
	printTimeCalc(1000, 16);
	printTimeCalc(10000, 16);
	printTimeCalc(100000, 16);
	printTimeCalc(1000000, 16);
	cout << endl;

	return 0;
}

