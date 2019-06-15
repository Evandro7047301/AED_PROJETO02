#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<fstream>

#define PRIMO 31
#define TAM 11

using namespace std;

template <class TYPE>
class No{
private:
    TYPE data;
public:
    No<TYPE> *proximoPtr;

    No(const TYPE &);
    TYPE getData()const;
};

template<class TYPE>
No<TYPE>::No(const TYPE &info)
{
    data = info;
    proximoPtr = 0;
}

template<class TYPE>
TYPE No<TYPE>::getData()const{
    return data;
}

template<class TYPE>
class Lista{
public:
    Lista();
    ~Lista();

    int getTamanho();
//    void inserirFrente(const TYPE &);
    void inserirAtras(const TYPE &);
    bool removerFrente();
    bool removerAtras();
    void print()const;
    string busca(const string &);
    string get(const int &);

private:
    int tamanho;
    bool estaVazia()const;

    No<TYPE> *primeiroPtr;
    No<TYPE> *ultimoPtr;

    No<TYPE> *getNovoNo(const TYPE &);
};


template<class TYPE>
Lista<TYPE>::Lista(){
    tamanho = 0;
    primeiroPtr = 0;
    ultimoPtr = 0;
}

template<class TYPE>
Lista<TYPE>::~Lista(){
    if(!estaVazia()){
        No <TYPE> *atualPtr = primeiroPtr;
        No <TYPE> *temporarioPtr;

        while(atualPtr != 0){
            temporarioPtr = atualPtr;
            atualPtr = atualPtr->proximoPtr;
            delete temporarioPtr;
        }
    }
}

template<class TYPE>
int Lista<TYPE>::getTamanho(){
    return tamanho;
}

// template<class TYPE>
// void Lista<TYPE>::inserirFrente(const TYPE &valor){
//     No<TYPE> *novoPtr = getNovoNo(valor);
//
//     if(estaVazia()){
//         primeiroPtr = ultimoPtr = novoPtr;
//     }
//     else{
//         tamanho += 1;
//         novoPtr->proximoPtr = primeiroPtr;
//         primeiroPtr = novoPtr;
//     }
// }

template<class TYPE>
void Lista<TYPE>::inserirAtras(const TYPE &valor){
    No<TYPE> *novoPtr = getNovoNo(valor);

    //Lista est� vazia
    if(estaVazia()){
        primeiroPtr = ultimoPtr = novoPtr;
    }
    else{
        tamanho += 1;
        ultimoPtr-> proximoPtr = novoPtr;
        ultimoPtr = novoPtr;
    }
}

template<class TYPE>
bool Lista<TYPE>::removerFrente(){

    if(estaVazia()){
        return false;
    }
    else{
        No<TYPE> *temporarioPtr = primeiroPtr;

        if(primeiroPtr == ultimoPtr){
            primeiroPtr = ultimoPtr = 0;
        }
        else{
            primeiroPtr = primeiroPtr->proximoPtr;
        }

        tamanho -= 1;
        delete temporarioPtr;
        return true;

    }
}

template<class TYPE>
bool Lista<TYPE>::removerAtras(){
    if(estaVazia()){
        return false;
    }
    else{
        No<TYPE> *temporarioPtr = ultimoPtr;
        if(primeiroPtr == ultimoPtr){
            primeiroPtr = ultimoPtr = 0;
        }
        else{
            No<TYPE> *atualPtr = primeiroPtr;

            while(atualPtr->proximoPtr != ultimoPtr){
                atualPtr = atualPtr->proximoPtr;
            }

            ultimoPtr = atualPtr;
            atualPtr->proximoPtr = 0;
        }

        tamanho -= 1;
        //valor = temporarioPtr->getData();
        delete temporarioPtr;
        return true;

    }
}

template<class TYPE>
bool Lista<TYPE>::estaVazia()const{
    return primeiroPtr == 0;
}

