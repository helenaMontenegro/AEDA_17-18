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
 * Os seus objetos são constituídos por um dia, um mês e um ano.
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
	 * Função que retorna o dia de uma data.
	 */
	int getDia() const;
	/**
	 * Função que retorna o mês de uma data.
	 */
	int getMes() const;
	/**
	 * Função que retorna o ano de uma data.
	 */
	int getAno() const;
	/**
	 * Função que serve para alterar o dia de uma data.
	 */
	void setDia(int dia);
	/**
	 * Função que serve para alterar o mes de uma data.
	 */
	void setMes(int mes);
	/**
	 * Função que serve para alterar o ano de uma data.
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
	 * Overload do operador de comparação < para a class Data.
	 * Uma data d1 é menor que uma data d2 se for anterior a d2.
	 */
	bool operator<(const Data &d1);
	/**
	 * Overload do operador de comparação == para a class Data.
	 * Uma data d1 é igual a outra data d2 se todos os seus elementos forem iguais.
	 */
	bool operator==(const Data &d1) const;
	/**
	 * Overload do operador aritmético - para a class Data.
	 * Unidade do resultado são anos.
	 */
	double operator-(const Data &d1);
};

/**
 * Exceção que reconhece um dia inválido. (dia < 1 ou dia > 31)
 */

class DiaInvalido {
	int dia;
public:
	DiaInvalido(int dia) {
		this->dia = dia;
	}
};

/**
 * Exceção que reconhece um mês inválido. (mês < 1 ou mês > 12)
 */

class MesInvalido {
	int mes;
public:
	MesInvalido(int mes) {
		this->mes = mes;
	}
};

/**
 * Exceção que reconhece um ano inválido. (ano < 0);
 */

class AnoInvalido {
	int ano;
public:
	AnoInvalido(int ano) {
		this->ano = ano;
	}
};

/**
 * Exceção lançada quando data não está no formato: dd-mm-aaa. Nomeadamente, quando em vez de hifens tem
 * qualquer outro char.
 */

class DataInvalida {
public:
	DataInvalida() {}
};

#endif /* DATA_H_ */
