#include <map>

#include "../s21_map.h"
#include "gtest/gtest.h"

TEST(map, map_default_constr_1) {
  s21::Map<int, float> myMap;
  ASSERT_EQ(myMap.size(), 0);
}

TEST(map, map_initializer_const_1) {
  s21::Map<int, float> myMap{{4, 3.4}, {6, 4.8}, {2, 4.5}};
  ASSERT_EQ(myMap.size(), 3);
}

TEST(map, map_default_constr_2) {
  s21::Map<int, float> myMap{};
  ASSERT_EQ(myMap.size(), 0);
}

TEST(map, map_initializer_const_2) {
  s21::Map<int, float> myMap{{4, 3.4}, {6, 4.8}, {2, 4.5}};
  s21::Map<int, float> myMap2(myMap);
  ASSERT_EQ(myMap2.size(), 3);
}

TEST(map, map_copy_constr) {
  s21::Map<int, float> myMap{};
  s21::Map<int, float> myMap2(myMap);
  ASSERT_EQ(myMap2.size(), 0);
}

TEST(map, map_move_constr_1) {
  s21::Map<int, float> myMap{};
  s21::Map<int, float> myMap2(std::move(myMap));
  ASSERT_EQ(myMap2.size(), 0);
}

TEST(map, map_move_constr_2) {
  s21::Map<int, float> myMap{{4, 3.4}, {6, 4.8}, {2, 4.5}};
  s21::Map<int, float> myMap2(std::move(myMap));
  ASSERT_EQ(myMap2.size(), 3);
  ASSERT_EQ(myMap.size(), 0);
}

TEST(map, map_operator_assign_copy_1) {
  s21::Map<int, float> myMap{{4, 3.4}, {6, 4.8}, {2, 4.5}};
  s21::Map<int, float> myMap2;
  myMap2 = myMap;
  ASSERT_EQ(myMap2.size(), 3);
  ASSERT_EQ(myMap.size(), 3);
}

TEST(map, map_operator_assign_move_1) {
  s21::Map<int, float> myMap{{4, 3.4}, {6, 4.8}, {2, 4.5}};
  s21::Map<int, float> myMap2;
  myMap2 = std::move(myMap);
  ASSERT_EQ(myMap2.size(), 3);
  ASSERT_EQ(myMap.size(), 0);
}

TEST(map, map_at_1) {
  s21::Map<int, std::string> myMap{{4, "first"}, {6, "second"}, {2, "third"}};
  ASSERT_EQ(myMap.at(6), "second");
}

TEST(map, map_at_2) {
  s21::Map<int, std::string> myMap{{4, "first"}, {6, "second"}, {2, "third"}};
  ASSERT_EQ(myMap.at(2), "third");
}

TEST(map, map_at_3) {
  s21::Map<int, std::string> myMap{{4, "first"}, {6, "second"}, {2, "third"}};
  ASSERT_EQ(myMap.at(6), "second");
}

TEST(map, map_operator_SB_1) {
  s21::Map<int, std::string> myMap{{4, "first"}, {6, "second"}, {2, "third"}};
  ASSERT_EQ(myMap[4], "first");
}

TEST(map, map_operator_SB_2) {
  s21::Map<int, std::string> myMap{{4, "first"}, {6, "second"}, {2, "third"}};
  ASSERT_EQ(myMap[4], "first");
}

TEST(map, map_operator_SB_3) {
  s21::Map<int, std::string> myMap{{4, "first"}, {6, "second"}, {2, "third"}};
  myMap[4] = "qwerty";
  ASSERT_EQ(myMap[4], "qwerty");
}

TEST(map, map_operator_SB_4) {
  s21::Map<int, std::string> myMap{};
  myMap[4] = "qwerty";
  ASSERT_EQ(myMap[4], "qwerty");
}

TEST(map, map_empty_1) {
  s21::Map<int, std::string> myMap{};
  ASSERT_TRUE(myMap.empty());
}

TEST(map, map_empty_2) {
  s21::Map<int, std::string> myMap{{4, "first"}, {6, "second"}, {2, "third"}};
  myMap.clear();
  ASSERT_TRUE(myMap.empty());
}

TEST(map, map_empty_3) {
  s21::Map<int, std::string> myMap{};
  myMap.clear();
  ASSERT_TRUE(myMap.empty());
}

TEST(map, map_insert_1) {
  s21::Map<int, std::string> myMap{};
  myMap.insert({5, "qwerty"});
  myMap.insert({8, "qwerty"});
  myMap.insert({9, "qwerty"});
  myMap.insert({4, "qwerty"});
  myMap.insert({6, "qwerty"});
  ASSERT_EQ(myMap[6], "qwerty");
}

