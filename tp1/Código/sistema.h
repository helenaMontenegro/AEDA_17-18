/*
 * sistema.h
 *
 *  Created on: 17 de Out de 2017
 *      Author: Mariana
 */

#ifndef SISTEMA_H_
#define SISTEMA_H_

#include <fstream>
#include <vector>
#include "acidentes.h"
#include "postos.h"

/**
 * Constituida por um vector de apontadores para objetos da classe Acidente e um
 * vector de apontadores para objetos da classe PostoSocorro.
 */

class Sistema {
	std::vector<Acidente *> acidentes;
	std::vector<PostoSocorro *> postos;
public:
	/**
	 * \brief Default construtor da classe Sistema.
	 */
	Sistema() {
	}
	/**
	 * \brief Destrutor da classe Sistema.
	 */
	~Sistema();
	/**
	 * \brief Retorna atributo acidentes.
	 * \return Vetor de apontadores para objetos da classe Acidente.
	 */
	vector<Acidente*> getAcidentes() const;
	/**
	 * \brief Retorna atributo postos.
	 * \return Vetor de apontadores para objetos da classe PostoSocorro.
	 */
	vector<PostoSocorro*> getPostos() const;
	/**
	 * \brief Insire informacao do ficheiro de texto "postos.txt" em postos.
	 * \param ficheiro objecto de acesso a abertura do ficheiro "postos.txt" para leitura
	 */
	void abrirFicheiroPostos(istream &ficheiro);
	/**
	 * \brief Abre o ficheiro sobre os acidentes, intitulado de "acidentes.txt", e guarda a sua informacao
	 * em acidentes.
	 * \param ficheiro objecto de acesso a abertura do ficheiro "acidentes.txt" para leitura
	 */
	void abrirFicheiroAcidentes(istream &ficheiro);
	/**
	 * \brief Adiciona um apontador para um objeto da classe Acidente ao vector acidentes.
	 * \param acid objeto da classe Acidente
	 */
	void insereAcidente(Acidente *acid);
	/**
	 * \brief Adiciona um novo acidente ao vector acidentes.
	 *
	 * Funcao pergunta ao utilizador todas as informacoes necessarias para adicionar um novo acidente a base
	 * de dados.
	 */
	void adicionaAcidente();
	/**
	 * \brief Adiciona um novo posto de socorro ao vector postos.
	 *
	 *
	 * Função pergunta ao utilizador todas as informacoes necessarias para adicionar um novo posto a base de dados.
	 */
	void criaPostoSocorro();
	/**
	 * \brief Permite editar os recursos disponiveis de um posto.
	 *
	 * Função pergunta ao utilizador todas as informacoes necessarias para posteriormente atualizar
	 * a informacao do posto na base de dados.
	 */
	void editaPostoSocorro();
	/**
	 * \brief Altera os dados relativos a um dado acidente em caso de erro da sua insercao
	 * na base de dados.
	 */
	void editaAcidente();
	/**
	 * \brief Remove todos os acidentes tratados do vector de apontadores para objetos da classe Acidente e
	 * do ficheiro de texto "acidentes.txt".
	 */
	void removeAcidentesSistema(ostream &out);
	/**
	 * \brief Visualiza informacao sobre os acidentes.
	 */
	void visualizaInformacaoAcidentes() const;
	/**
	 * \brief Imprime informacao sobre os acidentes.
	 * \param out objecto de acesso a abertura do ficheiro "acidentes.txt" para escrita
	 */
	void imprimeInformacaoAcidentes(ostream &out);
	/**
	 * \brief Visualiza informacao sobre os postos.
	 */
	void visualizaInformacaoPostos() const;
	/**
	 * \brief Atualiza o ficheiro de texto dos postos de socorro de acordo com as alteracoes feitas
	 * ao vetor de apontadores para objetos da classe PostoSocorro no decorrer do programa.
	 * \param out objecto de acesso a abertura do ficheiro "postos.txt" para escrita
	 */
	void atualizaFicheiroPostos(ostream &out);
	/**
	 * \brief Verifica qual o posto que se encontra mais perto de um acidente. Quando "policia" e verdadeiro,
	 * significa que estamos a procurar um posto de policia ou de INEM que utiliza motas ou carros.
	 *
	 * Para incendios florestais, sao apenas necessarios bombeiros.
	 *
	 * Para incendios domesticos, sao necessarios bombeiros e policia ou INEM (com carros ou motas), pelo que
	 * esta funcao sera chamada duas vezes, uma com "policia" = false e outra com "policia" = true.
	 *
	 * Para assaltos, apenas e necessaria policia ou INEM que utilize carro ou mota, mais INEM (que utilize
	 *  ambulancias) ou bombeiros, caso haja feridos.
	 *
	 * Para acidentes de viacao, e necessaria policia ou INEM que utilize carro ou mota, mais INEM que utilize
	 * ambulancia ou bombeiros, caso haja feridos, como no acidente anterior.
	 * \param a objeto da classe Acidente
	 * \param policia valor booleano e true quando estamos a procurar um posto de policia ou de INEM que utiliza motas ou carros
	 * \return Apontador para um objeto da classe PostoSocorro.
	 */
	PostoSocorro* verificaPostoMaisPerto(Acidente &a, bool policia);
	/**
	 * \brief Retorna o posto de socorro, entre dois, que se encontra mais perto do acidente.
	 * \param a objeto da classe Acidente
	 * \param p1 objeto da classe PostoSocorro
	 * \param p2 objeto da classe PostoSocorro
	 * \return Apontador para um objeto da classe PostoSocorro.
	 */
	PostoSocorro* comparaDistancias(Acidente &a, PostoSocorro *p1,
			PostoSocorro *p2);
	/**
	 * \brief Trata acidentes, isto é, atribui meios de socorro aos acidentes.
	 */
	void trataAcidentes();
	/**
	 * \brief Mostra postos atribuidos a cada um dos acidentes presentes no vetor de acidentes do sistema,
	 * mostrando tambem os recursos disponibilizados pelos postos.
	 */
	void mostraPostosAtribuidosAcidentes();
	/**
	 * \brief Visualiza informacao de acidentes de um determinado dia.
	 */
	void mostraAcidenteData();
	/**
	 * \brief Visualiza todos os acidentes que nao foram tratados.
	 */
	void mostraAcidentesNaoTratados();
	/**
	 * \brief Visualizaa todos os acidentes que aconteceram num determinado distrito.
	 */
	void mostraAcidentesDistrito();
	/**
	 * \brief Visualiza historico de acidentes de um posto.
	 */
	void mostraHistoricoPosto();
	/**
	 * \brief Ordena o vetor de apontadores para objetos da classe Acidente por ordem da data mais recente.
	 *
	 * No final do programa, o ficheiro de texto "acidentes.txt" e tambem ordenado.
	 */
	void ordenaAcidenteData();
	/**
	 * \brief Compara dois apontadores para acidentes em funcao do qual e mais recente.
	 * \param a apontador para objeto da classe Acidente
	 * \param b apontador para objeto da classe Acidente
	 * \return True se acidente a for menor que acidente b.
	 */
	bool compara(const Acidente *a, const Acidente *b);
};

/**
 * \brief Excecao SemRecursosDisponiveis.
 *
 * Lancada quando, na atribuicao de meios de socorro aos acidentes, nao existem
 * recursos suficientes para atender ao acidente.
 */

class SemRecursosDisponiveis {
public:
	SemRecursosDisponiveis() {
	}
};

#endif /* SISTEMA_H_ */
