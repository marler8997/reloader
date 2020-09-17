const std = @import("std");

const reloader = @import("./reloader.zig");

extern fn foopassthru(i32) i32;

pub fn main() void {
    reloader.reload();
    std.debug.warn("in main\n", .{});
    std.debug.warn("foopassthru(1234) = {}\n", .{foopassthru(1234)});
    std.debug.warn("Success\n", .{});
}