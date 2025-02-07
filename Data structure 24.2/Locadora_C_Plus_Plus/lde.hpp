#include <iostream>
using namespace std;

template <typename T>
struct No{
    T info;
    No <T> *eloA = NULL;
    No <T> *eloP = NULL;
};

template <typename T>
struct LDE{
    No <T> *comeco = NULL;
    No <T> *fim = NULL;
};

struct filmes
{
    int cod;
    string nome;
    string categoria;
    string diretor;
    LDE<string> atores;
    string disponibilidade;
};

struct login{
    int matricula;
    string nome;
    string senha;
};

struct filmeAlugado{
    int matriculaUser;
    int codFilme;
    string nomeFilme;
    string nomeUser;
    int data;
    int codAluguel;
};

bool operator==(const LDE<string> &a1, const LDE<string> &a2){
    return(a1.comeco->info == a2.comeco->info);
}

bool operator>(const LDE<string> &a1, const LDE<string> &a2){
    return(a1.comeco->info > a2.comeco->info);
}

bool operator<(const LDE<string> &a1, const LDE<string> &a2){
    return(a1.comeco->info < a2.comeco->info);
}

bool operator>=(const LDE<string> &a1, const LDE<string> &a2){
    return(a1.comeco->info >= a2.comeco->info);
}

bool operator<=(const LDE<string> &a1, const LDE<string> &a2){
    return(a1.comeco->info <= a2.comeco->info);
}

bool operator==(const filmes &f1, const filmes &f2)
{
    return (f1.cod == f2.cod &&
            f1.nome == f2.nome &&
            f1.categoria == f2.categoria &&
            f1.diretor == f2.diretor &&
            f1.atores == f2.atores && 
            f1.disponibilidade == f2.disponibilidade);
}

bool operator<(const filmes &f1, const filmes &f2)
{
    return f1.cod < f2.cod;
}

bool operator>(const filmes &f1, const filmes &f2)
{
    return f1.cod > f2.cod;
}

bool operator<=(const filmes &f1, const filmes &f2)
{
    return f1.cod < f2.cod;
}

bool operator>=(const filmes &f1, const filmes &f2)
{
    return f1.cod > f2.cod;
}

bool operator==(const login &l1, const login &l2){
    return (l1.nome == l2.nome && l1.senha == l2.senha);
}

bool operator>(const login &l1, const login &l2){
    return (l1.matricula > l2.matricula);
}
bool operator<(const login &l1, const login &l2){
    return (l1.matricula < l2.matricula);
}
bool operator>=(const login &l1, const login &l2){
    return (l1.matricula >= l2.matricula);
}
bool operator<=(const login &l1, const login &l2){
    return (l1.matricula <= l2.matricula);
}

bool operator==(const filmeAlugado &l1, const filmeAlugado &l2){
    return (l1.codAluguel == l2.codAluguel);
}

bool operator>(const filmeAlugado &l1, const filmeAlugado &l2){
    return (l1.codAluguel > l2.codAluguel);
}
bool operator<(const filmeAlugado &l1, const filmeAlugado &l2){
    return (l1.codAluguel < l2.codAluguel);
}
bool operator>=(const filmeAlugado &l1, const filmeAlugado &l2){
    return (l1.codAluguel >= l2.codAluguel);
}
bool operator<=(const filmeAlugado &l1, const filmeAlugado &l2){
    return (l1.codAluguel <= l2.codAluguel);
}


/*------------------------------------------------------------------------------ */


template <typename T>
void inicializarLDE( LDE <T> &lista ){
    lista.comeco = NULL;
    lista.fim = NULL;
}

template <typename T>
bool inserirFinalLDE( LDE <T> &lista, T valor ){
    No <T> *novo = new No <T>;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->eloA = NULL;
    novo->eloP = NULL;

    if( lista.comeco == NULL ){ // Caso 1 - lista vazia
        lista.comeco = novo;
        lista.fim = novo;
    }
    else{   // Caso 2 - Inserir no final
        lista.fim->eloP = novo;
        novo->eloA = lista.fim;
        lista.fim = novo;
    }
    return true;
}

template <typename T>
bool inserirLDE(LDE <T> &lista, T valor){
    No <T> *novo = new No <T>;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->eloA = NULL;
    novo->eloP = NULL;

    if( lista.comeco == NULL ){ // Caso A
        lista.comeco = novo;
        lista.fim = novo;
    }
    else if( valor <= lista.comeco->info ){ // Caso B
        novo->eloP = lista.comeco;
        lista.comeco->eloA = novo;
        lista.comeco = novo;
    }
    else if( valor > lista.fim->info ){ // Caso C
        lista.fim->eloP = novo;
        novo->eloA = lista.fim;
        lista.fim = novo;
    }
    else{ // Caso D
        No <T> *aux = lista.comeco;
        while( aux != NULL ){
            No <T> *prox = aux->eloP;
            if( aux->info <= valor && valor < prox->info ){
                aux->eloP = novo;
                prox->eloA = novo;
                novo->eloA = aux;
                novo->eloP = prox;
                break;
            }
            aux = aux->eloP;
        }
    }
    return true;
}

template <typename T>
bool retirarLDE( LDE <T> &lista, T valor ){
    if( lista.comeco == NULL ) return false;
    No <T> *aux, *ant, *prox;

    if( valor == lista.comeco->info ){
        aux = lista.comeco;
        if( valor == lista.fim->info ){ // Caso a
            lista.comeco = NULL;
            lista.fim = NULL;
        }
        else{ // Caso b
            lista.comeco = aux->eloP;
            lista.comeco->eloA = NULL;
        }
    }
    else{
        if( valor == lista.fim->info ){ // Caso c
            aux = lista.fim;
            lista.fim = aux->eloA;
            lista.fim->eloP = NULL;
        }
        else{ // Caso d
            aux = lista.comeco;
            while( aux != NULL ){
                if( aux->info == valor ){
                    ant = aux->eloA;
                    prox = aux->eloP;
                    ant->eloP = prox;
                    prox->eloA = ant;
                    break;
                }
                aux = aux->eloP;
            }
            if( aux == NULL ) return false;
        }
    }

    delete aux;
    return true;
}

template <typename T>
void mostrarLDE(LDE <T> lista, char ordem){
    if( ordem == 'C' || ordem == 'c' ){
        No <T> *aux = lista.comeco;
        while( aux != NULL ){
            cout << aux->info << " ";
            aux = aux->eloP; // Avan�a para o pr�ximo no
        }
    } else {
        No <T> *aux = lista.fim;
        while( aux != NULL ){
            cout << aux->info << " ";
            aux = aux->eloA; // Avan�a para o no anterior
        }
    }
}

template <typename T>
void liberarLDE(LDE <T> &lista){
    No <T> *temp, *aux = lista.comeco;
    while( aux != NULL ){
        temp = aux;
        aux = aux->eloP;
        delete temp;
    }
    lista.comeco = lista.fim = NULL;
}

// Retornar true se o valor for encontrado ou false se n�o estiver na lista
// **********
template <typename T>
bool pesquisarLDE(LDE <T> lista, T valor){
    No <T> *aux = lista.comeco;
    while( aux != NULL ){
        if( aux->info == valor ) return true;
        aux = aux->eloP;
    }
    return false;
}



