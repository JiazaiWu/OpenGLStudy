#include<iostream>
#include"Matrix.h"

using namespace std;

int main() {
	Matrix<int> m1(2, 2, 10);
	auto m2 = m1+10;
	m2(1,1) += 10;
	cout << "m2 " << m2(1,1) <<endl;
	return 0;
}