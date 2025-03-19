#include "UiProducts.h"
#include "Validator.h"
#include <iostream>
#include "Product.h"
#include "MyExceptie.h"

using namespace std;

void UiProducts::addProduct() {

	try {
		string Name, Type, Producer;
		string Price;
		int Price_int;

		cout << "Dati numele la produs: ";
		cin >> Name;
		cout << "Dati tipul la produs: ";
		cin >> Type;
		cout << "Dati producatorul la produs: ";
		cin >> Producer;
		cout << "Dati pretul la produs: ";
		cin >> Price;

		Price_int = Validator::validatePrice(Price);
		if (Price_int == -1)
			throw(MyException("Pretul nu e de tip int!!\n"));

		Product pr(Name, Type, Price_int, Producer);

		this->products.addProduct(pr);
		cout << "S a adaugat cu succes\n";
	}
	catch (MyException& c) {
		cout << c.what();
	}
}

void UiProducts::deleteProduct() {

	try {
		string Name, Type, Producer;
		cout << "Dati numele la produs: ";
		cin >> Name;
		this->products.deleteProduct(Name);
		cout << "S a sters cu succes\n";
	}
	catch (MyException& c) {
		cout << c.what();
	}
}

void UiProducts::modifyProduct() {
	try {
		string Name, Type, Producer, Price; ;
		cout << "Dati numele la produs: ";
		cin >> Name;
		int Price_int;
		cout << "Dati tipul la produs: ";
		cin >> Type;
		cout << "Dati producatorul la produs: ";
		cin >> Producer;
		cout << "Dati pretul la produs: ";
		cin >> Price;

		Price_int = Validator::validatePrice(Price);
		if (Price_int == -1)
			throw(MyException("Pretul nu e de tip int!!\n"));

		Product pr(Name, Type, Price_int, Producer);
		this->products.modifyProduct(Name, pr);
		cout << "S a actualizat cu succes\n";
	}
	catch (MyException& c) {
		cout << c.what();
	}
}

void UiProducts::sort_nume() {

	vector<Product> copy;
	string optiune;
	cout << "--------------------\n";
	cout << "1. Crescator\n";
	cout << "2. Descrescator\n";
	cout << "Alegeti optiunea:\n";
	cin >> optiune;
	if (optiune == "1")
		copy = this->products.sort(0, cmp_name);
	else if (optiune == "2")
		copy = this->products.sort(1, cmp_name);
	cout << "\n";
	this->print(copy);
}

void UiProducts::sort_pret() {

	vector<Product> copy;
	string optiune;
	cout << "--------------------\n";
	cout << "1. Crescator\n";
	cout << "2. Descrescator\n";
	cout << "Alegeti optiunea:\n";
	cin >> optiune;
	if (optiune == "1")
		copy = this->products.sort(0, cmp_price);
	else if (optiune == "2")
		copy = this->products.sort(1, cmp_price);
	cout << "\n";
	this->print(copy);
}

void UiProducts::sort_nume_tip() {

	vector<Product> copy;
	string optiune;
	cout << "--------------------\n";
	cout << "1. Crescator\n";
	cout << "2. Descrescator\n";
	cout << "Alegeti optiunea:\n";
	cin >> optiune;
	if (optiune == "1")
		copy = this->products.sort(0, cmp_name_type);
	else if (optiune == "2")
		copy = this->products.sort(1, cmp_name_type);
	cout << "\n";
	this->print(copy);
}

void UiProducts::cautare() {


	try {
		string Name, Type, Producer, Price; ;
		cout << "Dati numele la produs: ";
		cin >> Name;
		int Price_int;
		cout << "Dati tipul la produs: ";
		cin >> Type;
		cout << "Dati producatorul la produs: ";
		cin >> Producer;
		cout << "Dati pretul la produs: ";
		cin >> Price;

		Price_int = Validator::validatePrice(Price);
		if (Price_int == -1)
			throw(MyException("Pretul nu e de tip int!!\n"));

		Product pr(Name, Type, Price_int, Producer);
		cout << this->products.cautare(pr);
	}
	catch (MyException& c) {
		cout << c.what();
	}
}

void UiProducts::sort() {

	while (true)
	{
		printSort();
		string optiune;
		cout << "Alegeti optiunea:\n";
		cin >> optiune;
		if (optiune == "1")
			sort_nume();
		else if (optiune == "2")
			sort_pret();
		else if (optiune == "3")
			sort_nume_tip();
		else if (optiune == "x")
			break;
		else
			cout << "Aceasta optiune nu e in lista, alegeti alta!\n";
	}
	
}

