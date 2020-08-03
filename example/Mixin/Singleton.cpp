#include "FTC/Mixin/Singleton.hpp"

#include "FTC/Debug/ObjBehaviourTester.hpp"

#include <iostream>

using namespace ftc;

class A
    : public GlobalSingleton<A>
    , public ObjBehaviourTester<>
{
public:
    A() : ObjBehaviourTester<>("A") {}
    ~A() = default;

    int GetId() { return 'A'; }
};

class AWithCreator;
struct ACreator
{
    AWithCreator operator()();
};

class AWithCreator
    : public GlobalSingleton<AWithCreator, ACreator>
    , public ObjBehaviourTester<>
{
public:
    AWithCreator(int idOffset) : ObjBehaviourTester<>("AWithCreator"), idOffset(idOffset) {}
    ~AWithCreator() = default;

    int GetId() { return 'A' + idOffset; }

private:
    int idOffset;
};

AWithCreator ACreator::operator()()
{
    return AWithCreator(100);
}

class B
    : public StaticSingleton<B>
    , public ObjBehaviourTester<>
{
public:
    B() : ObjBehaviourTester<>("B") {}
    ~B() = default;

    int GetId() { return 'B'; }
};

class C
    : public DelayedStaticSingleton<C>
    , public ObjBehaviourTester<>
{
public:
    C(int idOffset) : ObjBehaviourTester<>("C"), idOffset(idOffset) {}
    ~C() = default;

    int GetId() { return 'C' + idOffset; }

private:
    int idOffset;
};

int main()
{
    std::cout << "========== main() started ==========\n";
    std::cout << A::Get().GetId() << '\n';
    std::cout << AWithCreator::Get().GetId() << '\n';
    std::cout << B::Get().GetId() << '\n';
    std::cout << C::Get(1000).GetId() << '\n';
    std::cout << C::Get(2000).GetId() << '\n';

    std::cout << "========== main() ended ==========\n";
}