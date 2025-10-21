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