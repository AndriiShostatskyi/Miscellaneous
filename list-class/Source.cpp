#include "List.cpp"

void main() 
{
	List<int> example;
	example.push_front(5);
	example.push_front(10);
	example.push_front(15);
	example.push_back(20);
	example.push_back(30);
	example.show();
	cout << example.pop_back() << endl;
	example.show();
	cout << example.pop_front() << endl;
	example.show();
	example.insert_after(2, 100);
	example.show();
	system("pause");
}