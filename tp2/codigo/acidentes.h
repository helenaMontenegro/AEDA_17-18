/*
 * acidentes.h
 *
 *  Created on: 16/10/2017
 *      Author: Asus
 */

#ifndef ACIDENTES_H_
#define ACIDENTES_H_

#include <iostream>
#include <string>
#include <vector>
#include "local.h"
#include "data.h"

/**
 * \brief Tem como variaveis o "local" onde ocorreu, pertencente a classe Local; a "data" na qual ocorreu,
 * pertencente a classe Data; uma variavel denominada "tratado" do tipo bool, que caso seja true, significa
 * que o acidente foi tratado, ou seja, tem socorristas.
 */

class Acidente {
	Local local;
	Data data;
	bool tratado;
public:
	 /**
	  * \brief Construtor da classe Acidente.
	  */
	Acidente(Local &local, Data &data);
	/**
	 * \brief Retorna local do acidente.
	 * \return Objeto da classe Local, atributo da classe Acidente.
	 */
	Local getLocal() const;
	/**
	 * \brief Retorna data do acidente.
	 * \return Objeto da classe Data, atributo da classe Acidente.
	 */
	Data getData() const;
	/**
	 * \brief Retorna valor do atributo tratado.
	 * \return True se o acidente foi tratado.
	 */
	bool getTratado() const;
	/**
	 * \brief Altera variavel booleana tratado para true quando o acidente estiver tratado.
	 */
	void setTratado();
	/**
	 * \brief Imprime informacao sobre o acidente.
	 * \param out objecto de acesso a abertura do ficheiro "acidentes.txt" para escrita
	 */
	virtual void imprimeInformacao(std::ostream &out) const;
	/**
	 * \brief Visualiza informacao sobre o acidente.
	 */
	virtual void visualizaInformacao() const;
	/**
	 * \brief Retorna tipo de acidente - Acidente Florestal, Acidente Domestico, Assalto ou Acidente de Viacao.
	 * \return Subclasse a que pertence o objeto.
	 */
	virtual std::string getTipoAcidente() const {}
	/**
	 * \brief Retorna numero de socorristas que sao necessarios ao acidente.
	 */
	virtual int getNumSocorristas() const {}
	/**
	 * \return Retorna numero de autotanques que sao necessarios ao acidente.
	 */
	virtual int getNumCarrosBombeiros() const {}
	/**
	 * \brief Retorna numero de agentes de Policia ou socorristas de Inem de postos que utilizem carro
	 * ou mota que sao necessarios ao acidente.
	 */
	virtual int getNumPolicia() const {}
	/**
	 * \brief Overload do operador de comparacao < para a classe Acidente.
	 * Um acidente e menor que outro se ocorreu antes do mesmo.
	 * \param ac2 objeto da classe Acidente
	 * \return True se ac2 for maior que o outro acidente.
	 */
	bool operator<(const Acidente &ac2);
	/**
	 * Altera atributo area da classe derivada IncendioFlorestal.
	 * \param area area alcancada pelo incendio
	 */
	virtual void setArea(float area) {}
	/**
	 * \brief Retorna valor do atributo apartamento da classe derivada IncendioDomestico.
	 * \return True se o acidente aconteceu num apartamento.
	 */
	virtual bool getApartamento() const {}
	/**
	 * \brief Troca o valor da variavel booleana apartamento.
	 */
	virtual void setApartamento() {}
	/**
	 * \brief Altera o numero de feridos de um acidente.
	 */
	virtual void setNumFeridos(int n) {}
	/**
	 * \brief Returna valor booleano da variavel casaComercial da classe Acidente.
	 * \return True se um assalto ocorreu numa casa comercial.
	 */
	virtual bool getCasaComercial() const {}
	/**
	 * \brief Altera valor de argumento de assalto: casaComercial.
	 */
	virtual void setCasaComercial() {}
	/**
	 * \brief Altera o numero de veiculos de um acidente de viacao.
	 */
	virtual void setNumVeiculos(int n) {}
	/**
	 * \brief Altera o valor de estradaNacional de um objeto da classe AcidenteViacao.
	 */
	virtual void setEstradaNacional() {}
	/**
	 * \brief Retorna valor do atributo estradaNacional de um objeto da classe AcidenteViacao.
	 * \return True se o acidente de viacao ocorreu numa estrada nacional.
	 */
	virtual bool getEstradaNacional() const {}
	/**
	 * \brief Retorna o numero de veiculos envolvidos no acidente de viacao.
	 * \return Atributo numVeiculos da classe.
	 */
	virtual int getNumVeiculos() const {}
};

