build:
	raco ctool --c-mods base.c ++lib racket/base
	gcc -o embd -I /usr/include/racket -ldl -lm -lffi -lpthread embd.c ../racket-6.1/src/racket/libracket3m.a
win:
	raco ctool --c-mods base.c ++lib racket/base ++lib racket/tcp ++lib racket/lang/reader
	i686-w64-mingw32-gcc -o embd.exe -I /usr/include/racket/ embd.c msvc/libracket3m_9xtikg.lib
