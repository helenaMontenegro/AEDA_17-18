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

bool Data::operator==(const Data &d1) const {
	if ((ano == d1.getAno()) && (mes == d1.getMes()) && (dia == d1.getDia()))
		return true;
	return false;
}

double Data::operator-(const Data &d1) {
	int ano_d, mes_d, ano1_d, mes1_d;
	bool bissexto = false, bissexto1 = false;

	if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
		bissexto = true;
		ano_d = ano * 366;
}
	else
		ano_d = ano * 365;

	if ((d1.ano % 4 == 0 && d1.ano % 100 != 0) || (d1.ano % 400 == 0)) {
		bissexto1 = true;
		ano1_d = d1.ano * 366;
	}
	else
		ano1_d = d1.ano * 365;

	if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
		mes_d = mes *31;
	else if (mes != 2)
		mes_d = mes * 30;
	else {
		if (bissexto)
			mes_d = mes* 29;
		else
			mes_d = mes*28;
	}

	if (d1.mes == 1 || d1.mes == 3 || d1.mes == 5 || d1.mes == 7 || d1.mes == 8 || d1.mes == 10 || d1.mes == 12)
		mes1_d = d1.mes *31;
	else if (d1.mes != 2)
		mes1_d = d1.mes * 30;
	else {
		if (bissexto)
			mes1_d = d1.mes* 29;
		else
			mes1_d = d1.mes*28;
	}

	ano_d += mes_d + ano;
	ano1_d += mes1_d + d1.dia;

	if (bissexto)
		ano_d /= 366;
	else
		ano_d /= 365;
	if (bissexto1)
		ano1_d /= 366;
	else
		ano1_d/=365;

	return ano_d - ano1_d;
}
