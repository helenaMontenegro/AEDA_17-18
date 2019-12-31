/*
 * sistema.cpp
 *
 *  Created on: 17 de Out de 2017
 *      Author: Mariana
 */

#include "sistema.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

Sistema::~Sistema() {
	for (size_t i = 0; i < acidentes.size(); i++) {
		delete acidentes.at(i);
	}
	for (size_t j = 0; j < postos.size(); j++) {
		delete postos.at(j);
	}
}

vector<Acidente*> Sistema::getAcidentes() const {
	return acidentes;
}

vector<PostoSocorro*> Sistema::getPostos() const {
	return postos;
}

void Sistema::abrirFicheiroPostos(istream &ficheiro) {
	string linha, distrito, numSoc, numVeic, numAmb, numAutot, tag, codigo, veiculo;
	int numSocorristas, numVeiculos, numAmbulancias, numAutotanques;

	while (getline(ficheiro, linha)) {
		getline(ficheiro, tag, ':');
		ficheiro.ignore(1);
		getline(ficheiro, distrito);

		getline(ficheiro, tag, ':');
		ficheiro.ignore(1);
		getline(ficheiro, codigo);

		Local local(distrito, codigo);

		getline(ficheiro, tag, ':');
		ficheiro.ignore(1);
		getline(ficheiro, numSoc);
		numSocorristas = atoi(numSoc.c_str());

		getline(ficheiro, tag, ':');
		ficheiro.ignore(1);
		getline(ficheiro, numVeic);
		numVeiculos = atoi(numVeic.c_str());

		if (linha == "Bombeiros") {
			getline(ficheiro, tag, ':');
			ficheiro.ignore(1);
			getline(ficheiro, numAmb);
			numAmbulancias = atoi(numAmb.c_str());

			getline(ficheiro, tag, ':');
			ficheiro.ignore(1);
			getline(ficheiro, numAutot);
			numAutotanques = atoi(numAutot.c_str());

			ficheiro.ignore(1000, '\n');

			Bombeiros *pBombeiros = new Bombeiros(local, numSocorristas, numVeiculos, numAmbulancias, numAutotanques);
			postos.push_back(pBombeiros);
		} else if (linha == "Policia") {
			getline(ficheiro, tag, ':');
			ficheiro.ignore(1);
			getline(ficheiro, veiculo);

			ficheiro.ignore(1000, '\n');
			if (veiculo == "Moto") {
				Policia *pPolicia = new Policia(local, numSocorristas, numVeiculos, true, false);
				postos.push_back(pPolicia);
			} else {
				Policia *pPolicia = new Policia(local, numSocorristas, numVeiculos, false, true);
				postos.push_back(pPolicia);
			}
		} else if (linha == "Inem") {
			getline(ficheiro, tag, ':');
			ficheiro.ignore(1);
			getline(ficheiro, veiculo);

			ficheiro.ignore(1000, '\n');
			if (veiculo == "Moto") {
				Inem *pInem = new Inem(local, numSocorristas, numVeiculos, true, false, false);
				postos.push_back(pInem);
			} else if (veiculo == "Carro") {
				Inem *pInem = new Inem(local, numSocorristas, numVeiculos, false, true, false);
				postos.push_back(pInem);
			} else {
				Inem *pInem = new Inem(local, numSocorristas, numVeiculos, false, false, true);
				postos.push_back(pInem);
			}
		}
	}
}

void Sistema::abrirFicheiroAcidentes(istream &ficheiro) {
	string linha, localD, extra, num, codigoPostal;
	int dia, mes, ano;

	while (!ficheiro.eof()) {
		getline(ficheiro, linha, '\n');

		getline(ficheiro, extra, ':');
		ficheiro.ignore(1);
		getline(ficheiro, localD, '\n');
		getline(ficheiro, extra, ':');
		ficheiro.ignore(1);
		getline(ficheiro, codigoPostal, '\n');
		Local local(localD, codigoPostal);

		getline(ficheiro, extra, ':');
		ficheiro.ignore(1);
		getline(ficheiro, num, '-');
		dia = atoi(num.c_str());
		getline(ficheiro, num, '-');
		mes = atoi(num.c_str());
		getline(ficheiro, num, '\n');
		ano = atoi(num.c_str());
		Data d(dia, mes, ano);

		if (linha == "Incendio Florestal") {
			string area1;
			int area;
			getline(ficheiro, extra, ':');
			ficheiro.ignore(1);
			getline(ficheiro, area1, '\n');
			area = atoi(area1.c_str());
			IncendioFlorestal *novoAcidente1 = new IncendioFlorestal(local, d,
					area);
			insereAcidente(novoAcidente1);

		} else if (linha == "Incendio Domestico") {
			string apartamento1;
			bool apartamento = false;
			getline(ficheiro, apartamento1, '\n');
			if (apartamento1 == "Apartamento")
				apartamento = true;
			IncendioDomestico *novoAcidente2 = new IncendioDomestico(local, d,
					apartamento);
			insereAcidente(novoAcidente2);

		} else if (linha == "Assalto") {
			string casaComercial, numFeridos;
			bool casaCom = false;
			int numFer;

			getline(ficheiro, extra, ':');
			ficheiro.ignore(1);
			getline(ficheiro, numFeridos, '\n');
			numFer = atoi(numFeridos.c_str());

			getline(ficheiro, casaComercial, '\n');
			if (casaComercial == "Casa Comercial")
				casaCom = true;
			Assalto *novoAcidente3 = new Assalto(local, d, numFer, casaCom);
			insereAcidente(novoAcidente3);

		} else if (linha == "Acidente de Viacao") {
			string numFeridos1, numVeiculos, estrada;
			bool estradaNacional = false;
			int numFer1, numVeic;

			getline(ficheiro, extra, ':');
			ficheiro.ignore(1);
			getline(ficheiro, numFeridos1, '\n');
			numFer1 = atoi(numFeridos1.c_str());

			getline(ficheiro, extra, ':');
			ficheiro.ignore(1);
			getline(ficheiro, numVeiculos, '\n');
			numVeic = atoi(numVeiculos.c_str());
			getline(ficheiro, estrada, '\n');
			if (estrada == "Estrada Nacional")
				estradaNacional = true;
			AcidenteViacao *novoAcidente4 = new AcidenteViacao(local, d,
					numFer1, numVeic, estradaNacional);
			insereAcidente(novoAcidente4);
		}
		ficheiro.ignore(1);
	}
}

