#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<fstream>

const int PRIMO = 37;
const int TAM = 7;

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
    int tamanhoString;
public:
    TabelaHash();
    ~TabelaHash(){};

    int hash(string);
    void inserirElemento(const string &);
    string buscarElemento(const string &chave);
    int getTamanhoString();
    void setTamanhoString(int &);
};

template<class TYPE>
void TabelaHash<TYPE>::setTamanhoString(int &tamanho){
    this.tamanhoString = tamanho;
}

template<class TYPE>
int TabelaHash<TYPE>::getTamanhoString(){
    return this.tamanhoString;
}



template<class TYPE>
TabelaHash<TYPE>::TabelaHash(){
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
        acumulador += (int)chave[i];
    }
    acumulador *= PRIMO;

    return acumulador % TAM;
}

template<class TYPE>
void TabelaHash<TYPE>::inserirElemento(const string &data){
    int i = hash(data);
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
    TYPE data;
    NoArvore <TYPE> *ptrEsquerdo;
    NoArvore <TYPE> *ptrDireito;
    int altura;

    NoArvore(){}

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

    void insereNo(const TYPE &);
    void percorrePreOrdem () const;

    NoArvore <TYPE> *ptrRaiz = NULL;
private:

    int max(int a, int b);
    int calcularAltura(NoArvore<TYPE> *);
    int getBalanco(NoArvore<TYPE> *);

    NoArvore<TYPE> *ajudanteDeInsereNo (NoArvore <TYPE> *, const TYPE valor);
    void ajudantePercorrePreOrdem (NoArvore <TYPE> *) const;
    NoArvore<int>* novoNoArvore(const int d);

};

template <class TYPE>
NoArvore<int>* Arvore<TYPE>::novoNoArvore(const int d){
    NoArvore<int>* no = new NoArvore<int>();
    no->data = d;
    no->ptrEsquerdo = NULL;
    no->ptrDireito = NULL;
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

    if (no == NULL){
        return 0;
    }


    else{
        return no->altura;
    }
    if (no == 0)
        return 0;
    else
        return no->getAltura();
}

template<class TYPE>
int Arvore<TYPE>::getBalanco(NoArvore<TYPE> *no){
    if (no == NULL){
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
}
template<class TYPE>
NoArvore<TYPE> *Arvore<TYPE>::rodarEsquerda(NoArvore<TYPE> *x){
    NoArvore<TYPE> *y = x->ptrDireito;
    NoArvore<TYPE> *temp = y->ptrEsquerdo;

    y->ptrEsquerdo = x;
    x->ptrDireito = temp;

    x->altura = max(calcularAltura(x->ptrEsquerdo), calcularAltura(x->ptrDireito)) + 1;
    y->altura = max(calcularAltura(y->ptrEsquerdo), calcularAltura(y->ptrDireito)) + 1;
}

template <class TYPE>
void Arvore<TYPE>::insereNo(const TYPE &valor){
    ptrRaiz = ajudanteDeInsereNo(ptrRaiz, valor);
}

template <class TYPE>
NoArvore<TYPE> *Arvore<TYPE>::ajudanteDeInsereNo(NoArvore<TYPE> *ptr, const TYPE valor){
    if(ptr == NULL){
        return (novoNoArvore(valor));

    }
    else{
        if(valor < ptr->data){
             ptr->ptrEsquerdo = ajudanteDeInsereNo(ptr->ptrEsquerdo, valor);
        }
        else{
            if(valor > ptr->data){
                ptr-> ptrDireito = ajudanteDeInsereNo(ptr->ptrDireito, valor);
            }
            else{
                return ptr;
            }
        }
    }

    ptr->altura = 1 + max(calcularAltura(ptr->ptrEsquerdo), calcularAltura(ptr->ptrDireito));

    int balanco = getBalanco(ptr);
    if (balanco > 1 && valor < ptr->ptrEsquerdo->data){
        return rodarDireita(ptr);
    }
    else if (balanco < -1 && valor > ptr->ptrDireito->data){
        return rodarEsquerda(ptr);
    }
    else if (balanco > 1 && valor > ptr->ptrEsquerdo->data){
        ptr->ptrEsquerdo = rodarEsquerda(ptr->ptrEsquerdo);
        return rodarDireita(ptr);
    }
    else if (balanco < -1 && valor < ptr->ptrDireito->data){
        ptr->ptrDireito = rodarDireita(ptr->ptrDireito);
        return rodarEsquerda(ptr);
    }
    return ptr;
}

template <class TYPE>
void Arvore<TYPE>::percorrePreOrdem() const{
    ajudantePercorrePreOrdem(ptrRaiz);
}

template <class TYPE>
void Arvore<TYPE>::ajudantePercorrePreOrdem(NoArvore<TYPE> *ptr) const{
    if(ptr != NULL){
        cout << ptr->data<<'\n';
        ajudantePercorrePreOrdem(ptr->ptrEsquerdo);
        ajudantePercorrePreOrdem(ptr->ptrDireito);
    }
}
//
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


// template <class TYPE>
// void PreOrdem(NoArvore<TYPE> *ptr){
//     if(ptr != NULL){
//         cout << ptr->data<<'\n';
//         PreOrdem(ptr->ptrEsquerdo);
//         PreOrdem(ptr->ptrDireito);
//     }
// }
//


int main(){
    //int valor;
    string linha;

    // Arvore<string> arvore;

    Arvore<int> arvoreInt;

    arvoreInt.insereNo(10);
    arvoreInt.insereNo(20);
    arvoreInt.insereNo(30);
    arvoreInt.insereNo(40);
    arvoreInt.insereNo(50);
    arvoreInt.insereNo(25);


    // ifstream arquivo("teste.txt");
    // if (!arquivo.is_open()){
    //     cout << "Falha na abertura do arquivo" << endl;
    //     exit(1);
    // }
    // else{
    //     while (getline (arquivo, linha)) {
    //         arvore.insereNo(linha);
    //         cout << linha << '\n';
    //     }
    // }
    // cout << "\nPercorrer...\n";
    // arvoreInt.percorrePreOrdem();
    // cout << "\nResultado da busca: " << arvore.busca("chave") << endl;

    // arquivo.close();


    cout << "Pre ordem\n";
    arvoreInt.percorrePreOrdem();

return 0;

}
