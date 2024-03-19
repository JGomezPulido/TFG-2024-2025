#include <iostream>
#include <string>

int main(void) {
	std::cout << "Hello Linux!" << std::endl;
	std::string c;
	std::cin >> c;
	system("pwd");
	std::cout << c << std::endl;
	return 0;
}