void Sistema::insereAcidente(Acidente *acid) {
	acidentes.push_back(acid);
}

void Sistema::adicionaAcidente() {
	int flag = 1, numFer, numVeic, dia, mes, ano, cp1, cp2;
	float area;
	string tipoAcidente, localD, data, apartamento, casa, estrada, codigoPostal;
	string incFlor = "Incendio Florestal", incDom = "Incendio Domestico",
			assalto = "Assalto", aciViacao = "Acidente de Viacao", ap =
					"apartamento", mr = "moradia", casaC = "comercial", casaP =
					"particular", estradaNac = "estrada", autoest =
					"autoestrada";
	bool apart, casaCom, estradaN;
	char hifen;
	cin.ignore(1000, '\n');
	cout << endl;
	do {
		cout << "Tipo de acidente? (Incendio Florestal; Incendio Domestico; Assalto; Acidente de Viacao)" << endl;
		getline(cin, tipoAcidente);
		if (tipoAcidente != incFlor && tipoAcidente != incDom && tipoAcidente != assalto
				&& tipoAcidente != aciViacao) {
			cout << "Tipo de acidente invalido. Tente novamente." << endl;
		} else
			flag = 0;
	} while (flag == 1);
	flag = 0; //AAAA
	cout << "Distrito onde ocorreu o acidente?" << endl;
	getline(cin, localD);
	Local local(localD);
	flag = 1;
	do {
		try {
			cout << "Codigo Postal do local do acidente? (Formato: nnnn-nnn)" << endl;
			cin >> codigoPostal;
			istringstream ss;
			ss.str(codigoPostal);
			ss >> cp1 >> hifen >> cp2;
			if (hifen != '-')
				throw CodigoPostalInvalido();
			local.setCodigoPostal1(cp1);
			local.setCodigoPostal2(cp2);
			flag = 0;
		} catch (CodigoPostalInvalido &c) {
			cout << "Codigo Postal invalido. Tente novamente." << endl;
		}
	} while (flag == 1);

	flag = 1;
	Data d;
	do {
		try {
			cout << "Data do acidente? (Formato: dd-mm-aaaa)" << endl;
			cin >> data;
			istringstream ss;
			ss.str(data);
			ss >> dia >> hifen >> mes;
			if (hifen != '-')
				throw DataInvalida();
			ss >> hifen >> ano;
			if (hifen != '-')
				throw DataInvalida();
			d.setDia(dia);
			d.setMes(mes);
			d.setAno(ano);
			flag = 0;
		} catch (...) {
			cout << "Data Invalida. Tente novamente." << endl;
		}
	} while (flag == 1);

	if (tipoAcidente == incFlor) {
		flag = 1;
		do {
			cout << "Area alcancada pelo incendio? (em metros quadrados)" << endl;
			cin >> area;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Area invalida. Tente novamente." << endl;
			} else
				flag = 0;
		} while (flag == 1);
		Acidente *novoAcidente = new IncendioFlorestal(local, d, area);
		insereAcidente(novoAcidente);
		cin.ignore(1, '\n');
		return;
	} else if (tipoAcidente == incDom) {
		flag = 1;
		do {
			cout << "Incendio num apartamento ou numa moradia?" << endl;
			cin >> apartamento;
			if (apartamento == ap) {
				apart = true;
				flag = 0;
			} else if (apartamento == mr) {
				apart = false;
				flag = 0;
			} else
				cout << "Input invalido. Tente novamente, escrevendo 'apartamento' ou 'moradia'." << endl;
		} while (flag == 1);
		Acidente *novoAcidente1 = new IncendioDomestico(local, d, apart);
		insereAcidente(novoAcidente1);
		cin.ignore(1, '\n');
		return;
	} else if (tipoAcidente == assalto) {
		flag = 1;
		do {
			cout << "Numero de feridos?" << endl;
			cin >> numFer;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Numero invalido. Tente novamente." << endl;
			} else
				flag = 0;
		} while (flag == 1);
		flag = 1;
		do {
			cout << "O assalto ocorreu em casa 'comercial' ou 'particular'?" << endl;
			cin >> casa;
			if (casa == casaC) {
				casaCom = true;
				flag = 0;
			} else if (casa == casaP) {
				casaCom = false;
				flag = 0;
			} else
				cout << "Input invalido. Tente novamente, escrevendo 'casa comercial' ou 'casa particular'" << endl;
		} while (flag == 1);
		Acidente *novoAcidente2 = new Assalto(local, d, numFer, casaCom);
		insereAcidente(novoAcidente2);
		cin.ignore(1, '\n');
		return;
	} else {
		flag = 1;
		do {
			cout << "Numero de feridos?" << endl;
			cin >> numFer;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Numero invalido. Tente novamente." << endl;
			} else
				flag = 0;
		} while (flag == 1);

		flag = 1;
		do {
			cout << "Numero de veiculos envolvidos?" << endl;
			cin >> numVeic;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Numero invalido. Tente novamente." << endl;
			} else
				flag = 0;
		} while (flag == 1);

		flag = 1;
		do {
			cout << "O acidente ocorreu em 'estrada' nacional ou 'autoestrada'?" << endl;
			cin >> estrada;
			if (estrada == estradaNac) {
				estradaN = true;
				flag = 0;
			} else if (estrada == autoest) {
				estradaN = false;
				flag = 0;
			} else
				cout << "Input invalido. Tente novamente, escrevendo 'estrada' ou 'autoestrada'" << endl;
		} while (flag == 1);
		Acidente *novoAcidente3 = new AcidenteViacao(local, d, numFer, numVeic,
				estradaN);
		insereAcidente(novoAcidente3);
		cin.ignore(1, '\n');
	}
}

