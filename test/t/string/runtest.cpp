
#include <test.hpp>

TEST_CASE("string") {

    SECTION("empty") {
        std::string buffer = get_file_data("test/t/string/data-empty.pbf");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE(item.get_string() == "");
        REQUIRE(!item.next());
    }

    SECTION("one") {
        std::string buffer = get_file_data("test/t/string/data-one.pbf");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE(item.get_string() == "x");
        REQUIRE(!item.next());
    }

    SECTION("string") {
        std::string buffer = get_file_data("test/t/string/data-string.pbf");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE(item.get_string() == "foobar");
        REQUIRE(!item.next());
    }

    SECTION("end_of_buffer") {
        std::string buffer = get_file_data("test/t/string/data-string.pbf");

        for (size_t i=1; i < buffer.size(); ++i) {
            mapbox::util::pbf item(buffer.data(), i);
            REQUIRE(item.next());
            REQUIRE_THROWS_AS(item.get_string(), mapbox::util::pbf::end_of_buffer_exception);
        }
    }

    SECTION("check assert on fixed int access") {
        std::string buffer = get_file_data("test/t/string/data-string.pbf");

        mapbox::util::pbf item(buffer.data(), buffer.size());

        REQUIRE(item.next());
        REQUIRE_THROWS_AS(item.get_fixed32(), assert_error);
    }

}

