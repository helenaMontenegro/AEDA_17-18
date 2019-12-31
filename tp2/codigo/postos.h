/*
 * postos.h
 *
 *  Created on: 16/10/2017
 *      Author: Asus
 */

#ifndef POSTOS_H_
#define POSTOS_H_

#include <iostream>
#include <string>
#include <vector>
#include "acidentes.h"
#include "local.h"

using namespace std;

/**
 * \brief Tem como variaveis o local onde ocorreu, pertencente a classe Local, a data na qual ocorreu,
 * pertencente a classe Data, o numero de socorristas e o numero de veiculos disponiveis para assistencia
 * e um vetor de apontador para acidentes que o posto trata.
 */

class PostoSocorro {
	Local local;
	int numSocorristas;
	int numVeiculos;
	vector<Acidente *> acidentes;
public:
	/**
	 * \brief Default construtor da classe PostoSocorro.
	 */
	PostoSocorro() {}
	/**
	 * \brief Construtor da classe PostoSocorro.
	 * \param local objeto da classe Local
	 * \param numSoc numero de socorristas disponiveis
	 * \param numVeic numero de veiculos disponiveis
	 */
	PostoSocorro(Local local, int numSoc, int numVeic);
	/**
	 * \brief Retorna o local do posto de socorro.
	 * \return Objeto da classe Local, atributo da classe PostoSocorro.
	 */
	Local getLocal();
	/**
	 * \brief Retorna numero de socorristas disponiveis no posto de socorro.
	 * \return Atributo numSocorristas da classe.
	 */
	int getNumSocorristas();
	/**
	 * \brief Altera o numero de socorristas disponiveis no posto de socorro.
	 * \param numSoc numero de socorristas a adicionar aos presentes
	 */
	void setNumSocorristas(int numSoc);
	/**
	 * \brief Retorna o numero de veiculos disponiveis no posto de socorro.
	 * \return Atibuto numVeiculos da classe.
	 */
	int getNumVeiculos();
	/*
	 * \brief Altera o numero de veículos disponiveis no posto de socorro.
	 * \param numVeic numero de veiculos a adicionar aos presentes
	 */
	void setNumVeiculos(int numVeic);
	/**
	 * \brief Retorna o vetor de acidentes do posto.
	 * \return Vetor de apontadores para a classe Acidente.
	 */
	vector<Acidente*> getAcidentes() const;
	/**
	 * \brief Retorna uma string correspondete subclasse a que pertence o objeto em questao.
	 */
	virtual std::string getTipoPosto() const {}
	/**
	 * \brief Retorna numero de autotanques existentes no posto.
	 */
	virtual int getNumAutotanques() {}
	/**
	 * \brief Retorna atributo moto.
	 * \return True se o posto utilizar motas.
	 */
	virtual bool getMoto() const {}
	/**
	* \brief Retorna atributo carro.
	* \return True se o posto utilizar carros.
	*/
	virtual bool getCarro() const {}
	/**
	* \brief Retorna atributo ambulancia.
	* \return True se o posto utilizar ambulâncias.
	*/
	virtual bool getAmbulancia() const {}
	/**
	* \brief Retorna numero de ambulancias existentes no posto.
	*/
	virtual int getNumAmbulancias() {}
	/**
	 * \brief Insere um acidente no vetor de acidentes do posto.
	 */
	void insereAcidente(Acidente *a);
	/**
	 * \brief Visualiza informacao sobre o posto de socorro.
	 */
	virtual void visualizaInformacao();
	/**
	 * \brief Imprime informacao sobre o posto de socorro.
	 * \param out objecto de acesso a abertura do ficheiro "postos.txt" para escrita
	 */
	virtual void imprimeInformacao(std::ostream &out);
};

/**
 * Derivada da classe PostoSocorro. Adicionalmente, tem como atributos o numero de ambulancias e autotanques
 * disponiveis para socorrer acidentes.
 */

