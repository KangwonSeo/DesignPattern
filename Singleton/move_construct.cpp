#include <iostream>
#include <cstring>

class MyString {
  char *string_content;
  int string_length;
  int memory_capacity;

public:
  MyString();
  MyString(const char *str);
  MyString(const MyString &str);
  MyString(MyString &&str);
  void reserve(int size);
  MyString operator+(const MyString &s);
  ~MyString();
  int length() const;
  void println();
};

MyString::MyString() {
  string_length = 0;
  memory_capacity = 0;
  string_content = nullptr;
}

MyString::MyString(const char *str) {
  string_length = strlen(str);
  memory_capacity = string_length;
  string_content = new char[string_length];
  for (int i = 0; i != string_length; i++) string_content[i] = str[i];
}

MyString::MyString(const MyString &str) {
  string_length = str.string_length;
  string_content = new char[string_length];

  for (int i = 0; i != string_length; i++)
    string_content[i] = str.string_content[i];
}

MyString::MyString(MyString &&str) {
  std::cout << "move" << std::endl;
  string_length = str.string_length;
  string_content = str.string_content;
  memory_capacity = str.memory_capacity;
  str.string_content = nullptr;
}
MyString::~MyString() {
  if (string_content) delete[] string_content;
}

void MyString::reserve(int size) {
  if (size > memory_capacity) {
    char *prev_string_content = string_content;

    string_content = new char[size];
    memory_capacity = size;

    for (int i = 0; i != string_length; i++)
      string_content[i] = prev_string_content[i];

    if (prev_string_content != nullptr) delete[] prev_string_content;
  }
}
MyString MyString::operator+(const MyString &s) {
  MyString str;
  str.reserve(string_length + s.string_length);
  for (int i = 0; i < string_length; i++)
    str.string_content[i] = string_content[i];
  for (int i = 0; i < s.string_length; i++)
    str.string_content[string_length + i] = s.string_content[i];
  str.string_length = string_length + s.string_length;
  return str;
}
int MyString::length() const { return string_length; }

void MyString::println() {
  for (int i = 0; i != string_length; i++) std::cout << string_content[i];
  std::cout << std::endl;
}

int main() {
  MyString str1("abc");
  MyString str2("def");
  std::cout << "-------------" << std::endl;
  MyString str3 = str1 + str2;
  str3.println();
}
