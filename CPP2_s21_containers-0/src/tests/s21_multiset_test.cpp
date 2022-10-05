#include "../s21_multiset.h"

#include <algorithm>
#include <ostream>

#include "gtest/gtest.h"

TEST(multiset1, initializer_list_constructor) {
  std::multiset<int> std_ms{0, 2, 1, 4, 3, 7, 5, 6, 8};
  s21::multiset<int> s21_ms{0, 2, 1, 4, 3, 7, 5, 6, 8};
  auto std_it = std_ms.begin();
  auto s21_it = s21_ms.begin();
  for (; std_it != std_ms.end(); ++std_it, ++s21_it) {
    ASSERT_EQ(*s21_it, *std_it);
  }
}

TEST(multiset2, copy_constructor) {
  s21::multiset<int> ms1{1, 2, 3, 4, 4, 5, 6, 7};
  s21::multiset<int> ms2(ms1);
  auto ms1_iter = ms1.begin();
  auto ms2_iter = ms2.begin();
  auto ms1_iter_end = ms1.end();
  for (; ms1_iter != ms1_iter_end; ++ms1_iter, ++ms2_iter) {
    ASSERT_EQ(*ms1_iter, *ms2_iter);
  }
  ASSERT_TRUE(ms1.getRoot() != ms2.getRoot());
}

TEST(multiset3, move_constructor) {
  s21::multiset<int> ms1{1, 2, 3, 4, 4, 5, 6, 7};
  int arr[] = {1, 2, 3, 4, 4, 5, 6, 7};
  s21::multiset<int> ms2(std::move(ms1));
  int i = 0;
  for (auto it = ms2.begin(); it != ms2.end(); ++it) {
    ASSERT_EQ(*it, arr[i]);
    ++i;
  }
}

TEST(multiset4, operator_assignment) {
  std::multiset<int> ms1{1, 2, 3, 4, 4, 5, 6, 7};
  std::multiset<int> ms2 = ms1;
  s21::multiset<int> s21_ms1{1, 2, 3, 4, 4, 5, 6, 7};
  s21::multiset<int> s21_ms2 = s21_ms1;
  auto s21_it = s21_ms2.begin();
  for (auto it = ms2.begin(); it != ms2.end(); ++it, ++s21_it) {
    ASSERT_EQ(*it, *s21_it);
  }
}

TEST(multiset5, iterator_begin) {
  s21::multiset<int> s21_ms{-4, 2, 1, 4, 3, 7, 5, 6, 8};
  std::multiset<int> std_ms{-4, 2, 1, 4, 3, 7, 5, 6, 8};
  auto s21_iter = s21_ms.begin();
  auto std_iter = std_ms.begin();
  for (int i = 0; i < 8; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    ++s21_iter;
    ++std_iter;
  }

  s21_iter = s21_ms.begin();
  std_iter = std_ms.begin();
  auto s21_end_iter = s21_ms.end();
  for (; s21_iter != s21_end_iter; ++s21_iter, ++std_iter) {
    ASSERT_EQ(*s21_iter, *std_iter);
  }

  s21_iter = s21_ms.begin();
  std_iter = std_ms.begin();
  for (; std_iter != std_ms.end(); ++s21_iter, ++std_iter) {
    ASSERT_EQ(*s21_iter, *std_iter);
  }
}

TEST(multiset6, iterator_end) {
  s21::multiset<int> s21_ms{0, 2, 1, 4, 3, 7, 5, 6, 8};
  std::multiset<int> std_ms{0, 2, 1, 4, 3, 7, 5, 6, 8};
  auto s21_iter = s21_ms.end();
  auto std_iter = std_ms.end();
  for (int i = 0; i < 8; i++) {
    --s21_iter;
    --std_iter;
    ASSERT_EQ(*s21_iter, *std_iter);
  }

  s21::multiset<int> s21_control{3, 4, 7, 5, 5, 6, 7, 6, 9, 7, 7, 7};
  std::multiset<int> std_control{3, 4, 7, 5, 5, 6, 7, 6, 9, 7, 7, 7};
  auto s21_it = s21_control.end();
  auto std_it = std_control.end();
  --s21_it;
  --std_it;
  for (; s21_it != s21_control.begin(); --s21_it, --std_it) {
    ASSERT_EQ(*s21_it, *std_it);
  }
}

TEST(multiset7, empty) {
  std::multiset<int> std_ms;
  s21::multiset<int> s21_ms;
  ASSERT_EQ(s21_ms.empty(), std_ms.empty());
  std::multiset<int> std_ms2{1, 2};
  s21::multiset<int> s21_ms2{1, 2};
  ASSERT_EQ(s21_ms.empty(), std_ms.empty());
}

TEST(multiset8, size) {
  std::multiset<int> std_ms;
  s21::multiset<int> s21_ms;
  ASSERT_EQ(std_ms.size(), s21_ms.size());
  std::multiset<int> std_ms2{1, 2};
  s21::multiset<int> s21_ms2{1, 2};
  ASSERT_EQ(std_ms2.size(), s21_ms2.size());
}

TEST(multiset9, max_size) {
  std::multiset<int> std_ms;
  ASSERT_EQ(std_ms.max_size(), SIZE_MAX / 80);
}

TEST(multiset10, clear) {
  std::multiset<int> std_ms{1, 2};
  std_ms.clear();
  s21::multiset<int> s21_ms{1, 2};
  s21_ms.clear();
  ASSERT_EQ(s21_ms.size(), std_ms.size());
}