void Sistema::criaPostoSocorro() {
	int numSoc, numVeic, numAutot, numAmb, cp1, cp2;
	bool moto = false, carro = false, ambulancia = false, erro = true;
	string tipoPosto, local, codigoPostal, veiculo;
	char hifen, resposta;

	cout << "\nTipo de posto (Bombeiros/Policia/Inem): ";
	while (erro) {
		cin >> tipoPosto;
		cin.ignore(100, '\n');
		if (tipoPosto != "Bombeiros" && tipoPosto != "Policia" && tipoPosto != "Inem")
			cout << "Tipo de posto invalido! Tente novamente: ";
		else
			erro = false;
	}

	erro = true;
	cout << "Distrito onde se situa o posto: ";
	getline(cin, local);
	Local l(local);

	cout << "Codigo postal do local (Formato: nnnn-nnn): ";
	while (erro) {
		try {
			cin >> codigoPostal;
			istringstream ss;
			ss.str(codigoPostal);
			ss >> cp1 >> hifen >> cp2;
			if (hifen != '-')
				throw CodigoPostalInvalido();
			l.setCodigoPostal1(cp1);
			l.setCodigoPostal2(cp2);
			erro = false;
		} catch (CodigoPostalInvalido &c) {
			cout << "\nCodigo postal invalido! Tente novamente: ";
		}
	}

	erro = true;
	cout << "Numero de socorristas: ";
	while (erro) {
		cin >> numSoc;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nNumero invalido! Tente novamente." << endl;
		} else
			erro = false;
	}

	erro = true;
	cout << "Numero de veiculos: ";
	while (erro) {
		cin >> numVeic;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nNumero invalido! Tente novamente." << endl;
		} else
			erro = false;
	}

	if (tipoPosto == "Bombeiros") {
		erro = true;
		cout << "Numero de ambulancias: ";
		while (erro) {
			cin >> numAmb;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(100, '\n');
				cout << "\nNumero invalido! Tente novamente." << endl;
			} else
				erro = false;
		}
		erro = true;
		cout << "Numero de autotanques: ";
		while (erro) {
			cin >> numAutot;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Numero invalido! Tente novamente." << endl;
			} else
				erro = false;
		}

		Bombeiros *pBombeiros = new Bombeiros(l, numSoc, numVeic, numAmb, numAutot);
		/* adiciona informacao ao vetor postos */
		postos.push_back(pBombeiros);
	} else if (tipoPosto == "Policia") {
		erro = true;
		cout << "Tipo de veiculo que conduz (Moto/Carro): ";
		while (erro) {
			cin >> veiculo;
			if (veiculo != "Moto" && veiculo != "Carro")
				cout << "\nTipo de veiculo invalido! Tente novamente: ";
			else
				erro = false;
		}
		if (veiculo == "Moto")
			moto = true;
		else
			carro = true;

		Policia *pPolicia = new Policia(l, numSoc, numVeic, moto, carro);
		/* adiciona informacao ao vetor postos */
		postos.push_back(pPolicia);
	} else {
		erro = true;
		cout << "Tipo de veiculo que conduz (Moto/Carro/Ambulancia): ";
		while (erro) {
			cin >> veiculo;
			if (veiculo != "Moto" && veiculo != "Carro" && veiculo != "Ambulancia")
				cout << "\nTipo de veiculo invalido! Tente novamente: ";
			else
				erro = false;
		}
		if (veiculo == "Moto")
			moto = true;
		else if (veiculo == "Carro")
			carro = true;
		else
			ambulancia = true;

		Inem *pInem = new Inem(l, numSoc, numVeic, moto, carro, ambulancia);
		/* adiciona informacao ao vetor postos */
		postos.push_back(pInem);
	}
	cout << "Criacao feita com sucesso! Pretende visualizar todos os postos de socorro? (S/N)";
	cin >> resposta;
	while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\nResposta invalida. Tente novamente: ";
		cin >> resposta;
	}
	if (resposta == 'S')
		visualizaInformacaoPostos();
}

