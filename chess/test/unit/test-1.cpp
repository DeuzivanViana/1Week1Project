#include <gtest/gtest.h>

#include "Exemple.hpp"

TEST(IsHelloWorld, HelloWorld) {
  EXPECT_EQ(HELLO_WORLD, "Hello, World");
}