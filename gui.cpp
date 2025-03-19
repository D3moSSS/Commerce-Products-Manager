#include "gui.h"
#include "Validator.h"

void MdGUI::initConnect() {
	QObject::connect(btnExit, &QPushButton::clicked, [&]() {
		QMessageBox::information(nullptr, "Info", "Exit apasat");
		close();
		});

	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
		try {
			auto nume = txtNume->text();
			auto tip = txtTip->text();
			auto producator = txtProducator->text();
			auto pret = txtPret->text();
		
			if (nume.compare("") != 0)
			{
				if (tip.compare("") != 0)
				{
					if (pret.compare("") != 0)
					{
						if (producator.compare("") != 0)
						{
							string pret_string = pret.toStdString();
							int pret_int = Validator::validatePrice(pret_string);

							if (pret_int == -1)
								throw(MyException("Pretul nu e de tip int!!\n"));

							Product pr(nume.toStdString(), tip.toStdString(), pret_int, producator.toStdString());
							serv.addProduct(pr);

							QMessageBox::warning(this, "Warning", QString::fromStdString("A fost adaugat cu succes!!"));

							loadData(serv.getAll());
						}
						else
							throw(MyException("Nu ai introfus toate elementele!"));
					}
					else
						throw(MyException("Nu ai introfus toate elementele!"));
				}
				else
					throw(MyException("Nu ai introdus toate elementele!"));
			}
			else
				throw(MyException("Nu ai introdus toate elementele!"));
		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}

	});

	QObject::connect(btnDel, &QPushButton::clicked, [&]() {
		try {
			auto nume = txtNume->text();
			serv.deleteProduct(nume.toStdString());
			loadData(serv.getAll());
			QMessageBox::warning(this, "Warning", QString::fromStdString("A fost sters cu succes!!"));

		} catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
	});

	QObject::connect(btnSortNume, &QPushButton::clicked, [&]() {

		loadData(serv.sort(false, cmp_name));

		});

	QObject::connect(btnSortPret, &QPushButton::clicked, [&]() {

		loadData(serv.sort(false, cmp_price));

		});

	QObject::connect(btnSortNumeTip, &QPushButton::clicked, [&]() {

		loadData(serv.sort(false, cmp_name_type));

		});

	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {

		auto sel = lst->selectedItems();
		if (sel.isEmpty())
		{
			txtNume->setText("");
			txtTip->setText("");
			txtPret->setText("");
			txtProducator->setText("");
		}
		else {
			auto selItem = sel.at(0);
			auto name = selItem->text();

			txtNume->setText(name);
			Product pr1;
			for (auto& i : serv.getAll())
				if (i.getName() == name.toStdString())
					pr1 = i;

			auto pr = serv.cautare(pr1);
			txtPret->setText(QString::number(pr.getPrice()));
			txtProducator->setText(QString::fromStdString(pr.getProducer()));
			txtTip->setText(QString::fromStdString(pr.getType()));

		}

		});

	QObject::connect(btnUndo, &QPushButton::clicked, [&]() {

		try {
			serv.undo();
			loadData(serv.getAll());

		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}

	});

	QObject::connect(btnCauta, &QPushButton::clicked, [&]() {

		try {
			Product pr;
			auto name = txtNume->text();
			for (auto& i : serv.getAll())
				if (i.getName() == name.toStdString())
					pr = i;


			txtNume->setText(QString::fromStdString(pr.getName()));
			txtPret->setText(QString::number(pr.getPrice()));
			txtProducator->setText(QString::fromStdString(pr.getProducer()));
			txtTip->setText(QString::fromStdString(pr.getType()));

		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}

		});
	
	QObject::connect(btnMod, &QPushButton::clicked, [&]() {

		try {
			auto nume = txtNume->text();
			auto pret = txtPret->text();
			auto producator = txtProducator->text();
			auto tip = txtTip->text();

			string pret_string = pret.toStdString();
			int pret_int = Validator::validatePrice(pret_string);

			if (pret_int == -1)
				throw(MyException("Pretul nu e de tip int!!\n"));

			Product pr(nume.toStdString(), tip.toStdString(), pret_int, producator.toStdString());

			serv.modifyProduct(nume.toStdString() , pr);
			loadData(serv.getAll());

			QMessageBox::warning(this, "Warning", QString::fromStdString("A fost modificat cu succes!!"));


		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}

		});

	QObject::connect(btnGolesteCos, &QPushButton::clicked, [&]() {
		try {
			serv.emptyCos();
		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
		});

	QObject::connect(btnAddCos, &QPushButton::clicked, [&]() {

			QWidget* addToCos = new QWidget;
			QFormLayout* lyAddToCosGUI = new QFormLayout;
			addToCos->setLayout(lyAddToCosGUI);

			editName = new QLineEdit;

			lyAddToCosGUI->addRow(lblName, editName);

			lyAddToCosGUI->addWidget(btnAddCosGUI);
			addToCos->show();

		});

	QObject::connect(btnAddCosGUI, &QPushButton::clicked, [&]() {
		try {

			string nume = editName->text().toStdString();
			Product pr;
			for (auto& i : serv.getAll())
				if (i.getName() == nume)
					pr = i;
			
			serv.adaugaCos(pr);
			editName->clear();
			QMessageBox::information(this, "Info", QString::fromStdString("Medicament adaugat cu succes."));
		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}

		});

	QObject::connect(btnRandomCos, &QPushButton::clicked, [&]() {

		generateCosGUI = new QWidget;
		QFormLayout* lyGenerateToCosGUI = new QFormLayout;
		generateCosGUI->setLayout(lyGenerateToCosGUI);
			
		editNumber = new QLineEdit;

		lyGenerateToCosGUI->addRow("Numarul de medicamente generate pe lista: ", editNumber);
		lyGenerateToCosGUI->addWidget(btnRandomCosGUI);

		generateCosGUI->show();

		});

	QObject::connect(btnRandomCosGUI, &QPushButton::clicked, [&]() {
		try {
			auto nr = editNumber->text().toInt();
			serv.randomADD_serv(nr);
		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}

		});

	QObject::connect(btnFiltrare, &QPushButton::clicked, [&]() {
		
		auto gui = new FiltrareGui{ serv };
		gui->show();
		
	});

	QObject::connect(btnCosReadOnly, &QPushButton::clicked, [&]() {
		auto gui = new CosReadOnlyGUI{ serv.getCosClass()};
		gui->show();
		});

	QObject::connect(btnCosCRUDGUI, &QPushButton::clicked, [&]() {
		auto gui = new CosCRUDGUI{ serv.getCosClass() };
		gui->show();
		});

	QObject::connect(btnRaport, &QPushButton::clicked, [&]() {
		auto gui = new RaportGUI(serv.raportType());
		gui->show();
	});

	QObject::connect(btnRaport, &QPushButton::clicked, [&]() {
		auto gui = new RaportGUI(serv.raportType());
		gui->show();
		});

	QObject::connect(btnCsv, &QPushButton::clicked, [&]() {
		try {
			serv.exportCSV("csv.csv");
			QMessageBox::information(this, "Info", QString{ "Export succes!" });
		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
		});

	QObject::connect(btnHtml, &QPushButton::clicked, [&]() {
		try {
			serv.exportHTML("html.html");
			QMessageBox::information(this, "Info", QString{ "Export succes!" });
		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
		});

}

void CosGUI::initGUI() {
	QHBoxLayout* lyMain = new QHBoxLayout;
	setLayout(lyMain);

	QLabel* titlu = new QLabel{ "Reteta: " };
	QVBoxLayout* stgLy = new QVBoxLayout;

	auto expLy = new QHBoxLayout;

	expLy->addWidget(btnCsv);
	expLy->addWidget(btnHtml);

	stgLy->addWidget(titlu);
	stgLy->addWidget(lst);
	stgLy->addLayout(expLy);

	auto formLy = new QFormLayout;

	formLy->addRow("Numele: ", txtNume);
	formLy->addRow("Numar pt random", txtNr);

	auto drLy = new QVBoxLayout;
	drLy->addLayout(formLy);
	drLy->addWidget(btnAdd);
	drLy->addWidget(btnGol);
	drLy->addWidget(btnRand);
	drLy->addWidget(btnExit);

	lyMain->addLayout(stgLy);
	lyMain->addLayout(drLy);

}

void CosGUI::loadList(const vector<Product>& list) {
	lst->clear();
	for (auto const& i : list) {
		auto item = new QListWidgetItem{ QString::fromStdString(i.getName()) };
		lst->addItem(item);
	}
}

void CosGUI::initConnect() {
	QObject::connect(btnExit, &QPushButton::clicked, [&]() {
		close();
		});

	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
		try {
			string nume = txtNume->text().toStdString();
			Product pr;
			for (auto& i : serv.getAll())
				if (i.getName() == nume)
					pr = i;

			serv.adaugaCos(pr);
			loadList(serv.getAll_cos());
		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
		});

	QObject::connect(btnGol, &QPushButton::clicked, [&]() {
		try {
			serv.emptyCos();
			loadList(serv.getAll_cos());
		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
		});

	QObject::connect(btnRand, &QPushButton::clicked, [&]() {
		try {
			auto nr = txtNr->text().toInt();
			serv.randomADD_serv(nr);
			loadList(serv.getAll_cos());
		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
		});

	QObject::connect(btnCsv, &QPushButton::clicked, [&]() {
		try {
			serv.exportCSV("csv.csv");
			QMessageBox::information(this, "Info", QString{ "Export succes!" });
		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
		});

	QObject::connect(btnHtml, &QPushButton::clicked, [&]() {
		try {
			serv.exportHTML("html.html");
			QMessageBox::information(this, "Info", QString{ "Export succes!" });
		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
		});
}


void CosCRUDGUI::initGUI() {
	QVBoxLayout* lyMain = new QVBoxLayout;
	setLayout(lyMain);

	QLabel* titlu = new QLabel{ "Reteta: " };
	QVBoxLayout* stgLy = new QVBoxLayout;


	stgLy->addWidget(titlu);
	stgLy->addWidget(lst);

	auto drLy = new QVBoxLayout;
	drLy->addWidget(btnGol);
	drLy->addWidget(btnRand);
	drLy->addWidget(btnExit);

	lyMain->addLayout(stgLy);
	lyMain->addLayout(drLy);

}

void CosCRUDGUI::loadList(const vector<Product>& list) {
	lst->clear();
	for (auto const& i : list) {
		auto item = new QListWidgetItem{ QString::fromStdString(i.getName()) };
		lst->addItem(item);
	}
}

void CosCRUDGUI::initConnect() {
	cos.addObserver(this);
	QObject::connect(btnExit, &QPushButton::clicked, [&]() {
		close();
		});

	QObject::connect(btnGol, &QPushButton::clicked, [&]() {
		try {
			cos.deleteAllProducts();
			loadList(cos.get_all_cos());
		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
		});

	QObject::connect(btnRand, &QPushButton::clicked, [&]() {
		try {
			QInputDialog* inputDialog = new QInputDialog(this);
			bool ok = false;

			int result = inputDialog->getInt(nullptr, "", "Numarul de produse generate de lista", 0, 0, 2147483647, 1, &ok);

			cos.randomADD1(result);
			loadList(cos.get_all_cos());
		}
		catch (MyException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
		});
}