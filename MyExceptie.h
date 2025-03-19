#pragma once
#include <exception>
#include <string>

using namespace std;

class MyException : public exception {
private:
    string mesaj;
public:
    MyException(string msg) : mesaj{ msg } {}
    const string& what() {
        return mesaj;
    }
};