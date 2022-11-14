#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"

#include "repositorio_artistas.h"

#include "repositorio_musicas.h"
#include "repositorio_playlists.h"

int main(int argc, char *argv[]) {
    if (argc != 3)
        return EXIT_FAILURE;

    /* App *app = InicializaApp(argv[1], argv[2]);

    RodaApp(app);

    LiberaApp(app);

    return EXIT_SUCCESS; */

    RepoMusicas *repomscs = InicializaRepoMusicas(argv[1]);
    char query[] = "baby";
    Lista *mscs = EncontraPeloNomeRepoMusica(repomscs, query); // Lista<musica>

    Lista *mscs1 = InicializaLista(); // Lista<musica>
    AdicionaElementoLista(mscs1, CopiaMusica(AdquireElementoLista(mscs, 0)));
    AdicionaElementoLista(mscs1, CopiaMusica(AdquireElementoLista(mscs, 1)));

    Lista *mscs1_id = InicializaLista(); // Lista<string>
    AdicionaElementoLista(mscs1_id,
                          strdup(GetMscId(AdquireElementoLista(mscs, 0))));
    AdicionaElementoLista(mscs1_id,
                          strdup(GetMscId(AdquireElementoLista(mscs, 1))));

    Lista *mscs2 = InicializaLista(); // Lista<musica>
    AdicionaElementoLista(mscs2, CopiaMusica(AdquireElementoLista(mscs, 2)));
    AdicionaElementoLista(mscs2, CopiaMusica(AdquireElementoLista(mscs, 3)));

    Lista *mscs2_id = InicializaLista(); // Lista<string>
    AdicionaElementoLista(mscs2_id,
                          strdup(GetMscId(AdquireElementoLista(mscs, 2))));
    AdicionaElementoLista(mscs2_id,
                          strdup(GetMscId(AdquireElementoLista(mscs, 3))));

    char nome1[] = "biber so as melhores";
    Playlist *pl1 = InicializaPlaylist(nome1, mscs1_id);
    IncluiMusicasPlaylist(pl1, mscs1);
    char nome2[] = "just_in after";
    Playlist *pl2 = InicializaPlaylist(nome2, mscs2_id);
    IncluiMusicasPlaylist(pl1, mscs2);

    LiberaLista(mscs, &LiberaMusica);
    LiberaLista(mscs1, &LiberaMusica);
    LiberaLista(mscs2, &LiberaMusica);
    LiberaLista(mscs1_id, &free);
    LiberaLista(mscs2_id, &free);

    Lista *pls = InicializaLista(); // Lista<playlist>
    AdicionaElementoLista(pls, CopiaPlaylist(pl1));
    AdicionaElementoLista(pls, CopiaPlaylist(pl2));

    LiberaPLaylist(pl1);
    LiberaPLaylist(pl2);

    SalvaTodasPlaylistsRepo(pls);

    LiberaLista(pls, &LiberaPLaylist);

    Lista *plscarr = CarregaTodasPlaylistsRepo(); // Lista<playlist>

    LiberaLista(plscarr, &LiberaPLaylist);

    LiberaRepoMusicas(repomscs);
}
