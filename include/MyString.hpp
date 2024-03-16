#ifndef testLib_h
#define testLib_h

#pragma pack(push, 1)

#include <string.h>
#include <cstdlib>

class MyString {

public:

    static const size_t npos = -1;
    MyString();
    MyString(const char &s);
    MyString(const char *oldStr);
    MyString(const MyString& other);
    ~MyString();
    short getLength() const;
    char *getString() const;
    void push_back(char c);
    short find(char c);
    bool empty() const;
    void clear();
    bool operator==(const MyString &str) const;
    bool operator!=(const MyString &str) const;
    bool operator>(const MyString &str) const;
    bool operator<(const MyString &str) const;
    bool operator>=(const MyString &str) const;
    bool operator<=(const MyString &str) const;
    MyString& operator=(const char* newStr);
    MyString& operator=(const MyString &otherStr);

private:
    short len;
    char *string;
};

MyString::MyString() : string(nullptr), len(0) {}

MyString::MyString(const char &s) {
    // Выделяем память под один символ и завершающий нуль-символ
    this->string = new char[2];
    if (this->string != nullptr) {
        this->string[0] = s;
        this->string[1] = '\0';
        this->len = 1;
    } else {
        this->string = nullptr;
        this->len = 0;
    }
}

MyString::MyString(const char *oldStr) {
    if (oldStr == nullptr) {
        this->string = nullptr;
        this->len = 0;
    } else {
        this->len = strlen(oldStr);
        this->string = new char[this->len + 1];
        if (this->string != nullptr)
            strcpy(this->string, oldStr);
    }
}

MyString::MyString(const MyString& other) {

    this->string = nullptr;
    this->len = 0;

    int otherLen = other.getLength();
    this->len = otherLen;

    if (other.string != nullptr) {
        this->string = new char[otherLen + 1];
        if (this->string != nullptr) {
            strcpy(this->string, other.string);
        }
    }
}


MyString::~MyString() {
    if (this->string != nullptr) {
        delete[] this->string;
        this->string = nullptr;
    }
    this->len = 0;
}

char *MyString::getString() const {
    return this->string;
}

short MyString::getLength() const {
    return this->len;
}

void MyString::push_back(char c) {
    if (this->string == nullptr) {
        this->string = new char[2];
        this->string[0] = c;
        this->string[1] = '\0';
        this->len = 1;
    } else {
        char *newStr = new char[this->len + 2]; // Текущая длина + символ + '\0'
        if (newStr != nullptr) {
            for (int i = 0; i < this->len; ++i) {
                newStr[i] = this->string[i];
            }
            newStr[this->len] = c;
            newStr[this->len + 1] = '\0';
            delete[] this->string;
            this->string = newStr;
            this->len++;
        }
    }
}

short MyString::find(char c) {
    char *ptr = strchr(string, c);
    if (ptr) { // Если символ найден (ptr != NULL)
        return ptr - string;
    } else
        return MyString::npos;
}

bool MyString::empty() const{
    if (this->string == nullptr)
        return true;
    else return false;
}

void MyString::clear() {
    if (this->string != nullptr) {
        delete[] this->string;
        this->string = nullptr;
    }
    this->len = 0;
}

bool MyString::operator==(const MyString& str) const {
    // Проверка на nullptr
    if (this->string == nullptr && str.getString() == nullptr)
        return true; // Обе строки пусты, считаем их равными
    else if (this->string == nullptr || str.getString() == nullptr)
        return false; // Одна из строк пуста, они не могут быть равными

    if (strcmp(this->string, str.getString()) == 0)
        return true;
    else
        return false;
}

bool MyString::operator>(const MyString& str) const {
    return strcmp(this->string, str.getString()) > 0;
}

bool MyString::operator<(const MyString& str) const {
    return strcmp(this->string, str.getString()) < 0;
}

bool MyString::operator>=(const MyString& str) const {
    return strcmp(this->string, str.getString()) >= 0;
}

bool MyString::operator<=(const MyString& str) const {
    return strcmp(this->string, str.getString()) <= 0;
}

bool MyString::operator!=(const MyString& str) const {
    return strcmp(this->string, str.getString()) != 0;
}

MyString& MyString::operator=(const char* newStr) {
    if (this->string) { // Если у нас уже есть выделенная память под строку
        delete[] this->string; // Удаляем её
        len = 0;
    }

    if (newStr == nullptr) {
        this->string = nullptr;
        this->len = 0;
    } else {
        this->len = strlen(newStr); // Вычисляем длину новой строки
        this->string = new char[this->len + 1]; // Выделяем память под новую строку (+1 для '\0')
        if (this->string != nullptr) {
            strcpy(this->string, newStr); // Копируем новую строку
        }
    }

    return *this; // Возвращаем ссылку на текущий объект
}

MyString& MyString::operator=(const MyString& otherStr) {
    if (this != &otherStr) {
        delete[] this->string;

        // Allocating memory for the new string
        if (otherStr.string == nullptr) {
            this->string = nullptr;
            this->len = 0;
        } else {
            this->len = otherStr.getLength();
            this->string = new char[this->len + 1];
            if (this->string != nullptr) {
                strcpy(this->string, otherStr.getString());
            }
        }
    }
    return *this;
}


#endif
#pragma pack(pop)