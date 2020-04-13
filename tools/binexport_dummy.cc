// Copyright 2011-2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Dummy command that does (mostly) nothing.

#include <vector>

#include "third_party/absl/flags/flag.h"
#include "third_party/absl/flags/internal/usage.h"
#include "third_party/absl/flags/parse.h"
#include "third_party/absl/flags/usage.h"
#include "third_party/absl/flags/usage_config.h"
#include "third_party/absl/status/status.h"
#include "third_party/absl/strings/match.h"
#include "third_party/absl/strings/str_format.h"
#include "third_party/absl/strings/string_view.h"

ABSL_FLAG(std::string, subcommand_query, "",
          "internal, output information for the 'binexport' tool");

constexpr absl::string_view kCommandAliases[] = {"nop"};

namespace security::binexport {
namespace {

absl::Status DummyMain(const std::vector<char*>& positional) {
  absl::PrintF("Hello from Dummy\n");
  for (const auto& arg : positional) {
  absl::PrintF("  posarg: %s\n", arg);
  }
  return absl::OkStatus();
}

}  // namespace
}  // namespace security::binexport

int main(int argc, char* argv[]) {
  std::vector<char*> parsed_argv = absl::ParseCommandLine(argc, argv);
  parsed_argv.erase(parsed_argv.begin());

  if (const auto status = security::binexport::DummyMain(parsed_argv);
      !status.ok()) {
    absl::FPrintF(stderr, "error: %s\n", status.message());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
