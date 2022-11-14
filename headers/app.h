#ifndef _APP_
#define _APP_

typedef struct tApp App;

App *InicializaApp(const char *artistascsv, const char *musicascsv);

void *LiberaApp(App *app);

void RodaApp();

void SairApp();

#endif
