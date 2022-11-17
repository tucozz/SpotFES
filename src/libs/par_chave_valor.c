#include <stdlib.h>

#include "par_chave_valor.h"

struct tParChaveValor {
    void *chave;
    void *valor;
    void (*liberaChave)(void *);
    void (*liberaValor)(void *);
};

ParChaveValor *InicializaParCV(void *chave, void *valor,
                               void (*liberaChave)(void *),
                               void (*liberaValor)(void *)) {
    ParChaveValor *par = malloc(sizeof *par);

    par->chave = chave;
    par->valor = valor;
    par->liberaChave = liberaChave;
    par->liberaValor = liberaValor;

    return par;
}

void LiberaParCV(ParChaveValor *par) {
    par->liberaChave(par->chave);
    par->liberaValor(par->valor);

    free(par);
}

void *GetChaveParCV(ParChaveValor *par) { return par->chave; }

void *GetValorParCV(ParChaveValor *par) { return par->valor; }

void **GetPtrValorParCV(ParChaveValor *par) { return &(par->valor); }

size_t SizeofParCV() { return sizeof(ParChaveValor); }