#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <type_traits>

// Простий контейнер
template <typename T>
class SimpleContainer {
private:
    T value;

public:
    SimpleContainer(T val) : value(val) {}

    void input() {
        std::cout << "Enter value: ";
        std::cin >> value;
    }

    void print() const {
        std::cout << "Value: " << value << std::endl;
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

    std::string type() const {
        if (std::is_same<T, int>::value) return "int";
        if (std::is_same<T, float>::value) return "float";
        if (std::is_same<T, double>::value) return "double";
        if (std::is_same<T, char>::value) return "char";
        if (std::is_same<T, bool>::value) return "bool";
        return "unknown";
    }
};

// Контейнер масиву
template <typename T>
class ArrayContainer {
private:
    std::vector<T> data;

public:
    ArrayContainer() = default;

    ArrayContainer(const std::vector<T>& values) : data(values) {}

    ArrayContainer(size_t size, T defaultValue = T()) : data(size, defaultValue) {}

    void input() {
        std::cout << "Enter number of elements: ";
        size_t n;
        std::cin >> n;
        data.resize(n);
        for (size_t i = 0; i < n; ++i) {
            std::cout << "Element [" << i << "]: ";
            std::cin >> data[i];
        }
    }

    void print() const {
        std::cout << "Array: ";
        for (const auto& val : data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    std::string toString() const {
        std::ostringstream oss;
        for (const auto& val : data) {
            oss << val << " ";
        }
        return oss.str();
    }

    std::string type() const {
        std::ostringstream oss;
        if (std::is_same<T, int>::value) oss << "int";
        else if (std::is_same<T, float>::value) oss << "float";
        else if (std::is_same<T, double>::value) oss << "double";
        else if (std::is_same<T, char>::value) oss << "char";
        else if (std::is_same<T, bool>::value) oss << "bool";
        else oss << "unknown";

        oss << "[" << data.size() << "]";
        return oss.str();
    }

    size_t size() const {
        return data.size();
    }

    void resize(size_t newSize, T defaultValue = T()) {
        data.resize(newSize, defaultValue);
    }

    SimpleContainer<T>* getElement(size_t index) const {
        if (index >= data.size()) return nullptr;
        return new SimpleContainer<T>(data[index]);
    }
};

// Головна функція
int main() {
    // Приклад 1: Проста змінна
    SimpleContainer<int> intCont(42);
    intCont.print();
    std::cout << "Type: " << intCont.type() << std::endl;

    // Приклад 2: Масив
    ArrayContainer<double> arrCont(5, 3.14);
    arrCont.print();
    std::cout << "Type: " << arrCont.type() << std::endl;

    // Отримання елемента
    auto elem = arrCont.getElement(2);
    if (elem) {
        elem->print();
        delete elem;
    }

    return 0;
}
