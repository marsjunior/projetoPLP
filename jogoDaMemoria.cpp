#include<iostream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include<time.h>


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
void resetMatriz(int linha1, int coluna1, int linha2, int coluna2){
    matriz[linha1][coluna1] = " X";
    matriz[linha2][coluna2] = " X";
}

/*
 * Função que finaliza o jogo.
 */
bool fimDeJogo(time_t tempo){
    return ((fimDoJogo > (tamMatriz*2)) || (difftime(time(NULL), tempo) > 180));
}

/*
 * Função delay. Criada com o objetivo de funcionar em diferentes Sistemas Operacionais.
 */
void pause(int i){
    time_t tempo = time(NULL);
    while(difftime(time(NULL), tempo) <= i){}
}


int main(){
    int linha1, coluna1, linha2, coluna2;
    time_t tempo;

    cout<< "Escolha um dos niveis:\n\n" <<
			"1. Iniciante\n" <<
			"2. Intermediario\n" <<
			"3. Avancado\n\n";

    cin>> nivel;

    while(nivel <= 0 || nivel > 3){
        cout << "\nOpcao Invalida! Insira um nivel valido!\n\n";
        cin >> nivel;
    }

    tempo = time(NULL);
    cout << geraMatriz(nivel);
    while (!fimDeJogo(tempo)){
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
            modificarMatriz(linha1, coluna1, linha2, coluna2);
            cout << representaMatriz();
        }else{
            modificarMatriz(linha1, coluna1, linha2, coluna2);
            cout << representaMatriz();
            pause(5);
            system("clear");
            resetMatriz(linha1, coluna1, linha2, coluna2);
            cout << representaMatriz();
        }
	}
    cout << "Fim de jogo!";
    return 0;
}
