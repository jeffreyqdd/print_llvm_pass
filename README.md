# llvm-pass-skeleton

A toy LLVM pass that prints out function names and their arguments to stderr when called. 


    $ cd llvm-pass-skeleton
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run (fish):
```fish
llvm_dir=(brew --prefix llvm) $llvm_dir/bin/clang -fpass-plugin=./build/skeleton/SkeletonPass.dylib -g runtime/rt.c examples/fibonnaci.c
```

Sample output on fibonacci.c:
```
llvm: calling function: parse_user_input@examples/fibonacci.c:18()
llvm: calling function: printf@examples/fibonacci.c:5(Enter an integer: , )
llvm: calling function: scanf@examples/fibonacci.c:6(%d, , )
Enter an integer: 5
llvm: calling function: fibonacci@examples/fibonacci.c:19(5, )
llvm: calling function: fibonacci@examples/fibonacci.c:14(4, )
llvm: calling function: fibonacci@examples/fibonacci.c:14(3, )
llvm: calling function: fibonacci@examples/fibonacci.c:14(2, )
llvm: calling function: fibonacci@examples/fibonacci.c:14(1, )
llvm: calling function: fibonacci@examples/fibonacci.c:14(0, )
llvm: calling function: fibonacci@examples/fibonacci.c:14(1, )
llvm: calling function: fibonacci@examples/fibonacci.c:14(2, )
llvm: calling function: fibonacci@examples/fibonacci.c:14(1, )
llvm: calling function: fibonacci@examples/fibonacci.c:14(0, )
llvm: calling function: fibonacci@examples/fibonacci.c:14(3, )
llvm: calling function: fibonacci@examples/fibonacci.c:14(2, )
llvm: calling function: fibonacci@examples/fibonacci.c:14(1, )
llvm: calling function: fibonacci@examples/fibonacci.c:14(0, )
llvm: calling function: fibonacci@examples/fibonacci.c:14(1, )
llvm: calling function: printf@examples/fibonacci.c:19(fibonacci(%d) = %lld\n, 5, 5, )
fibonacci(5) = 5
```

Sample output on a frame buffer I wrote in C:

```
// writing process
llvm: calling function: __memcpy_chk@lib/c/buffer.c:79(�����������..., , �����������..., , 6220800, -1, )
llvm: calling function: _pthread_rwlock_unlock@lib/c/buffer.c:86(KLWR, )
llvm: calling function: pthread_mutex_lock@lib/c/buffer.c:91(ZTUM, )
llvm: calling function: pthread_cond_broadcast@lib/c/buffer.c:92(ENOC, )
llvm: calling function: pthread_mutex_unlock@lib/c/buffer.c:93(ZTUM, )
llvm: calling function: _pthread_rwlock_wrlock@lib/c/buffer.c:75(KLWR, )
llvm: calling function: buffer_image_size@lib/c/buffer.c:78(, )
llvm: calling function: llvm.objectsize.i64.p0@lib/c/buffer.c:79(�����������..., , any, any, any, )
llvm: calling function: __memcpy_chk@lib/c/buffer.c:79(�����������..., , �����������..., , 6220800, -1, )
llvm: calling function: _pthread_rwlock_unlock@lib/c/buffer.c:86(KLWR, )
llvm: calling function: pthread_mutex_lock@lib/c/buffer.c:91(ZTUM, )
llvm: calling function: pthread_cond_broadcast@lib/c/buffer.c:92(ENOC, )
llvm: calling function: pthread_mutex_unlock@lib/c/buffer.c:93(ZTUM, )

// reading process
latency ms: 1    llvm: calling function: pthread_mutex_lock@lib/c/buffer.c:103(ZTUM, )
llvm: calling function: buffer_image_size@lib/c/buffer.c:110(�, )
llvm: calling function: realloc@lib/c/buffer.c:109(�����������..., , 6220800, )
llvm: calling function: _pthread_cond_wait@lib/c/buffer.c:142(ENOC, ZTUM, )
llvm: calling function: _pthread_rwlock_tryrdlock@lib/c/buffer.c:153(KLWR, )
llvm: calling function: pthread_mutex_unlock@lib/c/buffer.c:162(ZTUM, )
llvm: calling function: frame_image_size@lib/c/buffer.c:165(�, )
llvm: calling function: llvm.objectsize.i64.p0@lib/c/buffer.c:168(�����������..., , any, any, any, )
llvm: calling function: __memcpy_chk@lib/c/buffer.c:168(�����������..., , �����������..., , 6220800, -1, )
llvm: calling function: _pthread_rwlock_unlock@lib/c/buffer.c:170(KLWR, )
latency ms: 1    llvm: calling function: pthread_mutex_lock@lib/c/buffer.c:103(ZTUM, )
llvm: calling function: buffer_image_size@lib/c/buffer.c:110(�, )
llvm: calling function: realloc@lib/c/buffer.c:109(�����������..., , 6220800, )
llvm: calling function: _pthread_cond_wait@lib/c/buffer.c:142(ENOC, ZTUM, )
llvm: calling function: _pthread_rwlock_tryrdlock@lib/c/buffer.c:153(KLWR, )
llvm: calling function: pthread_mutex_unlock@lib/c/buffer.c:162(ZTUM, )
llvm: calling function: frame_image_size@lib/c/buffer.c:165(�, )
llvm: calling function: llvm.objectsize.i64.p0@lib/c/buffer.c:168(�����������..., , any, any, any, )
llvm: calling function: __memcpy_chk@lib/c/buffer.c:168(�����������..., , �����������..., , 6220800, -1, )
llvm: calling function: _pthread_rwlock_unlock@lib/c/buffer.c:170(KLWR, )
latency ms: 1    llvm: calling function: pthread_mutex_lock@lib/c/buffer.c:103(ZTUM, )
llvm: calling function: buffer_image_size@lib/c/buffer.c:110(, )
```
