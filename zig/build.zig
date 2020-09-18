const std = @import("std");
const Builder = std.build.Builder;

pub fn build(b: *Builder) !void {
    const mode = b.standardReleaseOptions();
    const target = b.standardTargetOptions(.{});
    const lib = b.addSharedLibrary("foo", "foo.zig", b.version(0, 0, 0));
    lib.setBuildMode(mode);
    lib.setTarget(target);
    lib.install();

    const exe = b.addExecutable("app", "app.zig");
    exe.setBuildMode(mode);
    exe.setTarget(target);
    exe.linkLibrary(lib);
    // NOTE: we don't use libc but it fixes an issue with the zig compiler
    //       where it's not making the exe dynamic: https://github.com/ziglang/zig/issues/6368
    // TODO: note that when this issue is fixed, I can probably simulate no linker by
    //       removing the interp section with patchelf
    // maybe objcopy --remove-section .interp?
    //     this doesn't seem to work, I get an exec format error
    exe.linkSystemLibrary("c");
    exe.install();
}
