#include <stack>

#include "../s21_stack.h"
#include "gtest/gtest.h"
#include "queueTests.cpp"

TEST(stack, stack_1) {
  s21::stack<int> stack{};
  ASSERT_TRUE(stack.empty());
}

TEST(stack, stack_2) {
  s21::stack<int> stack{};
  stack.push(45);
  ASSERT_EQ(stack.top(), 45);
}

TEST(stack, stack_3) {
  s21::stack<int> stack{1, 2, 3};
  std::stack<int> original;
  original.push(1);
  original.push(2);
  original.push(3);

  while (!stack.empty()) {
    ASSERT_EQ(stack.top(), original.top());
    stack.pop();
    original.pop();
  }
}

TEST(stack, stack_4) {
  s21::stack<int> stack{55, 44, 33};
  ASSERT_EQ(stack.size(), 3);
  ASSERT_EQ(stack.top(), 33);
  stack.pop();
  ASSERT_EQ(stack.top(), 44);
  stack.pop();
  ASSERT_EQ(stack.top(), 55);
  stack.pop();
}

TEST(stack, stack_5) {
  s21::stack<int> stack1{1, 2, 3};
  s21::stack<int> stack2{4, 5, 6, 7};
  stack1.swap(stack2);
  ASSERT_EQ(stack1.size(), 4);
  ASSERT_EQ(stack1.top(), 7);
  stack1.pop();
  ASSERT_EQ(stack1.top(), 6);
  stack1.pop();
  ASSERT_EQ(stack1.top(), 5);
  stack1.pop();
  ASSERT_EQ(stack1.top(), 4);
  stack1.pop();
  ASSERT_EQ(stack2.size(), 3);
  ASSERT_EQ(stack2.top(), 3);
  stack2.pop();
  ASSERT_EQ(stack2.top(), 2);
  stack2.pop();
  ASSERT_EQ(stack2.top(), 1);
  stack2.pop();
}

TEST(stack, stack_6) {
  s21::stack<int> stack1{1, 2, 3};
  s21::stack<int> stack2(std::move(stack1));
  ASSERT_TRUE(stack1.empty());
  ASSERT_EQ(stack2.top(), 3);
}

TEST(stack, stack_7) {
  s21::stack<int> stack1{1, 2, 3};
  s21::stack<int> stack2{4, 5};
  stack2 = std::move(stack1);
  ASSERT_TRUE(stack1.empty());
  ASSERT_EQ(stack2.top(), 3);
}

TEST(stack, stack_8) {
  s21::stack<int> stack{};
  stack.emplace_front(1, 2, 3, 4);
  ASSERT_EQ(stack.top(), 4);
  stack.pop();
  ASSERT_EQ(stack.top(), 3);
  stack.pop();
  ASSERT_EQ(stack.top(), 2);
  stack.pop();
  ASSERT_EQ(stack.top(), 1);
  stack.pop();
}

TEST(stack, stack_9) {
  s21::stack<int> stack{};
  stack.emplace_front();
  ASSERT_TRUE(stack.empty());
}

TEST(stack, stack_10) {
  s21::stack<std::string> stack{"a", "b", "c"};
  ASSERT_EQ(stack.size(), 3);
  ASSERT_EQ(stack.top(), "c");
  stack.pop();
  ASSERT_EQ(stack.top(), "b");
  stack.pop();
  ASSERT_EQ(stack.top(), "a");
  stack.pop();
}

TEST(stack, stack_11) {
  s21::stack<double> stack1{45, 56, 67};
  s21::stack<double> stack2(stack1);
  ASSERT_EQ(stack1.size(), stack2.size());
  ASSERT_EQ(stack2.top(), 67);
  stack2.pop();
  ASSERT_EQ(stack2.top(), 56);
  stack2.pop();
  ASSERT_EQ(stack2.top(), 45);
  stack2.pop();
}

TEST(stack, stack_12) {
  s21::stack<double> stack1{};
  s21::stack<double> stack2(stack1);
  ASSERT_EQ(stack2.size(), 0);
}

TEST(stack, stack_13) {
  s21::stack<double> stack2(stack2);
  ASSERT_EQ(stack2.size(), 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
