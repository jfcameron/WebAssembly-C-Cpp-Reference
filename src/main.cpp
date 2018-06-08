#include <cstdlib>
#include <iostream>

#include <gdk.h>

int main()
{
    std::cout << "Greetings from C++\n";

    gdk::init();

    gdk::free();
       
    return EXIT_SUCCESS;
}
