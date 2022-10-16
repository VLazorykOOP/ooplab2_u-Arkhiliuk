#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

int main(){
    int a, b, c, d;
    std::cin>> a >> b >> c >> d;
    double defaultNum = (12 * a + ((d*15+12*b)/1024) - 12 * c + d * 15);
    double customNum = ((a << 3) + (a << 2)) + ((((d << 4) - d) + ((d << 3) + (d << 2))) >> 10) - ((c << 3) + (c << 2)) + ((d << 4) - d);
    std::cout<< defaultNum << endl << customNum <<endl;
    return 0;
}