/**
 * \brief Derivada da classe Acidente, tem como variaveis o numero de bombeiros
 * e o numero de carros de bombeiro necessarios para apagar o incendio.
 */

class Incendio: public Acidente {
protected:
	int numBombeiros;
	int numCarrosBombeiros;
public:
	/**
	 * \brief Construtor da class Incendio.
	 */
	Incendio(Local &local, Data &data);
	/**
	 * \brief Retorna o numero de bombeiros necessarios para atender ao incendio.
	 * \return Atributo numBombeiros da classe.
	 */
	int getNumSocorristas() const;
	/**
	 * \brief Retorna o numero de carros de bombeiros necessarios para atender ao incendio.
	 * \return Atributo numCarrosBombeiros da classe.
	 */
	int getNumCarrosBombeiros() const;
	/**
	 * \brief Imprime informacao sobre o incendio.
	 * \param out objecto de acesso a abertura do ficheiro "acidentes.txt" para escrita
	 */
	virtual void imprimeInformacao(std::ostream &out) const = 0;
	/**
	 * \brief Visualiza informacao sobre o incendio.
	 */
	virtual void visualizaInformacao() const = 0;
	/**
	 * \brief Retorna a string correspondente a subclasse a que pertence o objeto em questao.
	 */
	virtual std::string getTipoAcidente() const {
	}
	/**
	 * \brief Retorna o numero de agentes de Policia ou socorristas de Inem de postos que utilizem carro
	 * ou mota que sao necessarios ao acidente.
	 */
	virtual int getNumPolicia() const {
	}
	/**
	 * \brief Altera area alcancada pelo incendio.
	 */
	virtual void setArea(float area) {
	}
	/**
	 * \brief Retorna o valor da variavel apartamento.
	 * \return True se o incendio ocorreu num apartamento e false se ocorreu numa moradia.
	 */
	virtual bool getApartamento() const {
	}
	/**
	 * \brief Altera o valor do atributo apartamento.
	 */
	virtual void setApartamento() {
	}
};

/**
 * \brief Derivada da classe Incendio. Tem como variavel a area que o incendio alcancou.
 */

class IncendioFlorestal: public Incendio {
	float area;
public:
	/**
	 * \brief Construtor da class IncendioFlorestal.
	 *
	 *
	 * Necessario 1 bombeiro por 10 metros quadrados de area.
	 *
	 * Cada autotanque tem capacidade para 5 bombeiros.
	 * \param local objeto da classe Local
	 * \param data objeto da classe Data
	 * \param area area alcancada pelo incendio
	 */
	IncendioFlorestal(Local &local, Data &data, float area);
	/**
	 * \brief Retorna a area alcancada pelo incendio.
	 * \return Atributo area da classe.
	 */
	float getArea() const;
	/**
	 * \brief Altera area alcancada pelo incendio.
	 */
	void setArea(float area);
	/**
	 * \brief Retorna a string correspondente a classe a que pertence o objeto em questao.
	 */
	std::string getTipoAcidente() const;
	/**
	 * \brief Imprime informacaoo sobre o incendio florestal.
	 * \param out objecto de acesso a abertura do ficheiro "acidentes.txt" para escrita
	 */
	void imprimeInformacao(std::ostream &out) const;
	/**
	 * \brief Visualizaa informacao sobre o incendio florestal.
	 */
	void visualizaInformacao() const;
	/**
	 * \brief Retorna o numero de agentes de Policia ou socorristas de Inem de postos que utilizem carro
	 * ou mota que são necessários ao acidente.
	 * \return Zero.
	 */
	int getNumPolicia() const;
};

