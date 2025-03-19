#pragma once
#include <string>
#include "ProductServ.h"

using std::string;

class UiProducts {
private:
	ProductServ& products;
public:

	UiProducts() = default;

	UiProducts(ProductServ& products1) : products{ products1 } {}

	/// <summary>
	/// Adauga produs
	/// </summary>
	void addProduct();
	/// <summary>
	/// Sterge produs
	/// </summary>
	void deleteProduct();
	/// <summary>
	/// Modifica produs
	/// </summary>
	void modifyProduct();
	/// <summary>
	/// Printeaza meniul
	/// </summary>
	void printMeniu();
	/// <summary>
	/// Printeaza vectorul de produse
	/// </summary>
	/// <param name="pr"></param>
	void print(const vector<Product>& pr);
	/// <summary>
	/// Meniul
	/// </summary>
	void meniu();
	/// <summary>
	/// Meniul de sortare
	/// </summary>
	void sort();
	/// <summary>
	/// Sorteaza dupa nume
	/// </summary>
	void sort_nume();
	/// <summary>
	/// Sorteaza dupa pret
	/// </summary>
	void sort_pret();
	/// <summary>
	/// Sorteaza dupa nume si tip
	/// </summary>
	void sort_nume_tip();
	/// <summary>
	/// Cauta un produs
	/// </summary>
	void cautare();
	/// <summary>
	/// Filtreaza dupa un criteriu
	/// </summary>
	void filtrare();
	/// <summary>
	/// Afiseaza meniul de filtrare
	/// </summary>
	void printFiltrare();
	/// <summary>
	/// Afiseaza meniul de sortare
	/// </summary>
	void printSort();
	void adaugaCosUI();
	void golesteCosUI();
	void randomADD();
	void raportType();
	void undo();
	void uiExportHTML();
	void uiExportCSV();
};