TEST(multiset11, insert) {
  std::multiset<int> std_ms{1, 2};
  std_ms.insert(-3);
  s21::multiset<int> s21_ms{1, 2};
  s21_ms.insert(-3);
  ASSERT_EQ(*s21_ms.begin(), *std_ms.begin());
}

TEST(multiset12, erase) {
  std::multiset<int> std_ms{0, 2, 1, 4, 3, 7, 5, 6, 8};
  auto std_it = std_ms.begin();
  std_ms.erase(std_it);
  s21::multiset<int> s21_ms{0, 2, 1, 4, 3, 7, 5, 6, 8};
  auto s21_it = s21_ms.begin();
  s21_ms.erase(s21_it);
  ASSERT_EQ(s21_ms.size(), std_ms.size());
  std_it = std_ms.begin();
  s21_it = s21_ms.begin();
  ASSERT_EQ(*std_it, *s21_it);
  s21::multiset<double> s21_ms2{3.4,  2.7,  -1.9, 4.6,  4.6, 3.7,
                                1.89, 1.91, 0.3,  2.65, 0.34};
  for (int i = 0; i < 100; ++i) {
    s21_ms2.insert((double)rand() / 5);
  }
  for (int i = 0; i < 5; i++) {
    s21_ms2.erase(s21_ms2.begin());
  }
  ASSERT_FALSE(s21_ms2.empty());
}

TEST(multiset13, swap) {
  std::multiset<int> std_ms1{0, 2, 1, 4, 3, 7, 5, 6, 8};
  std::multiset<int> std_ms2{-12, -16, -18, -27, -23, -21, -21, -15, -11};
  std_ms1.swap(std_ms2);
  ASSERT_EQ(*std_ms1.begin(), -27);
  ASSERT_EQ(*std_ms2.begin(), 0);
}

TEST(multiset14, merge) {
  s21::multiset<int> s21_ms1{4, 5, 6};
  s21::multiset<int> s21_ms2{3, 4, 5};

  s21_ms1.merge(s21_ms2);
  s21::multiset<int> s21_control{3, 4, 4, 5, 5, 6};
  auto it_control = s21_control.begin();
  for (auto it_begin_1 = s21_ms1.begin(); it_begin_1 != s21_ms1.end();
       ++it_begin_1, ++it_control) {
    ASSERT_EQ(*it_begin_1, *it_control);
  }
}

TEST(multiset15, count) {
  s21::multiset<int> s21_control{3, 4, 7, 5, 5, 6, 7, 6, 9, 7, 7, 7};
  ASSERT_EQ(s21_control.count(7), 5);
}

TEST(multiset16, find) {
  std::multiset<int> std_ms{0, 2, 1, 4, 3, 7, 5, 6, 8};
  auto std_find_iter = std_ms.find(6);
  ASSERT_EQ(*std_find_iter, 6);
  std_find_iter = std_ms.find(12);
  ASSERT_EQ(std_find_iter, std_ms.end());

  s21::multiset<int> s21_ms{0, 2, 1, 4, 3, 7, 5, 6, 8};
  auto s21_find_iter = s21_ms.find(6);
  ASSERT_EQ(*s21_find_iter, 6);
  s21_find_iter = s21_ms.find(12);
  ASSERT_EQ(s21_find_iter.current, s21_ms.end().current);
}

TEST(multiset17, contains) {
  s21::multiset<int> s21_ms{0, 2, 1, 4, 3, 7, 5, 6, 8};
  ASSERT_TRUE(s21_ms.contains(3));
  ASSERT_FALSE(s21_ms.contains(11));
}

TEST(multiset18, equal_range) {
  std::multiset<int> std_ms{7, -2, 5, 7, 7, 7, 9, -15, 5};
  auto std_eq = std_ms.equal_range(7);
  s21::multiset<int> s21_ms{7, -2, 5, 7, 7, 7, 9, -15, 5};
  auto s21_eq = s21_ms.equal_range(7);
  ASSERT_EQ(*s21_eq.first, *std_eq.first);
  ASSERT_EQ(*s21_eq.second, *std_eq.second);
}

TEST(multiset19, lower_bound) {
  std::multiset<int> std_ms{7, -2, 5, 7, 7, 7, 9, -15, 5};
  s21::multiset<int> s21_ms{7, -2, 5, 7, 7, 7, 9, -15, 5};
  auto std_lower_bound = std_ms.lower_bound(7);
  auto s21_lower_bound = s21_ms.lower_bound(7);
  ASSERT_EQ(*s21_lower_bound, *std_lower_bound);
}

TEST(multiset20, upper_bound) {
  std::multiset<int> std_ms{7, -2, 5, 7, 7, 7, 9, -15, 5};
  s21::multiset<int> s21_ms{7, -2, 5, 7, 7, 7, 9, -15, 5};
  auto std_upper_bound = std_ms.upper_bound(7);
  auto s21_upper_bound = s21_ms.upper_bound(7);
  ASSERT_EQ(*s21_upper_bound, *std_upper_bound);
}

TEST(multiset21, emplace) {
  s21::multiset<int> s21_ms{1, 2, 3};
  auto s21_pair = s21_ms.emplace(2, 3, 4);
  int control_array[6]{1, 2, 2, 3, 3, 4};
  auto s21_iter = s21_ms.begin();
  for (int i = 0; i < 6; ++i) {
    ASSERT_EQ(control_array[i], *s21_iter);
    ++s21_iter;
  }
  ASSERT_EQ(*s21_pair.first, *s21_ms.find(4));
  ASSERT_TRUE(s21_pair.second);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