void Sistema::editaPostoSocorro() {
	PostoSocorro *p;
	char resposta, hifen;
	string tipoPosto, local, codigoPostal;
	bool erro = true, naoExiste = true;
	int socorristas, veiculos, cp1, cp2;

	cin.ignore(1000, '\n');
	cout << "\nInsira o tipo de posto que quer alterar(Bombeiros/Policia/Inem): ";
	while (erro) {
		cin >> tipoPosto;
		cin.ignore(100, '\n');
		if (tipoPosto != "Bombeiros" && tipoPosto != "Policia"
				&& tipoPosto != "Inem")
			cout << "Tipo de posto invalido! Tente novamente: ";
		else
			erro = false;
	}

	erro = true;
	cout << "Distrito onde se situa o posto: ";
	getline(cin, local);
	Local l(local);

	cout << "Codigo postal do local (Formato: nnnn-nnn): ";
	while (erro) {
		try {
			cin >> codigoPostal;
			istringstream ss;
			ss.str(codigoPostal);
			ss >> cp1 >> hifen >> cp2;
			if (hifen != '-')
				throw CodigoPostalInvalido();
			l.setCodigoPostal1(cp1);
			l.setCodigoPostal2(cp2);
			erro = false;
		} catch (CodigoPostalInvalido c) {
			cout << "\nCodigo postal invalido! Tente novamente: ";
		}
	}

	for (size_t i = 0; i < postos.size(); i++) {
		if (postos[i]->getTipoPosto() == tipoPosto
				&& postos[i]->getLocal().getDistrito() == l.getDistrito()
				&& postos[i]->getLocal().getCodigoPostal()
						== l.getCodigoPostal()) {
			p = postos[i];
			naoExiste = false;
		}
	}
	if (naoExiste) {
		cerr << "Postos de socorro inexistente!\n";
		return;
	}

	cout << "Adicionar socorristas? (S/N)";
	cin >> resposta;
	while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
		cin.clear();
		cin.ignore(100, '\n');
		cerr << "\nResposta invalida. Tente novamente: ";
		cin >> resposta;
	}
	if (resposta == 'S') {
		cout << "Quantos?\n";
		cin >> socorristas;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "\nNumero invalido. Tente novamente: ";
			cin >> socorristas;
		}
		p->setNumSocorristas(socorristas);
	}

	cout << "Remover socorristas? (S/N)";
	cin >> resposta;
	while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
		cin.clear();
		cin.ignore(100, '\n');
		cerr << "\nResposta invalida. Tente novamente: ";
		cin >> resposta;
	}
	if (resposta == 'S') {
		cout << "Quantos?\n";
		cin >> socorristas;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "\nNumero invalido. Tente novamente: ";
			cin >> socorristas;
		}
		socorristas *= -1;
		p->setNumVeiculos(socorristas);
	}

	cout << "Adicionar veiculos? (S/N)";
	cin >> resposta;
	while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
		cin.clear();
		cin.ignore(100, '\n');
		cerr << "\nResposta invalida. Tente novamente: ";
		cin >> resposta;
	}
	if (resposta == 'S') {
		cout << "Quantos?\n";
		cin >> veiculos;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "\nNumero invalido. Tente novamente: ";
			cin >> veiculos;
		}
		p->setNumVeiculos(veiculos);
	}

	cout << "Remover veiculos? (S/N)";
	cin >> resposta;
	while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
		cin.clear();
		cin.ignore(100, '\n');
		cerr << "\nResposta invalida. Tente novamente: ";
		cin >> resposta;
	}
	if (resposta == 'S') {
		cout << "Quantos?\n";
		cin >> veiculos;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cerr << "\nNumero invalido. Tente novamente: ";
			cin >> veiculos;
		}
		veiculos *= -1;
		p->setNumVeiculos(veiculos);
	}

	cout
			<< "Alteracao feita com sucesso! Pretende visualizar todos os postos de socorro? (S/N)";
	cin >> resposta;
	while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
		cin.clear();
		cin.ignore(100, '\n');
		cerr << "\nResposta invalida. Tente novamente: ";
		cin >> resposta;
	}
	if (resposta == 'S')
		visualizaInformacaoPostos();
}

