#pragma once
#include <string>
#include "Product.h"
#include <vector>

using std::string;

class Validator {
public:
	static int validatePrice(string price);
	static int validateName(string Name , const std::vector<Product>& products);
};