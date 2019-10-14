// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include <caeser.hpp>

namespace {
size_t GetKey(size_t index) {
  size_t key = 26 + IndexToSymbol(index) - 'e';
  return key % 26;
}
}  // namespace

TEST(Task1, CountOf) {
  EXPECT_EQ(4, CountOf("qqqq", 'q'));
  EXPECT_EQ(0, CountOf("", 'q'));
  EXPECT_EQ(0, CountOf("qqqq", 'a'));
  EXPECT_EQ(1, CountOf("abcd", 'a'));
  EXPECT_EQ(3, CountOf("addd", 'd'));
  EXPECT_EQ(1, CountOf("abcd", 'd'));
}

TEST(Task2, StatisticsAlphabet) {
  std::vector<size_t> stat;
  StatisticsAlphabet("abcde", stat);
  ASSERT_EQ(26, stat.size());
  EXPECT_EQ(1, stat[0]);
  EXPECT_EQ(1, stat[1]);
  EXPECT_EQ(1, stat[2]);
  EXPECT_EQ(1, stat[3]);
  EXPECT_EQ(1, stat[4]);
  EXPECT_EQ(0, stat[25]);

  StatisticsAlphabet("aaaaa", stat);
  ASSERT_EQ(26, stat.size());
  EXPECT_EQ(5, stat[0]);
  EXPECT_EQ(0, stat[1]);
  EXPECT_EQ(0, stat[2]);
  EXPECT_EQ(0, stat[3]);
  EXPECT_EQ(0, stat[4]);
  EXPECT_EQ(0, stat[25]);

  StatisticsAlphabet("qwertyuiopasdfghjklzxcvbnm", stat);
  ASSERT_EQ(26, stat.size());
  for (size_t cnt : stat) {
    EXPECT_EQ(1, cnt);
  }

  StatisticsAlphabet(
      "qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjk"
      "lzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnm",
      stat);
  ASSERT_EQ(26, stat.size());
  for (size_t cnt : stat) {
    EXPECT_EQ(5, cnt);
  }

  StatisticsAlphabet(
      "QWERTYUIOPASDFGHJKLZXCVBNMQWERTYUIOPASDFGHJKLZXCVBNMQWERTYUIOPASDFGHJK"
      "LZXCVBNMqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiop"
      "asdfghjk"
      "lzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnm",
      stat);
  ASSERT_EQ(26, stat.size());
  for (size_t cnt : stat) {
    EXPECT_EQ(8, cnt);
  }

  StatisticsAlphabet("ABCDEabdeZ", stat);
  ASSERT_EQ(26, stat.size());
  EXPECT_EQ(2, stat[0]);
  EXPECT_EQ(2, stat[1]);
  EXPECT_EQ(2, stat[2]);
  EXPECT_EQ(2, stat[3]);
  EXPECT_EQ(2, stat[4]);
  EXPECT_EQ(1, stat[25]);
}

TEST(Task3, Find3Max) {
  size_t max_index = 0;
  size_t second_max_index = 0;
  size_t third_max_index = 0;

  Find3Max({0}, max_index, second_max_index, third_max_index);
  EXPECT_EQ(0, max_index);
  EXPECT_EQ(0, second_max_index);
  EXPECT_EQ(0, third_max_index);

  Find3Max({0, 1}, max_index, second_max_index, third_max_index);
  EXPECT_EQ(1, max_index);
  EXPECT_EQ(0, second_max_index);
  EXPECT_EQ(0, third_max_index);

  Find3Max({0, 1, 2}, max_index, second_max_index, third_max_index);
  EXPECT_EQ(2, max_index);
  EXPECT_EQ(1, second_max_index);
  EXPECT_EQ(0, third_max_index);

  Find3Max({0, 1, 2, 3, 4, 0, 1, 3}, max_index, second_max_index,
           third_max_index);
  EXPECT_EQ(4, max_index);
  EXPECT_EQ(3, second_max_index);
  EXPECT_EQ(3, third_max_index);

  Find3Max({0, 1, 2, 3, 4, 0, 1, 0}, max_index, second_max_index,
           third_max_index);
  EXPECT_EQ(4, max_index);
  EXPECT_EQ(3, second_max_index);
  EXPECT_EQ(2, third_max_index);
}

TEST(Task4, IndexToSymbol) {
  EXPECT_EQ('a', IndexToSymbol(0));
  EXPECT_EQ('b', IndexToSymbol(1));
  EXPECT_EQ('c', IndexToSymbol(2));
  EXPECT_EQ('d', IndexToSymbol(3));
  EXPECT_EQ('e', IndexToSymbol(4));
  EXPECT_EQ('f', IndexToSymbol(5));

  EXPECT_EQ('x', IndexToSymbol(23));
  EXPECT_EQ('y', IndexToSymbol(24));
  EXPECT_EQ('z', IndexToSymbol(25));
}

TEST(Task5, Decrypt) {
  EXPECT_EQ("zabcde", Decrypt("abcdef", 1));
  EXPECT_EQ("zxy", Decrypt("ayz", 1));
  EXPECT_EQ("abcde", Decrypt("cdefg", 2));
  EXPECT_EQ("abcd", Decrypt("defg", 3));
}

TEST(Task6, GenerateCandidates) {
  std::vector<std::string> candidates;
  GenerateCandidates("defg", {1, 2, 3}, candidates);
  ASSERT_EQ(3, candidates.size());
  EXPECT_EQ("cdef", candidates[0]);
  EXPECT_EQ("bcde", candidates[1]);
  EXPECT_EQ("abcd", candidates[2]);
}

TEST(Tasks, Compose) {
  std::string cipher_text = "a";

  std::vector<size_t> stat;
  StatisticsAlphabet(cipher_text, stat);

  size_t max_index = 0;
  size_t second_max_index = 0;
  size_t third_max_index = 0;
  Find3Max(stat, max_index, second_max_index, third_max_index);

  EXPECT_EQ('a', IndexToSymbol(max_index));
  EXPECT_EQ('b', IndexToSymbol(second_max_index));
  EXPECT_EQ('c', IndexToSymbol(third_max_index));

  std::vector<size_t> candidate_keys = {
      GetKey(max_index),
      GetKey(second_max_index),
      GetKey(third_max_index),
  };

  std::vector<std::string> candidates;
  GenerateCandidates(cipher_text, candidate_keys, candidates);

  ASSERT_EQ(3, candidates.size());
  EXPECT_EQ("a", candidates[0]);
  EXPECT_EQ("a", candidates[1]);
  EXPECT_EQ("a", candidates[2]);
}
