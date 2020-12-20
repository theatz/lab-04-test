//
// Created by mrbgn on 15.12.2020.
//

#include "Explorer.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  std::string path;
  if (argc == 0)
  {
    path = ".";
    Explorer exp(path);
    exp.Analyze();
    exp.OutPut();
  }

  if (argc == 2)
  {
    path = argv[1];
    //std::cout << path << std::endl;
    Explorer exp(path);
    exp.Analyze();
    exp.OutPut();
  }

}