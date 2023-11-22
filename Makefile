all: libnss_netdependent.so.2 libnss_debug.so.2
.PHONY: install

libnss_debug.so.2: debug.c
	gcc -o $@ -shared -Wl,-soname,libnss_debug.so.2 $^

libnss_netdependent.so.2: netdependent.c
	#-Wall -Wstrict-prototypes -Werror -fPIC
	#-fPIC
	gcc -o $@ -shared -Wl,-soname,libnss_netdependent.so.2 $^

install: libnss_netdependent.so.2 libnss_debug.so.2
	mkdir -p "$$out"
	install -m 755 -d "$$out/lib"
	install -m 555 libnss_netdependent.so.2 "$$out/lib/"
	install -m 555 libnss_debug.so.2 "$$out/lib/"
	chmod 555 "$$out/lib"
