#include <gtest/gtest.h>

#include <list>
#include <string>

#include "../s21_list.h"

TEST(List, test_default_constructor) {
  s21::List<int> test;
  std::list<int> origin;
  ASSERT_TRUE(test.empty() == origin.empty());
}
TEST(List, test_constructor_init) {
  s21::List<int> test(2);
  std::list<int> origin(2);
  ASSERT_TRUE(test.size() == origin.size());
  ASSERT_TRUE(test.front() == origin.front());
  ASSERT_TRUE(test.back() == origin.back());
}

TEST(List, test_init_list) {
  s21::List<std::string> test{"Hello", " world"};
  std::list<std::string> origin{"Hello", " world"};
  ASSERT_TRUE(test.size() == origin.size());
  ASSERT_TRUE(test.front() == origin.front());
  ASSERT_TRUE(test.back() == origin.back());
}

TEST(List, test_init_list_pair) {
  s21::List<std::pair<int, double>> test{{1, 1.2}, {3, 4.5}};
  std::list<std::pair<int, double>> origin{{1, 1.2}, {3, 4.5}};
  ASSERT_TRUE(test.size() == origin.size());
  ASSERT_TRUE(test.front() == origin.front());
  ASSERT_TRUE(test.back() == origin.back());
}

TEST(List, test_init_list2) {
  s21::List<char> test{'H', 'e', 'l', 'l', 'o', ' ',
                       ' ', 'w', 'o', 'r', 'l', 'd'};
  std::list<char> origin{'H', 'e', 'l', 'l', 'o', ' ',
                         ' ', 'w', 'o', 'r', 'l', 'd'};
  ASSERT_TRUE(test.size() == origin.size());
  ASSERT_TRUE(test.front() == origin.front());
  ASSERT_TRUE(test.back() == origin.back());
}

TEST(List, test_init_list_fail) {
  s21::List<char> test{'H', 'e', 'l', 'l', 'o', ' ',
                       ' ', 'w', 'o', 'r', 'l', 'd'};
  std::list<char> origin{'H', 'e', 'l', 'l', 'o', ' ', ' ',
                         'w', 'o', 'r', 'l', 'd', '!'};
  ASSERT_FALSE(test.size() == origin.size());
  ASSERT_TRUE(test.front() == origin.front());
  ASSERT_FALSE(test.back() == origin.back());
}

TEST(List, test_constructor_copy) {
  s21::List<char> test{'H', 'i'};
  std::list<char> origin{'H', 'i'};
  s21::List<char> testCopy(test);
  std::list<char> originCopy(origin);

  ASSERT_TRUE(testCopy.size() == originCopy.size());
  ASSERT_TRUE(testCopy.front() == originCopy.front());
  ASSERT_TRUE(testCopy.back() == originCopy.back());
}

TEST(List, test_constructor_copy2) {
  s21::List<double> test{1.278453, 9.87654321};
  std::list<double> origin{1.278453, 9.87654321};
  s21::List<double> testCopy(test);
  std::list<double> originCopy(origin);

  ASSERT_TRUE(testCopy.size() == originCopy.size());
  ASSERT_TRUE(testCopy.front() == originCopy.front());
  ASSERT_TRUE(testCopy.back() == originCopy.back());
}

TEST(List, test_constructor_move) {
  s21::List<double> test{1.278453, 9.87654321};
  std::list<double> origin{1.278453, 9.87654321};
  s21::List<double> testMove(std::move(test));
  std::list<double> originMove(std::move(origin));

  ASSERT_TRUE(testMove.size() == originMove.size());
  ASSERT_TRUE(testMove.front() == originMove.front());
  ASSERT_TRUE(testMove.back() == originMove.back());
}

TEST(List, test_iterator) {
  s21::List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  s21::List<double>::iterator testIt = test.begin();
  std::list<double>::iterator originIt = origin.begin();
  while (testIt != test.end()) {
    ASSERT_TRUE(*testIt == *originIt);
    ++testIt;
    ++originIt;
  }
  --testIt;
  --originIt;
  ASSERT_TRUE(*testIt == *originIt);
}

TEST(List, test_ConstIterator_1) {
  s21::List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  s21::List<double>::const_iterator testIt = test.cbegin();
  std::list<double>::const_iterator originIt = origin.cbegin();
  while (testIt != test.end()) {
    ASSERT_TRUE(*testIt == *originIt);
    ++testIt;
    ++originIt;
  }
  --testIt;
  --originIt;
  ASSERT_TRUE(*testIt == *originIt);
}

