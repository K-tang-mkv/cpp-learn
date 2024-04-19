# cpp多线程编程
C++11才出现多线程的标准库，在以往的c++版本中需要借助第三方库或系统api才能实现多线程编程。

## 1.1 争用条件
当多个线程都访问同一个变量时，将发生争用

## 1.2 撕裂
撕裂（tearing）是争用导致的结果，分为撕裂读和撕裂写，
* 撕裂读：假设一个

## 1.3 死锁
假设两个线程执行如下代码：
* 线程1：获取A；
* 线程2：获取B；
* 线程1：获取B（等待/阻塞，因为B被线程2持有）
* 线程2：获取A（等待/阻塞，因为A被线程1持有）

##
在C++中，`std::thread` 对象的构造函数可以接受多种类型的参数，用于定义线程的启动函数。以下是几种常见的初始化方式：

1. **传入一个函数名**：
   你可以直接传入一个函数的名称，这个函数将作为线程的启动函数。

   ```cpp
   void functionToRun() {
       // 线程要执行的代码
   }
   std::thread t1(functionToRun);
   ```

2. **传入一个指向函数的指针**：
   与传入函数名类似，你也可以传入一个指向函数的指针。

   ```cpp
   std::thread t2(&functionToRun);
   ```

3. **传入Lambda表达式**：
   C++11及以后的版本支持Lambda表达式，允许你直接在构造线程时定义线程函数。

   ```cpp
   std::thread t3([] {
       // 线程要执行的代码
   });
   ```

4. **传入可调用对象**：
   任何可调用对象（包括函数对象、Lambda表达式、绑定表达式等）都可以作为线程的启动函数。

   ```cpp
   struct Functor {
       void operator()() {
           // 线程要执行的代码
       }
   };
   std::thread t4(Functor());
   ```

5. **传入成员函数**：
   如果要在新线程中调用一个对象的成员函数，可以使用`std::bind`或者Lambda来绑定成员函数和对象。

   ```cpp
   struct MyClass {
       void memberFunction() {
           // 线程要执行的代码
       }
   };
   MyClass myObject;
   std::thread t5(&MyClass::memberFunction, &myObject);
   // 或者使用Lambda：
   std::thread t6([&myObject] {
       myObject.memberFunction();
   });
   ```

6. **传入参数**：
   线程函数可能需要参数，这些参数可以作为构造函数的额外参数传入。

   ```cpp
   std::thread t7(functionToRun, arg1, arg2, ...);
   ```

在所有这些情况下，`std::thread` 的构造函数负责启动一个新线程，并在这个线程中执行提供的函数或Lambda表达式。线程函数的返回类型必须是`void`，因为线程不能返回值。如果需要在线程执行完毕后获取结果，可以考虑使用线程同步机制，如互斥锁（`std::mutex`）、条件变量（`std::condition_variable`）或原子操作（`std::atomic`）等。