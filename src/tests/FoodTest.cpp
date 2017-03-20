#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Food.h>

TEST(FoodTest, setSizeTest) //TODO: can be removed later
{
    CFood Food;
    uint size = 10u;

    Food.setSize(size);
    ASSERT_EQ(size, Food.getPos().h);
    ASSERT_EQ(size, Food.getPos().w);
}

TEST(FoodTest, DISABLED_setSizeTooSmallTest) //TODO: can be removed later
{
    CFood Food;
    uint size = 0u;

    Food.setSize(size);
    ASSERT_EQ(1u, Food.getPos().h);
    ASSERT_EQ(1u, Food.getPos().w);
}

TEST(FoodTest, spawnFormWithinScreenBordersTest)
{
    CFood Food;
    ASSERT_TRUE(Food.spawn());

    auto Pos = Food.getPos();
    EXPECT_GE(Pos.x, 0);
    EXPECT_GE(Pos.y, 0);
    EXPECT_LE(Pos.x, 800); //TODO: remove magic number
    EXPECT_LE(Pos.y, 600);
}

TEST(FoodTest, spawnNewFormWhenPreviousStillExistsTest)
{
    CFood Food;
    ASSERT_TRUE(Food.spawn());
    auto prevPos = Food.getPos();

    ASSERT_FALSE(Food.spawn());
    auto newPos = Food.getPos();

    ASSERT_EQ(prevPos.x, newPos.x); //TODO: implement ==operator for SDL_Rect
    ASSERT_EQ(prevPos.y, newPos.y);
}

TEST(FoodTest, spawnNewFormWhenPreviousNoLongerExistsTest)
{
    CFood Food;
    ASSERT_TRUE(Food.spawn());
    auto prevPos = Food.getPos();

    Food.destroy();
    ASSERT_TRUE(Food.spawn());
    auto newPos = Food.getPos();

    ASSERT_NE(prevPos.x, newPos.x); //TODO: implement ==operator for SDL_Rect
    ASSERT_NE(prevPos.y, newPos.y); //auf diese Weise falsch, da nmindestens eins der beiden ungleich sein muss
}
