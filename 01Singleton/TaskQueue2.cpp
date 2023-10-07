#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <functional>
#include <memory>
#include<string>
//单例模板类
template<typename T>
class EagerSingleton
{
private:
    static T* t_;

public:
    static T& GetInstance()
    {
        return *t_;
    }

    EagerSingleton(T&&) = delete;
    EagerSingleton(const T&) = delete;
    void operator= (const T&) = delete;

protected:
    EagerSingleton() = default;
    virtual ~EagerSingleton() = default;
};
// 任务队列的类，继承自单例模板类
template<typename T>
T* EagerSingleton<T>::t_ = new (std::nothrow) T;

class TaskQueue:public EagerSingleton<TaskQueue>
{
public:
    // = delete 代表函数禁用, 也可以将其访问权限设置为私有
    TaskQueue(const TaskQueue& obj) = delete;
    TaskQueue& operator=(const TaskQueue& obj) = delete;
    static TaskQueue* getInstance()
    {
        return &m_obj;
    }
    // 任务队列是否为空
    bool isEmpty()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        bool flag = m_taskQ.empty();
        return flag;
    }
    // 添加任务
    void addTask(std::function<void()> task)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        m_taskQ.push(task);
    }
    std::function<void()> getTask() { // 从队列中取出一个任务
        std::lock_guard<std::mutex> locker(m_mutex); // 上锁
        if (m_taskQ.empty()) { // 队列为空，返回空函数
            return []{};
        }
        auto task = m_taskQ.front(); // 取出队首元素
         m_taskQ.pop(); // 出队
        return task; // 返回任务函数
    }
    // 删除一个任务
    bool popTask()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        if (!m_taskQ.empty())
        {
            m_taskQ.pop();
            return true;
        }
        return false;
    }
private:
    TaskQueue() = default;
    static TaskQueue m_obj;
    std::queue<std::function<void()>> m_taskQ;
    std::mutex m_mutex;
};
TaskQueue TaskQueue::m_obj;
// WorkItem 类的定义，是一个抽象的基类
class WorkItem {
public:
    // 构造函数，接受一个任务名
    WorkItem(const std::string& name) : name_(name) {}

    // 虚析构函数，用于支持多态
    virtual ~WorkItem() {}

    // 纯虚函数，用于执行任务的具体逻辑，由子类实现
    virtual void run() = 0;

    // 获取任务名
    std::string getName() const {
        return name_;
    }

private:
    std::string name_; // 任务名
};

// PrintTask 类的定义，继承自 WorkItem 类
class PrintTask : public WorkItem {
public:
    // 构造函数，调用基类的构造函数
    PrintTask(const std::string& name) : WorkItem(name) {}

    // 重写 run 方法，打印任务名
    void run() override {
        std::cout << "###Running task: " << getName() <<"### ";
    }
};
int main()
{
  
    // 创建三个任务对象
    std::thread t1([]() {
        TaskQueue* taskQ = TaskQueue::getInstance();
        for (int i = 0; i < 100; ++i)
        {
            auto task=std::make_shared<PrintTask>("task"+std::to_string(i+100));
            taskQ->addTask(std::bind(&PrintTask::run,task));
            std::cout << "+++push task: " << i + 100 << ", threadID: " 
                << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });
    std::thread t2([]() {
        TaskQueue* taskQ = TaskQueue::getInstance();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        while (!taskQ->isEmpty())
        {
            std::cout << "---take task: ";taskQ->getTask()();
            std::cout<< " threadID: " 
                << std::this_thread::get_id() << std::endl;
            taskQ->getTask()();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
        std::thread t3([]() {
        TaskQueue* taskQ = TaskQueue::getInstance();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        while (!taskQ->isEmpty())
        {
            std::cout << "---take task: ";taskQ->getTask()();
            std::cout<< " threadID: " 
                << std::this_thread::get_id() << std::endl;
            taskQ->getTask()();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    t1.join();
    t2.join();
    t3.join();
}
