#include <iostream>
#include <cstdlib>
#include <string>

struct F {
	void println(std::string s) { std::cout<<s<<std::endl; }
};

struct S {
	F out;
};

S System;

#define LameJavaApp int main(int argc, char** argv)
#define class 
#define public
#define static
#define void

class LameJavaApp {

#define main(X)

	public static void main(String[] argv) {
		System.out.println("Hello world!");
	}

}