TEST(List, test_ConstIterator_2) {
  s21::List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  s21::List<double>::const_iterator testIt = test.cend();
  --testIt;
  std::list<double>::const_iterator originIt = origin.cend();
  --originIt;
  while (testIt != test.begin()) {
    ASSERT_TRUE(*testIt == *originIt);
    --testIt;
    --originIt;
  }
  ASSERT_TRUE(*testIt == *originIt);
}

TEST(List, test_clear) {
  s21::List<double> test{1.1, 2.2};
  std::list<double> origin{1.1, 2.2};
  test.clear();
  origin.clear();
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
}

TEST(List, test_pop_back_1) {
  s21::List<double> test{1.1, 2.2};
  std::list<double> origin{1.1, 2.2};
  test.pop_back();
  origin.pop_back();
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
  ASSERT_TRUE(test.back() == origin.back());
}
TEST(List, test_pop_back_2) {
  s21::List<int> test{1};
  std::list<int> origin{1};
  test.pop_back();
  origin.pop_back();
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
}

TEST(List, test_pop_front_1) {
  s21::List<double> test{1.1, 2.2};
  std::list<double> origin{1.1, 2.2};
  test.pop_front();
  origin.pop_front();
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
  ASSERT_TRUE(test.front() == origin.front());
}
TEST(List, test_pop_front_2) {
  s21::List<int> test{1};
  std::list<int> origin{1};
  test.pop_front();
  origin.pop_front();
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
}

TEST(List, test_push_back_1) {
  s21::List<double> test{1.1, 2.2};
  std::list<double> origin{1.1, 2.2};
  test.push_back(3.3);
  origin.push_back(3.3);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_TRUE(test.back() == origin.back());
  ASSERT_TRUE(test.back() == origin.back());
}

TEST(List, test_push_back_2) {
  s21::List<int> test;
  std::list<int> origin;
  test.push_back(1);
  origin.push_back(1);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
  ASSERT_TRUE(test.back() == origin.back());
}

TEST(List, test_push_front_1) {
  s21::List<double> test{1.1, 2.2};
  std::list<double> origin{1.1, 2.2};
  test.push_front(3.3);
  origin.push_front(3.3);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_TRUE(test.back() == origin.back());
  ASSERT_TRUE(test.front() == origin.front());
}

TEST(List, test_push_front_2) {
  s21::List<int> test;
  std::list<int> origin;
  test.push_front(1);
  origin.push_front(1);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
  ASSERT_TRUE(test.front() == origin.front());
}

TEST(List, test_push_front_3) {
  s21::List<double> test{1.1};
  std::list<double> origin{1.1};
  test.push_front(3.3);
  origin.push_front(3.3);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_TRUE(test.back() == origin.back());
  ASSERT_TRUE(test.front() == origin.front());
}

TEST(List, test_swap_1) {
  s21::List<double> test{1.1, 2.2};
  std::list<double> origin{1.1, 2.2};
  s21::List<double> test1{3.3, 4.4};
  std::list<double> origin1{3.3, 4.4};

  test.swap(test1);
  origin.swap(origin1);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_TRUE(test.front() == origin.front());
  ASSERT_TRUE(test.back() == origin.back());
}

TEST(List, test_swap_2) {
  s21::List<double> test{1.1, 2.2};
  std::list<double> origin{1.1, 2.2};
  s21::List<double> test1;
  std::list<double> origin1;
  test.swap(test1);
  origin.swap(origin1);
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_swap_3) {
  s21::List<double> test;
  std::list<double> origin;
  s21::List<double> test1{1.1, 2.2};
  std::list<double> origin1{1.1, 2.2};
  test.swap(test1);
  origin.swap(origin1);
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_erase_1) {
  s21::List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  s21::List<double>::iterator itT = test.begin();
  std::list<double>::iterator itO = origin.begin();
  test.erase(itT);
  origin.erase(itO);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_TRUE(test.front() == origin.front());
  ASSERT_TRUE(test.back() == origin.back());
}

TEST(List, test_erase_2) {
  s21::List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  s21::List<double>::iterator itT = --test.end();
  std::list<double>::iterator itO = --origin.end();
  test.erase(itT);
  origin.erase(itO);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_TRUE(test.front() == origin.front());
  ASSERT_TRUE(test.back() == origin.back());
}
TEST(List, test_erase_3) {
  s21::List<double> test{1.11};
  std::list<double> origin{1.11};
  s21::List<double>::iterator itT = --test.end();
  std::list<double>::iterator itO = --origin.end();
  test.erase(itT);
  origin.erase(itO);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
}

