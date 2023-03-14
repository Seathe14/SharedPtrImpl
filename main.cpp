#include <iostream>
#include "SharedPtr.h"

class A {
public:
	A() {
		std::cout << "constructor" << std::endl;
	}
	A(int a) {
		std::cout << "constructor(int a)" << std::endl;
	}
	~A() {
		std::cout << "destructor" << std::endl;
	}

	int a;
};

int main()
{
	// Examples;
	SharedPtr<A> a(new A());
	SharedPtr<A> c(new A());
	SharedPtr<A> d;
	c->a = 11;
	{
		SharedPtr<A> b(a);
		a->a = 10;
		std::cout << a->a << std::endl;
		b->a = 15;
		std::cout << a->a << "\n" << b->a << std::endl;
		b = std::move(c);
		std::cout << b->a << "\n" << std::endl;
	}
	SharedPtr<A> b = MakeShared<A>(5);
	return 0;
}