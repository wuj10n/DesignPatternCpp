//静态局部对象:在实现懒汉模式的单例的时候，相较于双重检查锁定模式有一种更简单的实现方法并且不会出现线程安全问题，那就是使用静态局部局部对象
#include <iostream>
#include <queue>
using namespace std;

class TaskQueue
{
public:
    // = delete 代表函数禁用, 也可以将其访问权限设置为私有
    TaskQueue(const TaskQueue& obj) = delete;
    TaskQueue& operator=(const TaskQueue& obj) = delete;
    static TaskQueue* getInstance()
    {
        static TaskQueue taskQ;
        return &taskQ;
    }
    void print()
    {
        cout << "hello, world!!!" << endl;
    }

private:
    TaskQueue() = default;
};

int main()
{
    TaskQueue* queue = TaskQueue::getInstance();
    queue->print();
    return 0;
}
