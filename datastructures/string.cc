#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    char* data_;
    size_t size_;
    size_t capacity_;

    void reserve(size_t new_cap) {
        if (new_cap <= capacity_)
            return;

        char* new_data = new char[new_cap + 1];

        memcpy(new_data, data_, size_);
        new_data[size_] = '\0';

        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

public:
    String(const char* s = "") {
        size_ = strlen(s);
        capacity_ = size_;

        data_ = new char[capacity_ + 1];
        memcpy(data_, s, size_ + 1);
    }

    ~String() {
        delete[] data_;
    }

    // operator+
    String operator+(const String& other) const {
        String result;

        result.reserve(size_ + other.size_);

        memcpy(result.data_, data_, size_);
        memcpy(result.data_ + size_, other.data_, other.size_);

        result.size_ = size_ + other.size_;
        result.data_[result.size_] = '\0';

        return result;
    }

    // operator+=
    String& operator+=(const String& other) {
        if (size_ + other.size_ > capacity_) {
            size_t new_cap = max(capacity_ * 2, size_ + other.size_);
            reserve(new_cap);
        }

        memcpy(data_ + size_, other.data_, other.size_);

        size_ += other.size_;
        data_[size_] = '\0';

        return *this;
    }

    const char* c_str() const {
        return data_;
    }
};

int main() {
    String a("Hello ");
    String b("World");

    String c = a + b;     // operator+
    cout << c.c_str() << '\n';

    a += b;               // operator+=
    cout << a.c_str() << '\n';
}