TEST(map, map_insert_2) {
  s21::Map<int, std::string> myMap{{4, "first"}, {6, "second"}, {2, "third"}};
  myMap.insert({1, "qwerty"});
  ASSERT_EQ(myMap[1], "qwerty");
}

TEST(map, map_insert_3) {
  s21::Map<int, std::string> myMap{};
  myMap.insert(5, "qwerty");
  myMap.insert(3, "wer");
  myMap.insert(4, "ty");
  ASSERT_EQ(myMap[5], "qwerty");
}

TEST(map, map_insert_4) {
  s21::Map<int, std::string> myMap{{4, "first"}, {6, "second"}, {2, "third"}};
  myMap.insert(1, "qwerty");
  myMap.insert(-1, "qwerty");
  myMap.insert(-2, "qwerty");
  myMap.insert(-3, "qwerty");
  myMap.insert(7, "qwerty");
  myMap.insert(8, "qwerty");
  myMap.insert(9, "qwerty");
  ASSERT_EQ(myMap[1], "qwerty");
}

TEST(map, map_insert_or_assign_1) {
  s21::Map<int, std::string> myMap{};
  myMap.insert_or_assign(4, "first");
  ASSERT_EQ(myMap[4], "first");
}

TEST(map, map_insert_or_assign_2) {
  s21::Map<int, std::string> myMap{{4, "first"}, {6, "second"}, {2, "third"}};
  myMap.insert_or_assign(4, "wer");
  ASSERT_EQ(myMap[4], "wer");
}

TEST(map, map_insert_5) {
  s21::Map<int, std::string> myMap{{4, "first"}, {6, "second"}, {2, "third"}};
  myMap.insert(8, "qwerty");
  ASSERT_EQ(myMap[8], "qwerty");
}

TEST(map, map_swap_1) {
  s21::Map<int, std::string> myMap1{};
  s21::Map<int, std::string> myMap2{};
  myMap1.swap(myMap2);
  ASSERT_TRUE(myMap1.empty());
  ASSERT_TRUE(myMap2.empty());
}

TEST(map, map_swap_2) {
  s21::Map<int, std::string> myMap1{{4, "first"}};
  s21::Map<int, std::string> myMap2{};
  myMap1.swap(myMap2);
  ASSERT_TRUE(myMap1.empty());
  ASSERT_EQ(myMap2.size(), 1);
  ASSERT_EQ(myMap2[4], "first");
}

TEST(map, map_merge_1) {
  s21::Map<int, std::string> myMap1{{8, "qwerty"}};
  s21::Map<int, std::string> myMap2{
      {4, "first"}, {6, "second"}, {2, "third"}, {8, "qwerty"}};
  std::map<int, std::string> stdMap1{{8, "qwerty"}};
  std::map<int, std::string> stdMap2{
      {4, "first"}, {6, "second"}, {2, "third"}, {8, "qwerty"}};
  myMap1.merge(myMap2);
  stdMap1.merge(stdMap2);
  ASSERT_EQ(myMap1.size(), stdMap1.size());
  ASSERT_EQ(myMap2.size(), stdMap2.size());
  ASSERT_TRUE(myMap1.contains(6));
  ASSERT_FALSE(myMap1.contains(11));
}

TEST(map, map_merge_2) {
  s21::Map<int, std::string> myMap1{{8, "qwerty"}};
  s21::Map<int, std::string> myMap2{};
  myMap1.merge(myMap2);
  ASSERT_EQ(myMap1.size(), 1);
  ASSERT_TRUE(myMap1.contains(8));
}

TEST(map, map_merge_3) {
  s21::Map<int, std::string> myMap2{{8, "qwerty"}};
  s21::Map<int, std::string> myMap1{};
  myMap1.merge(myMap2);
  ASSERT_EQ(myMap1.size(), 1);
  ASSERT_TRUE(myMap1.contains(8));
}

TEST(map, map_contains_1) {
  s21::Map<int, std::string> myMap{{4, "first"}, {6, "second"}, {2, "third"}};
  ASSERT_TRUE(myMap.contains(2));
}

TEST(map, map_max_size_1) {
  s21::Map<int, std::string> myMap{};
  std::map<int, std::string> originMap{};
  ASSERT_EQ(myMap.max_size(), originMap.max_size());
}

TEST(map, map_max_size_2) {
  s21::Map<int, float> myMap{};
  std::map<int, float> originMap{};
  ASSERT_EQ(myMap.max_size(), originMap.max_size());
}

TEST(map, map_max_size_3) {
  s21::Map<long long int, float> myMap{};
  std::map<long long int, float> originMap{};
  ASSERT_EQ(myMap.max_size(), originMap.max_size());
}

TEST(map, map_max_size_4) {
  s21::Map<int, int> myMap{};
  std::map<int, int> originMap{};
  ASSERT_EQ(myMap.max_size(), originMap.max_size());
}

