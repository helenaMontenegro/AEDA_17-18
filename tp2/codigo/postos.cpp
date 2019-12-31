/*
 * postos.cpp
 *
 *  Created on: 17 de Out de 2017
 *      Author: Mariana
 */

#include <vector>
#include "postos.h"
#include "local.h"

// Classe PostoSocorro

PostoSocorro::PostoSocorro(Local local, int numSoc, int numVeic) :
	local(local), numSocorristas(numSoc), numVeiculos(numVeic) {
}

Local PostoSocorro::getLocal() {
	return local;
}

int PostoSocorro::getNumSocorristas() {
	return numSocorristas;
}

int PostoSocorro::getNumVeiculos() {
	return numVeiculos;
}


vector<Acidente*> PostoSocorro::getAcidentes() const {
	return acidentes;
}

void PostoSocorro::setNumSocorristas(int numSoc) {
	numSocorristas += numSoc;
}

void PostoSocorro::setNumVeiculos(int numVeic) {
	numVeiculos += numVeic;
}

void PostoSocorro::insereAcidente(Acidente *a) {
	acidentes.push_back(a);
}

void PostoSocorro::imprimeInformacao(ostream &out) {
	out << getTipoPosto() << "\nLocal: " << local.getDistrito()
			<< "\nCodigo Postal: " << local.getCodigoPostal()
			<< "\nNumero de socorristas: " << numSocorristas
			<< "\nNumero de veiculos: " << numVeiculos;
}

void PostoSocorro::visualizaInformacao() {
	cout << "\nPosto de " << getTipoPosto() << "\nLocal: "
			<< local.getDistrito() << "\nCodigo Postal: "
			<< local.getCodigoPostal() << "\nNumero de socorristas: "
			<< numSocorristas;
}
// Classe Bombeiros

Bombeiros::Bombeiros(Local local, int numSoc, int numVeic, int numAmb,
		int numAutot) :
	PostoSocorro(local, numSoc, numVeic), numAmbulancias(numAmb),
			numAutotanques(numAutot) {
}

int Bombeiros::getNumAmbulancias() {
	return numAmbulancias;
}

int Bombeiros::getNumAutotanques() {
	return numAutotanques;
}

string Bombeiros::getTipoPosto() const {
	string s = "Bombeiros";
	return s;
}

void Bombeiros::imprimeInformacao(ostream &out) {
	PostoSocorro::imprimeInformacao(out);
	out << "\nNumero de ambulancias: " << numAmbulancias
			<< "\nNumero de autotanques: " << numAutotanques << endl;
}

void Bombeiros::visualizaInformacao() {
	PostoSocorro::visualizaInformacao();
	cout << "\nNumero de ambulancias: " << numAmbulancias
			<< "\nNumero de autotanques: " << numAutotanques << endl;
}

// Classe Policia

Policia::Policia(Local local, int numSoc, int numVeic, bool moto, bool carro) :
	PostoSocorro(local, numSoc, numVeic), moto(moto), carro(carro) {
}

string Policia::getTipoPosto() const {
	string s = "Policia";
	return s;
}

bool Policia::getMoto() const {
	return moto;
}

bool Policia::getCarro() const {
	return carro;
}

void Policia::imprimeInformacao(ostream &out) {
	PostoSocorro::imprimeInformacao(out);
	if (moto)
		out << "\nTipo de veiculo: Moto\n";
	else
		out << "\nTipo de veiculo: Carro\n";
}

void Policia::visualizaInformacao() {
	PostoSocorro::visualizaInformacao();
	if (moto)
		cout << "\nNumero de motos: " << getNumVeiculos() << endl << endl;
	else
		cout << "\nNumero de carros: " << getNumVeiculos() << endl << endl;
}

// Classe Inem

Inem::Inem(Local local, int numSoc, int numVeic, bool moto, bool carro,
		bool amb) :
	PostoSocorro(local, numSoc, numVeic), moto(moto), carro(carro),
			ambulancia(amb) {
}

string Inem::getTipoPosto() const {
	string s = "Inem";
	return s;
}

bool Inem::getMoto() const {
	return moto;
}

bool Inem::getCarro() const {
	return carro;
}

bool Inem::getAmbulancia() const {
	return ambulancia;
}

int Inem::getNumAmbulancias() {
	if (ambulancia)
		return getNumVeiculos();
	return 0;
}

void Inem::imprimeInformacao(ostream &out) {
	PostoSocorro::imprimeInformacao(out);
	if (moto)
		out << "\nTipo de veiculo: Moto\n";
	else if (carro)
		out << "\nTipo de veiculo: Carro\n";
	else
		out << "\nTipo de veiculo: Ambulancia\n";
}

void Inem::visualizaInformacao() {
	PostoSocorro::visualizaInformacao();
	if (moto)
		cout << "\nNumero de motos: " << getNumVeiculos() << endl << endl;
	else if (carro)
		cout << "\nNumero de carros: " << getNumVeiculos() << endl << endl;
	else
		cout << "\nNumero de ambulancias: " << getNumAmbulancias() << endl << endl;
}
