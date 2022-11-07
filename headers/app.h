#ifndef _APP_
#define _APP_

typedef struct tApp App;

App *InicializaApp(char *artistascsv, char *musicascsv);

void *LiberaApp(App *app);

void RodaApp();

#endif
