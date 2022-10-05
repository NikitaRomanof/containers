#include "../s21_vector.h"

#include <algorithm>
#include <cstdio>

#include "gtest/gtest.h"

TEST(vector1, vector_simple_constructor) {
  s21::Vector<int> vec;
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.size(), 0);
}

TEST(vector2, vector_parametrized_constructor) {
  // EXPECT_NO_THROW(s21::Vector<int> vec(5));
  s21::Vector<int> vec1(5);
  std::vector<int> vec2(5);
  ASSERT_EQ(vec1.size(), 5);
  ASSERT_EQ(vec1.size(), vec2.size());
}

TEST(vector3, vector_init_size_constructor) {
  s21::Vector<int> vec{1, 2, 3, 4};
  ASSERT_EQ(vec.size(), 4);
  ASSERT_EQ(vec.at(3), 4);
}

TEST(vector4, vector_copy_constructor) {
  s21::Vector<int> vec2{1, 2, 3, 4};
  s21::Vector<int> vec3(vec2);
  ASSERT_EQ(vec2.size(), vec3.size());
  ASSERT_EQ(vec2.at(2), vec3.at(2));
  // ASSERT_FALSE(vec2.begin() == vec3.begin());
}

TEST(vector5, vector_move_constructor) {
  s21::Vector<int> vec1{1, 2, 3, 4};
  s21::Vector<int> vec2(std::move(vec1));
  ASSERT_EQ(vec2.at(0), 1);
  ASSERT_EQ(vec2.at(1), 2);
  ASSERT_EQ(vec2.at(2), 3);
  ASSERT_EQ(vec2.at(3), 4);
  ASSERT_EQ(vec2.size(), 4);
}

TEST(vector6, vector_at) {
  s21::Vector<int> vec1{1, 2, 3, 4};
  std::vector<int> vec2{1, 2, 3, 4};
  ASSERT_EQ(vec1.at(1), 2);
  ASSERT_EQ(vec1.at(1), vec2.at(1));
  // EXPECT_THROW(vec1.at(256), std::out_of_range);
}

TEST(vector7, vector_operator_square_brackets) {
  s21::Vector<int> vec1{1, 2, 3, 4};
  ASSERT_EQ(vec1[3], 4);
}

TEST(vector8, vector_front) {
  s21::Vector<int> vec1{1, 2, 3, 4};
  std::vector<int> vec2{1, 2, 3, 4};
  int s21_value = vec1.front();
  int std_value = vec2.front();
  ASSERT_EQ(s21_value, 1);
  ASSERT_EQ(s21_value, std_value);
  s21::Vector<int> vec3;
  // EXPECT_THROW(vec3.front(), std::out_of_range);
}

TEST(vector9, vector_back) {
  s21::Vector<int> vec1{1, 2, 3, 4};
  std::vector<int> vec2{1, 2, 3, 4};
  int s21_value = vec1.back();
  int std_value = vec2.back();
  ASSERT_EQ(s21_value, 4);
  ASSERT_EQ(s21_value, std_value);
  s21::Vector<int> vec3;
  // EXPECT_THROW(vec3.back(), std::out_of_range);
}

TEST(vector10, vector_data) {
  s21::Vector<int> vec1;
  std::vector<int> vec2;
  ASSERT_EQ(vec1.data(), nullptr);
  ASSERT_EQ(vec2.data(), nullptr);

  s21::Vector<int> vec3{1, 2, 3};
  std::vector<int> vec4{1, 2, 3};
  int *s21_int_ptr = vec3.data();
  int *std_int_ptr = vec4.data();
  ASSERT_EQ(s21_int_ptr[1], vec3.at(1));
  ASSERT_EQ(std_int_ptr[1], vec4.at(1));
  ASSERT_EQ(s21_int_ptr[1], std_int_ptr[1]);
}

TEST(vector11, vector_empty) {
  s21::Vector<int> vec1;
  std::vector<int> vec2;
  ASSERT_TRUE(vec1.empty());
  ASSERT_TRUE(vec2.empty());
  ASSERT_EQ(vec1.empty(), vec2.empty());
}

TEST(vector12, vector_size) {
  s21::Vector<int> vec1;
  std::vector<int> vec2;
  ASSERT_EQ(vec1.size(), vec2.size());

  s21::Vector<int> vec3{1, 2, 3};
  std::vector<int> vec4{1, 2, 3};
  ASSERT_EQ(vec3.size(), 3);
  ASSERT_EQ(vec3.size(), vec4.size());
}

