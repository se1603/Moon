#include <iostream>
#include "server.h"

using namespace std;

int main()
{
    Server s;
    cout << "服务器已启动。" << endl;
    s.acceptMreeage();
    return 0;
}
