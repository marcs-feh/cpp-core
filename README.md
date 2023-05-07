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
