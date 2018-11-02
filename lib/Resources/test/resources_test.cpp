// © 2018 Joseph Cameron - All Rights Reserved

#include <catch.hpp>

#include <gdk/resources_protected.h>
#include <gdk/resources.h>

TEST_CASE("local fetch succeeds", "[local::fetchfile]")
{
    /*SECTION("Fetch succeeded")
    {
        gdk::resources::local::fetchFile("123/456.a", [&](const bool aSucceeded, std::vector<unsigned char> aData)
        {
            REQUIRE(aSucceeded);
            REQUIRE(aData.size() != 0);
        });
    }*/

    SECTION("Fetch Failed")
    {
        gdk::resources::local::fetchFile("456/123.b", [&](const bool aSucceeded, std::vector<unsigned char> aData)
        {
            REQUIRE(aSucceeded == false);
            REQUIRE(aData.size() == 0);
        });
    }

    gdk::resources::PROTECTED::WorkerThreadUpdate();
    gdk::resources::PROTECTED::MainThreadUpdate();
}
