const std = @import("std");

// TODO: maybe provide a way to see which dynamic linker is being used?  although, one could just use strace to find out.
// TODO: maybe environment variable to enable debug output?

pub fn reload() void {
    std.debug.warn("RELOADER: called\n", .{});
    //for (std.os.argv) |arg, i| {
    //    std.debug.warn("RELOADER: [{}] '{}'\n", .{i, arg});
    //}
    //for (std.os.environ) |env, i| {
    //    std.debug.warn("RELOADER: {}\n", .{env});
    //}

    // TODO: need a way to check if we have already been reloaded
    //       there is probably a way to check this by inspecting the dll function addresses
    //       but for now I'm just going to use an environment variable as a proof of concept
    if (!eql(std.os.environ[0], "__RELOADED__=1")) {
        std.debug.warn("RELOADER: '__RELOADED__=1' env not found, will reload\n", .{});
        doReload();
    }
    // TODO: remove the __RELOADED__=1 environment variable
    //std.os.environ = std.os.environ[1..];
}

// TODO: is this in standard lib somewhere?
fn eql(a: [*]const u8, b: [*]const u8) bool {
    var i : usize = 0;
    while (true) : (i += 1) {
        if (a[i] != b[i])
            return false;
        if (a[i] == 0)
            return true;
    }
}

fn getDynamicLinker(allocator: *std.mem.Allocator) [*:0]const u8 {
    const slice : [:0]const u8 = "/nix/store/xg6ilb9g9zhi2zg1dpi4zcp288rhnvns-glibc-2.30/lib/ld-linux-x86-64.so.2";
    return slice.ptr;

//    this code isn't working, so just hardcoding my system's dynamic linker for now above
//    const info = std.zig.system.NativeTargetInfo.detect(allocator, .{}) catch |e| switch (e) {
//        else => std.debug.panic("failed to detect abi and dynamic linker: {}", .{e}),
//    };
//    // don't worry about releasing the memory
//    std.debug.warn("RELOADER: target '{}'\n", .{info.target});
//    const dynamic_linker = info.dynamic_linker.get() orelse {
//        @panic("failed to get dynamic linker");
//    };
//    std.debug.warn("RELOADER: dynamic_linker '{}'\n", .{dynamic_linker});
//    const dynamic_linkerz = allocator.allocSentinel(u8, dynamic_linker.len, 0) catch |e|
//        std.debug.panic("{}", .{e});
//    std.mem.copy(u8, dynamic_linkerz, dynamic_linker);
//    return dynamic_linkerz;
}

fn doReload() noreturn {
    // TODO: check an environment variable for the linker...maybe there is already one defined for this?

    // this means we are going to be reloaded, so we can allocate as much memory as we want
    // without freeing
    // todo: probably use arena allocator?
    const allocator = std.heap.page_allocator;

    const dynamic_linker = getDynamicLinker(allocator);
    std.debug.warn("RELOADER: dynamic linker '{}'\n", .{dynamic_linker});

    // allocSentinel won't work, see https://github.com/ziglang/zig/issues/6370
    const argv = allocator.alloc(?[*:0]const u8, std.os.argv.len + 2) catch |e|
        std.debug.panic("{}", .{e});
    argv[0] = dynamic_linker;
    for (std.os.argv) |arg, i| {
        argv[i+1] = arg;
    }
    argv[argv.len - 1] = null;

    //
    // Copy environment variables so we can add __RELOADED__=1 to temporarily
    // indicate that we have been reloaded, until a better way can be found
    //
    // allocSentinel wont' work, see https://github.com/ziglang/zig/issues/6370
    const envp = allocator.alloc(?[*:0]u8, std.os.environ.len + 2) catch |e| std.debug.panic("{}", .{e});
    envp[0] = "__RELOADED__=1";
    for (std.os.environ) |env, i| {
        envp[i+1] = env;
    }
    envp[std.os.environ.len - 1] = null;

    std.debug.warn("RELOADER: calling execve!\n", .{});
    const e = std.os.execveZ(
        dynamic_linker,
        @ptrCast([*:null]?[*:0]u8, argv.ptr),
        @ptrCast([*:null]const ?[*:0]const u8, envp));
    std.debug.panic("{}", .{e});
}