template<class TYPE>
No<TYPE> *Lista<TYPE>::getNovoNo(const TYPE &valor){
    return new No<TYPE>(valor);
}

template<class TYPE>
void Lista<TYPE>::print()const{
    if(estaVazia()){
        cout<< "A lista esta vazia"<<"\n";
        return;
    }

    No<TYPE> *atualPtr = primeiroPtr;

    while(atualPtr != 0){
        cout << atualPtr->getData();
        atualPtr = atualPtr->proximoPtr;

    }
}

template<class TYPE>
string Lista<TYPE>::busca(const string &chaveRecebida){

    No<TYPE> *atualPtr = primeiroPtr;


    while(atualPtr != 0){
        if(atualPtr->getData() == chaveRecebida){
            return atualPtr->getData();
        }
        atualPtr = atualPtr->proximoPtr;
    }

    return "-1";

}

template<class TYPE>
string Lista<TYPE>::get(const int &indice){

    No<TYPE> *atualPtr = primeiroPtr;

    int contador = 0;

    while(atualPtr != 0){
        if(contador == indice){
            return atualPtr->getData();
        }
        contador += 1;
        atualPtr = atualPtr->proximoPtr;
    }

    return "-1";
}

// struct Dupla{
//     string simbolo;
//     string chave;
// };

// int strParaInt(string chave){
//     int acumulador = 0;
//     int chaveTam = strlen(chave.c_str());
//     for(int i = 0; i < chaveTam; i++){
//         acumulador += (int)chave[i];
//     }
//     acumulador *= PRIMO;
//     return acumulador;
// }
//
// int h(string chave){
//
//     return strParaInt(chave) % TAM;
// }

template <class TYPE>
class TabelaHash{
private:
    Lista<TYPE> th[TAM];
    float qntElementos = 0.0;
    float fatorDeCarga;
    int tamanhoString;
public:
    TabelaHash(const TYPE &);
    ~TabelaHash(){};

    int hash(string);
    void inserirElemento(const string &);
    string buscarElemento(const string &chave);
    int getTamanhoString();
    void setTamanhoString(int);

    float getFatorDeCarga();
    void setFatorDeCarga();

    float getQntElementos();
    void adicionarQntElementos();

};

template<class TYPE>
void TabelaHash<TYPE>::setTamanhoString(int tamanho){
    this->tamanhoString = tamanho;
}
template<class TYPE>
int TabelaHash<TYPE>::getTamanhoString(){
    return this->tamanhoString;
}

template<class TYPE>
void TabelaHash<TYPE>::adicionarQntElementos(){
    this->qntElementos += 1.0;
}

template<class TYPE>
float TabelaHash<TYPE>::getQntElementos(){
    return this->tamanhoString;
}

template<class TYPE>
void TabelaHash<TYPE>::setFatorDeCarga(){
    this->fatorDeCarga = qntElementos / TAM;
}

template<class TYPE>
float TabelaHash<TYPE>::getFatorDeCarga(){
    return this->fatorDeCarga;
}



template<class TYPE>
TabelaHash<TYPE>::TabelaHash(const TYPE &string){
    setTamanhoString(strlen(string.c_str()));

    for(int i = 0; i < TAM; i++){
        Lista<TYPE> lista;
        th[i] = lista;
    }
}

template<class TYPE>
int TabelaHash<TYPE>::hash(string chave){
    int acumulador = 0;

    int chaveTam = strlen(chave.c_str());
    for(int i = 0; i < chaveTam; i++){
        unsigned char caractere = chave[i];
        acumulador += (int)caractere;
    }
    // cout<<endl;
    // cout<<acumulador;
    acumulador *= PRIMO;

    return acumulador % TAM;
}

template<class TYPE>
void TabelaHash<TYPE>::inserirElemento(const string &data){
    int i = hash(data);
    adicionarQntElementos();
    // cout <<"i: " <<i<<endl;
    th[i].inserirAtras(data);
}

