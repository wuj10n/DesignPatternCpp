#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
using namespace std;
class TaskQueue
{
public:
    // = delete 代表函数禁用, 也可以将其访问权限设置为私有
    TaskQueue(const TaskQueue& obj) = delete;
    TaskQueue& operator=(const TaskQueue& obj) = delete;
    static TaskQueue* getInstance()
    {
        TaskQueue* queue = m_taskQ.load();  
        if (queue == nullptr)
        {
            // m_mutex.lock();  // 加锁: 方式1
            lock_guard<mutex> locker(m_mutex);  // 加锁: 方式2
            queue = m_taskQ.load();
            if (queue == nullptr)
            {
                queue = new TaskQueue;
                m_taskQ.store(queue);
            }
            // m_mutex.unlock();
        }
        return queue;
    }

    void print()
    {
        cout << "hello, world!!!" << endl;
    }
private:
    TaskQueue() = default;
    static atomic<TaskQueue*> m_taskQ;
    static mutex m_mutex;
};
atomic<TaskQueue*> TaskQueue::m_taskQ;
mutex TaskQueue::m_mutex;

int main()
{
    TaskQueue* queue = TaskQueue::getInstance();
    queue->print();
    return 0;
}