TEST(map, map_insert_6) {
  s21::Map<int, std::string> myMap{};
  myMap.insert(5, "qwerty");
  myMap.insert(8, "ке");
  myMap.insert(7, "нг");
  ASSERT_EQ(myMap[5], "qwerty");
}

TEST(map, map_insert_7) {
  s21::Map<int, std::string> myMap{};
  myMap.insert(10, "qwerty");
  myMap.insert(16, "ке");
  myMap.insert(14, "нг");
  myMap.insert(13, "нг");
  myMap.insert(8, "нг");
  myMap.insert(12, "нг");
  ASSERT_EQ(myMap[10], "qwerty");
}

TEST(map, map_erase_1) {
  s21::Map<double, int> map1;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {10, 10};
  std::pair<double, int> ff4 = {14, 10};
  std::pair<double, int> ff5 = {13, 10};
  std::pair<double, int> ff6 = {15, 10};
  std::pair<double, int> ff7 = {17, 10};
  std::pair<double, int> ff8 = {22, 10};
  std::pair<double, int> ff9 = {9, 10};
  std::pair<double, int> ff10 = {15.5, 10};
  map1.insert(f);
  map1.insert(f1);
  map1.insert(ff);
  map1.insert(ff2);
  map1.insert(ff3);
  map1.insert(ff4);
  map1.insert(ff5);
  map1.insert(ff6);
  map1.insert(ff7);
  map1.insert(ff8);
  map1.insert(ff9);
  map1.insert(ff10);
  s21::Map<double, int>::iterator it(map1.begin());
  std::pair<double, int> z = *it;
  ASSERT_EQ(z.first, ff9.first);
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  map1.erase(it);
  ASSERT_EQ(map1.size(), 11);
  s21::Map<double, int>::iterator it2(map1.begin());
  ++it2;
  ++it2;
  ++it2;
  ++it2;
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, ff4.first);
}

TEST(map, map_erase_2) {
  s21::Map<double, int> map1;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {10, 10};
  std::pair<double, int> ff4 = {14, 10};
  std::pair<double, int> ff5 = {13, 10};
  std::pair<double, int> ff6 = {15, 10};
  std::pair<double, int> ff7 = {17, 10};
  std::pair<double, int> ff8 = {22, 10};
  std::pair<double, int> ff9 = {9, 10};
  std::pair<double, int> ff10 = {15.5, 10};
  map1.insert(f);
  map1.insert(f1);
  map1.insert(ff);
  map1.insert(ff2);
  map1.insert(ff3);
  map1.insert(ff4);
  map1.insert(ff5);
  map1.insert(ff6);
  map1.insert(ff7);
  map1.insert(ff8);
  map1.insert(ff9);
  map1.insert(ff10);
  s21::Map<double, int>::iterator it(map1.begin());
  ++it;
  ++it;
  ++it;
  ++it;
  map1.erase(it);
  ASSERT_EQ(map1.size(), 11);
  s21::Map<double, int>::iterator it2(map1.begin());
  ++it2;
  ++it2;
  ++it2;
  ++it2;
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, ff6.first);
}

TEST(map, map_erase_3) {
  s21::Map<double, int> map1;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {10, 10};
  std::pair<double, int> ff4 = {14, 10};
  std::pair<double, int> ff5 = {13, 10};
  std::pair<double, int> ff6 = {15, 10};
  std::pair<double, int> ff7 = {17, 10};
  std::pair<double, int> ff8 = {22, 10};
  std::pair<double, int> ff9 = {9, 10};
  std::pair<double, int> ff10 = {15.5, 10};
  map1.insert(f);
  map1.insert(f1);
  map1.insert(ff);
  map1.insert(ff2);
  map1.insert(ff3);
  map1.insert(ff4);
  map1.insert(ff5);
  map1.insert(ff6);
  map1.insert(ff7);
  map1.insert(ff8);
  map1.insert(ff9);
  map1.insert(ff10);
  s21::Map<double, int>::iterator it(map1.begin());
  ++it;
  ++it;
  map1.erase(it);
  ASSERT_EQ(map1.size(), 11);
  s21::Map<double, int>::iterator it2(map1.begin());
  ++it2;
  ++it2;
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, ff5.first);
}

TEST(map, map_erase_4) {
  s21::Map<double, int> map1;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};

  map1.insert(f);
  map1.insert(f1);
  map1.insert(ff);
  s21::Map<double, int>::iterator it(map1.begin());
  map1.erase(it);
  ASSERT_EQ(map1.size(), 2);
  s21::Map<double, int>::iterator it2(map1.begin());
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, f.first);
}

