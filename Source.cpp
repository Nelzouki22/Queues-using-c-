#include <iostream>
#include <queue>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>

// Thread-safe queue using std::queue
void useQueue() {
    std::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
}

// Using std::deque
void useDeque() {
    std::deque<int> dq;
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    while (!dq.empty()) {
        std::cout << dq.front() << " ";
        dq.pop_front();
    }
    std::cout << std::endl;
}

// Thread-safe queue using std::queue with multithreading
std::queue<int> ts_queue;
std::mutex mtx;
std::condition_variable cv;

void producer() {
    std::lock_guard<std::mutex> lock(mtx);
    ts_queue.push(10);
    ts_queue.push(20);
    ts_queue.push(30);
    cv.notify_all();
}

void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return !ts_queue.empty(); });
    while (!ts_queue.empty()) {
        std::cout << ts_queue.front() << " ";
        ts_queue.pop();
    }
    std::cout << std::endl;
}

void useThreadSafeQueue() {
    std::thread prod(producer);
    std::thread cons(consumer);
    prod.join();
    cons.join();
}

int main() {
    std::cout << "Using std::queue:" << std::endl;
    useQueue();

    std::cout << "Using std::deque:" << std::endl;
    useDeque();

    std::cout << "Using thread-safe std::queue:" << std::endl;
    useThreadSafeQueue();

    return 0;
}
