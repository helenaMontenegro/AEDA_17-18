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
#include <tr1/unordered_set>
#include "acidentes.h"
#include "postos.h"
#include "BST.h"

/**
 * Classe Oficina.
 * Tem como parametros um nome, para facilitar a verificacao de qual das oficinas está disponivel para o veiculo,
 * a disponibilidade, que se refere ao numero de dias ate esta se tornar disponivel, e um vector de marcas, as quais sao
 * representadas pela oficina.
 */

class Oficina {
	string nome;
	int disponibilidade;
	vector<string> marcas;
public:
	/**
	 * \brief Construtor da classe Oficina.
	 * \param disp disponibilidade da oficina.
	 * \param marc marcas que a oficina representa.
	 */
	Oficina(string n, int disp, vector<string> marc) : nome(n), disponibilidade(disp), marcas(marc) {}
	/**
	 * \brief Retorna nome da oficina.
	 */
	string getNome() const {return nome;}
	/**
	 * \brief Retorna disponibilidade da oficina.
	 */
	int getDisponibilidade() const {return disponibilidade;}
	/**
	 * \brief Retorna marcas que a oficina representa.
	 */
	vector<string> getMarcas() const {return marcas;}
	/**
	 * \brief Permite alterar disponibilidade da oficina.
	 * \param disp nova disponibilidade da oficina.
	 */
	void setDisponibilidade(int disp) {disponibilidade = disp;}
	/**
	 * \brief Operador <, necessario para colocar as oficinas nas filas de prioridade. Uma oficina é menor que outra,
	 * quanto maior for a sua disponibilidade.
	 */
	bool operator<(const Oficina &o1) const {return disponibilidade > o1.getDisponibilidade();}
	/**
	 * \brief Permite visualizar a informacao sobre a oficina.
	 */
	void visualizaInformacao() const {
		cout << "\nNome da oficina: " << nome
				<< "\nDisponibilidade da oficina: " << disponibilidade << endl
				<< marcas.size() << " marcas representadas pela oficina: ";
		for (unsigned int i = 0; i < marcas.size(); i++) {
			cout << marcas[i];
			if (i != marcas.size() - 1)
				cout << ", ";
		}
		cout << endl;
	}
	/**
	 * \brief Permite imprimir a informacao sobre a oficina para um ficheiro de texto.
	 */
	void imprimeInformacao(std::ostream &out) const {
		out << "Nome da oficina: " << nome << "\nDisponibilidade da oficina: "
				<< disponibilidade << endl << marcas.size()
				<< " marcas representadas pela oficina: ";
		for (unsigned int i = 0; i < marcas.size(); i++) {
			out << marcas[i];
			if (i != marcas.size() - 1)
				out << ", ";
		}
	}
};

class CondutorAcidente {
	string nome;
	Data data;
public:
	/**
	 * \brief Construtor da classe CondutorAcidente.
	 * \param n nome do condutor
	 * \param d data do condutor
	 */
	CondutorAcidente(string n, Data d) : nome(n), data(d) {}
	/**
	 * \brief Retorna nome do condutor.
	 */
	string getNome() const {return nome;}
	/**
	 * \brief Retorna data do acidente
	 */
	Data getData() const {return data;}
	/**
	 * \brief Permite visualizar a informacao sobre o condutor.
	 */
	void visualizaInformacao() const { cout << "\nNome do condutor: " << nome << "\nData do acidente: " << data << endl;}
	/**
	 * \brief Permite imprimir a informacao sobre o condutor para um ficheiro de texto.
	 */
	void imprimeInformacao(std::ostream &out) const {out << "Nome do condutor: " << nome << "\nData do acidente: " << data << endl;}
};

/**
 * Função de igualdade
 */
struct eqCondutorAcidente {
	bool operator()(const CondutorAcidente &c1,
			const CondutorAcidente &c2) const {
		return c1.getNome() == c2.getNome();
	}
};

/**
 * Função hash
 */
