#include <gtest/gtest.h>

#include <set>

#include "../s21_set.h"

TEST(set_test, member_functions) {
  // конструкторы
  s21::set<int> s21_set1;
  std::set<int> std_set1;
  EXPECT_EQ(s21_set1.size(), std_set1.size());

  s21::set<int> s21_set2{3};
  std::set<int> std_set2{3};
  EXPECT_EQ(s21_set2.size(), std_set2.size());

  s21::set<int> s21_set3{1, 2, 3, 4, 5};
  std::set<int> std_set3{1, 2, 3, 4, 5};
  EXPECT_EQ(s21_set3.size(), std_set3.size());

  s21::set<char> s21_set4{'g', 'a', 'b', 'y', 'm'};
  std::set<char> std_set4{'g', 'a', 'b', 'y', 'm'};
  EXPECT_EQ(s21_set4.size(), std_set4.size());

  s21::set<double> s21_set5{50.239543, 15.246353,   7.523653,
                            10.135976, 100.4632975, 79.6593246};
  std::set<double> std_set5{50.239543, 15.246353,   7.523653,
                            10.135976, 100.4632975, 79.6593246};
  EXPECT_EQ(s21_set5.size(), std_set5.size());

  // копирование
  s21::set<int> s21_set6 = s21_set3;
  std::set<int> std_set6 = std_set3;
  EXPECT_EQ(s21_set6.size(), std_set6.size());

  // перенос
  s21::set<int> s21_set7(std::move(s21_set3));
  std::set<int> std_set7(std::move(std_set3));
  EXPECT_EQ(s21_set7.size(), std_set7.size());
  EXPECT_TRUE(s21_set3.empty() == std_set3.empty());
  EXPECT_TRUE(s21_set7.empty() == std_set7.empty());

  // присвоение move
  s21::set<int> s21_set8;
  s21_set8 = std::move(s21_set3);
  std::set<int> std_set8;
  std_set8 = std::move(std_set3);
  EXPECT_EQ(s21_set8.size(), std_set8.size());
  EXPECT_EQ(s21_set3.size(), std_set3.size());

  // initializer_list
  std::initializer_list<int> list{15, 8,  6,  4,  3,  2,   1,
                                  8,  25, 78, 10, 84, 153, -1};
  s21::set<int> s21_set9(list);
  std::set<int> std_set9(list);
  EXPECT_EQ(s21_set9.size(), std_set9.size());
}

