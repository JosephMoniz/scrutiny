#include "scrutiny/io/cli_out.h"

class CliOutImpl final : public CliOut {
public:

  void println(std::string_view out) override;

};