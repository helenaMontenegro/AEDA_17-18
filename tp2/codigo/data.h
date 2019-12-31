/*
 * data.h
 *
 *  Created on: 16/10/2017
 *      Author: Asus
 */

#ifndef DATA_H_
#define DATA_H_

#include <iostream>
#include <fstream>

/**
 * Class Data
 * Os seus objetos s�o constitu�dos por um dia, um m�s e um ano.
 */

class Data {
	int dia, mes, ano;
public:
	/**
	 * Construtor da classe Data sem argumentos
	 */
	Data() {}
	/**
	 * Construtor da class Data.
	 */
	Data(int dia, int mes, int ano);
	/**
	 * Fun��o que retorna o dia de uma data.
	 */
	int getDia() const;
	/**
	 * Fun��o que retorna o m�s de uma data.
	 */
	int getMes() const;
	/**
	 * Fun��o que retorna o ano de uma data.
	 */
	int getAno() const;
	/**
	 * Fun��o que serve para alterar o dia de uma data.
	 */
	void setDia(int dia);
	/**
	 * Fun��o que serve para alterar o mes de uma data.
	 */
	void setMes(int mes);
	/**
	 * Fun��o que serve para alterar o ano de uma data.
	 */
	void setAno(int ano);
	/**
	 * Overload do operador de output para a class Data.
	 */

	friend std::ostream& operator<<(std::ostream &out, const Data d);
	/**
	 * Overload do operador de input para a class Data.
	 */
	friend std::istream& operator>>(std::istream &in, const Data d);
	/**
	 * Overload do operador de compara��o < para a class Data.
	 * Uma data d1 � menor que uma data d2 se for anterior a d2.
	 */
	bool operator<(const Data &d1);
	/**
	 * Overload do operador de compara��o == para a class Data.
	 * Uma data d1 � igual a outra data d2 se todos os seus elementos forem iguais.
	 */
	bool operator==(const Data &d1) const;
	/**
	 * Overload do operador aritm�tico - para a class Data.
	 * Unidade do resultado s�o anos.
	 */
	double operator-(const Data &d1);
};

/**
 * Exce��o que reconhece um dia inv�lido. (dia < 1 ou dia > 31)
 */

class DiaInvalido {
	int dia;
public:
	DiaInvalido(int dia) {
		this->dia = dia;
	}
};

/**
 * Exce��o que reconhece um m�s inv�lido. (m�s < 1 ou m�s > 12)
 */

class MesInvalido {
	int mes;
public:
	MesInvalido(int mes) {
		this->mes = mes;
	}
};

/**
 * Exce��o que reconhece um ano inv�lido. (ano < 0);
 */

class AnoInvalido {
	int ano;
public:
	AnoInvalido(int ano) {
		this->ano = ano;
	}
};

/**
 * Exce��o lan�ada quando data n�o est� no formato: dd-mm-aaa. Nomeadamente, quando em vez de hifens tem
 * qualquer outro char.
 */

class DataInvalida {
public:
	DataInvalida() {}
};

#endif /* DATA_H_ */
