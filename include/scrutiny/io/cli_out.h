#pragma once

#include <string_view>

class CliOut {
public:

  virtual void println(std::string_view out) = 0;

};