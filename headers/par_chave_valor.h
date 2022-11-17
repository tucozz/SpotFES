#ifndef _PAR_CHAVE_VALOR_
#define _PAR_CHAVE_VALOR_

typedef struct tParChaveValor ParChaveValor;

ParChaveValor *InicializaParCV(void *chave, void *valor,
                               void (*liberaChave)(void *),
                               void (*liberaValor)(void *));

void LiberaParCV(ParChaveValor *par);

void *GetChaveParCV(ParChaveValor *par);

void *GetValorParCV(ParChaveValor *par);

void *SetValorParCV(ParChaveValor *par, void *val);

void **GetPtrValorParCV(ParChaveValor *par);

size_t SizeofParCV();

#endif
