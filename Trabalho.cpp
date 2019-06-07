#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
const int PRIMO = 37;
const int TAM = 7;
using namespace std;

template <class TYPE>
class No{
public:
    No(const TYPE &);
    TYPE getData()const;

    TYPE data;
    No<TYPE> *proximoPtr;
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
    void inserirFrente(const TYPE &);
    void inserirAtras(const TYPE &);
    bool removerFrente();
    bool removerAtras(TYPE &);
    bool estaVazia()const;
    void print()const;
    string busca(const string &);
    string get(const int &);

private:
    No<TYPE> *primeiroPtr;
    No<TYPE> *ultimoPtr;

    No<TYPE> *getNovoNo(const TYPE &);
};

template<class TYPE>
Lista<TYPE>::Lista(){
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
void Lista<TYPE>::inserirFrente(const TYPE &valor){
    No<TYPE> *novoPtr = getNovoNo(valor);

    if(estaVazia()){
        primeiroPtr = ultimoPtr = novoPtr;
    }
    else{

        novoPtr->proximoPtr = primeiroPtr;
        primeiroPtr = novoPtr;
    }
}

template<class TYPE>
void Lista<TYPE>::inserirAtras(const TYPE &valor){
    No<TYPE> *novoPtr = getNovoNo(valor);

    //Lista está vazia
    if(estaVazia()){
        primeiroPtr = ultimoPtr = novoPtr;
    }
    else{

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


        delete temporarioPtr;
        return true;

    }
}

template<class TYPE>
bool Lista<TYPE>::removerAtras(TYPE &valor){
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


        valor = temporarioPtr->data;
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
        cout << atualPtr->data;
        atualPtr = atualPtr->proximoPtr;

    }
}

template<class TYPE>
string Lista<TYPE>::busca(const string &chaveRecebida){

    No<TYPE> *atualPtr = primeiroPtr;


    while(atualPtr != 0){
        if(atualPtr->data.chave == chaveRecebida){
            return atualPtr->data.simbolo;
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
            return atualPtr->data;
        }
        contador += 1;
        atualPtr = atualPtr->proximoPtr;
    }

    return "-1";
}

struct Dupla{
    string simbolo;
    string chave;
};

int strParaInt(string chave){
    int acumulador = 0;
    int chaveTam = strlen(chave.c_str());
    for(int i = 0; i < chaveTam; i++){
        acumulador += (int)chave[i];
    }
    acumulador *= PRIMO;
    return acumulador;
}

int h(string chave){

    return strParaInt(chave) % TAM;
}

template <class TYPE>
class TabelaHash{

public:

    Lista<TYPE> th[TAM];

    TabelaHash(){
        for(int i = 0; i < TAM; i++){
            Lista<TYPE> lista;
            th[i] = lista;
        }

    }

    ~TabelaHash(){};

    void inserirElemento(const string &chave, const string &data){
        int i = h(chave);
        // cout<< "i:"<<i<<"\n";
        Dupla dupla = {data,chave};

        th[i].inserirAtras(dupla);
    }


     string buscarElemento(const string &chave){
        string chaveStr = chave;
        int i = h(chave);
        return th[i].busca(chaveStr);
    }



};

template <class TYPE>

class NoArvore{
public:
    NoArvore <TYPE> *ptrEsquedo;
    TYPE data;
    NoArvore <TYPE> *ptrDireito;
    int altura;
    NoArvore(const TYPE &d){
        ptrEsquedo = 0;
        data = d;
        ptrDireito = 0;
    }

    TYPE pegarData() const{
        return data;
    }
};


template <class TYPE>
class Arvore{
public:
    Arvore();

