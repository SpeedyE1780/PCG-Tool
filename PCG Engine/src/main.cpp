#include <iostream>>
#include <pcg/engine/core/core.hpp>

int main()
{
    std::cout << "Hello World!" << std::endl;
    std::cout << "Add 1 + 5 = " << pcg::engine::core::add(1, 5) << std::endl;
    return 0;
}