TEST(vector13, vector_max_size) {
  s21::Vector<int> vec1;
  std::vector<int> vec2;
  ASSERT_EQ(vec1.max_size(), vec2.max_size());

  s21::Vector<int> vec3{1, 2, 3};
  std::vector<int> vec4{1, 2, 3};
  ASSERT_EQ(vec3.max_size(), vec4.max_size());
}

TEST(vector14, vector_reserve) {
  s21::Vector<int> vec1;
  std::vector<int> vec2;
  vec1.reserve(5);
  vec2.reserve(5);
  ASSERT_EQ(vec1.capacity(), 5);
  ASSERT_EQ(vec2.capacity(), 5);

  s21::Vector<int> vec3{1, 2, 3};
  std::vector<int> vec4{1, 2, 3};
  vec3.reserve(10);
  vec4.reserve(10);
  ASSERT_EQ(vec3.at(2), 3);
  ASSERT_EQ(vec4.at(2), 3);
  vec3[7] = 9;
  vec4[7] = 9;
  ASSERT_EQ(vec3.size(), 3);
  // EXPECT_ANY_THROW(vec3.at(7));
  // EXPECT_ANY_THROW(vec3[100]);
  ASSERT_EQ(vec3[7], 9);
  ASSERT_EQ(vec4.size(), 3);
  // EXPECT_ANY_THROW(vec4.at(7));
  ASSERT_EQ(vec4[7], 9);
}

TEST(vector15, vector_shrink_to_fit) {
  s21::Vector<int> vec1;
  std::vector<int> vec2;
  vec1.shrink_to_fit();
  vec2.shrink_to_fit();
  ASSERT_EQ(vec1.capacity(), 0);
  ASSERT_EQ(vec2.capacity(), 0);

  s21::Vector<int> vec3{1, 2, 3};
  std::vector<int> vec4{1, 2, 3};
  vec3.reserve(10);
  vec4.reserve(10);

  vec3.shrink_to_fit();
  vec4.shrink_to_fit();
  ASSERT_EQ(vec3.capacity(), 3);
  ASSERT_EQ(vec3.at(1), 2);
  ASSERT_EQ(vec4.capacity(), 3);
  ASSERT_EQ(vec4.at(1), 2);
}

TEST(vector16, vector_begin) {
  s21::Vector<int> vec1;
  ASSERT_EQ(vec1.begin(), nullptr);

  s21::Vector<int> vec2{1, 2, 3};
  ASSERT_EQ(*vec2.begin(), 1);
}

TEST(vector17, vector_end) {
  s21::Vector<int> vec1;
  ASSERT_EQ(vec1.end(), nullptr);

  s21::Vector<int> vec2{1, 2, 3};
  std::vector<int> vec3{1, 2, 3};
  ASSERT_EQ(*(vec2.end() - 1), 3);
  ASSERT_EQ(*(vec3.end() - 1), 3);
}

TEST(vector18, vector_clear) {
  s21::Vector<int> vec3{1, 2, 3};
  std::vector<int> vec4{1, 2, 3};
  vec3.clear();
  vec4.clear();
  ASSERT_EQ(vec3.size(), 0);
  ASSERT_EQ(vec4.size(), 0);
}

TEST(vector19, vector_insert) {
  s21::Vector<int> vec3{1, 2, 3};
  std::vector<int> vec4{1, 2, 3};
  s21::Vector<int> result{1, 8, 2, 3};
  auto s21it = vec3.begin();
  auto stdit = vec4.begin();
  ++s21it;
  ++stdit;
  vec3.insert(s21it, 8);
  vec4.insert(stdit, 8);
  ASSERT_EQ(vec3[0], vec4[0]);
  ASSERT_EQ(vec3[1], vec4[1]);
  ASSERT_EQ(vec3[2], vec4[2]);
  ASSERT_EQ(vec3[3], vec4[3]);
  ASSERT_EQ(vec3.size(), vec4.size());
  ASSERT_EQ(vec3.capacity(), vec4.capacity());
  // EXPECT_ANY_THROW(vec3.insert(nullptr, 89));
}

TEST(vector20, vector_erase) {
  s21::Vector<int> vec1{1, 2, 3, 4};
  std::vector<int> vec2{1, 2, 3, 4};
  auto s21it = vec1.begin();
  auto stdit = vec2.begin();
  s21it += 2;
  stdit += 2;
  vec1.erase(s21it);
  vec2.erase(stdit);
  ASSERT_EQ(vec1[0], vec2[0]);
  ASSERT_EQ(vec1[1], vec2[1]);
  ASSERT_EQ(vec1[2], vec2[2]);
  ASSERT_EQ(vec1.size(), vec2.size());
  ASSERT_EQ(vec1.capacity(), vec2.capacity());
  // s21::Vector<int> vec3;
  // auto vec3_it = vec3.begin();
  // EXPECT_ANY_THROW(vec3.erase(nullptr));
  // EXPECT_ANY_THROW(vec3.erase(vec3_it));
}

