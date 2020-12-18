#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx_;
std::condition_variable cv_;
bool wake_ = false; // spurious wakeup防止用

void ThreadA(void)
{
    // cv_.notify_allが呼ばれるまで待機
    std::cout << "ThreadA待機\n";
    std::unique_lock<std::mutex> lock(mtx_);
    cv_.wait(lock, []{return wake_;});
    std::cout << "ThreadA待機解除\n";
}

void ThreadB(void)
{
    // Aが待機するまで待つ
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::unique_lock<std::mutex> lock(mtx_);
    std::cout << "ThreadB待機解除\n";
    wake_ = true;
    cv_.notify_all();
    std::cout << "ThreadB終了\n";
}

int main()
{
    std::cout << "threadA" << std::endl;
    std::thread th_a(ThreadA);
    std::cout << "threadB" << std::endl;
    std::thread th_b(ThreadB);

    std::cout << "threadB Detach" << std::endl;
    th_b.detach();
    std::cout << "threadA Join" << std::endl;
    th_a.join();

    return 0;
}
