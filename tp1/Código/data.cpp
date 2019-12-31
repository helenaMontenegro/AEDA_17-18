/*
 * data.cpp
 *
 *  Created on: 23/10/2017
 *      Author: Asus
 */

#include <iostream>
#include "data.h"
using namespace std;

Data::Data(int dia = 1, int mes = 1, int ano = 1) {
	this->ano = ano;
	this->mes = mes;
	this->dia = dia;
}

int Data::getDia() const {
	return dia;
}

int Data::getMes() const {
	return mes;
}

int Data::getAno() const {
	return ano;
}

void Data::setDia(int dia) {
	if (dia < 1 || dia > 31)
		throw DiaInvalido(this->dia);
	this->dia = dia;
}

void Data::setMes(int mes) {
	if (mes < 1 || mes > 12)
		throw MesInvalido(this->mes);
	this->mes = mes;
}

void Data::setAno(int ano) {
	if (ano < 1)
		throw AnoInvalido(this->ano);
	this->ano = ano;
}

ostream& operator<<(ostream &out, const Data d) {
	out << d.getDia() << "-" << d.getMes() << "-" << d.getAno();
	return out;
}

bool Data::operator<(const Data &d1) {
	if (ano < d1.getAno())
		return true;
	else if (ano > d1.getAno())
		return false;
	else if (mes < d1.getMes())
		return true;
	else if (mes > d1.getMes())
		return false;
	else if (dia < d1.getDia())
		return true;
	else
		return false;
}

bool Data::operator==(const Data &d1) {
	if ((ano == d1.getAno()) && (mes == d1.getMes()) && (dia == d1.getDia()))
		return true;
	return false;
}
