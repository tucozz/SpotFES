#include <stdlib.h>
#include <string.h>

#include "procurador.h"

#include "dicionario.h"
#include "par_chave_valor.h"
#include "playlist.h"

void CompletaMusica(Musica *msc, RepoArtistas *repo) {
    if (GetMscArtists(msc) != NULL)
        return;

    Lista *artistas = InicializaLista();  // Lista<artista>
    Lista *hashes = GetMscArtistsId(msc); // Lista<string>

    int n = GetQuantidadeLista(hashes);
    for (int i = 0; i < n; i++) {
        char *hash = AdquireElementoLista(hashes, i);
        Artista *art = EncontraPeloHashRepoArtistas(repo, hash);
        AdicionaElementoLista(artistas, art);
    }

    IncluiMscArtistas(msc, artistas);
    LiberaLista(artistas, &LiberaArtista);
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
        AdicionaElementoLista(musicas, msc);
    }

    IncluiMusicasPlaylist(playlist, musicas);
    LiberaLista(musicas, &LiberaMusica);
}

Lista *RecomendaMusicas(Playlist *playlist, int k, RepoMusicas *repo) {
    CompletaPlaylist(playlist, repo);

    Musica *ideal = NULL; // TODO: CalculaMusicaIdeal(playlist);

    // Dicionario<string, float>
    Dicionario *hashDistancia = InicializaDicionario(&strcmp, &free, &free);
    // Dicionario<string, Musica *>
    Dicionario *hashMusica =
        InicializaDicionario(&strcmp, &free, &LiberaMusica);

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
    for (Musica *msc = ProximoIteradorRepoMsc(itr); !FimIteradorRepoMsc(itr);
         msc = ProximoIteradorRepoMsc(itr)) {
        if (EncontraLista(GetMusicasIdPlaylist(playlist), GetMscId(msc),
                          &strcmp) == -1) {
            LiberaMusica(msc);
            continue;
        }

        float distanciaDaIdeal = SemelhancaMusicas(ideal, msc);

        if (GetQuantidadeLista(hashDistanciaLista) < k) {
            char *hash = GetMscId(msc);
            void **hshDistVal =
                GetValorDicionario(hashDistancia, hash, &strdup);
            if (*hshDistVal == NULL) {
                *hshDistVal = malloc(sizeof(float));
                *((float *)*hshDistVal) = distanciaDaIdeal;
            }

            void **hshMscVal = GetValorDicionario(hashMusica, hash, &strdup);
            if (*hshMscVal == NULL)
                *hshMscVal = msc;
            else
                LiberaMusica(msc);

            // TODO: ordena hashDistanciaLista

            break;
        }

        // ParChaveValor<string, float>
        ParChaveValor *maisDistante = PopLista(hashDistanciaLista);
        if (*(float *)GetValorParCV(maisDistante) > distanciaDaIdeal) {

            char *hash = GetMscId(msc);
            void **hshDistVal =
                GetValorDicionario(hashDistancia, hash, &strdup);
            if (*hshDistVal == NULL) {
                *hshDistVal = malloc(sizeof(float));
                *((float *)*hshDistVal) = distanciaDaIdeal;

                LiberaParCV(maisDistante);
            } else {
                AdicionaElementoLista(hashDistanciaLista, maisDistante);
                LiberaMusica(msc);
                continue;
            }

            // TODO: ordena hashDistanciaLista

            void **hshMscVal = GetValorDicionario(hashMusica, hash, &strdup);
            if (*hshMscVal == NULL)
                *hshMscVal = msc;
            else
                LiberaMusica(msc);
        } else
            AdicionaElementoLista(hashDistanciaLista, maisDistante);
    }

    Lista *mscsRecomendadas = InicializaLista(); // Lista<Musica *>

    int n = GetQuantidadeLista(hashDistanciaLista);
    for (int i = 0; i < n; i++) {
        // ParChaveValor<string, float>
        ParChaveValor *curr = AdquireElementoLista(hashDistanciaLista, i);
        char *hash = GetChaveParCV(curr);

        void **hshMscVal = GetValorDicionario(hashMusica, hash, &strdup);
        if (*hshMscVal != NULL)
            AdicionaElementoLista(mscsRecomendadas, *hshMscVal);
    }

    LiberaDicionario(hashDistancia);
    LiberaDicionario(hashMusica);

    return mscsRecomendadas;
}
