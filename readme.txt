Smaller C is a simple and small single-pass C compiler.

Currently it generates 16-bit and 32-bit 80386+ assembly code for NASM
that can then be assembled and linked into DOS, Windows and Linux programs.

Code generation for MIPS CPUs is also supported.

This version is also capable of generating code for the Uni Stuttgart Hapra CPU, which 
slightly resembles a MIPS. The backend is therefore just a butcherd version of the MIPS 
codegen.

The compiler is capable of compiling its own source code.

See the Wiki for more up-to-date details:
https://github.com/alexfru/SmallerC/wiki
