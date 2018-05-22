#include<iostream>
#include<string>

using namespace std;


bool verificaPares(int vetor1, int vetor2){
}

void modificarMatriz(){
}

string matrizController(){
    if(nivel == 1){
       string  matriz  = "     1 2 3 4 \n";
                matriz += "   1 * * * * \n";
                matriz += "   2 * * * * \n";
                matriz += "   3 * * * * \n";
                matriz += "   4 * * * * \n";
        return matriz;
    }
    else if(nivel == 2){
        string  matriz  = "     1 2 3 4 5 6 \n";
                matriz += "   1 * * * * * * \n";
                matriz += "   2 * * * * * * \n";
                matriz += "   3 * * * * * * \n";
                matriz += "   4 * * * * * * \n";
                matriz += "   5 * * * * * * \n";
                matriz += "   6 * * * * * * \n";
        return matriz;
    }
    else if(nivel == 3){
        string  matriz  = "     1 2 3 4 5 6 7 8 \n";
                matriz += "   1 * * * * * * * * \n";
                matriz += "   2 * * * * * * * * \n";
                matriz += "   3 * * * * * * * * \n";
                matriz += "   4 * * * * * * * * \n";
                matriz += "   5 * * * * * * * * \n";
                matriz += "   6 * * * * * * * * \n";
                matriz += "   7 * * * * * * * * \n";
                matriz += "   8 * * * * * * * * \n";
        return matriz;
    }
    else{
        cout << "Insira um nivel valido"
    }
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

    cout << "Escolha um dos niveis:" << endl << "1. Iniciante" << endl << "2. Intermediario" << endl << "3. Avancado";
    cin >> nivel;
    cout << matrizController();
    cin >> entrada1[0] >> entrada1[1];
    cin >> entrada2[0] >> entrada2[1];

    cout << entrada1[0] << entrada1[1] << entrada2[0] << entrada2[1];
    return 0;
}