struct hCondutorAcidente {
	int operator()(const CondutorAcidente &c1) const {
		string n = c1.getNome();
		int v = 0;
		for (unsigned int i = 0; i < n.size(); i++)
			v = 37 * v + n[i];
		return v;
	}
};

typedef tr1::unordered_set<CondutorAcidente, hCondutorAcidente, eqCondutorAcidente> hashCondutorAcidente;

class Veiculo {
	string marca;
	int numAcidentes;
	Data data;
public:
	/**
	 * \brief Construtor de um veiculo que nao pode existir
	 */
	Veiculo() {
		marca = "NOT_FOUND";
		data = Data(1, 1, 1);
		numAcidentes = 0;
	}
	;
	/**
	 * \brief Construtor da classe veiculo
	 * \param marca marca do veiculo
	 * \param data data do acidente no qual o veiculo foi envolvido
	 */
	Veiculo(string marca, Data data);
	/**
	 * \brief Construtor da classe veiculo
	 * \param marca marca do veiculo
	 * \param data data do acidente no qual o veiculo foi envolvido
	 * \param numAcidentes numero de acidentes em que o veiculo foi envolvido
	 */
	Veiculo(string marca, Data data, int numAcidentes);
	/**
	 * \brief Retorna marca do veiculo
	 */
	string getMarca() const;
	/**
	 * \brief Retorna o numero de acidentes.
	 */
	int getNumAcidentes() const;
	/**
	 * \brief Retorna a ultima data em que ocorreu um acidente de um veiculo de uma marca.
	 */
	Data getData() const;
	/**
	 * \brief Permite alterar o numero de acidentes dos veiculos de uma determinada marca.
	 * 	param numAcid numero de acidentes a adicionar a numAcidentes
	 */
	void setNumAcidentes(int numAcid);
	/**
	 * \brief Funcao que permite alterar a data do ultimo acidente de um veiculo de determinada marca
	 */
	void setData(Data d);
	/**
	 * \brief Operador <, necessario para a implementacao da arvore binaria de pesquisa.
	 * \param v1 veiculo com o qual se pretende comparar.
	 */
	bool operator<(Veiculo v1) const;
	/**
	 * \brief Operador ==, que indica se dois veiculos tem a mesma marca ou nao.
	 * \param v1 veiculo com o qual se pretende comparar.
	 */
	bool operator==(Veiculo v1) const;
	/**
	 * \brief Operador =
	 * \param v1 veiculo que se pretende copiar.
	 */
	void operator=(Veiculo v1);
};

/**
 * Constituida por um vector de apontadores para objetos da classe Acidente e um
 * vector de apontadores para objetos da classe PostoSocorro.
 */

