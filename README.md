# C++ Base

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
Bundle > core.hpp
```