void UiProducts::filtrare() {

	try {
		string Name, Type, Producer;
		string Price;

		while (true) {
			printFiltrare();
			string optiunea;
			cout << "Dati optiunea: \n";
			cin >> optiunea;
			if (optiunea == "1")
			{
				cout << "Dati numele la produs: ";
				cin >> Name;
				const vector<Product>& filt = this->products.filtrare(optiunea, Name);
				cout << "\n";
				this->print(filt);
			}
			else if (optiunea == "2")
			{
				cout << "Dati producatorul la produs: ";
				cin >> Producer;
				const vector<Product>& filt = this->products.filtrare(optiunea, Producer);
				cout << "\n";
				this->print(filt);
			}
			else if (optiunea == "3")
			{
				cout << "Dati pretul la produs: ";
				cin >> Price;
				for (int i = 0; i < Price.size(); i++) {
					if (Price[i] > '9' || Price[i] < '1')
						throw(exception("Nu e de tip int!!\n"));
				}
				const vector<Product>& filt = this->products.filtrare(optiunea, Price);
				cout << "\n";
				this->print(filt);

			}
			else if (optiunea == "x")
				break;
			else
				cout << "Aceasta optiunea nu exista, va rog reincercati!\n";
		}

		
	}
	catch (MyException& c) {
		cout << c.what();
	}
}

void UiProducts::adaugaCosUI() {
	try {
		string Name, Type, Producer, Price; ;
		cout << "Dati numele la produs: ";
		cin >> Name;
		int Price_int;
		cout << "Dati tipul la produs: ";
		cin >> Type;
		cout << "Dati producatorul la produs: ";
		cin >> Producer;
		cout << "Dati pretul la produs: ";
		cin >> Price;

		Price_int = Validator::validatePrice(Price);
		if (Price_int == -1)
			throw(MyException("Pretul nu e de tip int!!\n"));

		Product pr(Name, Type, Price_int, Producer);
		products.adaugaCos(pr);
		print(products.getAll_cos());
	}
	catch (MyException& e)
	{
		cout << e.what();
	}
}

void UiProducts::raportType() {
	map<string, DTO> dic = this->products.raportType();
	cout << "\n";
	for (const auto& i : dic)
	{
		cout << "Type: " << i.second.getType() << " | Nr: " << i.second.getNr() << "\n";
	}
	cout << "\n";
}

void UiProducts::golesteCosUI() {
	products.emptyCos();
}

void UiProducts::randomADD() {
	int n;
	cin >> n;
	products.randomADD_serv(n);
}

void UiProducts::uiExportHTML() {
	this->products.exportHTML("html.html");
}

void UiProducts::uiExportCSV() {
	this->products.exportHTML("csv.csv");
}

void UiProducts::print(const vector<Product>& pr) {


	for (const auto& py: pr)
		cout << py << "\n";
	cout << "\n";
}

void UiProducts::printFiltrare() {

	cout << "1. Filtrare dupa nume.\n";
	cout << "2. Filtrare dupa producator.\n";
	cout << "3. Filtrare dupa pret\n";
	cout << "x. return\n";
}

void UiProducts::printSort() {

	cout << "1. Sortare dupa nume.\n";
	cout << "2. Sortare dupa pret.\n";
	cout << "3. Sortare dupa nume si tip\n";
	cout << "x. return\n";
}

void UiProducts::printMeniu() {
	cout << "1. Adaugati in magazin\n";
	cout << "2. Stergeti un produs dupa numele lui\n";
	cout << "3. Modificati produsul dupa un nume.\n";
	cout << "4. Sortare\n";
	cout << "5. Cautarea unui produs\n";
	cout << "6. Filtare\n";
	cout << "7. Add cos\n";
	cout << "8. Sterge cos\n";
	cout << "9. Random Add\n";
	cout << "10. RaportType\n";
	cout << "11. Undo\n";
	cout << "12. Export HTML\n";
	cout << "13. Export CSV\n";
	cout << "a. Afisati toate produsele din magazin\n";
	cout << "b. Afiseaza tot din cos\n";
	cout << "x. Exit\n";
}

void UiProducts::undo() {
	try {
		this->products.undo();
	}
	catch (MyException& c) {
		cout << c.what() << "\n";
	}
}


void UiProducts::meniu() {

	string optiune;
	bool ok = true;
	while (ok) {
		this->printMeniu();
		cout << "Dati de la tastatura optiunea aleasa: \n";
		cin >> optiune;
		if (optiune == "1")
			this->addProduct();
		else if (optiune == "2")
			this->deleteProduct();
		else if (optiune == "3")
			this->modifyProduct();
		else if (optiune == "4")
			this->sort();
		else if (optiune == "5")
			this->cautare();
		else if (optiune == "6")
			this->filtrare();
		else if (optiune == "7")
			this->adaugaCosUI();
		else if (optiune == "8")
			this->golesteCosUI();
		else if (optiune == "9")
			this->randomADD();
		else if (optiune == "10")
			this->raportType();
		else if (optiune == "11")
			this->undo();
		else if (optiune == "12")
			this->uiExportHTML();
		else if (optiune == "13")
			this->uiExportCSV();
		else if (optiune == "a")
			this->print(this->products.getAll());
		else if (optiune == "b")
			this->print(this->products.getAll_cos());
		else if (optiune == "x")
			ok = false;
		else
			cout << "Dati alti optiune, aceasta nu exista!!\n";
	}
}