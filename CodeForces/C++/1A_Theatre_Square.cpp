#include <iostream>

int main(){
    long long n, m, a;
    std::cin >> n >> m >> a;
    long long along_width = (n + a -1) / a;
    long long along_breadth = (m + a -1) / a;
    std::cout << along_width * along_breadth << std::endl;
    return 0;
}