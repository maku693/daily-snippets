#include <iostream>
#include <string>

int main {
	struct {
		template<std::string S>
		operator()() { std::cout << S; }
	} match;
	match<"foobar">();
}