TEST(List, test_insert_1) {
  s21::List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  s21::List<double>::iterator itT = test.begin();
  ++itT;
  ++itT;
  std::list<double>::iterator itO = origin.begin();
  ++itO;
  ++itO;
  itT = test.insert(itT, 777.77);
  itO = origin.insert(itO, 777.77);
  ASSERT_EQ(*itT, *itO);
  itT = test.begin();
  itO = origin.begin();
  itT = test.insert(itT, 777.77);
  itO = origin.insert(itO, 777.77);
  itT = test.insert(itT, 777.77);
  itO = origin.insert(itO, 777.77);
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_insert_2) {
  s21::List<double> test{1.11};
  std::list<double> origin{1.11};
  s21::List<double>::iterator itT;
  itT = test.begin();
  std::list<double>::iterator itO = origin.begin();
  itT = test.insert(itT, 777.77);
  itO = origin.insert(itO, 777.77);
  ASSERT_EQ(*itT, *itO);
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_splice_1) {
  s21::List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  s21::List<double> sT{777.777, 888.88};
  std::list<double> oT{777.777, 888.88};
  s21::List<double>::const_iterator cItT = test.cbegin();
  std::list<double>::const_iterator cItO = origin.cbegin();
  test.splice(cItT, sT);
  origin.splice(cItO, oT);
  s21::List<double>::iterator itT = test.begin();
  std::list<double>::iterator itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
  s21::List<double> sT2{777.777, 888.88};
  std::list<double> oT2{777.777, 888.88};
  cItT = test.end();
  --cItT;
  cItO = origin.end();
  --cItO;
  test.splice(cItT, sT2);
  origin.splice(cItO, oT2);
  itT = test.begin();
  itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_splice_2) {
  s21::List<double> test{1.11};
  std::list<double> origin{1.11};
  s21::List<double> sT{777.777};
  std::list<double> oT{777.777};
  s21::List<double>::const_iterator cItT = test.cbegin();
  std::list<double>::const_iterator cItO = origin.cbegin();
  test.splice(cItT, sT);
  origin.splice(cItO, oT);
  s21::List<double>::iterator itT = test.begin();
  std::list<double>::iterator itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_maxSize_1) {
  s21::List<long double> test;
  std::list<long double> origin;
  ASSERT_EQ(test.max_size(), origin.max_size());
}

TEST(List, test_maxSize_2) {
  s21::List<int> test;
  std::list<int> origin;
  ASSERT_EQ(test.max_size(), origin.max_size());
}
TEST(List, test_maxSize_3) {
  s21::List<std::string> test;
  std::list<std::string> origin;
  ASSERT_EQ(test.max_size(), origin.max_size());
}

TEST(List, test_sort_1) {
  s21::List<double> test{2.22, 5.55, 1.11, 3.33, 4.44};
  std::list<double> origin{2.22, 5.55, 1.11, 3.33, 4.44};
  test.sort();
  origin.sort();
  s21::List<double>::iterator itT = test.begin();
  std::list<double>::iterator itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
}

TEST(List, test_sort_2) {
  s21::List<std::string> test{"2.22", "5.55", "1.11", "3.33", "4.44"};
  std::list<std::string> origin{"2.22", "5.55", "1.11", "3.33", "4.44"};
  test.sort();
  origin.sort();
  s21::List<std::string>::iterator itT = test.begin();
  std::list<std::string>::iterator itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
}

TEST(List, test_merge_1) {
  s21::List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  s21::List<double> tMerge{0.0, 777.777, 888.88};
  std::list<double> oMerge{0.0, 777.777, 888.88};
  test.merge(tMerge);
  origin.merge(oMerge);
  s21::List<double>::iterator itT = test.begin();
  std::list<double>::iterator itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_merge_2) {
  s21::List<std::string> test{"1.11", "2.22", "3.33", "4.44", "5.55"};
  std::list<std::string> origin{"1.11", "2.22", "3.33", "4.44", "5.55"};
  s21::List<std::string> tMerge{"0.0", "777.777", "888.88"};
  std::list<std::string> oMerge{"0.0", "777.777", "888.88"};
  test.merge(tMerge);
  origin.merge(oMerge);
  s21::List<std::string>::iterator itT = test.begin();
  std::list<std::string>::iterator itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_merge_3) {
  s21::List<double> test;
  std::list<double> origin;
  s21::List<double> tMerge{0.0, 777.777, 888.88};
  std::list<double> oMerge{0.0, 777.777, 888.88};
  test.merge(tMerge);
  origin.merge(oMerge);
  s21::List<double>::iterator itT = test.begin();
  std::list<double>::iterator itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_reverse_1) {
  s21::List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  test.reverse();
  origin.reverse();
  s21::List<double>::iterator itT = test.begin();
  std::list<double>::iterator itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
}

