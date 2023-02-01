#include <iostream>
#include <string>

class Toy {
	std::string name;
public:
	Toy(const std::string inName) : name(inName) {};
	Toy() : name("SomeToy") {};
	~Toy() {};
	std::string& get_name() {
		return name;
	}
};

class shared_ptr_toy {
	Toy* obj;
	int* link;
public:
	shared_ptr_toy();
	shared_ptr_toy(const Toy& t);
	shared_ptr_toy(const shared_ptr_toy& other);
	shared_ptr_toy& operator = (const shared_ptr_toy& other);
	~shared_ptr_toy();
};

shared_ptr_toy::shared_ptr_toy() : obj(nullptr), link(nullptr) { //Создание пустого указателя
	std::cout << "Create empty ptr" << std::endl;
}

shared_ptr_toy::shared_ptr_toy(const Toy& t) : obj(new Toy(t)), link(new int(1)) { //Создание указателя от имени
	std::cout << "Create " << obj->get_name() << ", links: " << *link << std::endl;
}

shared_ptr_toy::shared_ptr_toy(const shared_ptr_toy& other) { //Копия указателя
	obj = other.obj;
	link = other.link;
	++(*link);
	std::cout << "Copy " << obj->get_name() << ", links: " << *link << std::endl;
}

shared_ptr_toy& shared_ptr_toy::operator=(const shared_ptr_toy& other) { 
	if (this == &other) {
		return *this;
	}

	if (--(*link) == 0) {
		std::cout << "Delete " << obj->get_name() << ", links: " << *link << std::endl;
		delete link;
		delete obj;
	}

	if (other.obj) {
		obj = other.obj;
		link = other.link;
		++(*link);
		std::cout << "operator " << obj->get_name() << ", links: " << *link << std::endl;
		return *this;
	}

	obj = nullptr;
	link = nullptr;
	std::cout << "operator nullptr " << std::endl;
	return *this;
}

shared_ptr_toy::~shared_ptr_toy() {
	if (obj) {
		if (--(*link) == 0) {
			std::cout << "Delete " << obj->get_name() << ", links: " << *link << std::endl;
			delete link;
			delete obj;
		}
		else {
			std::cout << "Delete " << obj->get_name() << ", links: " << *link << std::endl;
		}
	}
	else {
		std::cout << "Delete nullptr" << std::endl;
	}
}

shared_ptr_toy make_shared_toy(const Toy& toy) {
	shared_ptr_toy ptr(toy);
	return ptr;
}

shared_ptr_toy make_shared_toy(const std::string& name) {
	Toy toy(name);
	shared_ptr_toy ptr(toy);
	return ptr;
}

int main() {
	Toy ball("Ball");
	shared_ptr_toy toy1 = make_shared_toy(ball);
	shared_ptr_toy toy2 = toy1;
	shared_ptr_toy toy3;
	toy2 = toy3;

	shared_ptr_toy bone = make_shared_toy("Bone");
	toy1 = bone;

	return 0;
}