template<class TYPE>
string TabelaHash<TYPE>::buscarElemento(const string &chave){
    string chaveStr = chave;
    int i = hash(chave);
    return th[i].busca(chaveStr);
}

template <class TYPE>
class NoArvore{

public:
    TYPE *data;
    NoArvore <TYPE> *ptrEsquerdo;
    NoArvore <TYPE> *ptrDireito;
    int altura;

    NoArvore(){};

    int getAltura() const{
        return altura;
    }

    void setAltura(const int &a){
        altura = a;
    }

    TYPE getData() const{
        return data;
    }

};


template <class TYPE>
class Arvore{
public:
    Arvore();
    ~Arvore(){}

    NoArvore<TYPE> *rodarDireita(NoArvore<TYPE> *a);
    NoArvore<TYPE> *rodarEsquerda(NoArvore<TYPE> *a);

    void insereNo(const string &);
    void percorrePreOrdem () const;
    void desenha();
    string busca(const string &);

    NoArvore <TYPE> *ptrRaiz = 0;
private:

    int max(int a, int b);
    int calcularAltura(NoArvore<TYPE> *);
    int getBalanco(NoArvore<TYPE> *);

    void desenhaAux(NoArvore<TYPE> *p, int nivel);
    void desenhaNo(NoArvore<TYPE> *p, int nivel);

    NoArvore<TYPE> *ajudanteDeInsereNo (NoArvore <TYPE> *, const string &);
    string ajudanteDeBusca (NoArvore <TYPE> *, const string &,  int &);

    void ajudantePercorrePreOrdem (NoArvore <TYPE> *) const;
    NoArvore<TYPE>* novoNoArvore(const string &);



};

template <class TYPE>
NoArvore<TYPE>* Arvore<TYPE>::novoNoArvore(const string &d){
    NoArvore<TYPE>* no = new NoArvore<TYPE>();

    TabelaHash<string> *hash = new TabelaHash<string>(d);
    hash->inserirElemento(d);
    no->data = hash;
    no->ptrEsquerdo = 0;
    no->ptrDireito = 0;
    no->altura = 1;
    return (no);
}

template <class TYPE>

Arvore<TYPE>::Arvore(){};

template<class TYPE>
int Arvore<TYPE>::max(int a, int b){
    return (a > b) ? a : b;
}

template<class TYPE>
int Arvore<TYPE>::calcularAltura(NoArvore<TYPE> *no){

    if (no == 0){
        return 0;
    }


    else{
        return no->altura;
    }

}

template<class TYPE>
int Arvore<TYPE>::getBalanco(NoArvore<TYPE> *no){
    if (no == 0){
        return 0;
    }
    else{
        return calcularAltura(no->ptrEsquerdo) - calcularAltura(no->ptrDireito);
    }

}

template<class TYPE>
NoArvore<TYPE> *Arvore<TYPE>::rodarDireita(NoArvore<TYPE> *y){
    NoArvore<TYPE> *x = y->ptrEsquerdo;
    NoArvore<TYPE> *temp = x->ptrDireito;

    x->ptrDireito = y;
    y->ptrEsquerdo = temp;

    y->altura = max(calcularAltura(y->ptrEsquerdo), calcularAltura(y->ptrDireito)) + 1;
    // cout<<"altura de y:" << y->altura<<endl;
    x->altura = max(calcularAltura(x->ptrEsquerdo), calcularAltura(x->ptrDireito)) + 1;

    return x;
}
template<class TYPE>
NoArvore<TYPE> *Arvore<TYPE>::rodarEsquerda(NoArvore<TYPE> *x){
    NoArvore<TYPE> *y = x->ptrDireito;
    NoArvore<TYPE> *temp = y->ptrEsquerdo;

    y->ptrEsquerdo = x;
    x->ptrDireito = temp;

    x->altura = max(calcularAltura(x->ptrEsquerdo), calcularAltura(x->ptrDireito)) + 1;
    y->altura = max(calcularAltura(y->ptrEsquerdo), calcularAltura(y->ptrDireito)) + 1;
    return y;
}

