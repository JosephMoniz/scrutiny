#include "scrutiny/io/cli_out_impl.h"

#include <cstdio>

void CliOutImpl::println(std::string_view out) {
  puts(out.data());
}