void Sistema::editaAcidente() {
	int flag = 1, numFer, numVeic, dia, mes, ano, cp1, cp2;
	string tipoAcidente, localD, data, codigoPostal;
	string incFlor = "Incendio Florestal", incDom = "Incendio Domestico",
			assalto = "Assalto", aciViacao = "Acidente de Viacao";
	char hifen, resposta;

	cout << endl;
	cin.ignore(1000, '\n');
	do {
		cout << "Tipo do acidente? (Incendio Florestal; Incendio Domestico; Assalto; Acidente de Viacao)"
				<< endl;
		getline(cin, tipoAcidente);
		if (tipoAcidente != incFlor && tipoAcidente != incDom
				&& tipoAcidente != assalto && tipoAcidente != aciViacao) {
			cout << "Tipo de acidente invalido. Tente novamente." << endl;
		} else
			flag = 0;
	} while (flag == 1);

	flag = 0;
	cout << "Distrito onde ocorreu o acidente?" << endl;
	getline(cin, localD);
	Local local(localD);

	flag = 1;
	do {
		try {
			cout << "Codigo Postal do local do acidente? (Formato: nnnn-nnn)"
					<< endl;
			cin >> codigoPostal;
			istringstream ss;
			ss.str(codigoPostal);
			ss >> cp1 >> hifen >> cp2;
			if (hifen != '-')
				throw CodigoPostalInvalido();
			local.setCodigoPostal1(cp1);
			local.setCodigoPostal2(cp2);
			flag = 0;
		} catch (CodigoPostalInvalido c) {
			cout << "Codigo Postal invalido. Tente novamente." << endl;
		}
	} while (flag == 1);

	cin.ignore(1000, '\n');
	flag = 1;
	Data d;
	do {
		try {
			cout << "Data do acidente? (Formato: dd-mm-aaaa)" << endl;
			cin >> data;
			istringstream ss;
			ss.str(data);
			ss >> dia >> hifen >> mes;
			if (hifen != '-')
				throw DataInvalida();
			ss >> hifen >> ano;
			if (hifen != '-')
				throw DataInvalida();
			d.setDia(dia);
			d.setMes(mes);
			d.setAno(ano);
			flag = 0;
		} catch (...) {
			cout << "Data Invalida. Tente novamente." << endl;
		}
	} while (flag == 1);

	size_t i = 0;
	for (; i < acidentes.size(); i++) {
		if ((acidentes.at(i)->getTipoAcidente() == tipoAcidente)
				&& (acidentes.at(i)->getLocal().getDistrito() == localD)
				&& (acidentes.at(i)->getLocal().getCodigoPostal()
						== codigoPostal) && (acidentes.at(i)->getData() == d)) {
			if (acidentes.at(i)->getTratado()) {
				cout
						<< "Nao e possivel modificar um acidente que já foi socorrido."
						<< endl;
				return;
			}
			break;
		}
	}
	if (i == acidentes.size()) {
		cout << "O acidente indicado nao existe." << endl;
		return;
	}

	//INCENDIO FLORESTAL
	if (acidentes.at(i)->getTipoAcidente() == incFlor) {
		cin.ignore(1000, '\n');
		cout << "Alterar area do incendio? (S/N) ";
		cin >> resposta;
		while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nResposta invalida. Tente novamente." << endl;
			cout << "Alterar area do incendio? (S/N) ";
			cin >> resposta;
		}
		if (resposta == 'S') {
			float area;
			flag = 1;
			do {
				cin.ignore(1000, '\n');
				cout << "Area alcancada pelo incendio? (em metros quadrados)"
						<< endl;
				cin >> area;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Area invalida. Tente novamente." << endl;
				} else
					flag = 0;
			} while (flag == 1);
			acidentes.at(i)->setArea(area);
		}
		cin.ignore(1000, '\n');
		cout << "Visualizar acidentes? (S/N) ";
		cin >> resposta;
		while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nResposta invalida. Tente novamente." << endl;
			cout << "Visualizar acidentes? (S/N) ";
			cin >> resposta;
		}
		if (resposta == 'S') {
			cout << endl;
			visualizaInformacaoAcidentes();
			cout << endl;
		} else
			return;
	}
	//INCENDIO DOMESTICO
	else if (acidentes.at(i)->getTipoAcidente() == incDom) {
		if (acidentes.at(i)->getApartamento())
			cout << "Incendio em apartamento. Alterar? (S/N) ";
		else
			cout << "Incendio em moradia. Alterar? (S/N) ";
		cin >> resposta;
		while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nResposta invalida. Tente novamente: " << endl;
			cin >> resposta;
		}
		if (resposta == 'S') {
			acidentes.at(i)->setApartamento();
		}
		cin.ignore(1000, '\n');
		cout << "Visualizar acidentes? (S/N) ";
		cin >> resposta;
		while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nResposta invalida. Tente novamente." << endl;
			cout << "Visualizar acidentes? (S/N) ";
			cin >> resposta;
		}
		if (resposta == 'S') {
			cout << endl;
			visualizaInformacaoAcidentes();
			cout << endl;
		} else
			return;
	}
	//ASSALTO
	else if (acidentes.at(i)->getTipoAcidente() == assalto) {
		cin.ignore(1000, '\n');
		cout << "Alterar numero de feridos? (S/N) ";
		cin >> resposta;
		while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nResposta invalida. Tente novamente." << endl;
			cout << "Alterar numero de feridos? (S/N) ";
			cin >> resposta;
		}
		if (resposta == 'S') {
			int numFeridos;
			flag = 1;
			do {
				cin.ignore(1000, '\n');
				cout << "Quantos feridos?" << endl;
				cin >> numFeridos;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Numero invalido. Tente novamente." << endl;
				} else
					flag = 0;
			} while (flag == 1);
			acidentes.at(i)->setNumFeridos(numFeridos);
		}
		if (acidentes.at(i)->getCasaComercial())
			cout << "Assalto em casa comercial. Alterar? (S/N) ";
		else
			cout << "Assalto em casa particular. Alterar? (S/N) ";
		cin >> resposta;
		while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nResposta invalida. Tente novamente." << endl;
			cin >> resposta;
		}
		if (resposta == 'S')
			acidentes.at(i)->setCasaComercial();
		cin.ignore(1000, '\n');
		cout << "Visualizar acidentes? (S/N) ";
		cin >> resposta;
		while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nResposta invalida. Tente novamente." << endl;
			cout << "Visualizar acidentes? (S/N) ";
			cin >> resposta;
		}
		if (resposta == 'S') {
			cout << endl;
			visualizaInformacaoAcidentes();
			cout << endl;
		} else
			return;
	}
	//ACIDENTE DE VIACAO
	else {
		cin.ignore(1000, '\n');
		cout << "Alterar numero de feridos? (S/N) ";
		cin >> resposta;
		while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nResposta invalida. Tente novamente." << endl;
			cout << "Alterar numero de feridos? (S/N) ";
			cin >> resposta;
		}
		if (resposta == 'S') {
			int numFeridos;
			flag = 1;
			do {
				cin.ignore(1000, '\n');
				cout << "Quantos feridos?" << endl;
				cin >> numFeridos;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Numero invalido. Tente novamente." << endl;
				} else
					flag = 0;
			} while (flag == 1);
			acidentes.at(i)->setNumFeridos(numFeridos);
		}

		cin.ignore(1000, '\n');
		cout << "Alterar numero de veiculos? (S/N) ";
		cin >> resposta;
		while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nResposta invalida. Tente novamente." << endl;
			cout << "Alterar numero de veiculos? (S/N) ";
			cin >> resposta;
		}
		if (resposta == 'S') {
			int numVeiculos;
			flag = 1;
			do {
				cin.ignore(1000, '\n');
				cout << "Quantos veiculos?" << endl;
				cin >> numVeiculos;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Numero invalido. Tente novamente." << endl;
				} else
					flag = 0;
			} while (flag == 1);
			acidentes.at(i)->setNumVeiculos(numVeiculos);
		}
		cin.ignore(1000, '\n');
		if (acidentes.at(i)->getEstradaNacional())
			cout << "Acidente em estrada nacional. Alterar? (S/N) ";
		else
			cout << "Assalto em autoestrada. Alterar? (S/N) ";
		cin >> resposta;
		while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nResposta invalida. Tente novamente." << endl;
			cin >> resposta;
		}
		if (resposta == 'S')
			acidentes.at(i)->setEstradaNacional();
		cin.ignore(1000, '\n');
		cout << "Visualizar acidentes? (S/N) ";
		cin >> resposta;
		while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nResposta invalida. Tente novamente." << endl;
			cout << "Visualizar acidentes? (S/N) ";
			cin >> resposta;
		}
		if (resposta == 'S') {
			cout << endl;
			visualizaInformacaoAcidentes();
			cout << endl;
		} else
			return;
	}
}

void Sistema::removeAcidentesSistema(ostream &out) {
	for (size_t i = 0; i < acidentes.size(); i++) {
		if (acidentes[i]->getTratado()) {
			delete acidentes[i];
			acidentes.erase(acidentes.begin() + i);
			i--;
		}
	}

	/* reescreve conteudo do ficheiro de texto apenas com acidentes não tratados */
	imprimeInformacaoAcidentes(out);
}

