#include <gtest/gtest.h>
#include <stl_containers/stl_unique_ptr.h>

class TestUniquePtr : public ::testing::Test {
protected:
    void SetUp() override {

    };

    void TearDown() override {

    };
};

struct Foo {
    int x;
    int y;

    static int destructor_calls;
    ~Foo() { destructor_calls++; }
};
int Foo::destructor_calls = 0;

TEST_F(TestUniquePtr, Constructor)
{
    Foo* foo = new Foo(1, 2);
    {
        tom::unique_ptr<Foo> tmp(foo);
    }
    ASSERT_EQ(Foo::destructor_calls, 1);
}