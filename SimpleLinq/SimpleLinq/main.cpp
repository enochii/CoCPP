#include <iostream>
#include <functional>
#include <vector>

#include "nlinq.h"

using namespace std;

int main()
{
	auto i = [](int x) {return x * 2;};

	vector<int> ivec = { 1,2,3,4,5 };

	auto res = From(ivec).Select(function<int(int)>([](int x) {return x + 1;})).Where([](int x) {return x > 3;}).ToList();

	for (auto item : res) {
		cout << item << " ";
	}

	system("pause");
	return 0;
}