void Sistema::visualizaInformacaoAcidentes() const {
	for (size_t i = 0; i < acidentes.size(); i++) {
		acidentes.at(i)->visualizaInformacao();
		if (i != acidentes.size() - 1)
			cout << endl;
	}
}

void Sistema::imprimeInformacaoAcidentes(ostream &out) {
	for (size_t i = 0; i < acidentes.size(); i++) {
		acidentes.at(i)->imprimeInformacao(out);
		if (i != acidentes.size() - 1)
			out << endl;
	}
}

void Sistema::visualizaInformacaoPostos() const {
	for (size_t i = 0; i < postos.size(); i++)
		postos[i]->visualizaInformacao();
}

void Sistema::atualizaFicheiroPostos(ostream &out) {
	for (size_t i = 0; i < postos.size(); i++) {
		postos[i]->imprimeInformacao(out);
		if (i != postos.size() - 1)
			out << endl;
	}
}

PostoSocorro* Sistema::verificaPostoMaisPerto(Acidente &a, bool policia) {
	PostoSocorro *min = postos.at(0);
	string incF = "Incendio Florestal", incD = "Incendio Domestico", b =
			"Bombeiros", p = "Policia", inem = "Inem";

	//Incendio Florestal e Incendio Domestico - bombeiros
	if (a.getTipoAcidente() == incF || (a.getTipoAcidente() == incD && policia
			== false)) {
		int socorristas = a.getNumSocorristas();
		int autotanques = a.getNumCarrosBombeiros();
		size_t j;
		for (j = 0; j < postos.size(); j++) {
			int socorristasPosto = postos.at(j)->getNumSocorristas();
			int autotanquesPosto = postos.at(j)->getNumAutotanques();
			if (postos.at(j)->getTipoPosto() == b) {
				for (size_t k = 0; k < postos.at(j)->getAcidentes().size(); k++) {
					if (postos.at(j)->getAcidentes().at(k)->getData()
							== a.getData()) {
						socorristasPosto
								-= postos.at(j)->getAcidentes().at(k)->getNumSocorristas();
						autotanquesPosto
								-= postos.at(j)->getAcidentes().at(k)->getNumCarrosBombeiros();
					}
				}
				if (socorristasPosto >= socorristas && autotanquesPosto
						>= autotanques) {
					min = postos.at(j);
					break;
				}
			}
		}
		if (j == postos.size())
			throw SemRecursosDisponiveis();

		for (size_t i = j + 1; i < postos.size(); i++) {
			int socorristasPosto = postos.at(i)->getNumSocorristas();
			int autotanquesPosto = postos.at(i)->getNumAutotanques();
			if (postos.at(i)->getTipoPosto() == b) {
				for (size_t k = 0; k < postos.at(i)->getAcidentes().size(); k++) {
					if (postos.at(i)->getAcidentes().at(k)->getData()
							== a.getData()) {
						socorristasPosto
								-= postos.at(i)->getAcidentes().at(k)->getNumSocorristas();
						autotanquesPosto
								-= postos.at(i)->getAcidentes().at(k)->getNumCarrosBombeiros();
					}
				}
				if (socorristasPosto >= socorristas && autotanquesPosto
						>= autotanques) {
					min = comparaDistancias(a, min, postos.at(i));
				}
			}
		}
	}

	//Policia
	else if (policia == true) {
		int numPolicia = a.getNumPolicia();
		size_t j;
		for (j = 0; j < postos.size(); j++) {
			int numCarrosPolicia = postos.at(j)->getNumVeiculos();
			int numPoliciaPosto = postos.at(j)->getNumSocorristas();
			if (postos.at(j)->getTipoPosto() == p
					|| (postos.at(j)->getTipoPosto() == inem
							&& !postos.at(j)->getAmbulancia())) {
				for (size_t k = 0; k < postos.at(j)->getAcidentes().size(); k++) {
					if (postos.at(j)->getAcidentes().at(k)->getData()
							== a.getData()) {
						numPoliciaPosto
								-= postos.at(j)->getAcidentes().at(k)->getNumPolicia();
						if (postos.at(j)->getMoto())
							numCarrosPolicia
									-= postos.at(j)->getAcidentes().at(k)->getNumPolicia();
						else {
							numCarrosPolicia
									-= postos.at(j)->getAcidentes().at(k)->getNumPolicia()
											/ 2
											+ postos.at(j)->getAcidentes().at(k)->getNumPolicia()
													% 2;
						}
					}
				}
				if (postos.at(j)->getMoto()) {
					if (numPoliciaPosto >= numPolicia && numCarrosPolicia
							>= numPolicia) {
						min = postos.at(j);
						break;
					}
				} else if (numPoliciaPosto >= numPolicia && numCarrosPolicia
						>= numPolicia / 2 + numPolicia % 2) {
					min = postos.at(j);
					break;
				}
			}
		}
		if (j == postos.size())
			throw SemRecursosDisponiveis();

		for (size_t i = j + 1; i < postos.size(); i++) {
			int numCarrosPolicia = postos.at(i)->getNumVeiculos();
			int numPoliciaPosto = postos.at(i)->getNumSocorristas();
			if (postos.at(i)->getTipoPosto() == p
					|| (postos.at(i)->getTipoPosto() == inem
							&& !postos.at(i)->getAmbulancia())) {
				for (size_t k = 0; k < postos.at(i)->getAcidentes().size(); k++) {
					if (postos.at(i)->getAcidentes().at(k)->getData()
							== a.getData())
						numPoliciaPosto
								-= postos.at(i)->getAcidentes().at(k)->getNumPolicia();
				}
				if (postos.at(i)->getMoto()) {
					if (numPoliciaPosto >= numPolicia && numCarrosPolicia
							>= numPolicia) {
						min = comparaDistancias(a, min, postos.at(i));
					}
				} else if (numPoliciaPosto >= numPolicia && numCarrosPolicia
						>= numPolicia / 2 + numPolicia % 2) {
					min = comparaDistancias(a, min, postos.at(i));
				}
			}
		}
	}

	//Assalto e Acidente de Viação - INEM ou Bombeiros
	else {
		int socorristas = a.getNumSocorristas();
		int ambulancias = a.getNumCarrosBombeiros();
		size_t j;
		for (j = 0; j < postos.size(); j++) {
			int socorristasPosto = postos.at(j)->getNumSocorristas();
			int ambulanciasPosto = postos.at(j)->getNumAmbulancias();
			if (postos.at(j)->getTipoPosto() == b
					|| (postos.at(j)->getTipoPosto() == inem
							&& postos.at(j)->getAmbulancia())) {
				for (size_t k = 0; k < postos.at(j)->getAcidentes().size(); k++) {
					if (postos.at(j)->getAcidentes().at(k)->getData()
							== a.getData()) {
						socorristasPosto
								-= postos.at(j)->getAcidentes().at(k)->getNumSocorristas();
						ambulanciasPosto
								-= postos.at(j)->getAcidentes().at(k)->getNumSocorristas()
										/ 2
										+ postos.at(j)->getAcidentes().at(k)->getNumSocorristas()
												% 2;
					}
				}
				if (socorristasPosto >= socorristas && ambulanciasPosto
						>= ambulancias) {
					min = postos.at(j);
					break;
				}
			}
		}
		if (j == postos.size())
			throw SemRecursosDisponiveis();

		for (size_t i = j + 1; i < postos.size(); i++) {
			int socorristasPosto = postos.at(i)->getNumSocorristas();
			int ambulanciasPosto = postos.at(i)->getNumAmbulancias();
			if (postos.at(i)->getTipoPosto() == b
					|| (postos.at(i)->getTipoPosto() == inem
							&& postos.at(i)->getAmbulancia())) {
				for (size_t k = 0; k < postos.at(i)->getAcidentes().size(); k++) {
					if (postos.at(i)->getAcidentes().at(k)->getData()
							== a.getData()) {
						socorristasPosto
								-= postos.at(i)->getAcidentes().at(k)->getNumSocorristas();
						ambulanciasPosto
								-= postos.at(i)->getAcidentes().at(k)->getNumSocorristas()
										/ 2
										+ postos.at(i)->getAcidentes().at(k)->getNumSocorristas()
												% 2;
					}
				}
				if (socorristasPosto >= socorristas && ambulanciasPosto
						>= ambulancias) {
					min = comparaDistancias(a, min, postos.at(i));
				}
			}
		}
	}
	return min;
}

