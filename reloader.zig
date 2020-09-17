const std = @import("std");

pub fn reload() void {
    std.debug.warn("reload called!\n", .{});

    // TODO: need a way to check if we have already been reloaded
    const alreadyReloaded = false;
    if (alreadyReloaded)
        return;
    doReload();
}
fn doReload() noreturn {
    // TODO: check an environment variable for the linker...maybe there is already one defined for this?

    // this means we are going to be reloaded, so we can allocate as much memory as we want
    // without freeing
    // todo: probably use arena allocator?
    const allocator = std.heap.page_allocator;
    const info = std.zig.system.NativeTargetInfo.detect(allocator, .{}) catch |e| switch (e) {
        else => std.debug.panic("failed to detect abi and dynamic linker: {}", .{e}),
    };
    std.debug.warn("target '{}'\n", .{info.target});
    const dynamic_linker = info.dynamic_linker.get();
    // TODO: do I need to handle errors here?

    std.debug.warn("dynamic_linker '{}'\n", .{dynamic_linker});
    // TODO: can the dynamic linker be empty?
    @panic("reload not fully implemented");
}
