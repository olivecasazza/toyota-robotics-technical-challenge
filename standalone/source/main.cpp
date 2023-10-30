#include <app/app.h>
#include <app/version.h>

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

auto main(int argc, char** argv) -> int {
  cxxopts::Options options(*argv, "a program to store and count user's words.");

  std::string language;
  std::string name;

  // clang-format off
  options.add_options()
    ("h,help", "show help")
    ("v,version", "print the current version number")
  ;
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  if (result["version"].as<bool>()) {
    std::cout << "app version " << APP_VERSION << std::endl;
    return 0;
  }

  app::App* app = new app::App();
  app->run();

  return 0;
}