TEST(set_test, iterators) {
  // nullptr

  s21::set<int> s21_set0;
  std::set<int> std_set0;
  EXPECT_EQ(s21_set0.size(), std_set0.size());

  s21::set<int>::iterator s21_it01 = s21_set0.begin();
  s21::set<int>::iterator s21_it02 = s21_set0.end();
  std::set<int>::iterator std_it01 = std_set0.begin();
  std::set<int>::iterator std_it02 = std_set0.end();
  EXPECT_TRUE(std_it01 == std_it02);
  EXPECT_TRUE(s21_it01 == s21_it02);

  // !nullptr

  s21::set<int> s21_set1{30, 20, 35, 15, 40};
  std::set<int> std_set1{30, 20, 35, 15, 40};
  EXPECT_EQ(s21_set1.size(), std_set1.size());

  s21::set<int>::iterator s21_it1 = s21_set1.begin();
  s21::set<int>::iterator s21_it2 = s21_set1.end();
  std::set<int>::iterator std_it1 = std_set1.begin();
  std::set<int>::iterator std_it2 = std_set1.end();
  --std_it2;

  EXPECT_FALSE(std_it1 == std_it2);
  EXPECT_FALSE(s21_it1 == s21_it2);
  EXPECT_EQ(*s21_it1, *std_it1);
  EXPECT_EQ(*s21_it2, *std_it2);

  ++s21_it1;
  ++std_it1;
  --s21_it2;
  --std_it2;

  EXPECT_FALSE(std_it1 == std_it2);
  EXPECT_FALSE(s21_it1 == s21_it2);
  EXPECT_EQ(*s21_it1, *std_it1);
  EXPECT_EQ(*s21_it2, *std_it2);

  ++s21_it1;
  ++std_it1;
  --s21_it2;
  --std_it2;

  EXPECT_TRUE(std_it1 == std_it2);
  EXPECT_TRUE(s21_it1 == s21_it2);
  EXPECT_EQ(*s21_it1, *std_it2);
  EXPECT_EQ(*s21_it2, *std_it1);

  ++s21_it1;
  ++std_it1;
  ++s21_it1;
  ++std_it1;
  --s21_it2;
  --std_it2;
  --s21_it2;
  --std_it2;
  EXPECT_EQ(*s21_it1, *std_it1);
  EXPECT_EQ(*s21_it2, *std_it2);

  // OUT OF RANGE
  ++s21_it1;
  ++std_it1;

  // Сложное дерево сбалансированное
  s21::set<int> s21_set2{30, 20, 35, 15, 25, 33, 40, 10,
                         17, 23, 29, 31, 34, 37, 45};
  std::set<int> std_set2{30, 20, 35, 15, 25, 33, 40, 10,
                         17, 23, 29, 31, 34, 37, 45};
  EXPECT_EQ(s21_set2.size(), std_set2.size());

  s21::set<int>::iterator s21_it21 = s21_set2.begin();
  s21::set<int>::iterator s21_it22 = s21_set2.end();
  std::set<int>::iterator std_it21 = std_set2.begin();
  EXPECT_EQ(*s21_it21, *std_it21);

  while (s21_it21 != s21_it22) {
    ++s21_it21;
    ++std_it21;
    EXPECT_EQ(*s21_it21, *std_it21);
  }

  while (s21_it22 != s21_it21) {
    --s21_it21;
    --std_it21;
    EXPECT_EQ(*s21_it21, *std_it21);
  }

  // Сложное дерево не сбалансированное
  s21::set<int> s21_set3{1, 3, 7, 9, 10, 2, 5, 6, 8, 4};
  std::set<int> std_set3{1, 3, 7, 9, 10, 2, 5, 6, 8, 4};
  EXPECT_EQ(s21_set3.size(), std_set3.size());

  s21::set<int>::iterator s21_it31 = s21_set3.begin();
  s21::set<int>::iterator s21_it32 = s21_set3.end();
  std::set<int>::iterator std_it31 = std_set3.begin();
  EXPECT_EQ(*s21_it31, *std_it31);

  while (s21_it31 != s21_it32) {
    ++s21_it31;
    ++std_it31;
    EXPECT_EQ(*s21_it31, *std_it31);
  }

  while (s21_it32 != s21_it31) {
    --s21_it31;
    --std_it31;
    EXPECT_EQ(*s21_it31, *std_it31);
  }

  // char
  s21::set<char> s21_set4{'g', 'a', 'b', 'y', 'm'};
  std::set<char> std_set4{'g', 'a', 'b', 'y', 'm'};
  EXPECT_EQ(s21_set4.size(), std_set4.size());

  s21::set<char>::iterator s21_it41 = s21_set4.begin();
  s21::set<char>::iterator s21_it42 = s21_set4.end();
  std::set<char>::iterator std_it41 = std_set4.begin();
  EXPECT_EQ(*s21_it41, *std_it41);

  while (s21_it41 != s21_it42) {
    ++s21_it41;
    ++std_it41;
    EXPECT_EQ(*s21_it41, *std_it41);
  }

  while (s21_it42 != s21_it41) {
    --s21_it41;
    --std_it41;
    EXPECT_EQ(*s21_it41, *std_it41);
  }

  // double
  s21::set<double> s21_set5{50.239543, 15.246353,   7.523653,
                            10.135976, 100.4632975, 79.6593246};
  std::set<double> std_set5{50.239543, 15.246353,   7.523653,
                            10.135976, 100.4632975, 79.6593246};
  EXPECT_EQ(s21_set5.size(), std_set5.size());

  s21::set<double>::iterator s21_it51 = s21_set5.begin();
  s21::set<double>::iterator s21_it52 = s21_set5.end();
  std::set<double>::iterator std_it51 = std_set5.begin();
  EXPECT_EQ(*s21_it51, *std_it51);

  while (s21_it51 != s21_it52) {
    ++s21_it51;
    ++std_it51;
    EXPECT_EQ(*s21_it51, *std_it51);
  }

  while (s21_it52 != s21_it51) {
    --s21_it51;
    --std_it51;
    EXPECT_EQ(*s21_it51, *std_it51);
  }

  // begin && end
  s21::set<int> s21_set6{30, 20, 35, 25, 33, 40, 23, 29, 31, 34, 37};
  std::set<int> std_set6{30, 20, 35, 25, 33, 40, 23, 29, 31, 34, 37};
  EXPECT_EQ(s21_set6.size(), std_set6.size());

  s21::set<int>::iterator s21_it61 = s21_set6.begin();
  s21::set<int>::iterator s21_it62 = s21_set6.end();
  std::set<int>::iterator std_it61 = std_set6.begin();
  std::set<int>::iterator std_it62 = std_set6.end();
  --std_it62;
  EXPECT_EQ(*s21_it61, *std_it61);
  EXPECT_EQ(*s21_it62, *std_it62);
}

TEST(set_test, set_capacity) {
  s21::set<int> s21_set1;
  std::set<int> std_set1;
  EXPECT_EQ(s21_set1.size(), std_set1.size());

  EXPECT_TRUE(std_set1.empty());
  EXPECT_TRUE(s21_set1.empty());

  s21::set<int> s21_set2{3};
  std::set<int> std_set2{3};
  EXPECT_EQ(s21_set2.size(), std_set2.size());

  EXPECT_FALSE(std_set2.empty());
  EXPECT_FALSE(s21_set2.empty());
}

