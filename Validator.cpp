#include "Validator.h"
#include <exception>

int Validator::validatePrice(string Price) {
	for (int j = 0; j < Price.size(); j++) {
		if (Price[j] > '9' || Price[j] < '1')
			return -1;
	}

	int priceInt = stoi(Price);
	return priceInt;
}


int Validator::validateName(string Name, const std::vector<Product>& products){
	int nr = 0;
	for (const auto& pr : products)
	{
		if (pr.getName() == Name)
			return nr;
		nr++;
	}
	return -1;
}