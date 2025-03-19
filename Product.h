#pragma once
#include <string>

using std::string;

class Product {
private:
	string name;
	string type;
	int price;
	string producer;

public:

	//constructor default
	Product() = default;

	//constructor cu name, type, price, producator
	Product(string name, string type , int price , string producer);

	Product(const Product& other);

	string getName() const;

	string getType() const;

	int getPrice() const noexcept;

	string getProducer() const;

	void setName(string nameNew);

	void setType(string typeNew);

	void setPrice(int priceNew);

	void setProducer(string producerNew);

	// Verifica daca 2 produse sunt egale
	// par: pr de tip Product
	int operator ==(const Product& pr) const noexcept;
	void operator =(const Product& pr) noexcept;

	// Verifica daca 2 produse nu sunt egale
	// par: pr de tip Product
	int operator !=(const Product& pr) const noexcept;

	friend std::ostream& operator<<(std::ostream& os, const Product& product);

}; 

bool cmp_name(const Product& pr1, const Product& pr2);
bool cmp_price(const Product& pr1, const Product& pr2);
bool cmp_name_type(const Product& pr1, const Product& pr2);