TEST(set_test, modifiers) {
  s21::set<int> s21_set1;
  std::set<int> std_set1;
  EXPECT_EQ(s21_set1.size(), std_set1.size());

  // insert

  EXPECT_EQ((s21_set1.insert(0).second), (std_set1.insert(0).second));
  EXPECT_TRUE(s21_set1.size() == std_set1.size());

  EXPECT_EQ((s21_set1.insert(1).second), (std_set1.insert(1).second));
  EXPECT_TRUE(s21_set1.size() == std_set1.size());

  EXPECT_EQ((s21_set1.insert(2).second), (std_set1.insert(2).second));
  EXPECT_TRUE(s21_set1.size() == std_set1.size());

  // erase

  std::initializer_list<int> list{30, 20, 35, 15, 25, 33, 40, 10,
                                  17, 23, 29, 31, 34, 37, 45};
  s21::set<int> s21_set2(list);
  std::set<int> std_set2(list);
  EXPECT_EQ(s21_set2.size(), std_set2.size());

  s21::set<int>::iterator s21_it21 = s21_set2.begin();
  std::set<int>::iterator std_it21 = std_set2.begin();
  EXPECT_EQ(*s21_it21, *std_it21);

  s21_set2.erase(s21_set2.find(15));
  std_set2.erase(std_set2.find(15));
  s21_set2.erase(s21_set2.find(35));
  std_set2.erase(std_set2.find(35));
  s21_set2.erase(s21_set2.find(30));
  std_set2.erase(std_set2.find(30));

  s21::set<int>::iterator s21_it31 = s21_set2.begin();
  std::set<int>::iterator std_it31 = std_set2.begin();
  s21::set<int>::iterator s21_it32 = s21_set2.end();
  while (s21_it31 != s21_it32) {
    ++s21_it31;
    ++std_it31;
    EXPECT_EQ(*s21_it31, *std_it31);
  }

  // swap
  s21::set<int> s21_set5{1, 2, 3, 4};
  std::set<int> std_set5{1, 2, 3, 4};
  s21::set<int> s21_set6{6, 7, 8, 9, 10, 11};
  std::set<int> std_set6{6, 7, 8, 9, 10, 11};
  EXPECT_EQ(s21_set5.size(), std_set5.size());
  EXPECT_EQ(s21_set6.size(), std_set6.size());

  s21_set5.swap(s21_set6);
  std_set5.swap(std_set6);
  EXPECT_EQ(s21_set5.size(), std_set5.size());
  EXPECT_EQ(s21_set6.size(), std_set6.size());

  // merge полный
  s21_set6.merge(s21_set5);
  std_set6.merge(std_set5);

  EXPECT_EQ(s21_set5.size(), std_set5.size());
  EXPECT_EQ(s21_set6.size(), std_set6.size());

  // merge не полный
  s21::set<int> s21_set7{2, 7, 11, 12, 13, 14};
  std::set<int> std_set7{2, 7, 11, 12, 13, 14};
  s21_set6.merge(s21_set7);
  std_set6.merge(std_set7);
  EXPECT_EQ(s21_set6.size(), std_set6.size());
  EXPECT_EQ(s21_set7.size(), std_set7.size());
}

TEST(set_test, lookup) {
  // find
  std::initializer_list<int> list{30, 20, 35, 15, 25, 33, 40, 10,
                                  17, 23, 29, 31, 34, 37, 45};
  s21::set<int> s21_set1(list);
  std::set<int> std_set1(list);
  EXPECT_EQ(s21_set1.size(), std_set1.size());

  s21::set<int>::iterator s21_it21 = s21_set1.find(25);
  std::set<int>::iterator std_it21 = std_set1.find(25);
  EXPECT_EQ(*s21_it21, *std_it21);

  s21_it21 = s21_set1.find(17);
  std_it21 = std_set1.find(17);
  EXPECT_EQ(*s21_it21, *std_it21);

  // contains
  EXPECT_TRUE(s21_set1.contains(29));
  while (s21_it21 != s21_set1.end()) {
    ++s21_it21;
    EXPECT_TRUE(s21_set1.contains(*s21_set1.find(*s21_it21)));
  }
}

TEST(set_test, bonus) {
  std::initializer_list<int> list{30, 20, 35, 15, 25, 33, 40, 10,
                                  17, 23, 29, 31, 34, 37, 45};
  s21::set<int> s21_set1;
  std::set<int> std_set1(list);
  s21_set1.emplace(30, 20, 35, 15, 25, 33, 40, 10, 17, 23, 29, 31, 34, 37, 45);
  EXPECT_EQ(s21_set1.size(), std_set1.size());
  s21::set<int>::iterator s21_it11 = s21_set1.begin();
  std::set<int>::iterator std_it11 = std_set1.begin();
  s21::set<int>::iterator s21_it12 = s21_set1.end();
  while (s21_it11 != s21_it12) {
    ++s21_it11;
    ++std_it11;
    EXPECT_EQ(*s21_it11, *std_it11);
  }
}

TEST(set_test, support) {
  std::initializer_list<int> list{30, 20, 35, 15, 25, 33, 40, 10,
                                  17, 23, 29, 31, 34, 37, 45};
  s21::set<int> s21_set1(list);
  EXPECT_EQ(s21_set1.size(), 15);
  s21_set1.s21_print_set();
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
