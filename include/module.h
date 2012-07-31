#ifndef MODULE_H
#define MODULE_H

#include <metodo/misc/modules.h>

#define MODULE(name, ...) \
	int name##__ModuleInit();\
	/*void _start() { RegisterModuleCallback(name##__ModuleInit, #name, ##__VA_ARGS__); }*/\
	void _start() { name##__ModuleInit(); };\
	int name##__ModuleInit()


#endif /* end of include guard: MODULE_H */
