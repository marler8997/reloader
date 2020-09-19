# reloader

Experiment to test the viability of embedding a "distribution compatible bootstrap loader" into executables rather than making use of the ELF interpreter feature.

# The Problem

When an ELF executable needs shared libraries, it a configures dynamic loader to take care of loading the shared libraries before jumping to the entry function of the executable.  The kernel searches for the dynamic loader program in the ELF `.interp` section.

The problem with this is that the dynamic loader must be an absolute file path, but linux distributions don't store the ELF dynamic loader in the same place and some systems require multiple loaders (i.e. one for 32 and 64 bit executables). This means that if developers want their program to work on multiple distributions, they don't have much choice except to compile their executable statically with all their dependencies embedded in their final binary.

# How Reloader Works

The "reloader" mechanism omits the ELF interpreter section and instead, includes bootstrap code to find an invoke the system's actual dynamic loader.

# References

Related issue: https://github.com/ziglang/zig/issues/6350