template <class TYPE>
void Arvore<TYPE>::insereNo(const string &valor){
    ptrRaiz = ajudanteDeInsereNo(ptrRaiz, valor);
}

template <class TYPE>
NoArvore<TYPE> *Arvore<TYPE>::ajudanteDeInsereNo(NoArvore<TYPE> *ptr, const string &valor){
    if(ptr == 0){
        // cout<<"adiciona hash de tamanho: " << strlen(valor.c_str()) <<endl;
        return (novoNoArvore(valor));

    }
    else{
        if((int)strlen(valor.c_str()) < ptr->data->getTamanhoString()){
             ptr->ptrEsquerdo = ajudanteDeInsereNo(ptr->ptrEsquerdo, valor);
        }
        else{
            if((int)strlen(valor.c_str()) > ptr->data->getTamanhoString()){
                ptr-> ptrDireito = ajudanteDeInsereNo(ptr->ptrDireito, valor);
            }
            else{
                ptr->data->inserirElemento(valor);
                // cout << ptr->data->buscarElemento(valor);
                return ptr;
            }
        }
    }

    ptr->altura = 1 + max(calcularAltura(ptr->ptrEsquerdo), calcularAltura(ptr->ptrDireito));

    int balanco = getBalanco(ptr);

    if (balanco > 1 && (int)strlen(valor.c_str()) < ptr->ptrEsquerdo->data->getTamanhoString()){
        // cout<<"teste01";
        return rodarDireita(ptr);
    }
    // cout<<"teste02";
    else if (balanco < -1 && (int)strlen(valor.c_str()) > ptr->ptrDireito->data->getTamanhoString()){
        return rodarEsquerda(ptr);
    }
    else if (balanco > 1 && (int)strlen(valor.c_str()) > ptr->ptrEsquerdo->data->getTamanhoString()){
        ptr->ptrEsquerdo = rodarEsquerda(ptr->ptrEsquerdo);
        // cout<<"teste03";
        return rodarDireita(ptr);
    }
    else if (balanco < -1 && (int)strlen(valor.c_str()) < ptr->ptrDireito->data->getTamanhoString()){
        ptr->ptrDireito = rodarDireita(ptr->ptrDireito);
        // cout<<"teste04";
        return rodarEsquerda(ptr);
    }
    return ptr;
}

template <class TYPE>
string Arvore<TYPE>::busca(const string &valor){
    int profundidade = 0;
    return ajudanteDeBusca(ptrRaiz, valor, profundidade);
}

template <class TYPE>
string Arvore<TYPE>::ajudanteDeBusca(NoArvore<TYPE> *ptr, const string &valor, int &profundidade){
    if(ptr == 0){
        return "-1";

    }
    else{
        if((int)strlen(valor.c_str()) < ptr->data->getTamanhoString()){
             profundidade += 1;
             ajudanteDeBusca(ptr->ptrEsquerdo, valor, profundidade);
        }
        else{
            if((int)strlen(valor.c_str()) > ptr->data->getTamanhoString()){
                profundidade += 1;
                ajudanteDeBusca(ptr->ptrDireito, valor, profundidade);
            }
            else{
                ptr->data->setFatorDeCarga();
                // cout<<"Altura ptrRaiz: "<<calcularAltura(ptrRaiz)<<endl;
                // cout<<"Altura ptr: "<<calcularAltura(ptr)<<endl;
                // cout<< "Fator de carga: "<< ptr->data->getFatorDeCarga()<<endl;
                // cout<< "tamanhoString: "<< ptr->data->getTamanhoString()<<endl;
                // cout << "Elemento: "<< ptr->data->buscarElemento(valor)<<endl;
                // cout << "profundidade: "<<calcularAltura(ptrRaiz) - calcularAltura(ptr)<<endl;

                if( ptr->data->buscarElemento(valor) == "-1"){
                    cout << "chave não encontrada" <<endl;
                }
                else{
                    cout<< profundidade<<' '<<ptr->data->getFatorDeCarga()<<endl;
                    return ptr->data->buscarElemento(valor);

                }
            }
        }
    }
    return "-1";
}

