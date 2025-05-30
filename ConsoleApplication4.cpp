#include <iostream>
#include <memory>
#include <cmath>

//класс для двумерного вектора
class Vector2D {
public:
    float x, y;

    Vector2D(float x = 0, float y = 0) : x(x), y(y) {}

    //метод для вывода вектора
    void print() const {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};

//интерфейс для стратегии обработки векторов
class VectorOperation {
public:
    virtual ~VectorOperation() {}
    virtual Vector2D operate(const Vector2D& v1, const Vector2D& v2) const = 0;
};

//cтратегия для произведения
class ScalarProduct : public VectorOperation {
public:
    Vector2D operate(const Vector2D& v1, const Vector2D& v2) const override {
        float scalar = v1.x * v2.x + v1.y * v2.y;
        return Vector2D(scalar, 0); // Возвращаем скаляр как вектор (x, 0)
    }
};

//cтратегия для сложения
class VectorSum : public VectorOperation {
public:
    Vector2D operate(const Vector2D& v1, const Vector2D& v2) const override {
        return Vector2D(v1.x + v2.x, v1.y + v2.y);
    }
};

//обработчик векторов
class VectorHandler {
private:
    std::unique_ptr<VectorOperation> strategy;

public:
    VectorHandler(std::unique_ptr<VectorOperation> strategy) : strategy(std::move(strategy)) {}

    void setStrategy(std::unique_ptr<VectorOperation> newStrategy) {
        strategy = std::move(newStrategy);
    }

    Vector2D process(const Vector2D& v1, const Vector2D& v2) {
        return strategy->operate(v1, v2);
    }
};
int main() {
    setlocale(LC_ALL, "RU");
    Vector2D v1(7, 9);
    Vector2D v2(6, 8);

    VectorHandler handler(std::make_unique<VectorSum>());
    Vector2D result = handler.process(v1, v2);
    std::cout << "Сложение векторов: ";
    result.print();

    handler.setStrategy(std::make_unique<ScalarProduct>());
    result = handler.process(v1, v2);
    std::cout << "Скалярное произведение векторов: ";
    result.print();

    return 0;
}
