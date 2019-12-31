/*
 * acidentes.cpp
 *
 *  Created on: 16/10/2017
 *      Author: Asus
 */

#include <iostream>
#include <fstream>
#include <string>
#include "acidentes.h"
#include "data.h"

using namespace std;

//Classe Acidente

Acidente::Acidente(Local &local, Data &data) {
	this->local = local;
	this->data = data;
	tratado = false;
}

Local Acidente::getLocal() const {
	return local;
}

Data Acidente::getData() const {
	return data;
}

bool Acidente::getTratado() const {
	return tratado;
}

void Acidente::setTratado() {
	tratado = true;
}

void Acidente::imprimeInformacao(ostream &out) const {
	out << getTipoAcidente() << "\nLocal: " << local.getDistrito() << endl
			<< "Codigo Postal: " << local.getCodigoPostal() << endl << "Data: "
			<< data << endl;
}

void Acidente::visualizaInformacao() const {
	cout << "Local: " << local.getDistrito() << endl << "Codigo Postal: "
			<< local.getCodigoPostal() << endl << "Data: " << data << endl;
}

bool Acidente::operator<(const Acidente &ac2) {
	if (data < ac2.getData())
		return true;
	else
		return false;
}

//Classe Incendio

Incendio::Incendio(Local &local, Data &data) :
		Acidente(local, data) {
	numBombeiros = 0;
	numCarrosBombeiros = 0;
}

int Incendio::getNumSocorristas() const {
	return numBombeiros;
}

int Incendio::getNumCarrosBombeiros() const {
	return numCarrosBombeiros;
}

//Classe Incendio Florestal

IncendioFlorestal::IncendioFlorestal(Local &local, Data &data, float area) :
		Incendio(local, data) {
	this->area = area;
	numBombeiros = (int) area / 10 + 1;
	if (numBombeiros % 5 == 0)
		numCarrosBombeiros = numBombeiros / 5;
	else
		numCarrosBombeiros = numBombeiros / 5 + 1;
}

float IncendioFlorestal::getArea() const {
	return area;
}

void IncendioFlorestal::setArea(float area) {
	this->area = area;
}

string IncendioFlorestal::getTipoAcidente() const {
	string s = "Incendio Florestal";
	return s;
}

void IncendioFlorestal::imprimeInformacao(ostream &out) const {
	Acidente::imprimeInformacao(out);
	out << "Area: " << area << endl;
}

void IncendioFlorestal::visualizaInformacao() const {
	cout << "Incendio Florestal" << endl;
	Acidente::visualizaInformacao();
	cout << "Area: " << area << endl;
}

int IncendioFlorestal::getNumPolicia() const {
	return 0;
}

//Class Incendio Domestico

IncendioDomestico::IncendioDomestico(Local &local, Data &data, bool apartamento) :
		Incendio(local, data) {
	this->apartamento = apartamento;
	if (apartamento)
		numBombeiros = 4;
	else
		numBombeiros = 8;
	if (numBombeiros % 5 == 0)
		numCarrosBombeiros = numBombeiros / 5;
	else
		numCarrosBombeiros = numBombeiros / 5 + 1;
}

bool IncendioDomestico::getApartamento() const {
	return apartamento;
}

void IncendioDomestico::setApartamento() {
	if (apartamento)
		apartamento = false;
	else
		apartamento = true;
}

string IncendioDomestico::getTipoAcidente() const {
	string s = "Incendio Domestico";
	return s;
}

void IncendioDomestico::imprimeInformacao(ostream &out) const {
	Acidente::imprimeInformacao(out);
	if (apartamento)
		out << "Apartamento" << endl;
	else
		out << "Moradia" << endl;
}

void IncendioDomestico::visualizaInformacao() const {
	cout << "Incendio Domestico" << endl;
	Acidente::visualizaInformacao();
	if (apartamento)
		cout << "Apartamento" << endl;
	else
		cout << "Moradia" << endl;
}

int IncendioDomestico::getNumPolicia() const {
	if (apartamento)
		return 2;
	else
		return 4;
}

//Class Assalto

Assalto::Assalto(Local &local, Data &data, int numFer, bool casaCom) :
		Acidente(local, data) {
	numFeridos = numFer;
	casaComercial = casaCom;
}

bool Assalto::getCasaComercial() const {
	return casaComercial;
}

int Assalto::getNumFeridos() const {
	return numFeridos;
}

string Assalto::getTipoAcidente() const {
	string s = "Assalto";
	return s;
}

void Assalto::setNumFeridos(int n) {
	numFeridos = n;
}

void Assalto::setCasaComercial() {
	if (casaComercial)
		casaComercial = false;
	else
		casaComercial = true;
}

void Assalto::imprimeInformacao(ostream &out) const {
	Acidente::imprimeInformacao(out);
	out << "Numero de Feridos: " << numFeridos << endl;
	if (casaComercial)
		out << "Casa Comercial" << endl;
	else
		out << "Casa Particular" << endl;
}

void Assalto::visualizaInformacao() const {
	cout << "Assalto" << endl;
	Acidente::visualizaInformacao();
	cout << "Numero de Feridos: " << numFeridos << endl;
	if (casaComercial)
		cout << "Casa Comercial" << endl;
	else
		cout << "Casa Particular" << endl;
}

int Assalto::getNumPolicia() const {
	if (casaComercial)
		return 4;
	return 2;
}

int Assalto::getNumSocorristas() const {
	return numFeridos;
}

//Class Acidente de Viacao

AcidenteViacao::AcidenteViacao(Local &local, Data &data, int numFer,
		int numVeic, bool estrada) :
		Acidente(local, data) {
	numFeridos = numFer;
	numVeiculos = numVeic;
	estradaNacional = estrada;
}

int AcidenteViacao::getNumFeridos() const {
	return numFeridos;
}

int AcidenteViacao::getNumVeiculos() const {
	return numVeiculos;
}

int AcidenteViacao::getNumSocorristas() const {
	return numVeiculos * 2;
}

string AcidenteViacao::getTipoAcidente() const {
	string s = "Acidente de Viacao";
	return s;
}

int AcidenteViacao::getNumPolicia() const {
	return 4;
}

void AcidenteViacao::setNumFeridos(int n) {
	numFeridos = n;
}

void AcidenteViacao::setNumVeiculos(int n) {
	numVeiculos = n;
}

void AcidenteViacao::setEstradaNacional() {
	if (estradaNacional)
		estradaNacional = false;
	else
		estradaNacional = true;
}

bool AcidenteViacao::getEstradaNacional() const {
	return estradaNacional;
}

void AcidenteViacao::imprimeInformacao(ostream &out) const {
	Acidente::imprimeInformacao(out);
	out << "Numero de Feridos: " << numFeridos << endl
			<< "Numero de Veiculos Envolvidos: " << numVeiculos << endl;
	if (estradaNacional)
		out << "Estrada Nacional" << endl;
	else
		out << "Autoestrada" << endl;
}

void AcidenteViacao::visualizaInformacao() const {
	cout << "Acidente de Viacao" << endl;
	Acidente::visualizaInformacao();
	cout << "Numero de Feridos: " << numFeridos << endl
			<< "Numero de Veiculos Envolvidos: " << numVeiculos << endl;
	if (estradaNacional)
		cout << "Estrada Nacional" << endl;
	else
		cout << "Autoestrada" << endl;
}
