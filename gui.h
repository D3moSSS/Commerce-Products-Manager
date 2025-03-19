#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qinputdialog.h>
#include <qpainter.h>
#include <QPaintEvent>
#include <vector>
#include <string>
#include "ProductServ.h"
#include "MyExceptie.h"
#include "Validator.h"
#include "random"
#include "tableModel.h"

using std::vector;
using std::string;

class MdGUI : public QWidget {
public:
	MdGUI(ProductServ& serv) : serv{ serv } {

		initGUI();
		loadData(serv.getAll());
		initConnect();
	}

private:
	ProductServ& serv;
	QListWidget* lst = new QListWidget;
	QPushButton* btnExit = new QPushButton{ "&Exit" };
	QPushButton* btnAdd = new QPushButton{ "&Add" };
	QPushButton* btnDel = new QPushButton{ "&Del" };
	QPushButton* btnSortNume = new QPushButton{ "&SortNume" };
	QPushButton* btnSortPret= new QPushButton{ "&SortPret" };
	QPushButton* btnSortNumeTip = new QPushButton{ "&SortNumeTip" };
	QPushButton* btnUndo = new QPushButton{ "&Undo" };
	QPushButton* btnMod = new QPushButton{ "&Mod" };
	QPushButton* btnCauta = new QPushButton{ "&Cauta" };
	QPushButton* btnFiltrare = new QPushButton{ "&Filtrare" };
	QPushButton* btnCosReadOnly = new QPushButton{ "&CosReadOnly" };
	QPushButton* btnRaport = new QPushButton{ "&Raport" };
	QPushButton* btnCosCRUDGUI = new QPushButton{ "&CosCRUDGUI"};
	QPushButton* btnAddCos = new QPushButton{ "&AddCos" };
	QPushButton* btnGolesteCos = new QPushButton{ "&GolesteCos" };
	QPushButton* btnRandomCos = new QPushButton{ "&RandomCos" };
	QPushButton* btnAddCosGUI = new QPushButton{ "&AddCos" };
	QPushButton* btnRandomCosGUI = new QPushButton{ "&AddCos" };
	QPushButton* btnCsv = new QPushButton{ "&Export Csv" };
	QPushButton* btnHtml = new QPushButton{ "&Export Html" };
	QLineEdit* editName;
	QWidget* generateCosGUI;
	QLineEdit* editNumber;
	QLabel* lblName = new QLabel{ "Numele: " };
	QLineEdit* txtNume = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QLineEdit* txtPret = new QLineEdit;
	QLineEdit* txtProducator = new QLineEdit;
	TableModel* model;
	QTableView* tableViewProducts;

	void initConnect();

	void loadData(const vector<Product>& pr)
	{

		model->setProducts(pr);
		/*lst->clear();
		for (const auto& prod : pr)
		{
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(prod.getName()));
			lst->addItem(item);

		}*/
	}

	void initGUI()
	{
		QHBoxLayout* lyMain = new QHBoxLayout{};
		setLayout(lyMain);

		model = new TableModel(serv.getAll());
		tableViewProducts = new QTableView();

		tableViewProducts->setModel(model);


		QVBoxLayout* lyLst = new QVBoxLayout{};
		QHBoxLayout* lyBtnLst = new QHBoxLayout{};
		lyBtnLst->addWidget(btnSortNume);
		lyBtnLst->addWidget(btnSortPret);
		lyBtnLst->addWidget(btnSortNumeTip);

		QHBoxLayout* lyBtnLst1 = new QHBoxLayout{};
		lyBtnLst1->addWidget(btnAddCos);
		lyBtnLst1->addWidget(btnGolesteCos);
		lyBtnLst1->addWidget(btnRandomCos);

		lyLst->addWidget(new QLabel{ "Lista produse: " });
		lyLst->addWidget(tableViewProducts);
		lyLst->addLayout(lyBtnLst);
		lyLst->addLayout(lyBtnLst1);

		lyMain->addLayout(lyLst);

		auto stgLy = new QVBoxLayout;

		auto formLy = new QFormLayout;
		formLy->addRow("Nume", txtNume);
		formLy->addRow("Tip", txtTip);
		formLy->addRow("Pret", txtPret);
		formLy->addRow("Producator", txtProducator);
		stgLy->addLayout(formLy);

		auto meniu = new QHBoxLayout;
		auto meniu1 = new QVBoxLayout;

		meniu1->addWidget(btnAdd);
		meniu1->addWidget(btnDel);
		meniu1->addWidget(btnMod);
		meniu1->addWidget(btnUndo);
		meniu1->addWidget(btnCauta);
		meniu1->addWidget(btnCsv);
		meniu->addLayout(meniu1);

		auto meniu2 = new QVBoxLayout;

		meniu2->addWidget(btnFiltrare);
		meniu2->addWidget(btnCosReadOnly);
		meniu2->addWidget(btnCosCRUDGUI);
		meniu2->addWidget(btnRaport);
		meniu2->addWidget(btnHtml);
		meniu2->addWidget(btnExit);
		meniu->addLayout(meniu2);

		stgLy->addLayout(meniu);

		lyMain->addLayout(stgLy);

	}

};

