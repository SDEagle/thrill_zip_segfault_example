#include <thrill/api/print.hpp>
#include <thrill/api/read_lines.hpp>
#include <thrill/api/zip.hpp>
#include <thrill/api/generate.hpp>

void doit(thrill::Context& context) {
  auto input = thrill::api::Generate(context, 50, [](size_t index) { return index; });
  auto sizes = input.Keep().Map([](const size_t & n) { return n % 5; });

  input
    .Zip(sizes, [](const size_t& foo, const size_t &) { return foo; }) // SEGFAULT
    // this works
    // .Zip(thrill::api::NoRebalanceTag, input, [](const std::string& foo, const std::string& ) { return foo; })
    .Print("zipped");
}

int main(int, char const *[]) {
  return thrill::Run([&](thrill::Context& context) {
    doit(context);
  });
}
