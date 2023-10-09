#include <iostream>
#include "Array.h"

using namespace std;

int main() {
	srand(time(0));
	Array<int> arr1(3);
	arr1.Init();
	cout << arr1;
	arr1.SetSize(5, 3);
	cout << arr1;
	arr1.Add(5);
	cout << arr1;
	arr1.InsertAt(1,95);
	cout << arr1;
	arr1.RemoveAt(0);
	cout << arr1;
	arr1.RemoveAll();
	cout << arr1.IsEmpty()<< endl;

	cout << endl;
	Array<float> arr2(5);
	arr2.Init();
	cout << arr2;
	Array<float> arr3(3);
	arr3.Init();
	cout << arr3;
	arr2.Append(arr3);
	cout << arr2;
	cout << arr2.GetUpperBound();
	arr2.FreeExtra();
	cout << arr2;

	cout << endl;
	Array<char> arr4(4);
	arr4.Init();
	cout << arr4;
	Array<char> arr5(arr4);
	cout << arr5;
	arr5.SetAt(0, 'A');
	cout << arr5.GetAt(0) << endl;
	cout << arr5[1] << endl;
}