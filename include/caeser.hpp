// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_CAESER_HPP_
#define INCLUDE_CAESER_HPP_

#include <string>
#include <vector>

size_t CountOf(const std::string& str, char sym);

void StatisticsAlphabet(const std::string& str,
                        std::vector<size_t>& out_statistic);

void Find3Max(const std::vector<size_t>& statistics, size_t& max_index,
              size_t& second_max_index, size_t& third_max_index);

char IndexToSymbol(size_t index);

std::string Decrypt(const std::string& cipher_text, size_t key);

void GenerateCandidates(const std::string& cipher_text,
                        const std::vector<size_t>& keys,
                        std::vector<std::string>& candidates);

#endif // INCLUDE_CAESER_HPP_
