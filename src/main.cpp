#include <iostream>

#include <gdk.h>

int main()
{
    std::cout << "Greetings from C++11!\n";

    gdk::init();

    gdk::free();
       
    return 0;
}
