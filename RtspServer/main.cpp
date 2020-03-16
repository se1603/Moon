#include <iostream>
#include "rtspserver.h"

using namespace std;

int main()
{
    RtspServer r;
    r.start("192.168.1.13", 8554);
    return 0;
}
