#include "screen/entry.hpp"


std::unique_ptr<std::vector<std::string>> sc::entries_to_string(const std::vector<Entry>& entries){
    auto res = std::make_unique<std::vector<std::string>>();
    std::transform(entries.begin(), entries.end(), std::back_inserter(*(res.get())),
        [](Entry e) -> std::string{ return e.content; });
    return res;
}