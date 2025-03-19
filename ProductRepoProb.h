#pragma once
#include "ProductRepo.h"
#include <unordered_map>
using std::unordered_map;

class ProductRepoProb : public repoAbstract {
private:
	vector<Product> prVec;
	unordered_map < int, Product > pr;
	int nr;
	int prob;
public:
	ProductRepoProb() {
		nr = 0;
		prob = 5;
	}
	ProductRepoProb(const ProductRepoProb& ot) = delete;

	/// <summary>
	/// adaugam un produs in vectorul de pro	duse.
	/// </summary>
	/// <param name="product">tip Product</param>
	void addProduct(const Product& product) override;
	/// <summary>
	/// Stergem un produs din vectorul de produse.
	/// </summary>
	/// <param name="nameProduct">string , Numele produsul de sters</param>
	void deleteProduct(const string& nameProduct) override;
	/// <summary>
	/// Modifica un produs
	/// </summary>
	/// <param name="nameProduct">string, Numele produsul de modificat</param>
	/// <param name="modifiedProduct">Product, Produsul cu care se modifica</param>
	void modifyProduct(const string& nameProduct, const Product& modifiedProduct) override;
	/// <summary>
	/// Returneaza tot vectorul de produse.
	/// </summary>
	/// <returns>vectorul de produse</returns>
	const vector<Product>& getAll() noexcept override;
	/// <summary>
	/// Returneaza dimensiunea vectorului.
	/// </summary>
	/// <returns>int dimensiunea vectorului</returns>
	int size() const noexcept;
	const Product& operator [](int index) const;
	vector<Product> getAll_1() noexcept;
	const Product& cautare(const Product& Product) override;

	const Product& get_i(int i) const override;

	void pass();
	void setPrb1000() {
		prob = 1000;
	}
	void setPrb0() {
		prob = 0;
	}
};