/**
 * \brief Derivada da classe Incendio, tem uma variável booleana que indica se o incendio aconteceu num
 * apartamento (true) ou numa moradia (false).
 */

class IncendioDomestico: public Incendio {
	bool apartamento;
public:
	/**
	 * \brief Construtor da class IncendioDomestico.
	 *
	 * Um incendio num apartamento necessita de 4 bombeiros.
	 *
	 * Um incendio numa moradia precisa de 8 bombeiros.
	 *
	 * Cada auto-tanque tem capacidade para 5 bombeiros.
	 * \param local objeto da classe Local
	 * \param data objeto da classe Data
	 * \param apartamento true se incendio ocorreu num apartamento e false se ocorreu numa moradia
	 */
	IncendioDomestico(Local &local, Data &data, bool apartamento);
	/**
	 * \brief Retorna uma string que corresponde a classe a que pertence o objeto em questao.
	 */
	std::string getTipoAcidente() const;
	/**
	 * \brief Retorna o valor da variavel apartamento.
	 * \return True se incendio ocorreu num apartamento e false se ocorreu numa moradia.
	 */
	bool getApartamento() const;
	/**
	 * \brief Altera o valor da variavel apartamento.
	 */
	void setApartamento();
	/**
	 * \brief Imprime informacao sobre o incendio domestico.
	 * \param out objecto de acesso a abertura do ficheiro "acidentes.txt" para escrita
	 */
	void imprimeInformacao(std::ostream &out) const;
	/**
	 * \brief Visualiza informacao sobre o incendio domestico.
	 */
	void visualizaInformacao() const;
	/**
	 *\brief Retorna o numero de agentes de Policia ou socorristas de Inem de postos que utilizem carro
	 * ou mota que sao necessarios ao acidente.
	 * \return 2 se o incendio tiver ocorrido num apartamento e 4 se tiver ocorrido numa moradia.
	 */
	int getNumPolicia() const;
};

/**
 * \brief Derivada da classe Acidente, tem como variaveis o numero de feridos decorrentes do acidente
 * e uma variavel do tipo bool que indica se o assalto ocorreu numa casa comercial (true) ou
 * numa casa particular (false).
 */

class Assalto: public Acidente {
	int numFeridos;
	bool casaComercial;
public:
	/**
	 * \brief Construtor da classe Assalto.
	 * \param local objeto da classe Local
	 * \param data objeto da classe Data
	 * \param numFer numero de feridos no assalto
	 * \param casaCom valor booleano true se assalto ocorreu numa casa comercial e false se for numa casa particular
	 */
	Assalto(Local &local, Data &data, int numFer, bool casaCom);
	/**
	 * \brief Retorna valor de atributo casaComercial.
	 * \return True se assalto ocorreu numa casa comercial e false se ocorreu numa casa particular.
	 */
	bool getCasaComercial() const;
	/**
	 * \brief Retorna numero de feridos durante o assalto.
	 *
	 * O numero de feridos sera igual ao numero de socorristas necessarios para atender ao acidente.
	 * \return Atributo numFeridos da classe.
	 */
	int getNumFeridos() const;
	/**
	 * \brief Retorna numero de agentes de Policia ou socorristas da Inem que utilize moto ou carro,
	 * necessarios para o acidente.
	 * \return 2 se assalto ocorrer numa casa particular e 4 se for uma casa comercial.
	 */
	int getNumPolicia() const;
	/**
	 * \brief Retorna o numero de socorristas necessarios.
	 *
	 * Vai ser igual ao numero de feridos.
	 */
	int getNumSocorristas() const;
	/**
	 * \brief Retorna uma string que corresponde a classe a que pertence o objeto em questao.
	 */
	std::string getTipoAcidente() const;
	/**
	 * \brief Imprime informacao sobre o assalto.
	 * \param out objecto de acesso a abertura do ficheiro "acidentes.txt" para escrita
	 */
	void imprimeInformacao(std::ostream &out) const;
	/**
	 * \brief Visualiza informacao sobre o assalto.
	 */
	void visualizaInformacao() const;
	/**
	 * \brief Retorna o numero de autotanques necessarios.
	 * \return Zero.
	 */
	int getNumCarrosBombeiros() const {
		return 0;
	}
	/**
	 * \brief Altera o numero de feridos de um acidente.
	 */
	void setNumFeridos(int n);
	/**
	 * \brief Altera valor de argumento de assalto: casaComercial.
	 */
	void setCasaComercial();
};

