#include "ProductRepoProb.h"
#include "ProductRepo.h"
#include "MyExceptie.h"
#include <random>

void ProductRepoProb::addProduct(const Product& pr1) {
	pass();
	auto it = pr.find(nr);
	pr.insert(it, { nr, pr1 });
	nr++;
}

void ProductRepoProb::deleteProduct(const string& nameProduct) {
	pass();
	auto it = pr.begin();
	for (; it != pr.end(); ++it) {
		if (it->second.getName() == nameProduct)
			break;
	}
	this->pr.erase(it);
}


void ProductRepoProb::modifyProduct(const string & nameProduct, const Product & modifiedProduct){
	pass();
	bool stop = 0;
	for (auto it = pr.begin(); it != pr.end() && !stop; ++it) {
		if (it->second.getName() == nameProduct) {
			it->second = modifiedProduct;
			stop = 1;
		}
	}
}
const vector<Product>& ProductRepoProb::getAll() noexcept {

	prVec.erase(prVec.begin(), prVec.end());
	for (auto it = pr.begin(); it != pr.end(); ++it) {
		prVec.push_back(it->second);
	}
	return prVec;

}
int ProductRepoProb::size() const noexcept {
	return (int)pr.size();
}
const Product& ProductRepoProb::operator [](int index) const {
	int nr1 = 0;
	for (const auto& i : pr) {
		if (nr1 == index)
			return i.second;
		nr1++;
	}

	throw("Nu exista unu cu acest id\n");
}
vector<Product> ProductRepoProb::getAll_1() noexcept {

	prVec.erase(prVec.begin(), prVec.end());
	for (auto it = pr.begin(); it != pr.end(); ++it) {
		prVec.push_back(it->second);
	}
	return prVec;

}

const Product& ProductRepoProb::cautare(const Product& Product) {

	for (const auto& pr1 : pr) {
		if (pr1.second == Product)
			return pr1.second;
	}

	throw("Nu exista unu cu acest id\n");
}

const Product& ProductRepoProb::get_i(int i) const {

	int nr1 = 0;
	for (const auto& pr1 : pr) {
		if (nr1 == i)
			return pr1.second;
		nr1++;
	}

	throw("Nu exista unu cu acest id\n");
}


void ProductRepoProb::pass() {
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(0, static_cast<int>(11) - 1);
	int rndNr = dist(mt);// numar aleator intre [0,size-1]
	if (rndNr > this->prob)
		throw(MyException("Nu se poate executa functia. Mai incearca o data\n"));
}

