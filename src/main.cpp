#include <cstdlib>
#include <iostream>

#include <gdk.h>
#include <gdk/buildinfo.h>

int main()
{
    std::cout << gdk::BuildInfo::TargetPlatform << std::endl;

    std::cout << "Greetings from C++\n";

    gdk::init();

    gdk::free();
       
    return EXIT_SUCCESS;
}