class Bombeiros: public PostoSocorro {
	int numAmbulancias;
	int numAutotanques;
public:
	/**
	 * brief Construtor da classe Bombeiros.
	 * \param local objeto da classe Local
	 * \param numSoc numero de socorristas disponiveis
	 * \param numVeic numero de veiculos disponiveis
	 * \param numAmb numero de ambulancias disponiveis
	 * \param numAutot numero de autotanques disponiveis
	 */
	Bombeiros(Local local, int numSoc, int numVeic, int numAmb, int numAutot);
	/**
	 * \brief Retorna numero de ambulancias disponiveis no posto de socorro dos bombeiros.
	 * \return Atributo numAmbulancias da classe.
	 */
	int getNumAmbulancias();
	/**
	 * \brief Retorna numero de autotanques disponiveis no posto de socorro dos bombeiros.
	 * \return Atributo numAutotanques da classe.
	 */
	int getNumAutotanques();
	/**
	* \brief Retorna string correspondete a subclasse a que pertence o objeto em questao.
	*/
	std::string getTipoPosto() const;
	/*
	 * \brief Visualiza informacao sobre o posto dos bombeiros.
	 */
	void visualizaInformacao();
	/*
	 * \brief Imprime informacao sobre o posto dos bombeiros.
	 * \param out objecto de acesso a abertura do ficheiro "posto.txt" para escrita
	 */
	void imprimeInformacao(std::ostream &out);
};

/**
 * Derivada da classe PostoSocorro. Adicionalmente, tem como atributos valores booleanos que correspondem
 * ao tipo de veiculo que conduz - moto ou carro.
 */

class Policia: public PostoSocorro {
	bool moto;
	bool carro;
public:
	/**
	 * \brief Construtor da classe Policia.
	 * \param local objeto da classe Local
	 * \param numSoc numero de socorristas disponiveis
	 * \param numVeic numero de veiculos disponiveis
	 * \param moto valor booleano true se conduzir moto
	 * \param carro valor booleano true se conduzir carro
	 */
	Policia(Local local, int numSoc, int numVeic, bool moto, bool carro);
	/**
	* \brief Retorna a string correspondente a subclasse a que pertence o objeto em questao.
	*/
	std::string getTipoPosto() const;
	/**
	* \brief Retorna atributo moto.
	* \return True se o posto utilizar motas.
	*/
	bool getMoto() const;
	/**
	* \brief Retorna atributo carro.
	* \return True se o posto utilizar carros.
	*/
	bool getCarro() const;
	/*
	* \brief Visualiza informacao sobre o posto da policia.
	*/
	void visualizaInformacao();
	/*
	 * \brief Imprime informação sobre o posto da policia.
	 * \param out objecto de acesso a abertura do ficheiro "postos.txt" para escrita
	 */
	void imprimeInformacao(std::ostream &out);
};

/**
 * Derivada da classe PostoSocorro. Adicionalmente, tem como atributos valores booleanos que correspondem ao
 * tipo de veiculos que conduz - moto, carro ou ambulancia.
 */

class Inem: public PostoSocorro {
	bool moto;
	bool carro;
	bool ambulancia;
public:
	/**
	 * \brief Construtor da classe Inem.
	 * \param local objeto da classe Local
	 * \param numSoc numero de socorristas disponiveis
	 * \param numVeic numero de veiculos disponiveis
	 * \param moto valor booleano true se conduzir moto
	 * \param carro valor booleano true se conduzir carro
	 * \param amb valor booleano true se conduzir ambulancia
	 */
	Inem(Local local, int numSoc, int numVeic, bool moto, bool carro, bool amb);
	/**
	* \brief Retorna a string correspondente a subclasse a que pertence o objeto em questao.
	*/
	std::string getTipoPosto() const;
	/**
	* \brief Retorna atributo moto.
	* \return True se o posto utilizar motas.
	*/
	bool getMoto() const;
	/**
	* \brief Retorna atributo carro.
	* \return True se o posto utilizar carros.
	*/
	bool getCarro() const;
	/**
	* \brief Retorna atributo ambulancia.
	* \return True se o posto utilizar ambulancias.
	*/
	bool getAmbulancia() const;
	/**
	* \brief Retorna numero de ambulancias existentes no posto.
	* \return Atributo numAmbulancias da classe.
	*/
	int getNumAmbulancias();
	/*
	* \brief Visualiza informacao sobre o posto do INEM.
	*/
	void visualizaInformacao();
	/*
	* \brief Imprime informacao sobre o posto do INEM.
	* \param objecto de acesso a abertura do ficheiro "postos.txt" para escrita
	*/
	void imprimeInformacao(std::ostream &out);
};
#endif /* POSTOS_H_ */
