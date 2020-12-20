//
// Created by mrbgn on 15.12.2020.
//

#include "Explorer.hpp"

Explorer::Explorer(std::string &dirPath)
{
  try {
    _path = path(dirPath);
    _dirIterator = directory_iterator(_path);
  } catch (...) {
    _path = path(".");
    _dirIterator = directory_iterator(_path);

  }
}

Explorer::~Explorer()
{
  for (account& acc : _trader)
  {
    acc.balance.clear();
  }
  _trader.clear();
}

void Explorer::AccPush(const account& tempAcc)
{
  for (auto& x : _trader)
  {
    if (x.acc_id == tempAcc.acc_id && x.bal_id == tempAcc.bal_id)
    {
      x.file_count++;
      x.balance.push_back(tempAcc.balance[0]);
      if (x.last_date < tempAcc.last_date) x.last_date = tempAcc.last_date;
      return;
    }
  }

  _trader.push_back(tempAcc);

}

void Explorer::PathAnalyze(const directory_entry& dirEntry)
{
  if (is_regular_file(dirEntry)) FileAnalyze(dirEntry.path());
  if (is_directory(dirEntry)) DirAnalyze(dirEntry);
  if (is_symlink(dirEntry))
  {
    std::cout << "Symlink " << read_symlink(dirEntry.path()).filename() << std::endl;
  }
}

bool Explorer::isNumber(const std::string& fileNamePart)
{
  const std::string number = "0123456789";
  std::size_t found;
  for (const auto& part : fileNamePart) {
    found = number.find(part);
    if (found == std::string::npos) return false;
  }
  return true;
}



bool Explorer::NameAnalyze(const path& filePath) {
  const std::string balance = "balance";
  const std::string trueFileExt = ".txt";
  const std::string falseFileExt = "old";
  const std::string sep = "_";
  const uint32_t trueFileLength = 25;
  const uint32_t secSepStart = 16;
  const uint32_t firstNumberStart = 8;
  const uint32_t secNumberStart = 17;
  const uint32_t numberLength = 8;
  const uint32_t balanceLength = balance.length();
  const std::string fileName = filePath.stem().string();
  const std::string fileExt = filePath.extension().string();

  std::size_t found;

  if (fileExt == trueFileExt) {
    found = fileName.find(falseFileExt);
    if (found == std::string::npos) {
      if (fileName.length() == trueFileLength) {
        found = fileName.find(balance);
        if (found != std::string::npos) {
          if (found == 0) {
            if (fileName.substr(balanceLength, 1) == sep &&
                fileName.substr(secSepStart, 1) == sep) {
              if (isNumber(fileName.substr(firstNumberStart, numberLength)) &&
                  isNumber(fileName.substr(secNumberStart, numberLength))) {
                return true;
              } else
                return false;
            } else
              return false;
          } else
            return false;
        } else
          return false;
      } else
        return false;
    } else
      return false;
  } else
    return false;
}

void Explorer::FileAnalyze(const path& filePath)
{
  if (NameAnalyze(filePath))
  {
      account tempAcc;
      tempAcc.balance.clear();
      std::string br;
      std::string acc;
      std::string dat;
      std::string bal;
      std::size_t sub = 8;
      std::size_t secsub = 17;


      const std::string sep = "/";
      br = filePath.parent_path().string();
      std::reverse(br.begin(), br.end());
      br = br.substr(0, br.find(sep));
      std::reverse(br.begin(), br.end());
      acc = filePath.stem().string().substr(sub, sub);
      bal = filePath.stem().string();
      dat = filePath.stem().string().substr(secsub, sub);

      tempAcc.balance.push_back(filePath.filename().string());
      tempAcc.last_date = dat;
      tempAcc.acc_id = acc;
      tempAcc.file_count = 1;
      tempAcc.bal_id = br;

      AccPush(tempAcc);
  }
}

void Explorer::DirAnalyze(const directory_entry& dirPath)
{
  //std::cout << "DirAnalyze " << dirPath.path() << std::endl;
  directory_iterator dirIterator = directory_iterator(dirPath);
  for (const directory_entry& x : dirIterator)
  {
    PathAnalyze(x);
  }
}

void Explorer::Analyze()
{
  for (const directory_entry& x : _dirIterator)
  {
    PathAnalyze(x);
  }
}

void Explorer::OutPut()
{
  for (auto& x : _trader)
    for (auto& y : x.balance)
      std::cout << x.bal_id << " " << y << std::endl;

  std::cout << std::endl;

  for (auto& x : _trader)
  {
    std::cout << "broker:" << x.bal_id << " ";
    std::cout << "account: " << x.acc_id << " ";
    std::cout << "files:" << x.file_count << " ";
    std::cout << "lastdate:" << x.last_date << std::endl;
  }

}