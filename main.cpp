#include <iostream>
#include "OperationResult.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    //OperationResult x1 = OperationResult::Fail("HIHIHIHIHIHI");
   // OperationResult x2 = OperationResult::Fail("Hi", OperationResult::Fail("HIHIHIHIHIHI"));

    std::cout << OperationResult::Fail("Hi", OperationResult::Fail("HIHIHIHIHIHI")) << std::endl;

    OperationResult xxx = OperationResult::Success("xxxxx");
    OperationResult xx = OperationResult::Success(std::move(xxx));
    OperationResult x = OperationResult::Success(std::move(xx));

    //OperationResult::Success("xxxxx");

    x << "aaaaaaaaaaaaaa";
    x << " asdsadsa";

    std::cout << x << std::endl;
    std::cout << xx << std::endl;
    std::cout << xxx << std::endl;

    return 0;
}
