#ifndef SHUTDOWN_H
#define SHUTDOWN_H

#include <metodo/metodo.h>

#define SD_REBOOT 1
#define SD_OFF 2
#define SD_WAIT 3

void CoShutdown(int mode);

#include <text.h>

#endif /* end of include guard: SHUTDOWN_H */
