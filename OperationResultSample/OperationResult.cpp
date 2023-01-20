#include <iostream>
#include "OperationResult.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    //mep::OperationResult x1 = mep::OperationResult::Fail("HIHIHIHIHIHI");
	//mep::OperationResult x2 = mep::OperationResult::Fail("Hi", mep::OperationResult::Fail("HIHIHIHIHIHI"));

    std::cout << mep::OperationResult::Fail("Hi", mep::OperationResult::Fail("HIHIHIHIHIHI")) << std::endl;

	mep::OperationResult xxx = mep::OperationResult::Success("xxxxx");
	mep::OperationResult xx = mep::OperationResult::Success(std::move(xxx));
	mep::OperationResult x = mep::OperationResult::Success(std::move(xx));

    //mep::OperationResult::Success("xxxxx");

    x << "aaaaaaaaaaaaaa";
    x << " asdsadsa";

    std::cout << x << std::endl;
    std::cout << xx << std::endl;
    std::cout << xxx << std::endl;

    return 0;
}
