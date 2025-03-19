#include "ProductRepo.h"
#include <iostream>
#include <algorithm> 
#include <vector>
#include "MyExceptie.h"
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;


void ProductRepo::addProduct(const Product& product) {
	this->products.push_back(product);
}

void ProductRepoFile::addProduct(const Product& product) {
	ProductRepo::addProduct(product);
	writeFromFile();
}

void ProductRepoFile::deleteProduct(const string& nameProduct) {
	ProductRepo::deleteProduct(nameProduct);
	writeFromFile();
}

void ProductRepoFile::modifyProduct(const string& nameProduct, const Product& modifiedProduct) {
	ProductRepo::modifyProduct(nameProduct, modifiedProduct);
	writeFromFile();
}

void ProductRepo::deleteProduct(const string& nameProduct) {
	int nr = 0;
	for (const auto& pr : this->products)
	{
		if (pr.getName() == nameProduct)
		{
			this->products.erase(this->products.begin() + nr);
			break;
		}
		nr++;
	}
}

void ProductRepo::modifyProduct(const string& nameProduct, const Product& modifiedProduct) {

	for (auto& pr : this->products)
	{
		if (pr.getName() == nameProduct)
		{
			pr = modifiedProduct;
		}
	}
		
}

int ProductRepo::size() const noexcept{
	return (int)this->products.size(); 
}

const Product& ProductRepo::operator [](int index) const{
	return this->products[index];
}

const vector<Product>& ProductRepo::getAll() noexcept{
	return this->products;
}

vector<Product> ProductRepo::getAll_1() noexcept {
	return this->products;
}

const Product& ProductRepo::get_i(int i) const {
	return this->products[i];
}

const Product& ProductRepo::cautare(const Product& product) {

	vector<Product>::iterator it = find_if(this->products.begin(), this->products.end(), [&product](const Product& pr) {return pr == product; });
	if (it != products.end()) //check if you have actually found it
	{
		return *it; //dereferencing the iterator gives you the element in the container, which is a pointer to the chapter.
	}
	throw(MyException("Nu exista acest produs\n"));
}

void ProductRepoFile::loadFromFile() {
	ifstream in(filename);
	if (!in.is_open())
		throw MyException("Can't open file " + filename);
	string line;
	while (getline(in, line))
	{
		stringstream stream(line);

		string taken;
		vector<string> split;

		while (getline(stream, taken, ',')) {
			split.push_back(taken);
		}

		if (split.size() == 4) {
			string name = split[0];
			string tip = split[1];
			string producator = split[2];
			string pret = split[3];
			int pret_int = stoi(pret);

			Product pr(name, tip, pret_int, producator);
			ProductRepo::addProduct(pr);
		}

	}

	in.close();
}

void ProductRepoFile::writeFromFile() {

	ofstream out1(filename);

	for (const Product& pr : this->products) {
		out1 << pr.getName() << "," << pr.getType() << "," <<pr.getProducer() << "," << pr.getPrice() << "\n";
	}

	out1.close();
}