# libsha
Library from a personal student study on different SHA algorithms for Linux.

If you receive the following message:
```
./hashverif: error while loading shared libraries: libsha.so: cannot open shared object file: No such file or directory
```
Please try setting the 'LD_LIBRARY_PATH' environment variable as shown below:
```
$export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH
```