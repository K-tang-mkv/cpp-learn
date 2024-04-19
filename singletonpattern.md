# c++单例模式
单例（Singleton）是一种常用的软件设计模式，其核心思想是确保一个类只有一个实例，并提供一个全局访问点来获取这个实例。单例模式在很多场景下都非常有用，尤其是当某个类的对象需要被多个不同部分的程序频繁访问，同时又要确保只存在一个该类的对象时。

单例模式的几个关键特点包括：

1. **唯一性**：单例类保证只有一个实例被创建。
2. **全局访问点**：单例类提供了一个全局函数（通常是静态函数），用于获取其唯一实例。
3. **线程安全**：在多线程环境中，单例模式需要确保在多个线程尝试创建实例时，不会创建多个实例。
4. **延迟初始化**：单例实例通常在第一次被使用时才创建，这称为延迟初始化或懒加载。

在 C++ 中，单例模式可以通过多种方式实现，下面是一个简单的单例模式实现示例：

```cpp
#include <iostream>

class Singleton {
private:
    static Singleton* instance;  // 静态实例指针
    static_mutex mutex;  // 用于线程安全的互斥锁

    // 私有构造函数，防止外部通过new创建实例
    Singleton() {}

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // 获取单例实例的静态方法
    static Singleton* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);  // 锁定以确保线程安全
            if (instance == nullptr) {  // 再次检查，避免多个线程同时进入
                instance = new Singleton();
            }
        }
        return instance;
    }

    // 示例方法
    void doSomething() {
        std::cout << "Doing something..." << std::endl;
    }
};

// 初始化静态成员变量
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;

int main() {
    // 获取单例对象并调用其方法
    Singleton* singletonInstance = Singleton::getInstance();
    singletonInstance->doSomething();

    return 0;
}
```

在这个示例中：

- `instance` 是一个静态指针，指向单例类的唯一实例。
- `mutex` 是一个静态 `std::mutex` 对象，用于确保线程安全。
- `getInstance` 方法是获取单例实例的全局访问点。它首先检查 `instance` 是否为空，如果是，则锁定互斥锁，再次检查 `instance` 是否为空，然后创建单例实例。
- 构造函数是私有的，以防止外部直接创建 `Singleton` 类的对象。
- 拷贝构造函数和赋值操作符被删除，以防止复制单例实例。

通过这种方式，无论何时何地调用 `Singleton::getInstance()` 方法，都将返回指向相同单例对象的指针，确保了单例对象的唯一性。