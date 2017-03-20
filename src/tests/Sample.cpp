#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Sprite.h"
#include <SnakeConfig.h>

using ::testing::Test;

class SampleTest : public Test
{
protected:
    SampleTest(){}
    ~SampleTest(){}

    virtual void SetUp(){}
    virtual void TearDown(){}
};

TEST_F(SampleTest, DISABLED_Test1)
{

    CSprite Sprite;
    Sprite.Load(getDataDir() + "/cherryAtNight.bmp");
    Sprite.SetPos(10.0f, 10.0f);

    g_pFramework->Init(800, 600, 16, false);
    g_pFramework->Clear();

    Sprite.Render();

    g_pFramework->Quit();
    g_pFramework->Del();
}
