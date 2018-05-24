#include<iostream>
#include<string>
#include<sstream>


using namespace std;

int nivel;
int fimDoJogo;
int tamMatriz;
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

bool verificaPares(int linha1, int coluna1, int linha2, int coluna2){
	if (nivel == 1){
		if (matrizIniciante[linha1][coluna1] == matrizIniciante[linha2][coluna2]){
			return true;

		}else{
			return false;
		}

	}else if(nivel == 2){
		if (matrizIntermediaria[linha1][coluna1] == matrizIntermediaria[linha2][coluna2]){
			return true;

		}else{
			return false;
		}

	}else if (nivel == 3){
		if (matrizAvancada[linha1][coluna1] == matrizAvancada[linha2][coluna2]){
			return true;

		}else{
			return false;
		}

	}else{
		return false;
	}
}

string toString(int i){
    ostringstream temp;
    temp << i;
    return temp.str();
}

void modificarMatriz(int linha1, int coluna1, int linha2, int coluna2){
    if (nivel == 1){
       matriz[linha1][coluna1] = " " + toString(matrizIniciante[linha1][coluna1]);
       matriz[linha2][coluna2] = " " + toString(matrizIniciante[linha2][coluna2]);

    }else if (nivel == 2){
       matriz[linha1][coluna1] = " " + toString(matrizIntermediaria[linha1][coluna1]);
       matriz[linha2][coluna2] = " " + toString(matrizIntermediaria[linha2][coluna2]);

    }else{
       matriz[linha1][coluna1] = " " + toString(matrizAvancada[linha1][coluna1]);
       matriz[linha2][coluna2] = " " + toString(matrizAvancada[linha2][coluna2]);
    }
}

string ** matrizDinamica(int tam){
    string **matriz = (string **) calloc( tam ,sizeof(string *));
    for(int i = 0; i < tam; i++){
        matriz[i] = (string *) calloc(tam, sizeof(string));
    }
    return matriz;
}

void preencheMatriz(){
    for(int i = 0; i < tamMatriz; i++){
        for(int j = 0;j < tamMatriz; j++){
       		matriz[i][j] = " X";
        }
    }
}

string representaMatriz(){
    int tam = tamMatriz;
    string matrixRetorno = "";
    for(int i = 0; i < tam; i++){
        for(int j = 0;j < tam; j++){
            matrixRetorno += " ";
            matrixRetorno += matriz[i][j];

            }
            matrixRetorno += "\n";

    }
    return matrixRetorno;

}
string geraMatriz(int nivel){
    if(nivel == 1)
        tamMatriz = 4;
    else if(nivel == 2)
        tamMatriz = 6;
    else if(nivel == 3)
        tamMatriz = 8;

    matriz = matrizDinamica(tamMatriz);
    preencheMatriz();
    return representaMatriz();

}

string limpaTela(){
    string retorno = "";
    for(int i = 0; i < 100; i++){
        retorno += "\n";
    }
    return retorno;
}

void resetMatriz(int linha1, int coluna1, int linha2, int coluna2){
    modificarMatriz(linha1, coluna1, linha2, coluna2);
    cout << representaMatriz();
}

bool fimDeJogo(){
	if (nivel == 1){
		if (fimDoJogo == 8){
			return true;
		}else{
			return false;
		}
	}else if (nivel == 2){
		if (fimDoJogo == 18){
			return true;

		}else{
			return false;
		}

	}else{
		if (fimDoJogo == 32){
			return true;

		}else{
			return false;
		}
	}
}

int main(){
    int linha1, coluna1, linha2, coluna2;

    cout<< "Escolha um dos niveis:\n\n" <<
			"1. Iniciante\n" <<
			"2. Intermediario\n" <<
			"3. Avancado\n" <<
			"4. Sair\n\n";

    cin>> nivel;

    while(nivel <= 0 || nivel > 3){
        cout << "\nOpcao Invalida! Insira um nivel valido!\n\n";
        cin >> nivel;
    }

    //matriz = geraMatrizInicial(8);
    //matriz[0][0] = "oi";
    //cout << matriz[2][3];
   // cout<< matrizController(nivel);

    cout << geraMatriz(nivel);
    while (! fimDeJogo()){
		cout<< "\nEscolha a linha e a coluna, respectivamente, do primeiro elemento:"<< endl;
		cin>> linha1;
		cin>> coluna1;

		cout<< "\nEscolha a linha e a coluna, respectivamente, do segundo elemento:"<<endl;
		cin>> linha2;
		cin>> coluna2;

		if (verificaPares(linha1, coluna1, linha2, coluna2)){
            modificarMatriz(linha1, coluna1, linha2, coluna2);
            cout << representaMatriz();

        }else{
            resetMatriz(linha1, coluna1, linha2, coluna2);
            cout << representaMatriz();
        }
	}

    return 0;
}
