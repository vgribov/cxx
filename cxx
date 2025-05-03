#!/bin/sh

cxx_target=${CXX_TARGET:-${PWD##*/}}
cxx_default_flags="-std=c++23 -Wall -Wextra -Werror"
cxx_flags="${CXXFLAGS:-$cxx_default_flags} $LDFLAGS"
if [ -n "$LDFLAGS" ]; then
    cxx_flags="$cxx_flags $LDFLAGS"
fi
cxx_fsanitize="-fsanitize=undefined,address"
cxx_prefix="out"

usage() {
    echo "Usage:"
    echo "  ${0##*/} build           - builds a normal binary"
    echo "  ${0##*/} build --release - builds a release binary"
    echo "  ${0##*/} build --debug   - builds a binary with debug info"
    echo
    echo "  ${0##*/} build test - run tests"
    echo
    echo "  ${0##*/} build doc - build documentation"
    echo
    echo "  ${0##*/} build init - initialize project directory"
}

for arg in "$@"; do
    case $arg in
        --release)
            build_type=release
            ;;
        --debug)
            build_type=debug
            ;;
        --help|-h)
            usage
            exit 0
            ;;
        *)
            if [ -z "$cmd" ]; then
                cmd=$arg
            else
                args="$args $arg"
            fi
            ;;
    esac
    shift
done

_clang() {
    echo "clang++ $@"
    clang++ "$@"
}

do_build() {
    local src=$(find . -iname '*.cpp' -or -iname '*.cc')
    if [ -z "$src" ]; then
        echo "No source files found." >&2
        return 1
    fi

    local prefix="$cxx_prefix"
    local clang_args="$cxx_flags"
    case $build_type in
        release)
            prefix="$prefix/release"
            clang_args="$clang_args -DNDEBUG -O3"
            ;;
        debug)
            prefix="$prefix/debug"
            clang_args="$clang_args -g $cxx_fsanitize"
            ;;
        *)
            clang_args="$clang_args -O1 $cxx_fsanitize"
            ;;
    esac
    clang_args="$clang_args"

    mkdir -p $prefix
    _clang $clang_args -o "$prefix/$cxx_target" $src
}

do_test() {
    echo TODO
}

do_doc() {
    echo TODO
}

case "$cmd" in
    build)
        do_build
        ;;
    test)
        do_test
        ;;
    doc)
        do_doc
        ;;
    *)
        usage
        exit 1
        ;;
esac
