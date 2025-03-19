#pragma once
#include "undo.h"
#include <string>
#include "ProductRepo.h"
#include <map>
#include <memory>
#include <fstream>
#include "observer.h"

using namespace std;

class DTO {
protected:
	int nr;
	string type;
public:

	DTO() = default;

	DTO(int nr, string type) {
		this->nr = nr;
		this->type = type;
	}

	const int getNr() const {
		return nr;
	}

	const string getType() const {
		return type;
	}

	void increment() {
		nr++;
	}

};

class Cos : public Observable {
private:
	vector<Product> cos;
	repoAbstract& repo;
public:
	
	Cos(repoAbstract& repo) : repo{ repo } {};

	void AddCos(const Product& pr) {
		cos.push_back(pr);
		notify();
	}
	void deleteAllProducts();
	int cosSize() noexcept {
		return (int)cos.size();
		notify();
	}
	const vector<Product>& get_all_cos() noexcept{
		return cos;
	}
	void randomADD(int n, vector<Product> pr);
	void randomADD1(int n);
};


class ProductServ : public Observable {
private:
	repoAbstract& products;
	vector<unique_ptr<undoAction>> undoActions;
	Cos& cosul;
public:

	ProductServ() = default;
	ProductServ(repoAbstract& products, Cos& cosul) : products{ products }, cosul{ cosul } {
		std::ofstream html("html.html");
		html.close();

		std::ofstream csv("csv.csv");
		csv.close();
	}


	map<string, DTO> raportType();
	void exportHTML(const std::string& filename);
	void exportCSV(const std::string& filename);
	/// <summary>
	/// adaugam un produs in vectorul de produse.
	/// </summary>
	/// <param name="product">tip Product</param>
	void addProduct(const Product& product);
	/// <summary>
	/// Stergem un produs din vectorul de produse.
	/// </summary>
	/// <param name="nameProduct">string , Numele produsul de sters</param>
	void deleteProduct(string nameProduct);
	/// <summary>
	/// Modifica un produs
	/// </summary>
	/// <param name="nameProduct">string, Numele produsul de modificat</param>
	/// <param name="modifiedProduct">Product, Produsul cu care se modifica</param>
	void modifyProduct(string nameProduct, Product modifiedProduct);
	/// <summary>
	/// Returneaza tot vectorul de produse.
	/// </summary>
	/// <returns>vectorul de produse</returns>
	const vector<Product>& getAll();
	const vector<Product>& getAll_cos();
	/// <summary>
	/// Returneaza dimensiunea vectorului.
	/// </summary>
	/// <returns>int dimensiunea vectorului</returns>
	int size() const noexcept;
	/// <summary>
	/// Sorteaza dupa nume
	/// </summary>
	/// <param name="optiune">string</param>
	/// <returns></returns>
	vector<Product> sort(bool dir, bool(*cmp)(const Product& e1, const Product& e2));
	/// <summary>
	/// Filtreaza dupa tipul dat.
	/// </summary>
	/// <param name="optiune">string</param>
	/// <param name="tip">string</param>
	/// <returns></returns>
	vector<Product> filtrare(const string& optiune, const string& tip);
	/// <summary>
	/// Operator
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	const Product& operator [](int index) const noexcept;
	/// <summary>
	/// Cauta un produs
	/// </summary>
	/// <param name="Product"></param>
	/// <returns></returns>
	const Product& cautare(const Product& Product);
	/// <summary>
	/// Goleste cosul
	/// </summary>
	void emptyCos();
	/// <summary>
	/// Adauga in cos
	/// </summary>
	/// <param name="pr"></param>
	void adaugaCos(const Product& pr);
	/// <summary>
	/// Marimea cosului
	/// </summary>
	/// <returns></returns>
	int size_cos();
	/// <summary>
	/// Ia ilementul de pe pozitia i
	/// </summary>
	/// <param name="i"></param>
	/// <returns></returns>
	Product get_i(int i);

	void undo();
	void randomADD_serv(int n);
	Cos& getCosClass() {
		return cosul;
	}


};