#include <queue>

#include "../s21_queue.h"
#include "gtest/gtest.h"

TEST(queue, queue_1) {
  s21::queue<int> queue{};
  ASSERT_TRUE(queue.empty());
}

TEST(queue, queue_2) {
  s21::queue<int> queue{};
  queue.push(45);
  ASSERT_EQ(queue.front(), 45);
  ASSERT_EQ(queue.back(), 45);
}

TEST(queue, queue_3) {
  s21::queue<int> queue{1, 2, 3};
  std::queue<int> original;
  original.push(1);
  original.push(2);
  original.push(3);

  while (!queue.empty()) {
    ASSERT_EQ(queue.front(), original.front());
    queue.pop();
    original.pop();
  }
}

TEST(queue, queue_4) {
  s21::queue<int> queue{55, 44, 33};
  ASSERT_EQ(queue.size(), 3);
  ASSERT_EQ(queue.front(), 55);
  ASSERT_EQ(queue.back(), 33);
  queue.pop();
  ASSERT_EQ(queue.front(), 44);
  ASSERT_EQ(queue.back(), 33);
  queue.pop();
  ASSERT_EQ(queue.front(), 33);
  ASSERT_EQ(queue.back(), 33);
  queue.pop();
}

TEST(queue, queue_5) {
  s21::queue<int> queue1{1, 2, 3};
  s21::queue<int> queue2{4, 5, 6, 7};
  queue1.swap(queue2);

  ASSERT_EQ(queue1.size(), 4);
  ASSERT_EQ(queue1.front(), 4);
  ASSERT_EQ(queue1.back(), 7);
  queue1.pop();
  ASSERT_EQ(queue1.back(), 7);
  ASSERT_EQ(queue1.front(), 5);
  queue1.pop();
  ASSERT_EQ(queue1.back(), 7);
  ASSERT_EQ(queue1.front(), 6);
  queue1.pop();
  ASSERT_EQ(queue1.back(), 7);
  ASSERT_EQ(queue1.front(), 7);
  queue1.pop();

  ASSERT_EQ(queue2.size(), 3);
  ASSERT_EQ(queue2.front(), 1);
  ASSERT_EQ(queue2.back(), 3);
  queue2.pop();
  ASSERT_EQ(queue2.front(), 2);
  ASSERT_EQ(queue2.back(), 3);
  queue2.pop();
  ASSERT_EQ(queue2.front(), 3);
  ASSERT_EQ(queue2.back(), 3);
  queue2.pop();
}

TEST(queue, queue_6) {
  s21::queue<double> queue1{45, 56, 67};
  s21::queue<double> queue2(queue1);
  ASSERT_EQ(queue1.size(), queue2.size());
  ASSERT_EQ(queue2.front(), 67);
  ASSERT_EQ(queue2.back(), 45);
  queue2.pop();
  ASSERT_EQ(queue2.front(), 56);
  ASSERT_EQ(queue2.back(), 45);
  queue2.pop();
  ASSERT_EQ(queue2.front(), 45);
  ASSERT_EQ(queue2.back(), 45);
  queue2.pop();
}

TEST(queue, queue_7) {
  s21::queue<int> queue1{1, 2, 3};
  s21::queue<int> queue2{4, 5};
  queue2 = std::move(queue1);
  ASSERT_TRUE(queue1.empty());
  ASSERT_EQ(queue2.front(), 1);
  ASSERT_EQ(queue2.back(), 3);
}

TEST(queue, queue_8) {
  s21::queue<int> queue1{1, 2, 3};
  s21::queue<int> queue2(std::move(queue1));
  ASSERT_TRUE(queue1.empty());
  ASSERT_EQ(queue2.front(), 1);
  ASSERT_EQ(queue2.back(), 3);
}

TEST(queue, queue_9) {
  s21::queue<int> queue{};
  queue.emplace_back(1, 2, 3, 4);
  ASSERT_EQ(queue.front(), 1);
  ASSERT_EQ(queue.back(), 4);
  queue.pop();
  ASSERT_EQ(queue.front(), 2);
  ASSERT_EQ(queue.back(), 4);
  queue.pop();
  ASSERT_EQ(queue.front(), 3);
  ASSERT_EQ(queue.back(), 4);
  queue.pop();
  ASSERT_EQ(queue.front(), 4);
  ASSERT_EQ(queue.back(), 4);
  queue.pop();
}

TEST(queue, queue_10) {
  s21::queue<int> queue(queue);
  ASSERT_TRUE(queue.empty());
}

TEST(queue, queue_11) {
  s21::queue<int> queue{};
  s21::queue<int> queue2(queue);
  ASSERT_TRUE(queue2.empty());
}
