#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// 桑尼号
class SunnyShip
{
public:
    // 添加零件
    void addParts(string name)
    {
        m_parts.push_back(name);
    }
    void showParts()
    {
        for (const auto& item : m_parts)
        {
            cout << item << "   ";
        }
        cout << endl;
    }
private:
    vector<string> m_parts;
};

// 梅利号
class MerryShip
{
public:
    // 组装
    void assemble(string name, string parts)
    {
        m_patrs.insert(make_pair(name, parts));
    }
    void showParts()
    {
        for (const auto& item : m_patrs)
        {
            cout << item.first << ": " << item.second << "  ";
        }
        cout << endl;
    }
private:
    map<string, string> m_patrs;
};
// 生成器类
class ShipBuilder
{
public:
    virtual void reset() = 0;
    virtual void buildBody() = 0;
    virtual void buildWeapon() = 0;
    virtual void buildEngine() = 0;
    virtual void buildInterior() = 0;
    virtual ~ShipBuilder() {}
};
// 桑尼号生成器
class SunnyBuilder : public ShipBuilder
{
public:
    SunnyBuilder()
    {
        reset();
    }
    ~SunnyBuilder()
    {
        if (m_sunny != nullptr)
        {
            delete m_sunny;
        }
    }
    // 提供重置函数, 目的是能够使用生成器对象生成多个产品
    void reset() override
    {
        m_sunny = new SunnyShip;
    }
    void buildBody() override
    {
        m_sunny->addParts("神树亚当的树干");
    }
    void buildWeapon() override
    {
        m_sunny->addParts("狮吼炮");
    }
    void buildEngine() override
    {
        m_sunny->addParts("可乐驱动");
    }
    void buildInterior() override
    {
        m_sunny->addParts("豪华内室精装");
    }
    SunnyShip* getSunny()
    {
        SunnyShip* ship = m_sunny;
        m_sunny = nullptr;
        return ship;
    }
private:
    SunnyShip* m_sunny = nullptr;
};
// 梅利号生成器
class MerryBuilder : public ShipBuilder
{
public:
    MerryBuilder()
    {
        reset();
    }
    ~MerryBuilder()
    {
        if (m_merry != nullptr)
        {
            delete m_merry;
        }
    }
    void reset() override
    {
        m_merry = new MerryShip;
    }
    void buildBody() override
    {
        m_merry->assemble("船体", "优质木材");
    }
    void buildWeapon() override
    {
        m_merry->assemble("武器", "四门大炮");
    }
    void buildEngine() override
    {
        m_merry->assemble("动力", "蒸汽机");
    }
    void buildInterior() override
    {
        m_merry->assemble("内室", "精装");
    }
    MerryShip* getMerry()
    {
        MerryShip* ship = m_merry;
        m_merry = nullptr;
        return ship;
    }
private:
    MerryShip* m_merry = nullptr;
};
// 主管类
class Director
{
public:
    void setBuilder(ShipBuilder* builder)
    {
        m_builder = builder;
    }
    // 简约型
    void builderSimpleShip()
    {
        m_builder->buildBody();
        m_builder->buildEngine();
    }
    // 标准型
    void builderStandardShip()
    {
        builderSimpleShip();
        m_builder->buildWeapon();
    }
    // 豪华型
    void builderRegalShip()
    {
        builderStandardShip();
        m_builder->buildInterior();
    }
private:
    ShipBuilder* m_builder = nullptr;
};
// 建造桑尼号
void builderSunny()
{
    Director* director = new Director;
    SunnyBuilder* builder = new SunnyBuilder;
    // 简约型
    director->setBuilder(builder);
    director->builderSimpleShip();
    SunnyShip* sunny = builder->getSunny();
    sunny->showParts();
    delete sunny;

    // 标准型
    builder->reset();
    director->setBuilder(builder);
    director->builderStandardShip();
    sunny = builder->getSunny();
    sunny->showParts();
    delete sunny;

    // 豪华型
    builder->reset();
    director->setBuilder(builder);
    director->builderRegalShip();
    sunny = builder->getSunny();
    sunny->showParts();
    delete sunny;
    delete builder;
    delete director;
}

// 建造梅利号
void builderMerry()
{
    Director* director = new Director;
    MerryBuilder* builder = new MerryBuilder;
    // 简约型
    director->setBuilder(builder);
    director->builderSimpleShip();
    MerryShip* merry = builder->getMerry();
    merry->showParts();
    delete merry;

    // 标准型
    builder->reset();
    director->setBuilder(builder);
    director->builderStandardShip();
    merry = builder->getMerry();
    merry->showParts();
    delete merry;

    // 豪华型
    builder->reset();
    director->setBuilder(builder);
    director->builderRegalShip();
    merry = builder->getMerry();
    merry->showParts();
    delete merry;
    delete builder;
    delete director;
}

int main()
{
    builderSunny();
    cout << "=====================================" << endl;
    builderMerry();
}