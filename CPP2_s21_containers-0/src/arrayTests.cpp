#include "s21_array.h"
#include "gtest/gtest.h"
#include <array>

TEST(array, array_1) {
    s21::array<int, 2> array{4, 5};
    std::array<int, 2> array2{4, 5};
    ASSERT_EQ(array.size(), 2);
    ASSERT_EQ(array[0], 4);
    ASSERT_EQ(array[1], 5);
    ASSERT_EQ(array2.size(), 2);
    ASSERT_EQ(array2[0], 4);
    ASSERT_EQ(array2[1], 5);
}

TEST(array, array_2) {
    s21::array<int, 7> array{4, 5};
    s21::array<int, 7> array2(array);
    ASSERT_EQ(array2.size(), 7);
    ASSERT_EQ(array2[0], 4);
    ASSERT_EQ(array2[1], 5);
}

TEST(array, array_3) {
    s21::array<int, 7> array{4, 5};
    s21::array<int, 7> array2(std::move(array));
    ASSERT_EQ(array2.size(), 7);
    ASSERT_EQ(array2[0], 4);
    ASSERT_EQ(array2[1], 5);
}

TEST(array, array_4) {
    s21::array<int, 3> a =  s21::array<int, 3>();
    a[0] = 4;
    ASSERT_EQ(a[0], 4);
}

TEST(array, array_5) {
    s21::array<int, 3> array{4, 5};
    s21::array<int, 3> array2 =  s21::array<int, 3>();
    array.swap(array2);
    ASSERT_EQ(array[0], 0);
    ASSERT_EQ(array[1], 0);
    ASSERT_EQ(array[2], 0);
}

TEST(array, array_6) {
    s21::array<int, 2> array{4, 5};
    s21::array<int, 2> array2{7, 8};
    array = std::move(array2);
    ASSERT_EQ(array[0], 7);
    ASSERT_EQ(array[1], 8);
}

TEST(array, array_7) {
    s21::array<int, 2> array{4, 5};
    std::array<int, 2> array2{4, 5};
    ASSERT_EQ(array.at(0), 4);
    ASSERT_EQ(array.at(1), 5);
    ASSERT_EQ(array2.at(0), 4);
    ASSERT_EQ(array2.at(1), 5);
}

TEST(array, array_8) {
    s21::array<int, 2> array{1, 9};
    std::array<int, 2> array2{1, 9};
    ASSERT_EQ(array.back(), 9);
    ASSERT_EQ(array.front(), 1);
    ASSERT_EQ(array2.back(), 9);
    ASSERT_EQ(array2.front(), 1);
}

TEST(array, array_9) {
    s21::array<int, 2> array{4, 5};
    std::array<int, 2> array2{4, 5};
    ASSERT_EQ(array.data()[0], 4);
    ASSERT_EQ(array.data()[1], 5);
    ASSERT_EQ(array2.data()[0], 4);
    ASSERT_EQ(array2.data()[1], 5);
}

TEST(array, array_10) {
    s21::array<int, 2> array{4, 5};
    std::array<int, 2> array2{4, 5};
    ASSERT_EQ(*array.begin(), 4);
    ASSERT_EQ(*array2.begin(), 4);
}

TEST(array, array_11) {
    s21::array<int, 2> array{4, 5};
    std::array<int, 2> array2{4, 5};
    ASSERT_FALSE(array.empty());
    ASSERT_FALSE(array2.empty());
}

TEST(array, array_12) {
    s21::array<int, 11> array{4, 5};
    std::array<int, 11> array2{4, 5};
    ASSERT_EQ(array.max_size(), 11);
    ASSERT_EQ(array2.max_size(), 11);
}

TEST(array, array_13) {
    s21::array<int, 3> array{4, 5, 6};
    s21::array<int, 3> array2{7, 8, 9};
    array.swap(array2);
    ASSERT_EQ(array[0], 7);
    ASSERT_EQ(array[1], 8);
    ASSERT_EQ(array[2], 9);

    ASSERT_EQ(array2[0], 4);
    ASSERT_EQ(array2[1], 5);
    ASSERT_EQ(array2[2], 6);
}

TEST(array, array_14) {
    s21::array<int, 3> array{4, 7, 6};
    array.fill(5);
    ASSERT_EQ(array[0], 5);
    ASSERT_EQ(array[1], 5);
    ASSERT_EQ(array[2], 5);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
