#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SnakeConfig.h>
#include "Sprite.h"
#include "Player.h" //TODO: vorerst notwendig da sonst der ==operator für SDL_Rect fehlt
#include "tests/MockFramework.h"

using ::testing::_;

class SpriteTest : public ::testing::Test
{
    void TearDown()
    {
        g_pFramework->Del();
    }
};

TEST_F(SpriteTest, testSetPosition)
{
    SDL_Rect Rect = {10, 10, 10, 10};

    CSprite Sprite(*g_pFramework);
    Sprite.Load(getDataDir() + "/cherryAtNight.bmp");
    Sprite.SetPos(Rect.x, Rect.y);

    EXPECT_EQ(Rect, Sprite.GetRect());
}

TEST_F(SpriteTest, testRender)
{
    SDL_Rect Rect = {10, 10, 10, 10};

    CSprite Sprite(*g_pFramework);
    Sprite.Load(getDataDir() + "/cherryAtNight.bmp");
    Sprite.SetPos(Rect.x, Rect.y);

    EXPECT_CALL(*g_pFramework, BlitSurface(_, _));
    EXPECT_NO_THROW(Sprite.Render());

    EXPECT_EQ(Rect, Sprite.GetRect());
}

TEST_F(SpriteTest, testRenderPositionNotSet) //TODO: füge auch Implementierung für invalid pos hinzu
{
    CSprite Sprite(*g_pFramework);
    Sprite.Load(getDataDir() + "/cherryAtNight.bmp");

    EXPECT_CALL(*g_pFramework, BlitSurface(_, _))
            .Times(0);
    EXPECT_THROW(Sprite.Render(), const char*);
}
