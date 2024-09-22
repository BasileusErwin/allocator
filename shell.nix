{
  pkgs ? import <nixpkgs> { },
}:

pkgs.mkShell {
  buildInputs = with pkgs; [
    cmake
    cmake-format
    check
    gcc
    pkg-config
    git
    bear
    valgrind
    gdb
  ];
}