class Sistema {
	std::vector<Acidente *> acidentes;
	std::vector<PostoSocorro *> postos;
	BST<Veiculo> veiculos;
	hashCondutorAcidente condutores;
	priority_queue<Oficina> oficinas;
public:
	/**
	 * \brief Default construtor da classe Sistema.
	 */
	Sistema() : veiculos(Veiculo()) {}
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
	/**
	 * \brief Funcao que procura um veiculo na arvore binaria de pesquisa veiculos, pesquisando atraves do nome da marca.
	 * Esta funcao e necessaria visto que a arvore esta organizada nao pelas marcas dos carros envolvidos nos acidentes
	 * mas pelo numero de acidentes que cada marca teve, pelo que nao e possivel utilizar a funcao find para as BSTs
	 * neste caso.
	 * \param veiculo que se pretende encontrar na arvore.
	 * \return iterador para o veiculo com a mesma marca do veiculo v1, ou para o fim da arvore, caso este nao seja
	 * encontrado.
	 */
	BSTItrIn<Veiculo> bst_find(Veiculo &v1);
	/**
	 * \brief Guarda informacao sobre os veiculos e os condutores envolvidos nos acidentes de viacao nas
	 * respetivas estruturas.
	 * \param a apontador para objeto da classe Acidente
	 */
	void guardaInformacaoViacao(Acidente* a1);
	/**
	 * \brief Mostra informacao presente na arvore binaria, sobre as marcas de veiculos envolvidos em acidentes de
	 * viacao.
	 */
	void mostraInformacaoVeiculos() const;
	/**
	 * \brief Coloca a informacao presente no ficheiro de texto "consutores.txt", sobre os condutores, na tabela de
	 * dispersao.
	 */
	void abrirFicheiroCondutores(istream &ficheiro);
	/**
	 * \brief Insere marca na arvore, caso esta ainda nao exista, e altera o numero de acidentes dos veiculos de uma
	 * marca, caso esta ja exista na arvore.
	 * \param a veiculo a inserir na arvore.
	 */
	void insereVeiculo(Veiculo &v);
	/**
	 * \brief Atualiza ficheiro de condutores com as alteracoes efetuadas ao ser utilizado o sistema.
	 * \param a ficheiro objecto de acesso a abertura do ficheiro "condutores.txt" para escrita
	 */
	void atualizaCondutores(ostream &out);
	/**
	 * \brief Atualiza ficheiro de veiculos com as alteracoes efetuadas ao ser utilizado o sistema.
	 * \param a ficheiro objecto de acesso a abertura do ficheiro "veiculos.txt" para escrita
	 */
	void atualizaVeiculos(ostream &out);
	/**
	 * \brief Atualiza ficheiro de oficinas com as alteracoes efetuadas ao ser utilizado o sistema.
	 * \param a ficheiro objecto de acesso a abertura do ficheiro "oficinas.txt" para escrita
	 */
	void atualizaOficinas(ostream &out);
	/**
	 * \brief Permite visualizar a informacao sobre os condutores, existentes na tabela de dispersao.
	 */
	void visualizaInformacaoCondutores();
	/**
	 * \brief Permite visualizar a informacao sobre as oficinas, existentes na fila de prioridade.
	 */
	void visualizaInformacaoOficinas();
	/**
	 * \brief Permite visualizar uma listagem de oficinas existentes na fila de prioridade que representam uma dada marca.
	 */
	void listaOficinas();
	/**
	 * \brief Guarda na fila de prioridade a informacao sobre oficinas presente no ficheiro das oficinas.
	 * \param a ficheiro objecto de acesso a abertura do ficheiro "oficinas.txt" para leitura
	 */
	void abrirFicheiroVeiculos(istream &ficheiro);
	/**
	 * \brief Permite eliminar da arvore binaria de pesquisa todas as marcas cujo ultimo acidente tenha sido ha mais de
	 * x anos, sendo x especificado pelo utilizador.
	 */
	void eliminaVeiculo();
	/**
	 * \brief Funcao que permite adicionar uma nova oficina ao sistema.
	 */
	void adicionaOficina();
	/**
	 * \brief Funcao que permite alterar informações sobre uma oficina presente no sistema.
	 */
	void editaOficina();
	/**
	 * \brief Funcao que permite remover uma oficina do sistema.
	 */
	void removeOficina();
	/**
	 * \brief Funcao que arranja a oficina de menor disponibilidade para o veiculo cuja marca e especificada pelo
	 * utilizador.
	 */
	void colocaVeiculoEmEspera();
	/**
	 * \brief Funcao que decrementa a disponibilidade de todas as oficinas cuja disponibilidade e superior a zero, isto
	 * e, que permite reparar um veiculo de cada oficina.
	 */
	void passaUmDia();
	/**
	 * \brief Atualiza ficheiro de oficinas com as alteracoes efetuadas na utilizacao do sistema.
	 * \param a ficheiro objecto de acesso a abertura do ficheiro "oficinas.txt" para leitura
	 */
	void abrirFicheiroOficinas(istream &ficheiro);
	/**
	 * \brief Permite visualizar o numero de acidentes que ocorreu com uma determinada marca.
	 */
	void numAcidentesMarca();
	/**
	 * \brief Permite visualizar as marcas de veiculos que tenham sido envolvidas em mais de x acidentes de viacao,
	 * sendo x definido pelo utilizador.
	 */
	void numAcidentesAcima();
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