class FiltrareGui : public QWidget {
private:
	ProductServ& serv;
	QListWidget* lst = new QListWidget;
	QPushButton* btnNume = new QPushButton{ "&Filtrare dupa Nume" };
	QPushButton* btnProd = new QPushButton{ "&Filtrare dupa Prod" };
	QPushButton* btnPret = new QPushButton{ "&Filtrare dupa Pret" };
	QPushButton* btnExit = new QPushButton{ "&Iesire" };
	QLineEdit* txtNume = new QLineEdit;
	QLineEdit* txtProd = new QLineEdit;
	QLineEdit* txtPret = new QLineEdit;
public:

	FiltrareGui(ProductServ& serv) : serv{ serv } {
		initGUI();
		initConnect();
	}

	void initGUI()
	{
		QHBoxLayout* lyMain = new QHBoxLayout;
		setLayout(lyMain);

		QVBoxLayout* stgLy = new QVBoxLayout;
		QLabel* titluLista = new QLabel;

		titluLista->setText("Rezultat filtrare: ");
		stgLy->addWidget(titluLista);

		stgLy->addWidget(lst);

		QVBoxLayout* drly = new QVBoxLayout;
		drly->addWidget(btnNume);
		drly->addWidget(btnProd);
		drly->addWidget(btnPret);

		auto formLy = new QFormLayout;
		formLy->addRow("Nume", txtNume);
		formLy->addRow("Prod", txtProd);
		formLy->addRow("Pret", txtPret);
		drly->addLayout(formLy);

		lyMain->addLayout(stgLy);
		lyMain->addLayout(drly);

	}

	void loadList(const vector<Product>& pr) {
		lst->clear();
		for (const auto& i : pr) {
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(i.getName()));
			lst->addItem(item);
		}
	}

	void initConnect() {

		QObject::connect(btnNume, &QPushButton::clicked, [&]() {

			try {
				auto nume = txtNume->text();
				loadList(serv.filtrare("1", nume.toStdString()));

			}
			catch (MyException& e) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
			}

			});

		QObject::connect(btnProd, &QPushButton::clicked, [&]() {

			try {
				auto prod = txtProd->text();
				loadList(serv.filtrare("2", prod.toStdString()));

			}
			catch (MyException& e) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
			}

			});

		QObject::connect(btnPret, &QPushButton::clicked, [&]() {

			try {
				auto pret = txtPret->text();
				loadList(serv.filtrare("3", pret.toStdString()));

			}
			catch (MyException& e) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
			}

			});

		QObject::connect(btnExit, &QPushButton::clicked, [&]() {

			close();

			});
	}
};

class CosGUI : public QWidget {
private:
	ProductServ& serv;
	QListWidget* lst = new QListWidget;
	QLineEdit* txtNume = new QLineEdit;
	QLineEdit* txtNr = new QLineEdit;
	QPushButton* btnAdd = new QPushButton{ "&Adauga" };
	QPushButton* btnGol = new QPushButton{ "&Goleste" };
	QPushButton* btnRand = new QPushButton{ "&Random" };
	QPushButton* btnExit = new QPushButton{ "&Exit" };
	QPushButton* btnCsv = new QPushButton{ "&Export CSV" };
	QPushButton* btnHtml = new QPushButton{ "&Export Html" };

public:

