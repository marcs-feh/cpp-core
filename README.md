# C++ Core

This is a collection of C++20 utilities, they are not a replacement for the STL,
although I use them as *alternatives*.

The current main design goals are:

- Avoid OOP madness
- No `throw`s or weird control flow, prioritize returning errors whenever possible
- Containers that are friendly towards custom allocators
- Expose internals for users who wish to tinker, but do not force it upon them
- Avoid excessive templating
- No `delete[]`, use slices instead
- Be able to glue everything into one `.cpp` file
- Test coverage

Design non-goals:

- Fully replace the STL (even if I wanted it is impossible without modifying the compiler)
- System libraries for threading, I/O or networking
- API stability (you must recompile your code periodically, but I won't go out of my way yo break things)

## Build

Regular build + tests

```
$ make run
```

Sanitized build
```
$ make CFLAGS='-g -fsanitize=address' LDFLAGS='-lasan -lubsan' run
```

```sh
Bundle(){
    echo '#ifndef _core_hpp_include_'
    echo '#define _core_hpp_include_'
    for header in $(find | sed 's:^\./::' | grep '\.hpp' | grep -v '_core'); do
        echo "#include \"$header\""
    done
    echo '#endif /* Include guard */'
}
Bundle > _core.hpp
```