PostoSocorro* Sistema::comparaDistancias(Acidente &a, PostoSocorro *p1, PostoSocorro *p2) {
	int distCodigo1P1, distCodigo2P1, distCodigo1P2, distCodigo2P2;
	distCodigo1P1 = abs(p1->getLocal().getCodigoPostal1() - a.getLocal().getCodigoPostal1());
	distCodigo2P1 = abs(p1->getLocal().getCodigoPostal2() - a.getLocal().getCodigoPostal2());
	distCodigo1P2 = abs(p2->getLocal().getCodigoPostal1() - a.getLocal().getCodigoPostal1());
	distCodigo2P2 = abs(p2->getLocal().getCodigoPostal2() - a.getLocal().getCodigoPostal1());
	if (distCodigo1P1 > distCodigo1P2)
		return p2;
	else if (distCodigo1P1 < distCodigo1P2)
		return p1;
	else if(distCodigo2P1 > distCodigo2P2)
		return p2;
	else
		return p1;
}

void Sistema::trataAcidentes() {
		bool semExcecoes = true, semAcidentes = true;
		bool semRecursos = false;
		string incF = "Incendio Florestal";
		for (size_t i = 0; i < acidentes.size(); i++) {
			if (!acidentes.at(i)->getTratado()) {
				semAcidentes = false;
				if (acidentes.at(i)->getTipoAcidente() == incF) {
					try {
						PostoSocorro *p = verificaPostoMaisPerto(*(acidentes.at(i)), false);
						p->insereAcidente(acidentes.at(i));
						acidentes.at(i)->setTratado();
					}
					catch (...) {
						semExcecoes = false;
					}
				}
				else {
					try {
						PostoSocorro *p = verificaPostoMaisPerto(*(acidentes.at(i)), false);
						p->insereAcidente(acidentes.at(i));
						PostoSocorro *p2 = verificaPostoMaisPerto(*(acidentes.at(i)), true);
						p2->insereAcidente(acidentes.at(i));
						acidentes.at(i)->setTratado();
					}
					catch (...) {
						semExcecoes = false;
					}
				}
			}
		}
		if (semAcidentes)
		cout << "Nao existe nenhum acidente por tratar." << endl;
		else if (semExcecoes)
		cout << "Todos os acidentes foram tratados com sucesso." << endl;
		else
		cout << "Nao existem recursos suficientes para tratar todos os acidentes." << endl
		<< "Pode verificar que acidentes não foram tratados na opcao E do menu." << endl << endl;
}

void Sistema::mostraPostosAtribuidosAcidentes() {
	for (size_t i = 0; i < acidentes.size(); i++) {
		int n = 1;
		cout << acidentes.at(i)->getTipoAcidente() << endl << "Local: "
				<< acidentes.at(i)->getLocal().getDistrito() << ", "
				<< acidentes.at(i)->getLocal().getCodigoPostal() << endl
				<< "Postos de Socorro atribuidos: " << endl;
		for (size_t j = 0; j < postos.size(); j++) {
			vector<Acidente *> acid = postos.at(j)->getAcidentes();
			for (size_t k = 0; k < acid.size(); k++) {
				if (acid.at(k)->getTipoAcidente() == acidentes.at(i)->getTipoAcidente() &&
						acid.at(k)->getData() == acidentes.at(i)->getData() &&
						acid.at(k)->getLocal() == acidentes.at(i)->getLocal()) {
					if (postos.at(j)->getTipoPosto() == "Policia"
							|| (postos.at(j)->getTipoPosto() == "Inem" && !postos.at(j)->getAmbulancia())) {
						cout << n << ") " << postos.at(j)->getTipoPosto() << " - "
								<< postos.at(j)->getLocal().getDistrito() << ", "
								<< postos.at(j)->getLocal().getCodigoPostal()
								<< "; Socorristas disponibilizados: "
								<< acidentes.at(i)->getNumPolicia() << endl;
						n++;
					}
					else {
						cout << n << ") " << postos.at(j)->getTipoPosto() << " - "
								<< postos.at(j)->getLocal().getDistrito() << ", "
								<< postos.at(j)->getLocal().getCodigoPostal()
								<< "; Socorristas disponibilizados: "
								<< acidentes.at(i)->getNumSocorristas() << endl;
						n++;
					}
				}
			}
		}
		cout << endl << endl;
	}
}

