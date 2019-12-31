/*
 * local.cpp
 *
 *  Created on: 28/10/2017
 *      Author: Asus
 */

#include "local.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Local::Local(string dist, string cPostal) {
	distrito  = dist;
	istringstream ss;
	char hifen;
	ss.str(cPostal);
	ss >> codigoPostal1 >> hifen >> codigoPostal2;
}

Local::Local(string dist) {
	distrito = dist;
}

string Local::getDistrito() const {
	return distrito;
}

string Local::getCodigoPostal() const {
	stringstream ss;
	ss << codigoPostal1 << "-" << codigoPostal2;
	return ss.str();
}

int Local::getCodigoPostal1() const {
	return codigoPostal1;
}

int Local::getCodigoPostal2() const {
	return codigoPostal2;
}

void Local::setCodigoPostal1(int cp1) {
	if (cp1 < 100 || cp1 > 9999)
		throw CodigoPostalInvalido();
	codigoPostal1 = cp1;
}

void Local::setCodigoPostal2(int cp2) {
	if (cp2 < 100 || cp2 > 999)
		throw CodigoPostalInvalido();
	codigoPostal2 = cp2;
}

bool Local::operator== (const Local &l1) {
	if (distrito == l1.getDistrito() && getCodigoPostal() == l1.getCodigoPostal())
		return true;
	return false;
}
