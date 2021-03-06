// Copyright (c) 2020 by the Zeek Project. See LICENSE for details.

#include <doctest/doctest.h>

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <locale>

#include <hilti/rt/types/time.h>
#include <hilti/rt/util.h>

using namespace hilti::rt;

namespace std {
ostream& operator<<(ostream& stream, const vector<string_view>& xs) {
    stream << '[';

    for ( size_t i = 0; i < xs.size(); ++i ) {
        stream << xs[i];

        if ( i != xs.size() - 1 )
            stream << ", ";
    }

    return stream << ']';
}
} // namespace std

TEST_SUITE_BEGIN("util");

TEST_CASE("strftime") {
    REQUIRE_EQ(::setenv("TZ", "UTC", 1), 0);
    std::locale::global(std::locale::classic());

    CHECK_EQ(strftime("%A %c", Time()), "Thursday Thu Jan  1 00:00:00 1970");

    CHECK_THROWS_WITH_AS(strftime("", Time()), "could not format timestamp", const InvalidArgument&);
    CHECK_THROWS_WITH_AS(strftime("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
                                  "XXXXXXXXXXXXXXXX %A %c",
                                  Time()),
                         "could not format timestamp", const InvalidArgument&);
}

TEST_CASE("split") {
    CHECK_EQ(split("12345", "1"), std::vector<std::string_view>({"", "2345"}));
    CHECK_EQ(split("12345", "23"), std::vector<std::string_view>({"1", "45"}));
    CHECK_EQ(split("12345", "a"), std::vector<std::string_view>({"12345"}));
    CHECK_EQ(split("12345", ""), std::vector<std::string_view>({"12345"}));
}

TEST_SUITE_END();