/**
 * \brief Derivada da Classe Acidente, tem como atributos o numero de feridos e de veiculos envolvidos
 * no acidente e uma variavel do tipo booleano que indica se o acidente ocorreu numa estrada nacional.
 */

class AcidenteViacao: public Acidente {
	int numFeridos;
	int numVeiculos;
	bool estradaNacional;
public:
	/**
	 * \brief Construtor da classe sobre acidentes de viacao.
	 * \param local objeto da classe Local
	 * \param data objeto da classe Data
	 * \param numFer numero de feridos no acidente
	 * \param numVeic numero de veiculos envolvidos no acidente
	 * \param estrada valor booleano indica se acidente ocorreu numa estrada nacional
	 */
	AcidenteViacao(Local &local, Data &data, int numFer, int numVeic,
			bool estrada);
	/**
	 * \brief Retorna o numero de feridos graves no acidente.
	 *
	 * O numero de feridos e igual ao numero de
	 * socorristas necessarios para atender ao acidente.
	 * \return Atributo numFeridos da classe.
	 */
	int getNumFeridos() const;
	/**
	 * \brief Retorna o numero de veiculos envolvidos no acidente.
	 * \return Atributo numVeiculos da classe.
	 */
	int getNumVeiculos() const;
	/**
	 * \brief Retorna o numero de socorristas necessarios.
	 *
	 * Este numero de socorristas nao tem em conta a gravidade dos ferimentos. Depende unicamente
	 * do numero de veiculos envolvidos no acidente.
	 */
	int getNumSocorristas() const;
	/**
	 * \brief Retorna string que corresponde a classe a que pertence o objeto em questao.
	 */
	std::string getTipoAcidente() const;
	/**
	 * \brief Imprime informacao sobre o acidente de viacao.
	 * \param out objecto de acesso a abertura do ficheiro "acidentes.txt" para escrita
	 */
	void imprimeInformacao(std::ostream &out) const;
	/**
	 * \brief Visualiza informacao sobre o acidente de viacao.
	 */
	void visualizaInformacao() const;
	/**
	 * \brief Retorna o numero de agentes da Policia ou socorristas do Inem que utilizem carros ou motas,
	 * para controlar o transito e ajudar no socorro das pessoas envolvidas no acidente.
	 * \return 4
	 */
	int getNumPolicia() const;
	/**
	 * \brief Retorna o numero de autotanques necessarios.
	 * \return Zero.
	 */
	int getNumCarrosBombeiros() const {
		return 0;
	}
	/**
	 * \brief Altera o numero de feridos de um acidente.
	 * \param n numero de feridos envolvidos no acidente
	 */
	void setNumFeridos(int n);
	/**
	 * \brief Altera o numero de veiculos de um acidente.
	 * \param n numero de veiculos envolvidos no acidente
	 */
	void setNumVeiculos(int n);
	/**
	 * \brief Altera o valor de estradaNacional.
	 *
	 * Se atributo estradaNacional for true, altera-se para false, e, se for false, fica true.
	 */
	void setEstradaNacional();
	/**
	 * \brief Retorna o valor de estradaNacional.
	 * \return True se o acidente ocorrer numa estrada nacional.
	 */
	bool getEstradaNacional() const;
};

#endif /* ACIDENTES_H_ */
