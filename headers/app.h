#ifndef _APP_
#define _APP_

#include "lista.h"
#include "repositorio_artistas.h"
#include "repositorio_musicas.h"

typedef struct tApp App;

App *InicializaApp(const char *artistascsv, const char *musicascsv);

void *LiberaApp(App *app);

RepoMusicas *GetRepoMusicasApp(App *app);

RepoArtistas *GetRepoArtistasApp(App *app);

Lista *GetPlaylistsApp(App *app);

void SetMusicasApp(App *app, Lista *mscs);

void RodaApp(App *app);

#endif
