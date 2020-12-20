//
// Created by mrbgn on 15.12.2020.
//

#ifndef TEMPLATE_EXPLORER_HPP
#define TEMPLATE_EXPLORER_HPP
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <iostream>
#include <utility>
#include <algorithm>

using boost::filesystem::path;
using boost::filesystem::filesystem_error;
using boost::filesystem::directory_iterator;
//using boost::
using boost::filesystem::directory_entry;

struct account{
  std::vector<std::string> balance;
  uint32_t file_count;
  std::string acc_id;
  std::string bal_id;
  std::string last_date;
};

class Explorer
{
 public:
  Explorer(std::string& dirPath);
  ~Explorer();
  void Analyze();
  void AccPush(const account& tempAcc);
  void FileAnalyze(const path& filePath);
  void PathAnalyze(const directory_entry& dirEntry);
  void DirAnalyze(const directory_entry& dirPath);
  bool NameAnalyze(const path& filePath);
  bool isNumber(const std::string& fileNamePart);
  void OutPut();
 private:
  std::vector<struct account> _trader;
  path _path;
  directory_iterator _dirIterator;
};

#endif  // TEMPLATE_EXPLORER_HPP