TEST(map, map_erase_5) {
  s21::Map<double, int> map1;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};

  map1.insert(f);
  map1.insert(f1);
  map1.insert(ff);
  s21::Map<double, int>::iterator it(map1.begin());
  ++it;
  map1.erase(it);
  ASSERT_EQ(map1.size(), 2);
  s21::Map<double, int>::iterator it2(map1.begin());
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, ff.first);
}
TEST(map, map_erase_6) {
  s21::Map<double, int> map1;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  map1.insert(f);
  map1.insert(f1);
  s21::Map<double, int>::iterator it(map1.begin());
  map1.erase(it);
  ASSERT_EQ(map1.size(), 1);
  s21::Map<double, int>::iterator it2(map1.begin());
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, f1.first);
}

TEST(map, map_erase_7) {
  s21::Map<double, int> map1;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {12, 10};
  map1.insert(f);
  map1.insert(f1);
  s21::Map<double, int>::iterator it(map1.begin());
  ++it;
  map1.erase(it);
  ASSERT_EQ(map1.size(), 1);
  s21::Map<double, int>::iterator it2(map1.begin());
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, f1.first);
}

TEST(map, map_erase_8) {
  s21::Map<double, int> map1;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {10, 10};
  map1.insert(f);
  map1.insert(f1);
  map1.insert(ff);
  map1.insert(ff2);
  map1.insert(ff3);
  s21::Map<double, int>::iterator it(map1.begin());
  ++it;
  map1.erase(it);
  ASSERT_EQ(map1.size(), 4);
  s21::Map<double, int>::iterator it2(map1.begin());
  ++it2;
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, f.first);
}

TEST(map, map_erase_9) {
  s21::Map<double, int> map1;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {13, 10};
  map1.insert(f);
  map1.insert(f1);
  map1.insert(ff);
  map1.insert(ff2);
  map1.insert(ff3);
  s21::Map<double, int>::iterator it(map1.begin());

  map1.erase(it);
  ASSERT_EQ(map1.size(), 4);
  s21::Map<double, int>::iterator it2(map1.begin());
  ++it2;
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, f.first);
}

TEST(map, map_erase_10) {
  s21::Map<double, int> map1;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {13, 10};
  std::pair<double, int> ff4 = {10, 10};
  map1.insert(f);
  map1.insert(f1);
  map1.insert(ff);
  map1.insert(ff2);
  map1.insert(ff3);
  map1.insert(ff4);
  s21::Map<double, int>::iterator it(map1.begin());
  ++it;
  map1.erase(it);
  ASSERT_EQ(map1.size(), 5);
  s21::Map<double, int>::iterator it2(map1.begin());
  ++it2;
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, ff3.first);
}

TEST(map, map_erase_11) {
  s21::Map<double, int> map1;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {14, 10};
  std::pair<double, int> ff4 = {10, 10};
  std::pair<double, int> ff5 = {15, 10};
  map1.insert(f);
  map1.insert(f1);
  map1.insert(ff);
  map1.insert(ff2);
  map1.insert(ff3);
  map1.insert(ff4);
  map1.insert(ff5);
  s21::Map<double, int>::iterator it(map1.begin());
  ++it;
  map1.erase(it);
  ASSERT_EQ(map1.size(), 6);
  s21::Map<double, int>::iterator it2(map1.begin());
  ++it2;
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, ff3.first);
}

TEST(map, map_iterator) {
  s21::Map<double, int> map1;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {10, 10};
  std::pair<double, int> ff4 = {14, 10};
  std::pair<double, int> ff5 = {13, 10};
  std::pair<double, int> ff6 = {15, 10};
  std::pair<double, int> ff7 = {17, 10};
  std::pair<double, int> ff8 = {22, 10};
  std::pair<double, int> ff9 = {9, 10};
  std::pair<double, int> ff10 = {15.5, 10};
  map1.insert(f);
  map1.insert(f1);
  map1.insert(ff);
  map1.insert(ff2);
  map1.insert(ff3);
  map1.insert(ff4);
  map1.insert(ff5);
  map1.insert(ff6);
  map1.insert(ff7);
  map1.insert(ff8);
  map1.insert(ff9);
  map1.insert(ff10);
  s21::Map<double, int>::iterator it(map1.begin());
  while (it != map1.end()) {
    ++it;
  }
  --it;
  std::pair<double, int> z2 = *it;
  ASSERT_EQ(z2.first, ff8.first);

  while (it != map1.begin()) {
    --it;
  }
  std::pair<double, int> z3 = *it;
  ASSERT_EQ(z3.first, ff9.first);
}

TEST(map, map_emplace) {
  s21::Map<double, int> map1;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  map1.insert(f);
  map1.insert(f1);
  map1.insert(ff);
  std::pair<double, int> z = {19, 10};
  std::pair<double, int> zz = {11, 10};
  map1.emplace(z, zz);
  s21::Map<double, int>::iterator it(map1.begin());
  std::pair<double, int> z2 = *it;
  ASSERT_EQ(z2.first, zz.first);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
