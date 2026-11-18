#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

class Point {
private:
    double x_;
    double y_;

    static bool valid(double value) {
        return std::isfinite(value);
    }

public:
    Point() : x_(0.0), y_(0.0) {}

    Point(double x, double y) : x_(x), y_(y) {
        if (!valid(x) || !valid(y)) {
            throw std::invalid_argument("Координаты должны быть конечными числами.");
        }
    }

    Point(const Point& other) : x_(other.x_), y_(other.y_) {}

    double getX() const { return x_; }
    double getY() const { return y_; }

    void setX(double x) {
        if (!valid(x)) {
            throw std::invalid_argument("Координата x должна быть конечным числом.");
        }
        x_ = x;
    }

    void setY(double y) {
        if (!valid(y)) {
            throw std::invalid_argument("Координата y должна быть конечным числом.");
        }
        y_ = y;
    }

    double distanceToOrigin() const {
        return std::hypot(x_, y_);
    }

    Point& operator--() {
        x_ -= 1.0;
        y_ -= 1.0;
        return *this;
    }

    Point operator--(int) {
        Point old(*this);
        --(*this);
        return old;
    }

    Point operator-() const {
        return Point(y_, x_);
    }

    operator int() const {
        const long double value = static_cast<long double>(x_);
        if (value < static_cast<long double>(std::numeric_limits<int>::min()) ||
            value > static_cast<long double>(std::numeric_limits<int>::max())) {
            throw std::overflow_error("Координата x не помещается в int.");
        }
        return static_cast<int>(x_);
    }

    explicit operator double() const {
        return y_;
    }

    Point operator-(int value) const {
        return Point(x_ - value, y_);
    }

    double operator-(const Point& other) const {
        return std::hypot(x_ - other.x_, y_ - other.y_);
    }

    friend std::ostream& operator<<(std::ostream& out, const Point& point) {
        out << "Точка (x=" << point.x_ << ", y=" << point.y_ << ')';
        return out;
    }

};

double readNumber(const char* prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && std::isfinite(value)) {
            return value;
        }
        std::cout << "Ошибка: введите конечное число.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int readInteger(const char* prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        std::cout << "Ошибка: введите целое число.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    Point origin;
    std::cout << "Конструктор по умолчанию: " << origin << '\n';
    std::cout << "Введите координаты для проверки методов setX и setY.\n";
    const double originX = readNumber("Введите координату x: ");
    const double originY = readNumber("Введите координату y: ");
    origin.setX(originX);
    origin.setY(originY);
    std::cout << "Точка после изменения координат: " << origin << '\n'
              << "Значения, полученные методами getX и getY: x=" << origin.getX()
              << ", y=" << origin.getY() << "\n\n";

    std::cout << "Конструктор с параметрами. Введите координаты точки A.\n";
    const double ax = readNumber("Координата x точки A: ");
    const double ay = readNumber("Координата y точки A: ");
    Point a(ax, ay);
    std::cout << "Точка A: " << a << '\n';

    Point copy(a);
    std::cout << "Конструктор копирования. Копия точки A: "
              << copy << "\n\n";

    std::cout << "Введите координаты точки B для проверки операции вычитания точек.\n";
    const double bx = readNumber("Координата x точки B: ");
    const double by = readNumber("Координата y точки B: ");
    Point b(bx, by);
    std::cout << "Точка B: " << b << "\n\n";

    std::cout << "Задание 1. Расстояние от точки до начала координат: "
              << a.distanceToOrigin() << '\n';
    std::cout << "Задание 2. Расстояние между точками (A - B): "
              << (a - b) << '\n';

    Point swapped = -a;
    std::cout << "Унарная операция -A меняет координаты x и y местами: "
              << swapped << '\n';

    Point prefixDecremented = a;
    std::cout << "Операция -- уменьшает координаты x и y на 1. Результат --A: "
              << --prefixDecremented << '\n';
    Point postfixDecremented = a;
    const Point beforeDecrement = postfixDecremented--;
    std::cout << "Результат выражения A-- до уменьшения координат: "
              << beforeDecrement << '\n';
    std::cout << "Точка A после операции A--: " << postfixDecremented << '\n';

    const int integerValue = readInteger(
        "Введите целое число для вычитания из координаты x точки A: ");
    std::cout << "Операция A - целое число: "
              << (a - integerValue) << '\n';

    if (a.getX() >= static_cast<double>(std::numeric_limits<int>::min()) &&
        a.getX() <= static_cast<double>(std::numeric_limits<int>::max())) {
        const int xIntegerPart = a;
        std::cout << "Неявное преобразование Point в int "
                  << "(целая часть координаты x): "
                  << xIntegerPart << '\n';
    } else {
        std::cout << "Неявное преобразование в int невозможно: координата x "
                  << "выходит за допустимый диапазон целого типа.\n";
    }
    std::cout << "Явное преобразование Point в double (координата y): "
              << static_cast<double>(a) << '\n';

    std::cout << "\nДемонстрация методов и операций варианта 9 завершена.\n";
    return 0;
}
