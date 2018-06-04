#include<iostream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include<time.h>
#include<fstream>

using namespace std;

int nivel;
int fimDoJogo = 0;
int tamMatriz = 0;
string ** matriz;

int matrizIniciante[4][4] = {
	{4,6,7,2},
	{1,3,5,2},
	{4,5,6,3},
	{1,8,8,7}
};

int matrizIntermediaria[6][6] = {
	{18,5,8,2,4,9},
	{5,16,12,7,3,10},
	{1,17,8,6,11,18},
	{10,3,17,14,4,13},
	{7,15,2,11,16,6},
	{12,14,9,1,15,13}
};

int matrizAvancada[8][8] = {
	{10,4,9,2,14,14,21,26},
	{23,17,29,11,20,1,30,30},
	{4,27,17,5,24,29,6,6},
	{26,28,11,8,13,16,12,31},
	{21,22,2,19,19,1,25,25},
	{3,27,10,32,24,15,7,12},
	{23,18,28,5,16,15,31,13},
	{9,22,3,18,20,32,7,8}
};

/*
 * Função que verifica se os pares selecionados pelo usuário são iguais.
 */
bool verificaPares(int linha1, int coluna1, int linha2, int coluna2){
    bool retorno = false;
    if ((linha1 != linha2) || (coluna1 != coluna2)){
        if(matriz[linha1][coluna1] == " X" && matriz[linha2][coluna2] == " X"){
            if (nivel == 1){
                if (matrizIniciante[linha1][coluna1] == matrizIniciante[linha2][coluna2]){
                    fimDoJogo++;
                    retorno = true;
                }
            }else if(nivel == 2){
                if (matrizIntermediaria[linha1][coluna1] == matrizIntermediaria[linha2][coluna2]){
                    fimDoJogo++;
                    retorno = true;
                }
            }else if (nivel == 3){
                if (matrizAvancada[linha1][coluna1] == matrizAvancada[linha2][coluna2]){
                    fimDoJogo++;
                    retorno = true;
                }
            }
        }
    }
    return retorno;
}

/*
 * Função que converte um inteiro em string.
 */
string intToString(int i){
    ostringstream temp;
    temp << i;
    return temp.str();
}

/*
 * Função que modifica a matriz do usuário inserindo os pares nas respectivas posições.
 */
void modificarMatriz(int linha1, int coluna1, int linha2, int coluna2){
    if (nivel == 1){
       matriz[linha1][coluna1] = " " + intToString(matrizIniciante[linha1][coluna1]);
       matriz[linha2][coluna2] = " " + intToString(matrizIniciante[linha2][coluna2]);

    }else if (nivel == 2){
       matriz[linha1][coluna1] = " " + intToString(matrizIntermediaria[linha1][coluna1]);
       matriz[linha2][coluna2] = " " + intToString(matrizIntermediaria[linha2][coluna2]);

    }else{
       matriz[linha1][coluna1] = " " + intToString(matrizAvancada[linha1][coluna1]);
       matriz[linha2][coluna2] = " " + intToString(matrizAvancada[linha2][coluna2]);
    }
}

/*
 * Função que cria dinamicamete uma matriz.
 */
string ** matrizDinamica(int tam){
    string **matriz = (string **) calloc( tam ,sizeof(string *));
    for(int i = 0; i < tam; i++){
        matriz[i] = (string *) calloc(tam, sizeof(string));
    }
    return matriz;
}

/*
 * Função que preenche a matriz do usuário com X.
 */
void preencheMatriz(){
    for(int i = 0; i < tamMatriz; i++){
        for(int j = 0;j < tamMatriz; j++){
       		matriz[i][j] = " X";
        }
    }
}

/*
 * Função que retorna a representação da matriz do usuário no formato string.
 */
string representaMatriz(){
    string matrixRetorno = " ";
    for(int i = 0; i < tamMatriz; i++){
        matrixRetorno += "  " + intToString(i+1);
    }
    matrixRetorno += "\n";
    for(int i = 0; i < tamMatriz; i++){
        for(int j = 0;j < tamMatriz; j++){
            if (j == 0){
                matrixRetorno += intToString(i+1);
            }
            matrixRetorno += " ";
            matrixRetorno += matriz[i][j];
        }
        matrixRetorno += "\n";
    }
    return matrixRetorno;
}

