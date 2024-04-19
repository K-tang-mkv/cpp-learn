#include <iostream>
#include <thread>

void counter(int id, int numIterations) {
    for (int i = 0; i < numIterations; i++) {
        std::cout << "Counter " << id << "has value " << i << std::endl;
    }
}

class Counter {
    public:
        Counter(int id, int numIterations) : mId(id), mNumIterations(numIterations) {
        }

        void operator() () const {
            for (int i = 0; i < mNumIterations; ++i) {
                std::cout << "Counter " << mId << "has value " << i << std::endl;
            }
        }
    
    private:
        int mId;
        int mNumIterations;
};

class Request {
    public:
        Request(int id) : mId(id) {};

        void process() {
            std::cout << "Processing request " << mId << std::endl;
        }

    private:
        int mId;
};

int main() {
    // // Using uniform initialization syntax
    // std::thread t1{ Counter{ 1, 20 }}; // OK

    // // Using named variable
    // Counter c(2, 12);
    // std::thread t2(c);

    // // Using temporary
    // std::thread t3(Counter(3, 10)); // if there was no parmeter in Counter, this way will not work

    // // Wait for threads to finish
    // t1.join();
    // t2.join();
    // t3.join();

    // using lambda expression
    // int id = 1;
    // int numIterations = 5;
    // std::thread t1([id, numIterations] {
    //     for (int i = 0; i < numIterations; ++i) {
    //         std::cout << "Counter " << id << " has value " << i << std::endl;
    //     }
    // });
    // t1.join();

    Request req{ 100 };
    std::thread t{ &Request::process, &req };
    t.join();
    return 0;
}
