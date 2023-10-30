#include <app/app.h>
#include <app/version.h>
#include <doctest/doctest.h>

#include <string>

using namespace app;

TEST_CASE("App creates") { App app = App(); }

TEST_CASE("App version") {
  static_assert(std::string_view(APP_VERSION) == std::string_view("1.0"));
  CHECK(std::string(APP_VERSION) == std::string("1.0"));
}