/*
 * Função que gera a matriz a partir do nível escolhido pelo usuário.
 */
string geraMatriz(int nivel){
    if(nivel == 1)
        tamMatriz = 4;
    else if(nivel == 2)
        tamMatriz = 6;
    else
        tamMatriz = 8;
    matriz = matrizDinamica(tamMatriz);
    preencheMatriz();
    return representaMatriz();
}

/*
 * Função que deleta os pares escolhidos pelo usuário se forem diferentes.
 */
void resetMatriz(int linha1, int coluna1, int linha2, int coluna2, int naoModifica){
    if(naoModifica == 1){
        matriz[linha2][coluna2] = " X";
    }else if(naoModifica == 2){
        matriz[linha1][coluna1] = " X";
    }else if(naoModifica != 3){
        matriz[linha1][coluna1] = " X";
        matriz[linha2][coluna2] = " X";
    }

}
/*
 * Funcao recebe uma linha do arquivo ranking.txt ex: fulano: 1m23s
 * extrai so o tempo ex: 1 23
 */
string rankingTempo(string linha){
    string x = "";
    int i = 0;
    string retorno = "";
    while(x != ":" && i < linha.size()){
        x = linha.substr(i, 1);
        i++;
    }

    retorno += linha.substr(i+1, 1);
    retorno += " ";
    retorno += linha.substr(i+4, 2);
    return retorno;
}
/*
 * Funcao recebe um inteiro em segudos, transforma para string com minutos e segundos
 * ex: 1 34, onde 1 eh minuto e 34 sao segundos
 * os minutos nunca seram representados com 2 casas decimais
 */
string tempoString(int tempo){
    string m = "";
    string s = "";
    string retorno = "";
    m = intToString(tempo/60);
    s = intToString(tempo%60);
    retorno += m;
    retorno += " ";
    if(tempo%60 < 10){
        retorno += "0";
        retorno += s;
    }else{
        retorno += s;
    }

    return retorno;
}
/*
 * Funcao ler arquivo e compara o tempo do jogador com os temos registrados no arquivo,
 * se o tempo do jogador atual for menor do que 1 dos 5 ultimos recordes esse valor e alterado
 */
void rankingGrava(string nome, int tempo){
    fstream arquivo;
    string linha;
    string tempo1 = tempoString(tempo);
    string tempo2;
    string novoRanking = "";
    int minutos1 = stoi(tempo1.substr(0, 1));
    int segundos1 = stoi(tempo1.substr(2, 2));
    int minutos2 = 0;
    int segundos2 = 0;
    int linhas = 0;
    bool gravou = false;
    arquivo.open("ranking.txt", ios::in);
    if(arquivo.is_open()){
        while(getline(arquivo, linha)){
            tempo2 = rankingTempo(linha);
            minutos2 = stoi(tempo2.substr(0, 1));
            segundos2 = stoi(tempo2.substr(2, 2));
            if(minutos1 < minutos2 && !gravou){
                novoRanking += nome;
                novoRanking += ": ";
                novoRanking += intToString(minutos1);
                novoRanking += "m ";
                novoRanking += intToString(segundos1);
                novoRanking += "s\n";
                if(linhas < 4){
                    novoRanking += linha;
                    novoRanking += "\n";
                    linhas++;
                }
                gravou = true;
            }else if(minutos1 == minutos2 && !gravou){
                if(segundos1 < segundos2){
                    novoRanking += nome;
                    novoRanking += ": ";
                    novoRanking += intToString(minutos1);
                    novoRanking += "m ";
                    novoRanking += intToString(segundos1);
                    novoRanking += "s\n";
                    if(linhas < 4){
                        novoRanking += linha;
                        novoRanking += "\n";
                        linhas++;
                    }
                    gravou = true;
                }else if(linhas < 5){
                    novoRanking += linha;
                    novoRanking += "\n";
                }
            }else if(linhas < 5){
                novoRanking += linha;
                novoRanking += "\n";
            }
            linhas++;
        }
        if(linhas < 5 && !gravou){
            novoRanking += nome;
            novoRanking += ": ";
            novoRanking += intToString(minutos1);
            novoRanking += "m ";
            novoRanking += intToString(segundos1);
            novoRanking += "s\n";
            gravou = true;
        }
        arquivo.close();
        arquivo.open("ranking.txt", ios::out);
        arquivo << novoRanking;
        arquivo.close();

    }else{
        arquivo.close();
        arquivo.open("ranking.txt", ios::out);
        string tem;
        string temp = tempoString(tempo);
        tem += temp.substr(0, 1);
        tem += "m";
        tem += temp.substr(2, 2);
        tem += "s";
        arquivo << nome << ": " << tem << "\n";
    }

}
/*
 * Funcao ler arquivo ranking.txt e retorna uma string para exibir na tela
 */
