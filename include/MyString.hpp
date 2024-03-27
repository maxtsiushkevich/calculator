#ifndef testLib_h
#define testLib_h

#include <cstring>

class MyString {
public:
    static const size_t npos = -1;

    MyString();
    MyString(const char *s);
    MyString(const MyString& other);
    ~MyString();

    size_t getLength() const;
    const char *getString() const;

    void push_back(char c);
    void push_back(char *s, int len);

    size_t find(char c) const;
    bool empty() const;
    void clear();

    MyString substr(size_t pos, size_t count) const {
        if (pos >= len) {
            return MyString(); // Возвращаем пустую строку, если позиция выходит за границы
        }

        count = (pos + count > len) ? (len - pos) : count; // Проверяем, чтобы не выйти за границы строки
        MyString sub;
        sub.len = count;
        sub.string = new char[count + 1];
        if (sub.string != nullptr) {
            strncpy(sub.string, string + pos, count);
            sub.string[count] = '\0';
        }
        return sub;
    }


    bool operator==(const MyString &str) const;
    bool operator!=(const MyString &str) const;
    bool operator>(const MyString &str) const;
    bool operator<(const MyString &str) const;
    bool operator>=(const MyString &str) const;
    bool operator<=(const MyString &str) const;

    MyString& operator=(const char* newStr);
    MyString& operator=(const MyString &otherStr);

private:
    char *string;
    size_t len;
};

MyString::MyString() : string(nullptr), len(0) {}

MyString::MyString(const char *s) {
    if (s == nullptr) {
        string = nullptr;
        len = 0;
    } else {
        len = strlen(s);
        string = new char[len + 1];
        if (string != nullptr) {
            strncpy(string, s, len);
            string[len] = '\0';
        }
    }
}

MyString::MyString(const MyString& other) {
    len = other.len;
    if (other.string != nullptr) {
        string = new char[len + 1];
        if (string != nullptr) {
            strncpy(string, other.string, len);
            string[len] = '\0';
        }
    } else {
        string = nullptr;
    }
}

MyString::~MyString() {
    delete[] string;
}

size_t MyString::getLength() const {
    return len;
}

const char *MyString::getString() const {
    return string;
}

void MyString::push_back(char c) {
    char *temp = new char[len + 2];
    if (temp != nullptr) {
        if (string != nullptr) {
            strncpy(temp, string, len);
        }
        temp[len] = c;
        temp[len + 1] = '\0';
        delete[] string;
        string = temp;
        len++;
    }
}

void MyString::push_back(char *s, int len) {
    char *temp = new char[this->len + len + 1];

    if (temp != nullptr)
    {
        if (this->string != nullptr)
        {
            strncpy(temp, string, len);
            strcat(temp, s);
        }
        this->len += len;
        temp[this->len + 1] = '\0';
        delete[] string;
        string = temp;
    }
}

size_t MyString::find(char c) const {
    const char *ptr = strchr(string, c);
    if (ptr != nullptr) {
        return ptr - string;
    } else {
        return npos;
    }
}

bool MyString::empty() const {
    return len == 0;
}

void MyString::clear() {
    delete[] string;
    string = nullptr;
    len = 0;
}

bool MyString::operator==(const MyString& str) const {
    return strcmp(string, str.string) == 0;
}

bool MyString::operator!=(const MyString& str) const {
    return !(*this == str);
}

bool MyString::operator>(const MyString& str) const {
    return strcmp(string, str.string) > 0;
}

bool MyString::operator<(const MyString& str) const {
    return strcmp(string, str.string) < 0;
}

bool MyString::operator>=(const MyString& str) const {
    return !(*this < str);
}

bool MyString::operator<=(const MyString& str) const {
    return !(*this > str);
}

MyString& MyString::operator=(const char* newStr) {
    if (string != nullptr) {
        delete[] string;
        string = nullptr;
    }
    if (newStr != nullptr) {
        len = strlen(newStr);
        string = new char[len + 1];
        if (string != nullptr) {
            strncpy(string, newStr, len);
            string[len] = '\0';
        }
    } else {
        len = 0;
    }
    return *this;
}

MyString& MyString::operator=(const MyString& otherStr) {
    if (this != &otherStr) {
        delete[] string;
        if (otherStr.string != nullptr) {
            len = otherStr.len;
            string = new char[len + 1];
            if (string != nullptr) {
                strncpy(string, otherStr.string, len);
                string[len] = '\0';
            }
        } else {
            string = nullptr;
            len = 0;
        }
    }
    return *this;
}

#endif