void Sistema::mostraAcidenteData() {
	Data data;
	string d;
	int dia, mes, ano;
	char hifen;
	bool erro = true;

	while (erro) {
		try {
			cout << "\nInsira data (Formato: dd-mm-aaaa): ";
			cin >> d;
			istringstream ss;
			ss.str(d);
			ss >> dia >> hifen >> mes;
			if (hifen != '-')
				throw DataInvalida();
			ss >> hifen >> ano;
			if (hifen != '-')
				throw DataInvalida();
			erro = false;
			data.setDia(dia);
			data.setMes(mes);
			data.setAno(ano);
		} catch (...) {
			cerr << "\nData Invalida. Tente novamente." << endl;
		}
	}

	for (size_t i = 0; i < acidentes.size(); i++) {
		if (acidentes[i]->getData() == data) {
			cout << "\nTipo de acidente: ";
			acidentes[i]->visualizaInformacao();
			if (acidentes[i]->getTratado())
				cout << "Acidente tratado!\n";
			else
				cout << "Acidente não tratado!\n";
		}
	}
}

void Sistema::mostraAcidentesNaoTratados() {
	bool existe = false;
	for (size_t i = 0; i < acidentes.size(); i++) {
		if (!acidentes.at(i)->getTratado()){
			acidentes.at(i)->visualizaInformacao();
			cout << endl;
			existe = true;
		}
	}
	if (!existe)
		cout << "Todos os acidentes submetidos na base de dados foram tratados." << endl;
}

class ComparaPorData {
public:
	bool operator() (Acidente *a, Acidente *b) {return a->getData() < b->getData();}
};

void Sistema::ordenaAcidenteData() {
	char resposta;

	sort(acidentes.begin(), acidentes.end(), ComparaPorData());

	cout << "Ordenação feita com sucesso! Pretende visualizar os acidentes ordenados por data? (S/N)";
	cin >> resposta;
	while (resposta != 'S' && resposta != 'N') {
		cerr << "\nResposta invalida. Tente novamente: ";
		cin >> resposta;
	}
	if (resposta == 'S')
		visualizaInformacaoAcidentes();
}

void Sistema::mostraAcidentesDistrito() {
	bool existe = false;
	string distrito;

	cin.ignore(1000, '\n');
	cout << "Qual o distrito?" << endl;
	getline(cin, distrito);

	for(size_t i = 0; i < acidentes.size(); i++) {
		if(acidentes.at(i)->getLocal().getDistrito() == distrito) {
			existe = true;
			cout << "Tipo de acidente: ";
			acidentes[i]->visualizaInformacao();
			if (acidentes[i]->getTratado())
				cout << "Acidente tratado!\n";
			else
				cout << "Acidente não tratado!\n";
			cout << endl;
		}
	}

	if (!existe)
		cout << "Nao ocorreram acidentes no distrito pedido." << endl;
}

void Sistema::mostraHistoricoPosto() {
	bool erro = true;
	int cp1, cp2;
	string tipoPosto, codigoPostal;
	Local l;
	char hifen;

	cout << "Tipo de posto (Bombeiros/Policia/Inem): ";
	while (erro) {
		cin >> tipoPosto;
		if (tipoPosto != "Bombeiros" && tipoPosto != "Policia" && tipoPosto != "Inem") {
			erro = true;
			cin.ignore(100,'\n');
			cout << "Tipo de posto invalido! Tente novamente: ";
		}
		erro = false;
	}
	cin.ignore(1000, '\n');

	erro = true;
	cout << "\nCodigo postal do local (Formato: nnnn-nnn): ";
	while (erro) {
		try {
			cin >> codigoPostal;
			istringstream ss;
			ss.str(codigoPostal);
			ss >> cp1 >> hifen >> cp2;
			if (hifen != '-')
				throw CodigoPostalInvalido();
			l.setCodigoPostal1(cp1);
			l.setCodigoPostal2(cp2);
			erro = false;
		} catch (CodigoPostalInvalido &c) {
			erro = true;
			cout << "\nCodigo postal invalido! Tente novamente: ";
		}
	}

	size_t i = 0;
	for (; i < postos.size(); i++) {
		if((postos.at(i)->getTipoPosto() == tipoPosto) &&
				(postos.at(i)->getLocal().getCodigoPostal() == codigoPostal)) {
			vector<Acidente *> acid(postos.at(i)->getAcidentes());
			if (acid.size() == 0)
				cout << "Este posto ainda nao tratou de qualquer acidente." << endl;
			for (size_t j = 0; j < acid.size(); j++) {
				cout << j+1 << ") " << acid.at(j)->getTipoAcidente() << endl
					<< "Data: " << acid.at(j)->getData() << " ; Local: "
					<< acid.at(j)->getLocal().getDistrito() << ", "
					<< acid.at(j)->getLocal().getCodigoPostal() << endl << endl;
			}
			break;
		}
	}
	if (i == postos.size())
		cout << "Nao existe o posto do tipo: " << tipoPosto << " e de código postal: " << codigoPostal
			<< endl << endl;
}
