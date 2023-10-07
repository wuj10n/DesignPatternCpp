#include <iostream>
using namespace std;
// 人造恶魔果实· 绵羊形态
class SheepSmile
{
public:
    void transform()
    {
        cout << "变成人兽 -- 山羊人形态..." << endl;
    }
    void ability()
    {
        cout << "将手臂变成绵羊角的招式 -- 巨羊角" << endl;
    }
};

// 人造恶魔果实· 狮子形态
class LionSmile
{
public:
    void transform()
    {
        cout << "变成人兽 -- 狮子人形态..." << endl;
    }
    void ability()
    {
        cout << "火遁· 豪火球之术..." << endl;
    }
};

// 人造恶魔果实· 蝙蝠形态
class BatSmile
{
public:
    void transform()
    {
        cout << "变成人兽 -- 蝙蝠人形态..." << endl;
    }
    void ability()
    {
        cout << "声纳引箭之万剑归宗..." << endl;
    }
};

enum class Type:char{SHEEP, LION, BAT};

// 恶魔果实工厂类
class SmileFactory
{
public:
    enum class Type:char{SHEEP, LION, BAT};
    SmileFactory() {}
    ~SmileFactory() {}
    void* createSmile(Type type)
    {
        void* ptr = nullptr;
        switch (type)
        {
        case Type::SHEEP:
            ptr = new SheepSmile;
            break;
        case Type::LION:
            ptr = new LionSmile;
            break;
        case Type::BAT:
            ptr = new BatSmile;
            break;
        default:
            break;
        }
        return ptr;
    }
};

int main()
{
    SmileFactory* factory = new SmileFactory;
    BatSmile* batObj = (BatSmile*)factory->createSmile(Type::BAT);
    return 0;
}
