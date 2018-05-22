#include<iostream>
#include<string>
#include<sstream>

using namespace std;


bool verificaPares(int vetor1, int vetor2){
}

void modificarMatriz(){
}

string toString(int i){
    ostringstream temp;
    temp << i;
    return temp.str();
}

string geraMatriz(int tamanho){
    string matriz;
    tamanho += 1;
    matriz += "  ";
    for (int i = 1; i < tamanho; i++){
        matriz += toString(i);
        matriz += " ";
    }
    matriz += "\n";
    for(int i = 1; i < tamanho; i++){
        for (int j = 1; j < tamanho + 2; j++){
            if (j == 1){
                matriz += toString(i);
            }else if(j > 1 && j < tamanho + 1){
                matriz += " *";
            }
        }
        matriz += "\n";
    }
    return matriz;
}

string matrizController(int nivel){
    string matriz;
    switch (nivel){
        case 1:
            matriz = geraMatriz(4);
            break;
        case 2:
            matriz = geraMatriz(6);
            break;
        case 3:
            matriz = geraMatriz(8);
            break;
    }
    return matriz;
}

string limpaTela(){
    string retorno = "";
    for(int i = 0; i < 100; i++){
        retorno += "\n";
    }
    return retorno;
}

void resetMatriz(){
}

int main(){
    int entrada1[2], entrada2[2];
    int nivel;

    cout << "Escolha um dos niveis:" << endl << endl << "    1. Iniciante" << endl << "    2. Intermediario" << endl << "    3. Avancado" << endl;
    cin >> nivel;
    while(nivel <= 0 || nivel > 3){
        cout << "Insira um nivel valido!\n";
        cin >> nivel;
    }
    cout << matrizController(nivel);
    cin >> entrada1[0] >> entrada1[1];
    cin >> entrada2[0] >> entrada2[1];
    cout << entrada1[0] << entrada1[1] << entrada2[0] << entrada2[1];
    return 0;
}
