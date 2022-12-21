#include <iostream>
#include <thread>
#include <cstdio>
#include <cstdint>

uint32_t count_;

void ThreadA()
{
    for(int i=0; i<100000; ++i){
        ++count_;
        std::cout << 'A';
    }
}

void ThreadB()
{
    for (int i = 0; i<100000; ++i) {
        ++count_;
        std::cout << 'B';
    }
}

int main()
{
    count_ = 0;

    std::thread th_a(ThreadA);
    std::thread th_b(ThreadB);

    th_a.join();
    th_b.join();  
    printf("\ncount_ : %d\n", count_ );


    return 0;
}
