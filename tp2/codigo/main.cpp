/*
 * teste.cpp
 *
 *  Created on: 18 de Out de 2017
 *      Author: Mariana
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "data.h"
#include "acidentes.h"
#include "postos.h"
#include "sistema.h"
using namespace std;

int menu(Sistema &s);

int menu(Sistema &s) {
	while(1) {
	char resposta, opcao;

	cout << endl << "Deseja continuar para o menu? (S/N) ";
	cin >> resposta;
	while (cin.fail() || (resposta != 'S' && resposta != 'N')) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\nResposta invalida. Tente novamente." << endl;
		cin >> resposta;
	}

	if (resposta == 'S') {

			cout << endl << "\t\t******************************\n"
					<< "\t\t\tPROTECAO CIVIL\n"
					<< "\t\t******************************\n\n"
					<< "Opcao A: Visualizar informacao sobre postos de socorro"
					<< endl
					<< "Opcao B: Adicionar um novo acidente a base de dados"
					<< endl
					<< "Opcao C: Adicionar um novo posto de socorro a base de dados"
					<< endl
					<< "Opcao D: Editar posto de socorro"
					<< endl
					<< "Opcao E: Editar um acidente que nao tenha sido socorrido"
					<< endl
					<< "Opcao F: Ordenar histório de acidentes por ordem do mais antigo"
					<< endl
					<< "Opcao G: Visualizar acidentes que ainda nao tem meios de socorro atribuidos"
					<< endl
					<< "Opcao H: Visualizar os meios de socorro que atenderam aos acidentes"
					<< endl
					<< "Opcao I: Visualizar acidentes que ocorreram numa determinada data"
					<< endl
					<< "Opcao J: Visualizar acidentes que ocorreram num determinado distrito"
					<< endl
					<< "Opcao K: Visualizar o historico de acidentes de um posto de socorro"
					<< endl
					<< "---------------------------------PARTE 2--------------------------------"
					<< endl
					<< "Opcao L: Visualizar informacao sobre marcas de veiculos envolvidos em acidentes de viacao"
					<< endl
					<< "Opcao M: Retirar do sistema marcas cujos acidentes ocorreram ha mais de x anos"
					<< endl
					<< "Opcao N: Visualizar numero de acidentes que envolveram uma determinada marca"
					<< endl
					<< "Opcao O: Visualizar marcas que se envolveram num numero de acidentes superior a x"
					<< endl
					<< "Opcao P: Visualizar informacao sobre condutores"
					<< endl
					<< "Opcao Q: Adicionar oficina ao sistema"
					<< endl
					<< "Opcao R: Alterar informacao sobre oficina presente no sistema"
					<< endl
					<< "Opcao S: Remover oficina do sistema"
					<< endl
					<< "Opcao T: Colocar veiculo para reparacao"
					<< endl
					<< "Opcao U: Reparar 1 veiculo em cada oficina (passa um dia)"
					<< endl
					<< "Opcao V: Listar as oficinas que representam uma dada marca"
					<< endl
					<< "Opcao W: Visualizar informacao sobre oficinas"
					<< endl
					<< "Opcao X: Terminar"
					<< endl
					<< "\nEscolha uma opcao: ";
			cin >> opcao;
			while (cin.fail() || (int) opcao < (int) 'A' || (int) opcao > (int) 'X') {
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Opcao invalida. Tente novamente." << endl;
			}

			cout << endl;

			switch (opcao) {
			case 'A': s.visualizaInformacaoPostos(); break;
			case 'B': s.adicionaAcidente(); s.trataAcidentes(); break;
			case 'C': s.criaPostoSocorro(); s.trataAcidentes(); break;
			case 'D': s.editaPostoSocorro(); s.trataAcidentes(); break;
			case 'E': s.editaAcidente(); s.trataAcidentes(); break;
			case 'F': s.ordenaAcidenteData(); break;
			case 'G': s.mostraAcidentesNaoTratados(); break;
			case 'H': s.mostraPostosAtribuidosAcidentes(); break;
			case 'I': s.mostraAcidenteData(); break;
			case 'J': s.mostraAcidentesDistrito(); break;
			case 'K': s.mostraHistoricoPosto(); break;
			case 'L': s.mostraInformacaoVeiculos(); break;
			case 'M': s.eliminaVeiculo(); break;
			case 'N': s.numAcidentesMarca(); break;
			case 'O': s.numAcidentesAcima(); break;
			case 'P': s.visualizaInformacaoCondutores(); break;
			case 'Q': s.adicionaOficina(); break;
			case 'R': s.editaOficina(); break;
			case 'S': s.removeOficina(); break;
			case 'T': s.colocaVeiculoEmEspera(); break;
			case 'U': s.passaUmDia(); break;
			case 'V': s.listaOficinas(); break;
			case 'W': s.visualizaInformacaoOficinas(); break;
			case 'X': return 0;
			}
			cout << "______________________________________________________________" << endl;

		}
		else
			return 0;
	}
}

int main()
{
	Sistema s1;

	ifstream fichAcidentes("acidentes.txt");
	if (!fichAcidentes)
		cerr << "Ficheiro de acidentes inexistente!\n";
	else
		s1.abrirFicheiroAcidentes(fichAcidentes);
	fichAcidentes.close();

	ifstream fichPostosSocorro("postos.txt");
	if (!fichPostosSocorro)
			cerr << "Ficheiro de postos de socorro inexistente!\n";
		else
			s1.abrirFicheiroPostos(fichPostosSocorro);
	fichPostosSocorro.close();

	ifstream fichCondutores("condutores.txt");
	if (!fichCondutores)
		cerr << "Ficheiro de condutores inexistente!\n";
	else
		s1.abrirFicheiroCondutores(fichCondutores);
	fichCondutores.close();

	ifstream fichVeiculos("veiculos.txt");
	if (!fichVeiculos)
		cerr << "Ficheiro de veiculos inexistente!\n";
	else
		s1.abrirFicheiroVeiculos(fichVeiculos);
	fichVeiculos.close();

	ifstream fichOficinas("oficinas.txt");
	if (!fichOficinas)
		cerr << "Ficheiro de oficinas inexistente!\n";
	else
		s1.abrirFicheiroOficinas(fichOficinas);
	fichOficinas.close();

	s1.trataAcidentes();
	menu(s1);

	ifstream ficheiroA;
	ofstream out_a("acidentes.txt");
	if (!out_a)
		cerr << "Ficheiro de acidentes inexistente!\n";
	s1.removeAcidentesSistema(out_a);
	out_a.close();

	ifstream ficheiroP;
	ofstream out_p("postos.txt");
	if (!out_p)
		cerr << "Ficheiro de postos inexistente!\n";
	s1.atualizaFicheiroPostos(out_p);
	out_p.close();

	ofstream out_c("condutores.txt");
	if (!out_c)
		cerr << "Ficheiro de condutores inexistente!\n";
	s1.atualizaCondutores(out_c);
	out_c.close();

	ofstream out_v("veiculos.txt");
	if (!out_v)
		cerr << "Ficheiro de veiculos inexistente!\n";
	s1.atualizaVeiculos(out_v);
	out_v.close();

	ofstream out_o("oficinas.txt");
	if (!out_o)
		cerr << "Ficheiro de oficinas inexistente!\n";
	s1.atualizaOficinas(out_o);
	out_o.close();

	return 0;
}
