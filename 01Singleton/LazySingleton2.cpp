//加了一把互斥锁，解决多线程问题，但是性能不好
#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
class TaskQueue
{
public:
    // = delete 代表函数禁用, 也可以将其访问权限设置为私有
    TaskQueue(const TaskQueue& obj) = delete;
    TaskQueue& operator=(const TaskQueue& obj) = delete;
    static TaskQueue* getInstance()
    {
        m_mutex.lock();
        if (m_taskQ == nullptr)
        {
            m_taskQ = new TaskQueue;
        }
        m_mutex.unlock();
        return m_taskQ;
    }
private:
    TaskQueue() = default;
    static TaskQueue* m_taskQ;
    static std::mutex m_mutex;
};
TaskQueue* TaskQueue::m_taskQ = nullptr;
std::mutex TaskQueue::m_mutex;
int main()
{
    TaskQueue* obj = TaskQueue::getInstance();
}