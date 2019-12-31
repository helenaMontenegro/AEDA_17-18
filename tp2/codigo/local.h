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
 * Constituída por um distrito e um código postal.
 * CodigoPostal1 diz respeito aos primeiros 4 números de um código postal.
 * CodigoPostal2 diz respeito aos 3 últimos números de um código postal.
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
	 * Construtor da classe Local utilizado na função pertencente à classe Sistema: adicionaAcidente().
	 */
	Local(std::string dist);
	/**
	 * Construtor da classe Local
	 */
	Local(std::string dist, std::string cPostal);
	/**
	 * Função que retorna o distrito do local.
	 */
	std::string getDistrito() const;
	/**
	 * Função que retorna o código postal do local.
	 */
	std::string getCodigoPostal() const;
	/**
	 * Função que retorna a primeira parte de um código postal.
	 */
	int getCodigoPostal1() const;
	/**
	 * Função que retorna a segunda parte de um código postal.
	 */
	int getCodigoPostal2() const;
	/**
	 * Função que permite alterar a primeira parte do código postal de um local.
	 */
	void setCodigoPostal1(int cp1);
	/**
	 * Função que permite alterar a última parte do código postal de um local.
	 */
	void setCodigoPostal2(int cp2);
	/**
	 * Overload do operador == para a classe Local.
	 */
	bool operator== (const Local &l1);
};

/**
 * Exceção que reconhece códigos postais inválidos.
 */

class CodigoPostalInvalido {
public:
	CodigoPostalInvalido() {};
};

#endif /* LOCAL_H_ */
