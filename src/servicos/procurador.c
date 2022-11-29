#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "procurador.h"

#include "dicionario.h"
#include "exception.h"
#include "par_chave_valor.h"
#include "playlist.h"
#include "types.h"

void CompletaMusica(Musica *msc, RepoArtistas *repo) {
    if (GetMscArtists(msc) != NULL)
        return;

    Lista *artistas = InicializaLista();  // Lista<artista>
    Lista *hashes = GetMscArtistsId(msc); // Lista<string>

    int n = GetQuantidadeLista(hashes);
    for (int i = 0; i < n; i++) {
        char *hash = AdquireElementoLista(hashes, i);
        Artista *art = EncontraPeloHashRepoArtistas(repo, hash);
        if (art != NULL)
            AdicionaElementoLista(artistas, art);
    }

    IncluiMscArtistas(msc, artistas);
    LiberaLista(artistas, (free_fn)&LiberaArtista);
}

void CompletaPlaylist(Playlist *playlist, RepoMusicas *repo) {
    if (GetMusicasPlaylist(playlist) != NULL)
        return;

    Lista *musicas = InicializaLista();             // Lista<musica>
    Lista *hashes = GetMusicasIdPlaylist(playlist); // Lista<string>

    int n = GetQuantidadeLista(hashes);
    for (int i = 0; i < n; i++) {
        char *hash = AdquireElementoLista(hashes, i);
        Musica *msc = EncontraPeloHashRepoMusica(repo, hash);
        if (msc != NULL)
            AdicionaElementoLista(musicas, msc);
    }

    IncluiMusicasPlaylist(playlist, musicas);
    LiberaLista(musicas, (free_fn)&LiberaMusica);
}

static int parcvfloatvalcmp(const ParChaveValor *a, const ParChaveValor *b) {
    float diff = *(float *)GetValorParCV(a) - *(float *)GetValorParCV(b);
    return diff / fabsf(diff);
}

Lista *RecomendaMusicas(Playlist *playlist, int k, RepoMusicas *repo) {
    CompletaPlaylist(playlist, repo);

    Musica *ideal = CriaMusicaMedia(playlist);

    // Dicionario<string, float>
    Dicionario *hashDistancia =
        InicializaDicionario((compar_fn)&strcmp, &free, &free);
    // Dicionario<string, Musica *>
    Dicionario *hashMusica =
        InicializaDicionario(&strcmp, &free, (free_fn)&LiberaMusica);

    // Lista<ParChaveValor<string, float>
    Lista *hashDistanciaLista = GetTodosParesDicionario(hashDistancia);

    // Busca pelas k-musicas mais proximas da playlist;
    //     O codigo ficou demasiadamente grande pois usa o tipo dicionario
    //     desnecessariamente - sendo que poderia ter feito tudo com
    //     Lista<ParChaveValor<string, ???>
    //
    //     Tendo isso em mente, o unico motivo do uso do dicionario seria para
    //     previnir o caso do repositorio possuir mais de um registro da mesma
    //     musica, assim evitando duplicidade no retorno do funcao
    //
    //     Outrossim, o acesso pelo hash no laco for apos esse tambem e uma
    //     facilidade que o dicionario dispos
    FILE *itr = InicioIteradorRepoMsc(repo);
    bool preencheu = false;
    for (Musica *msc = ProximoIteradorRepoMsc(itr);
         msc != NULL || !FimIteradorRepoMsc(itr);
         LiberaMusica(msc), msc = ProximoIteradorRepoMsc(itr)) {
        if (EncontraLista(GetMusicasIdPlaylist(playlist), GetMscId(msc),
                          (compar_fn)&strcmp) != -1)
            continue;

        float distanciaDaIdeal = SemelhancaMusicas(ideal, msc);

        if (GetQuantidadeLista(hashDistanciaLista) < k) {
            char *hash = GetMscId(msc);
            void **hshDistVal =
                GetValorDicionario(hashDistancia, hash, (cpyval_fn)&strdup);
            if (*hshDistVal == NULL) {
                *hshDistVal = malloc(sizeof(float));
                if (*hshDistVal == NULL)
                    throwOutOfMemoryException(
                        "Procurador internal hashDistancia Dicionario value "
                        "malloc failed");

                *((float *)*hshDistVal) = distanciaDaIdeal;
            }

            void **hshMscVal = GetValorDicionario(hashMusica, hash, (cpyval_fn)&strdup);
            if (*hshMscVal == NULL)
                *hshMscVal = CopiaMusica(msc);

            continue;
        }

        if (!preencheu) {
            OrdenaLista(hashDistanciaLista, (compar_fn)&parcvfloatvalcmp);
            preencheu = true;
        }

        // ParChaveValor<string, float>
        ParChaveValor *maisDistante = PopLista(hashDistanciaLista);
        if (*(float *)GetValorParCV(maisDistante) > distanciaDaIdeal) {

            char *hash = GetMscId(msc);
            void **hshDistVal =
                GetValorDicionario(hashDistancia, hash, (cpyval_fn)&strdup);
            if (*hshDistVal == NULL) {
                *hshDistVal = malloc(sizeof(float));
                if (*hshDistVal == NULL)
                    throwOutOfMemoryException(
                        "Procurador internal hashDistancia Dicionario value "
                        "malloc failed");

                *((float *)*hshDistVal) = distanciaDaIdeal;

                LiberaParCV(maisDistante);
            } else {
                AdicionaElementoLista(hashDistanciaLista, maisDistante);
                continue;
            }

            OrdenaLista(hashDistanciaLista, (compar_fn)&parcvfloatvalcmp);

            void **hshMscVal = GetValorDicionario(hashMusica, hash, (cpyval_fn)&strdup);
            if (*hshMscVal == NULL)
                *hshMscVal = CopiaMusica(msc);
        } else
            AdicionaElementoLista(hashDistanciaLista, maisDistante);
    }

    LiberaMusica(ideal);

    Lista *mscsRecomendadas = InicializaLista(); // Lista<Musica *>

    int n = GetQuantidadeLista(hashDistanciaLista);
    for (int i = 0; i < n; i++) {
        // ParChaveValor<string, float>
        ParChaveValor *curr = AdquireElementoLista(hashDistanciaLista, i);
        char *hash = GetChaveParCV(curr);

        void **hshMscVal = GetValorDicionario(hashMusica, hash, (cpyval_fn)&strdup);
        if (*hshMscVal != NULL) {
            AdicionaElementoLista(mscsRecomendadas, CopiaMusica(*hshMscVal));
        }
    }

    LiberaDicionario(hashDistancia);
    LiberaDicionario(hashMusica);

    return mscsRecomendadas;
}
