#pragma once
#include "Product.h"
#include "vector"
#include "string"

using std::vector;
using std::string;

class repoAbstract {
public:
	repoAbstract() noexcept = default;

	/// <summary>
	/// adaugam un produs in vectorul de produse.
	/// </summary>
	/// <param name="product">tip Product</param>
	virtual void addProduct(const Product& product) = 0;
	/// <summary>
	/// Stergem un produs din vectorul de produse.
	/// </summary>
	/// <param name="nameProduct">string , Numele produsul de sters</param>
	virtual void deleteProduct(const string& nameProduct) = 0;
	/// <summary>
	/// Modifica un produs
	/// </summary>
	/// <param name="nameProduct">string, Numele produsul de modificat</param>
	/// <param name="modifiedProduct">Product, Produsul cu care se modifica</param>
	virtual void modifyProduct(const string& nameProduct, const Product& modifiedProduct) = 0;
	/// <summary>
	/// Returneaza tot vectorul de produse.
	/// </summary>
	/// <returns>vectorul de produse</returns>
	virtual const vector<Product>& getAll() noexcept = 0;

	virtual const Product& cautare(const Product& Product) = 0;

	virtual const Product& get_i(int i) const = 0;

	virtual int size() const noexcept = 0;
	virtual const Product& operator [](int index) const = 0;
	virtual vector<Product> getAll_1() noexcept = 0;
};

class ProductRepo : public repoAbstract {
protected:
	vector<Product> products;
public:

	ProductRepo() = default;

	ProductRepo(const vector<Product>& products1) : products{ products1 } {}

	/// <summary>
	/// adaugam un produs in vectorul de produse.
	/// </summary>
	/// <param name="product">tip Product</param>
	virtual void addProduct(const Product& product) override;
	/// <summary>
	/// Stergem un produs din vectorul de produse.
	/// </summary>
	/// <param name="nameProduct">string , Numele produsul de sters</param>
	virtual void deleteProduct(const string& nameProduct) override;
	/// <summary>
	/// Modifica un produs
	/// </summary>
	/// <param name="nameProduct">string, Numele produsul de modificat</param>
	/// <param name="modifiedProduct">Product, Produsul cu care se modifica</param>
	virtual void modifyProduct(const string& nameProduct , const Product& modifiedProduct) override;
	/// <summary>
	/// Returneaza tot vectorul de produse.
	/// </summary>
	/// <returns>vectorul de produse</returns>
	virtual const vector<Product>& getAll() noexcept override;
	/// <summary>
	/// Returneaza dimensiunea vectorului.
	/// </summary>
	/// <returns>int dimensiunea vectorului</returns>
	int size() const noexcept;
	const Product& operator [](int index) const;
	vector<Product> getAll_1() noexcept;
	virtual const Product& cautare(const Product& Product) override;

	virtual const Product& get_i(int i) const override;

	~ProductRepo() = default;

};

class ProductRepoFile : public ProductRepo {
private:
	string filename;
public:

	void loadFromFile();

	void writeFromFile();

	explicit ProductRepoFile(string filename1) : ProductRepo(), filename{ std::move(filename1) } {
		loadFromFile();
	}

	void addProduct(const Product& product) override;

	void deleteProduct(const string& nameProduct) override;

	void modifyProduct(const string& nameProduct, const Product& modifiedProduct) override;

};