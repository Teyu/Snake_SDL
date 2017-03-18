#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Test;

class SampleTest : public Test
{
protected:
    SampleTest(){}
    ~SampleTest(){}

    virtual void SetUp(){}
    virtual void TearDown(){}
};

TEST_F(SampleTest, Test1)
{
    ASSERT_TRUE(true);
}
