/*
 * local.h
 *
 *  Created on: 28/10/2017
 *      Author: Asus
 */

#ifndef LOCAL_H_
#define LOCAL_H_

#include <iostream>
#include <string>
/**
 * Classe Local
 * Constitu�da por um distrito e um c�digo postal.
 * CodigoPostal1 diz respeito aos primeiros 4 n�meros de um c�digo postal.
 * CodigoPostal2 diz respeito aos 3 �ltimos n�meros de um c�digo postal.
 */
class Local {
	std::string distrito;
	int codigoPostal1, codigoPostal2;
public:
	/**
	 * Construtor da classe Local sem argumentos
	 */
	Local() {}
	/**
	 * Construtor da classe Local utilizado na fun��o pertencente � classe Sistema: adicionaAcidente().
	 */
	Local(std::string dist);
	/**
	 * Construtor da classe Local
	 */
	Local(std::string dist, std::string cPostal);
	/**
	 * Fun��o que retorna o distrito do local.
	 */
	std::string getDistrito() const;
	/**
	 * Fun��o que retorna o c�digo postal do local.
	 */
	std::string getCodigoPostal() const;
	/**
	 * Fun��o que retorna a primeira parte de um c�digo postal.
	 */
	int getCodigoPostal1() const;
	/**
	 * Fun��o que retorna a segunda parte de um c�digo postal.
	 */
	int getCodigoPostal2() const;
	/**
	 * Fun��o que permite alterar a primeira parte do c�digo postal de um local.
	 */
	void setCodigoPostal1(int cp1);
	/**
	 * Fun��o que permite alterar a �ltima parte do c�digo postal de um local.
	 */
	void setCodigoPostal2(int cp2);
	/**
	 * Overload do operador == para a classe Local.
	 */
	bool operator== (const Local &l1);
};

/**
 * Exce��o que reconhece c�digos postais inv�lidos.
 */

class CodigoPostalInvalido {
public:
	CodigoPostalInvalido() {};
};

#endif /* LOCAL_H_ */