string rankingExibir(){
    string retorno = "\n";
    string linha = "";
    fstream arquivo;
    arquivo.open("ranking.txt", ios::in);
    if(arquivo.is_open()){
        while(getline(arquivo, linha)){
            linha += "\n";
            retorno += linha;
        }
    }else{
        retorno = "Nenhuma partida foi registrada ainda\n";
    }
    retorno += "\n";
    return retorno;
}


/*
 * Função que verificar as codicoes para finalizar o jogo
 * o jogo pode ser finalizado por tempo superior a 3 minutos
 * ou por ter encontrado todas as peças do jogo
 * tambem infoca a funcao ranking passado o tempo para verificar
 * se e um novo recorde para ser registrado
 */
bool fimDeJogo(string nome, time_t tempo){
    int segundos = difftime(time(NULL), tempo);
    bool retorno = ((fimDoJogo >= (tamMatriz*2)) || (segundos > 180));
    if(retorno){
        rankingGrava(nome, segundos);
    }
    return retorno;
}

/*
 * Função delay. Criada com o objetivo de funcionar em diferentes Sistemas Operacionais.
 */
void pause(int i){
    time_t tempo = time(NULL);
    while(difftime(time(NULL), tempo) <= i){}
}




int main(){
    int linha1, coluna1, linha2, coluna2, menu;
    time_t tempo;
    string nome;
    cout << "Menu:\n\n"<<
            "1. Iniciar Jogo\n"<<
            "2. Ranking\n"<<
            "3. Sair\n\n";
    cin >> menu;
    if(menu == 1){
        cout<< "\nInforme seu nome:\n";
        cin >> nome;
        system("clear");
        cout<< "\n" << nome<<" escolha um dos niveis:\n\n" <<
			"1. Iniciante\n" <<
			"2. Intermediario\n" <<
			"3. Avancado\n\n";

        cin>> nivel;

        while(nivel <= 0 || nivel > 3){
            cout << "\nOpcao Invalida! Insira um nivel valido!\n\n";
            cin >> nivel;
        }
        system("clear");
        tempo = time(NULL);
        cout << geraMatriz(nivel);
        while (!fimDeJogo(nome, tempo)){
            cout<< "\nEscolha a linha e a coluna, respectivamente, do primeiro elemento:"<< endl;
            cin>> linha1;
            linha1--;
            cin>> coluna1;
            coluna1--;

            cout<< "\nEscolha a linha e a coluna, respectivamente, do segundo elemento:"<<endl;
            cin>> linha2;
            linha2--;
            cin>> coluna2;
            coluna2--;

            if (verificaPares(linha1, coluna1, linha2, coluna2)){
                system("clear");
                modificarMatriz(linha1, coluna1, linha2, coluna2);
                cout << representaMatriz();
            }else{
                int naoModifica = 0;
                if(matriz[linha1][coluna1] != " X" && matriz[linha2][coluna2] != " X"){
                    naoModifica = 3;
                }else if(matriz[linha1][coluna1] != " X"){
                    naoModifica = 1;
                }else if(matriz[linha2][coluna2] != " X"){
                    naoModifica = 2;
                }
                modificarMatriz(linha1, coluna1, linha2, coluna2);
                cout << representaMatriz();
                pause(5);
                system("clear");
                resetMatriz(linha1, coluna1, linha2, coluna2, naoModifica);
                cout << representaMatriz();
            }
            }
        }else if(menu == 2){
            cout << rankingExibir();
        }else{
            cout << "Fim de jogo!\n\n";
            return 0;
        }
    cout << "Fim de jogo!\n\n";
    return 0;
}
