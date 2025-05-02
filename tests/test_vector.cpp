#include <gtest/gtest.h>
#include <stl_containers/stl_vector.h>

class TestVector : public ::testing::Test {
protected:
    void SetUp() override {

    };

    void TearDown() override {

    };
};

TEST_F(TestVector, push_back)
{
    tom::Vector<int> v;
    v.push_back(1);
    ASSERT_EQ(v.size(), 1);
    ASSERT_EQ(v[0], 1);
}

TEST_F(TestVector, FrontBack)
{
    tom::Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    ASSERT_EQ(v.front(), 1);
    ASSERT_EQ(v.back(), 2);
}

struct Foo {
    int x;
    int y;
};

TEST_F(TestVector, EmplaceBack)
{
    tom::Vector<Foo> v;
    v.emplace_back(1, 2);
    Foo& f = v.front();
    ASSERT_EQ(f.x, 1);
    ASSERT_EQ(f.y, 2);
}

TEST_F(TestVector, Move)
{
    tom::Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    tom::Vector<int> v2 = std::move(v1);
    ASSERT_EQ(v1.size(), 0);
    ASSERT_EQ(v2.size(), 2);
    ASSERT_EQ(v2[0], 1);
    ASSERT_EQ(v2[1], 2);
}

TEST_F(TestVector, Copy)
{
    tom::Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    // Copy constructor
    tom::Vector<int> v2 = v1;
    ASSERT_EQ(v1.size(), 2);
    ASSERT_EQ(v2.size(), 2);
    ASSERT_EQ(v1[0], 1);
    ASSERT_EQ(v2[0], 1);
    ASSERT_EQ(v1[1], 2);
    ASSERT_EQ(v2[1], 2);
    v2.push_back(3);
    ASSERT_EQ(v1.size(), 2);
    ASSERT_EQ(v2.size(), 3);

    tom::Vector<int> v3;
    v3.push_back(30);
    // Copy assignment
    v3 = v1;
    ASSERT_EQ(v3[0], 1);
}

TEST_F(TestVector, InitializeSize)
{
    tom::Vector<int> v{ 200 };
    ASSERT_EQ(v.size(), 200);
    ASSERT_EQ(v[0], 0);

    v = tom::Vector<int>( 200, 10 );
    ASSERT_EQ(v.size(), 200);
    ASSERT_EQ(v[0], 10);
}