#ifndef MODULE_H
#define MODULE_H

#define MODULE(name, ...) \
	int name##__moduleInit();\
/*	void _start() { RegisterModuleCallback(name##__ModuleInit, __VA_ARGS__); }*/\
	void _start() { name##__ModuleInit(); };\
	int name##__ModuleInit()


#endif /* end of include guard: MODULE_H */