TEST(List, test_reverse_2) {
  s21::List<std::string> test{"1.11", "2.22", "3.33", "4.44", "5.55"};
  std::list<std::string> origin{"1.11", "2.22", "3.33", "4.44", "5.55"};
  test.reverse();
  origin.reverse();
  s21::List<std::string>::iterator itT = test.begin();
  std::list<std::string>::iterator itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
}

TEST(List, test_unique_1) {
  s21::List<double> test{1.11, 1.1,  2.22,  2,    3.33, 3.33,
                         3.33, 4.44, 4.445, 5.55, 5.55};
  std::list<double> origin{1.11, 1.1,  2.22,  2,    3.33, 3.33,
                           3.33, 4.44, 4.445, 5.55, 5.55};
  test.unique();
  origin.unique();
  s21::List<double>::iterator itT = test.begin();
  std::list<double>::iterator itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_emplace_back) {
  s21::List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  test.emplace_back(3.0, 42.0, 5.0);
  s21::List<double> check{1.11, 2.22, 3.33, 4.44, 5.55, 3.0, 42.0, 5.0};
  s21::List<double>::iterator itT = test.begin();
  s21::List<double>::iterator itC = test.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itC);
    ++itT;
    ++itC;
  }
  ASSERT_EQ(test.size(), check.size());
}

TEST(List, test_emplace_front) {
  s21::List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  test.emplace_front(3.0, 42.0, 5.0);
  s21::List<double> check{3.0, 42.0, 5.0, 1.11, 2.22, 3.33, 4.44, 5.55};
  s21::List<double>::iterator itT = test.begin();
  s21::List<double>::iterator itC = test.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itC);
    ++itT;
    ++itC;
  }
  ASSERT_EQ(test.size(), check.size());
}

TEST(List, test_emplace_iter) {
  s21::List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  s21::List<double>::const_iterator cIterT = test.cbegin();
  ++cIterT;
  s21::List<double>::iterator cc = test.emplace(cIterT, 3.0, 42.0, 5.0);
  ASSERT_EQ(*cc, 2.22);
  s21::List<double> check{1.11, 3.0, 42.0, 5.0, 2.22, 3.33, 4.44, 5.55};
  s21::List<double>::iterator itT = test.begin();
  s21::List<double>::iterator itC = test.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itC);
    ++itT;
    ++itC;
  }
  ASSERT_EQ(test.size(), check.size());
}

TEST(List, test_operator_assig_l) {
  s21::List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  s21::List<double> test1{1.11, 2.22, 3.33, 4.44, 5.55};
  s21::List<double> check;
  check = test;

  s21::List<double>::iterator itT = test1.begin();
  s21::List<double>::iterator itC = check.begin();
  while (itT != test1.end()) {
    ASSERT_EQ(*itT, *itC);
    ++itT;
    ++itC;
  }
  ASSERT_EQ(test1.size(), check.size());
}

TEST(List, test_operator_assig_r) {
  s21::List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  s21::List<double> test1{1.11, 2.22, 3.33, 4.44, 5.55};
  s21::List<double> check;
  check = std::move(test);
  s21::List<double>::iterator itT = test1.begin();
  s21::List<double>::iterator itC = check.begin();
  while (itT != test1.end()) {
    ASSERT_EQ(*itT, *itC);
    ++itT;
    ++itC;
  }
  ASSERT_EQ(test1.size(), check.size());
}

TEST(List, test_iter_r) {
  s21::List<double> origin{1.1, 2.2};
  s21::List<double> origin1{1.1, 2.2};
  s21::List<double>::iterator a = origin.begin();
  s21::List<double>::iterator a1 = origin.begin();

  s21::List<double>::iterator b = origin1.begin();
  ASSERT_TRUE(a == a1);
  ASSERT_FALSE(a == b);
  ASSERT_TRUE(a != b);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
