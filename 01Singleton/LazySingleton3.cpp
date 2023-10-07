//双重检查锁定：两个嵌套的 if 来判断单例对象是否为空的操作就叫做双重检查锁定。
//问题：实际上 m_taskQ = new TaskQueue; 在执行过程中对应的机器指令可能会被重新排序。造成返回m_taskQ对象为空
#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
using namespace std;
class TaskQueue
{
public:
    // = delete 代表函数禁用, 也可以将其访问权限设置为私有
    TaskQueue(const TaskQueue& obj) = delete;
    TaskQueue& operator=(const TaskQueue& obj) = delete;
    static TaskQueue* getInstance()
    {
        if (m_taskQ == nullptr)
        {
            m_mutex.lock();
            if (m_taskQ == nullptr)
            {
                m_taskQ = new TaskQueue;
            }
            m_mutex.unlock();
        }
        return m_taskQ;
    }
private:
    TaskQueue() = default;
    static TaskQueue* m_taskQ;
    static mutex m_mutex;
};
TaskQueue* TaskQueue::m_taskQ = nullptr;
mutex TaskQueue::m_mutex;
int main()
{
    TaskQueue* obj = TaskQueue::getInstance();
}