load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def load_deps():
    maybe(
        http_archive,
        name="libigl",
        build_file = Label("//deps/libigl:BUILD.bazel"),
        strip_prefix = "libigl-2.5.0",
        url = "https://github.com/libigl/libigl/archive/refs/tags/v2.5.0.zip",
        # sha256 = "28772c1155aebd71f818ae43e29427571c4faa5e9cdda3b44b1d2c2dc64297f5",
    )

    maybe(
        http_archive,
        name="imgui",
        build_file = Label("//deps/imgui:BUILD.bazel"),
        strip_prefix = "imgui-1.90.5",
        url = "https://github.com/ocornut/imgui/archive/refs/tags/v1.90.5.zip",
        # sha256 = "28772c1155aebd71f818ae43e29427571c4faa5e9cdda3b44b1d2c2dc64297f5",
    )

    maybe(
        http_archive,
        name="imguizmo",
        build_file = Label("//deps/imguizmo:BUILD.bazel"),
        strip_prefix = "ImGuizmo-1.83",
        url = "https://github.com/CedricGuillemet/ImGuizmo/archive/refs/tags/1.83.zip",
        # sha256 = "28772c1155aebd71f818ae43e29427571c4faa5e9cdda3b44b1d2c2dc64297f5",
    )

    maybe(
        http_archive,
        name="unvpp",
        build_file = Label("//deps/unvpp:BUILD.bazel"),
        strip_prefix = "unvpp-01d972e9126bf98c30b3b36cb0f5d7c8db4515d2",
        url = "https://github.com/eigemx/unvpp/archive/01d972e9126bf98c30b3b36cb0f5d7c8db4515d2.zip",
        # sha256 = "28772c1155aebd71f818ae43e29427571c4faa5e9cdda3b44b1d2c2dc64297f5",
    )

    maybe(
        http_archive,
        name="fast_float",
        build_file = Label("//deps/fast_float:BUILD.bazel"),
        strip_prefix = "fast_float-6.1.1",
        url = "https://github.com/fastfloat/fast_float/archive/refs/tags/v6.1.1.zip",
        # sha256 = "28772c1155aebd71f818ae43e29427571c4faa5e9cdda3b44b1d2c2dc64297f5",
    )

    # maybe(
    #     http_archive,
    #     name="rules_python",
    #     url = "https://github.com/bazelbuild/rules_python/archive/refs/tags/0.31.0.zip"
    # )

    # maybe(
    #     http_archive,
    #     name="Eigen",
    #     build_file = Label("//deps/Eigen:BUILD.bazel"),
    #     strip_prefix = "eigen-3.4.0",
    #     url = "https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.zip",
    #     # sha256 = "28772c1155aebd71f818ae43e29427571c4faa5e9cdda3b44b1d2c2dc64297f5",
    # )


