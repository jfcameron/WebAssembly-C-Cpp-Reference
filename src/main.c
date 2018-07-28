#include <stdio.h>

#include <gdk/buildinfo.h>

int main(int argc, char ** argv) 
{
    printf("%s\n", "Greetings from C");
    printf("%s\n", gdk_BuildInfo_TargetPlatform);

    return 0;
}
