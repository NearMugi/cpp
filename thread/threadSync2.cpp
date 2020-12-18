#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

struct ProcessData {
  std::mutex mtx_;
  std::condition_variable cond_;

  bool data_ready_ = false;

public:
  // 処理に必要なデータの準備をする
  void prepare_data_for_processing()
  {
    // ...準備処理...
    std::cout << "preparing..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Finish" << std::endl;
    {
      // 確実にdata_ready_を更新するためロックしている
      std::lock_guard<std::mutex> lk(mtx_);
      data_ready_ = true;
    }

    // 準備完了したので待機スレッドを起床させる
    cond_.notify_one();
  }

  void wait_for_data_to_process()
  {
    std::cout << "main process" << std::endl;
    {
      std::unique_lock<std::mutex> lk(mtx_);

      // データの準備ができるまで待機してから処理する
      std::cout << "data_ready_:" << data_ready_ << std::endl;
      cond_.wait(lk, [this] { return data_ready_; });
      std::cout << "data_ready_:" << data_ready_ << std::endl;
    }
    process_data();
  }

private:
  void process_data()
  {
    // ...データを処理する...
    std::cout << "process data" << std::endl;
  }
};

int main()
{
  ProcessData p;

  std::thread t1([&] { p.prepare_data_for_processing(); });
  std::thread t2([&] { p.wait_for_data_to_process(); });

  t1.join();
  t2.join();
  std::cout << "end" << std::endl;
}
