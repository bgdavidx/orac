#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>

class MyClass {
private:
	int value;
public:
	MyClass(int x) {
		value = x;
		printf("Constructed MyClass with %d\n", value);
	}

	~MyClass() {
		printf("Destructor was called\n");
	}
};

class FileWrapper {
private:
	FILE *_file;

public:
	FileWrapper(const char *filePath) {
		_file = fopen(filePath, "w");
		printf("Opened file: %s\n", filePath);
	}

	~FileWrapper() {
		if (_file) {
			printf("File was automatically closed by destructor\n");
			fclose(_file);
			_file = NULL;
		}
	}

	void writeLine(const char *whatever) {
		fprintf(_file, whatever);
	}
};

class APerson {
public:
	std::string name;
	int age;
	std::string height;
	int weight;

	APerson(std::string _name, int _age, std::string _height, int _weight) {
		name = _name;
		age = _age;
		height = _height;
		weight = _weight;
	}
};

int main() {
	FileWrapper fw("out.txt");
	for (int i = 0; i < 10; i++)
		fw.writeLine("hey there\n");

	int stuff[10] = {5, 1, 5, 3, 7, 4, 8, 3, 8, 1 };
	std::sort(stuff, stuff+10);

	while (std::next_permutation(stuff, stuff+5)) {
		for (int i = 0; i < 5; i++) {
			printf("%d ", stuff[i]);
		}
		puts("");
	}

	std::map<std::string, APerson*> m;

	APerson *ava = new APerson("Ava", 16, "5'8", 125);
	APerson *david = new APerson("David", 20, "6'1", 180);

	m["ava"] = ava;
	m["david"] = david;

	APerson *lookup = m["ava"];

	printf("Details for %s: %d, %s, %d\n", lookup->name.c_str(), lookup->age, lookup->height.c_str(), lookup->weight);

	lookup = m["david"];

	printf("Details for %s: %d, %s, %d\n", lookup->name.c_str(), lookup->age, lookup->height.c_str(), lookup->weight);

	{
		std::string a = "Hello, ";
		std::string b = "world.";

		std::string c = a+b;



		std::cout<<c<<std::endl;
	}

	{
		const char *a = "Hello, ";
		const char *b = "world.";

		char c[20];

		sprintf(c, "%s%s", a, b);

		printf("%s\n", c);
	}

	std::cout<<"Hey there!"<<std::endl;

	return 0;
}