    void insereNo(const TYPE &);
    TYPE busca(const TYPE &);
    // void percorrePreOrdem () const;
    // void percorreCentral () const;
    // void percorrePosOrdem () const;

private:
    NoArvore <TYPE> *ptrRaiz;
    TYPE ajudanteDeBusca (NoArvore <TYPE> **, const TYPE &);
    void ajudanteDeInsereNo (NoArvore <TYPE> **, const TYPE &);
    // void ajudantePercorrePreOrdem (NoArvore <TYPE> *) const;
    // void ajudantePercorreCentral (NoArvore <TYPE> *) const;
    // void ajudantePercorrePosOrdem (NoArvore <TYPE> *) const;
};

template <class TYPE>

Arvore<TYPE>::Arvore(){
    ptrRaiz = 0;
}

template <class TYPE>
TYPE Arvore<TYPE>::busca(const TYPE &item){
    return ajudanteDeBusca(&ptrRaiz, item);
}

template <class TYPE>
TYPE Arvore<TYPE>::ajudanteDeBusca(NoArvore<TYPE> **ptr, const TYPE &item){
    if(*ptr == 0){
        return -1;
        cout << "item nao encontrado";
    }
    if(item == (*ptr)->data){
        return (*ptr)->data;
    }

    else{
        if(item < (*ptr)->data){
            ajudanteDeBusca(&((*ptr)->ptrEsquedo), item);
        }
        else{
            if(item > (*ptr)->data){
                ajudanteDeBusca(&((*ptr)->ptrDireito), item);
            }
        }
    }
}




template <class TYPE>
void Arvore<TYPE>::insereNo(const TYPE &valor){
    ajudanteDeInsereNo(&ptrRaiz, valor);
}

template <class TYPE>
void Arvore<TYPE>::ajudanteDeInsereNo(NoArvore<TYPE> **ptr, const TYPE &valor){
    if(*ptr == 0){
        *ptr = new NoArvore<TYPE>(valor);

    }
    else{
        if(valor < (*ptr)->data){
            ajudanteDeInsereNo(&((*ptr)->ptrEsquedo), valor);
        }
        else{
            if(valor > (*ptr) -> data){
                ajudanteDeInsereNo(&((*ptr)->ptrDireito), valor);
            }
            else{
                cout << valor << "duplicata" << endl;
            }
        }
    }
}

// template <class TYPE>
// void Arvore<TYPE>::percorrePreOrdem() const{
//     ajudantePercorrePreOrdem(ptrRaiz);
// }
//
// template <class TYPE>
// void Arvore<TYPE>::ajudantePercorrePreOrdem(NoArvore<TYPE> *ptr) const{
//     if(ptr != 0){
//         cout << ptr->data<<' ';
//         ajudantePercorrePreOrdem(ptr->ptrEsquedo);
//         ajudantePercorrePreOrdem(ptr->ptrDireito);
//     }
// }
//
// template <class TYPE>
// void Arvore<TYPE>::percorreCentral() const{
//     ajudantePercorreCentral(ptrRaiz);
// }
//
// template <class TYPE>
// void Arvore<TYPE>::ajudantePercorreCentral(NoArvore<TYPE> *ptr)const{
//     if(ptr != 0){
//         ajudantePercorreCentral(ptr->ptrEsquedo);
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
//         ajudantePercorrePosOrdem(ptr->ptrEsquedo);
//         ajudantePercorrePosOrdem(ptr->ptrDireito);
//         cout << ptr -> data << ' ';
//     }
// }

int main(){

    // TabelaHash<Dupla> hash;
    // hash.inserirElemento("e","d");
    // cout << hash.buscarElemento("e");

    // int valor;
    //
    // Arvore<int> arvoreInt;
    // cout << "insira 10 valores inteiros\n";
    //
    // for(int i = 0; i < 3; i++){
    //     cin >> valor;
    //     arvoreInt.insereNo(valor);
    // }
    // cout << arvoreInt.busca(2);
    // cout << "\nPre ordem\n";
    // arvoreInt.percorrePreOrdem();
    // cout << "\n\nCentral\n";
    // arvoreInt.percorreCentral();
    // cout << "\n\nPos ordem\n";
    // arvoreInt.percorrePosOrdem();
return 0;

}