TEST(vector21, vector_push_back) {
  s21::Vector<int> vec1{1, 2, 3};
  std::vector<int> vec2{1, 2, 3};
  vec1.push_back(4);
  vec2.push_back(4);
  ASSERT_EQ(vec1[0], vec2[0]);
  ASSERT_EQ(vec1[1], vec2[1]);
  ASSERT_EQ(vec1[2], vec2[2]);
  ASSERT_EQ(vec1[3], vec2[3]);
  ASSERT_EQ(vec1.size(), vec2.size());
  ASSERT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector22, vector_pop_back) {
  s21::Vector<int> vec1{1, 2, 3, 4};
  std::vector<int> vec2{1, 2, 3, 4};
  vec1.pop_back();
  vec2.pop_back();
  ASSERT_EQ(vec1[0], vec2[0]);
  ASSERT_EQ(vec1[1], vec2[1]);
  ASSERT_EQ(vec1[2], vec2[2]);
  // ASSERT_EQ(vec1[3], vec2[3]);
  ASSERT_EQ(vec1.size(), vec2.size());
  ASSERT_EQ(vec1.capacity(), vec2.capacity());
  // s21::Vector<int> vec3;
  // EXPECT_ANY_THROW(vec3.pop_back());
}

TEST(vector23, vector_swap) {
  s21::Vector<int> vec1{1, 2, 3, 4, 6};
  s21::Vector<int> vec2{5, 6, 7, 8};
  vec1.swap(vec2);
  ASSERT_EQ(vec1[0], 5);
  ASSERT_EQ(vec1[1], 6);
  ASSERT_EQ(vec1[2], 7);
  ASSERT_EQ(vec1[3], 8);

  ASSERT_EQ(vec2[0], 1);
  ASSERT_EQ(vec2[1], 2);
  ASSERT_EQ(vec2[2], 3);
  ASSERT_EQ(vec2[3], 4);
  ASSERT_EQ(vec2[4], 6);

  ASSERT_EQ(vec1.size(), 4);
  ASSERT_EQ(vec2.size(), 5);
}

TEST(vector24, vector_iterators) {
  typename s21::Vector<int>::iterator s21it;
  typename std::vector<int>::iterator stdit;
  s21::Vector<int> vec1{1, 2, 3, 4};
  std::vector<int> vec2{1, 2, 3, 4};
  s21it = vec1.begin();
  stdit = vec2.begin();
  ASSERT_EQ(*s21it, *stdit);
  ++s21it;
  ASSERT_EQ(*s21it, vec1.at(1));
  --s21it;
  ASSERT_EQ(s21it, vec1.begin());
}

TEST(vector25, vector_emplace) {
  s21::Vector<int> s21_vec{1, 2, 3, 4};
  s21_vec.emplace(s21_vec.begin(), 6);
  std::vector<int> std_vec{1, 2, 3, 4};
  std_vec.emplace(std_vec.begin(), 6);
  ASSERT_EQ(s21_vec.size(), std_vec.size());
  ASSERT_EQ(s21_vec.capacity(), std_vec.capacity());
  ASSERT_EQ(s21_vec[0], std_vec[0]);
  ASSERT_EQ(s21_vec[0], 6);
  ASSERT_EQ(6, std_vec[0]);
  ASSERT_EQ(s21_vec.at(1), std_vec.at(1));
}

TEST(vector26, vector_emplace_back) {
  s21::Vector<int> s21_vec{1, 2, 3, 4};
  s21_vec.emplace_back(6);
  std::vector<int> std_vec{1, 2, 3, 4};
  std_vec.emplace_back(6);
  ASSERT_EQ(s21_vec.size(), std_vec.size());
  ASSERT_EQ(s21_vec.capacity(), std_vec.capacity());
  ASSERT_EQ(s21_vec[4], std_vec[4]);
  ASSERT_EQ(s21_vec.at(1), std_vec.at(1));
  s21::Vector<int> s21_vec2{5, 6, 7, 8};
  s21_vec2.emplace_back(9, 0);
  ASSERT_EQ(s21_vec2.at(4), 9);
  ASSERT_EQ(s21_vec2.at(5), 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
