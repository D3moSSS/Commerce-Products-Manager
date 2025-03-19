#include "ProductServ.h"
#include "Validator.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <map>
#include "MyExceptie.h"

using namespace std;

void ProductServ::addProduct(const Product& product) {
	if (Validator::validateName(product.getName(), getAll()) != -1) {
		throw(MyException("Exista deja un produs de acest nume!!!"));
	}

	this->products.addProduct(product);
	undoActions.push_back(make_unique<undoAdd>(this->products, product));
}

void ProductServ::deleteProduct(string nameProduct) {
	if (Validator::validateName(nameProduct, getAll()) == -1) {
		throw(MyException("Nu exista un produs de acest nume!!!"));
	}
	int i = Validator::validateName(nameProduct, getAll());
	Product pr = get_i(i);
	this->products.deleteProduct(nameProduct);
	undoActions.push_back(make_unique<undoDelete>(this->products, pr));
}

void ProductServ::modifyProduct(string nameProduct, Product modifiedProduct) {
	if (Validator::validateName(nameProduct, getAll()) == -1) {
		throw(MyException("Nu exista un produs de acest nume!!!"));
	}
	int i = Validator::validateName(nameProduct, getAll());
	Product pr1 = get_i(i);
	this->products.modifyProduct(nameProduct, modifiedProduct);
	undoActions.push_back(make_unique<undoModify>(modifiedProduct, pr1 , this->products));
}

int ProductServ::size() const noexcept{
	return this->products.size();
}

const vector<Product>& ProductServ::getAll() {
	return this->products.getAll();
}

const vector<Product>& ProductServ::getAll_cos() {
	return cosul.get_all_cos();
}

void ProductServ::undo() {
	if (undoActions.empty()) {
		throw MyException("Nu mai exista operatii");
	}
	std::unique_ptr<undoAction> action = std::move(undoActions.back());
	undoActions.pop_back();
	action->doUndo();
}

vector<Product> ProductServ::sort(bool dir, bool(*cmp)(const Product& e1, const Product& e2)) {
	vector<Product> rez;
	for (const auto& i : this->products.getAll()) {
		rez.push_back(i);
	}
	if (!dir) {
		std::sort(rez.begin(), rez.end() , cmp);
	}
	else {
		std::sort(rez.begin(), rez.end(), cmp);
		reverse(rez.begin(), rez.end());
	}

	return rez;
}

const Product& ProductServ::operator [](int index) const noexcept {
	return this->products.get_i(index);
}

vector<Product> ProductServ::filtrare(const string& optiune, const string& tip){
	
	vector<Product> copy_all = this->products.getAll_1();
	vector<Product> copy(this->size());
	if (optiune == "1")
	{
		auto it = copy_if(copy_all.begin(), copy_all.end(), copy.begin(), [&tip](const Product& pr) {return pr.getName() == tip; });
		copy.resize(std::distance(copy.begin(), it));
	}
	else if (optiune == "2")
	{
		auto it = copy_if(copy_all.begin(), copy_all.end(), copy.begin(), [&tip](const Product& pr) {return pr.getProducer() == tip; });
		copy.resize(std::distance(copy.begin(), it));
	}
	else if (optiune == "3")
	{
		int price = stoi(tip);
		auto it = copy_if(copy_all.begin(), copy_all.end(), copy.begin(), [&price](const Product& pr) {return pr.getPrice() == price; });
		copy.resize(std::distance(copy.begin(), it));
	}
	return copy;
}

Product ProductServ::get_i(int i) {
	return this->products[i];
}

const Product& ProductServ::cautare(const Product& product) {
	return this->products.cautare(product);
}

void ProductServ::emptyCos() {
	cosul.deleteAllProducts();
}

void ProductServ::adaugaCos(const Product& pr) {
	const Product& pr1 = cautare(pr);
	cosul.AddCos(pr1);
}

int ProductServ::size_cos() {
	return cosul.cosSize();
}

void Cos::randomADD(int n, vector<Product> pr1) {

	std::mt19937 pr{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(0, static_cast<int>(pr1.size() - 1));
	for (int i = 0; i < n; i++)
	{
		int rndNr = dist(pr);
		cos.push_back(pr1[rndNr]);
	}
	notify();

}

void Cos::randomADD1(int n) {

	std::mt19937 pr{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(0, static_cast<int>(repo.getAll().size() - 1));
	for (int i = 0; i < n; i++)
	{
		int rndNr = dist(pr);
		cos.push_back(repo.getAll()[rndNr]);
	}
	notify();
}

void ProductServ::randomADD_serv(int n) {
	cosul.randomADD(n, this->products.getAll());
}


map<string,DTO> ProductServ::raportType() {

	map<string, DTO> dic;
	for (const auto& pr1 : this->products.getAll())
		if (dic.find(pr1.getType()) == dic.end())
			dic[pr1.getType()] = DTO(1, pr1.getType());
		else
			dic[pr1.getType()].increment();
	return dic;
		

}

void Cos::deleteAllProducts() {
	cos.clear();
	notify();
}

void ProductServ::exportHTML(const std::string& filename) {
	std::ofstream output_file(filename);

	output_file << "<!DOCTYPE html>\n<html lang=\"en\">\n"
		<< "<head>\n<title>Book List</title>\n"
		<< "<link rel=\"stylesheet\" href=\"style.css\">\n"
		<< "\n</head>\n<body>\n";
	output_file << "<h1>Book List</h1>\n<ul>\n";

	for (const auto& prod : getAll_cos()) {
		output_file << "<li>\n";
		output_file << "<strong>Title:</strong> " << prod.getName() << "<br>\n";
		output_file << "<strong>Author:</strong> " << prod.getType() << "<br>\n";
		output_file << "<strong>Genre:</strong> " << prod.getProducer() << "<br>\n";
		output_file << "<strong>Year:</strong> " << prod.getPrice() << "<br>\n";
		output_file << "</li>\n";
	}

	output_file << "</ul>\n</body>\n</html>\n";
}


void ProductServ::exportCSV(const std::string& filename) {
	std::ofstream output_file(filename);

	output_file << "Title,Author,Genre,Year\n";

	for (const auto& prod : getAll_cos()) {
		output_file << "\"" << prod.getName() << "\",";
		output_file << "\"" << prod.getType() << "\",";
		output_file << "\"" << prod.getProducer() << "\",";
		output_file << "\"" << prod.getPrice() << "\"\n";
	}

	output_file.close();
}