	CosGUI(ProductServ& serv) : serv{ serv } {
		initGUI();
		initConnect();
		loadList(serv.getAll_cos());
	}

	void initGUI();

	void initConnect();

	void loadList(const vector<Product>& list);
};

class RaportGUI : public QWidget {
private:
	QTableWidget* tabel = new QTableWidget;
	QPushButton* btnExit = new QPushButton{ "&Iesire" };

public:
	RaportGUI(const map<string, DTO>& lista) {
		auto lyMain = new QVBoxLayout;
		setLayout(lyMain);
		lyMain->addWidget(tabel);
		lyMain->addWidget(btnExit);

		tabel->setSelectionBehavior(QAbstractItemView::SelectRows);
		tabel->setRowCount(int(lista.size()));
		tabel->setColumnCount(2);
		QStringList labels;
		labels << "Tipul" << "Numar";

		tabel->setRowCount(int(lista.size()));
		int index = 0;
		for (const auto& i : lista) {
			auto item1 = new QTableWidgetItem(QString::fromStdString(i.second.getType()));
			auto item2 = new QTableWidgetItem(QString::number(i.second.getNr()));
			tabel->setItem(index, 0, item1);
			tabel->setItem(index, 1, item2);
			item1->setBackground(QColor(0, 255, 0));
			item2->setBackground(QColor(0, 0, 255));
			index++;
		}
		initConnect();
	}

	void initConnect() {
		QObject::connect(btnExit, &QPushButton::clicked, [&]() {
			close();
			
			});

		QObject::connect(tabel, &QTableWidget::itemSelectionChanged, [&]() {

			/*auto item = tabel->selectedItems();
			if (!item.empty())
			{
				item.at(0)->setBackground(QColor(0, 255, 0));
				item.at(1)->setBackground(QColor(0, 0, 255));
			}*/

			});
	}

	
};


class CosCRUDGUI : public QWidget, public Observer {
private:
	Cos& cos;
	QListWidget* lst = new QListWidget;
	QLineEdit* txtNr = new QLineEdit;
	QPushButton* btnGol = new QPushButton{ "&Goleste" };
	QPushButton* btnRand = new QPushButton{ "&Random" };
	QPushButton* btnExit = new QPushButton{ "&Exit" };

public:

	CosCRUDGUI(Cos& cos1) : cos{ cos1 } {
		initGUI();
		initConnect();
		loadList(cos.get_all_cos());
	}

	void initGUI();

	void initConnect();

	void loadList(const vector<Product>& list);

	~CosCRUDGUI() {
		cos.removeObserver(this);
	}

	void update() override {
		loadList(cos.get_all_cos());
	}
};

class CosReadOnlyGUI : public QWidget, public Observer {
	Cos& cos;
public:
	CosReadOnlyGUI(Cos& cos) : cos{ cos } {
		setMouseTracking(true);
		cos.addObserver(this);

	}

	void update() override {
		repaint();
	}
protected:
	void paintEvent(QPaintEvent*) override {
		QPainter p{ this };
		int nr = (int)cos.get_all_cos().size(), thickness, margin = 5, x = margin;
		double mn = 1;

		if (nr > 0) {
			thickness = (width() - 2 * margin) / nr;
			int space = (int)sqrt(thickness);
			thickness -= space;
			/*for (auto pr : cos.get_all_cos()) {
				if (pr.getPrice() > mn)
					mn = pr.getPrice();
			}*/

			std::mt19937 mt{ std::random_device{}() };
			std::uniform_int_distribution<> dist(0, 200);


			double e = height() / (int)dist(mt);
			//p.setPen(QPen(Qt::black, thickness));
			for (auto pr : cos.get_all_cos()) {
				QRect* rect = new QRect(x, 0, thickness, (int)pr.getPrice() * e - 2);
				p.drawRect(*rect);
				//p.drawLine(x + thickness / 2, 0, x + thickness / 2, med.getPret() * e);
				x += (thickness + space);
			}
		}
	}
};