template <class TYPE>
void Arvore<TYPE>::desenha() {

	if (ptrRaiz != NULL) {
		int nivel = 0;
		desenhaAux(ptrRaiz, nivel);
	}
}
template <class TYPE>

void Arvore<TYPE>::desenhaAux(NoArvore<TYPE> *p, int nivel) {
	if (p != NULL) {
		desenhaAux(p->ptrDireito, nivel + 1);
		desenhaNo(p, nivel);
		desenhaAux(p->ptrEsquerdo, nivel + 1);
	}
}
template <class TYPE>

void Arvore<TYPE>::desenhaNo(NoArvore<TYPE> *p, int nivel) {
	string espacos = "";
	for (int i = 0; i < nivel; i++)
		espacos += "  ";
	cout << espacos << ( p->data->getTamanhoString()) << endl;
}



template <class TYPE>
void Arvore<TYPE>::percorrePreOrdem() const{
    ajudantePercorrePreOrdem(ptrRaiz);
}

template <class TYPE>
void Arvore<TYPE>::ajudantePercorrePreOrdem(NoArvore<TYPE> *ptr) const{
    if(ptr != 0){
        cout << ptr->data->getTamanhoString()<<' '<<ptr->getAltura()<<'\n';
        ajudantePercorrePreOrdem(ptr->ptrEsquerdo);
        ajudantePercorrePreOrdem(ptr->ptrDireito);
    }
}


// template <class TYPE>
// void Arvore<TYPE>::percorreCentral() const{
//     ajudantePercorreCentral(ptrRaiz);
// }
//
// template <class TYPE>
// void Arvore<TYPE>::ajudantePercorreCentral(NoArvore<TYPE> *ptr)const{
//     if(ptr != 0){
//         ajudantePercorreCentral(ptr->ptrEsquerdo);
//         cout << ptr -> data << ' ';
//         ajudantePercorreCentral(ptr->ptrDireito);
//     }
// }
//
// template <class TYPE>
// void Arvore<TYPE>::percorrePosOrdem() const{
//     ajudantePercorrePosOrdem(ptrRaiz);
// }
//
// template <class TYPE>
// void Arvore<TYPE>::ajudantePercorrePosOrdem(NoArvore<TYPE> *ptr)const{
//     if(ptr != 0){
//         ajudantePercorrePosOrdem(ptr->ptrEsquerdo);
//         ajudantePercorrePosOrdem(ptr->ptrDireito);
//         cout << ptr -> getData() << '\n';
//     }
// }





int main(){
    //int valor;
    string linha;
    //
    // // Arvore<string> arvore;
    //

    // Arvore<TabelaHash<string>> arvoreString;

    Arvore<TabelaHash<string>> arvore;




    ifstream arquivo("chaves.txt");
    if (!arquivo.is_open()){
        cout << "Falha na abertura do arquivo" << endl;
        exit(1);
    }
    else{
        while (getline (arquivo, linha)) {
            // cout<< linha<<endl;
            arvore.insereNo(linha);
        }
    }
    // cout << "\nPercorrer...\n";
    // arvoreInt.percorrePreOrdem();
    string linhaRecebida = " ";
    while(true){
        getline(cin, linhaRecebida);
        if(linhaRecebida.length()==0){
            break;
        }
        else{
            arvore.busca(linhaRecebida);
        }
    }
    arquivo.close();
    // arvore.desenha();
    // arvore.percorrePreOrdem();


    // cout << "Pre ordem\n";
    // arvoreString.percorrePreOrdem();

return 0;

}
