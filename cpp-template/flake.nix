{

description = "Example flake with a devShell";

inputs.nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";

outputs =
{ self, nixpkgs }:
let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };
in
{
    devShells.x86_64-linux.default = pkgs.mkShell {
    buildInputs = with pkgs; [
        gcc
        glfw3
        sdl2-compat
        cmake
        clang-tools
        raylib
    ];
    shellHook = ''
        echo "Welcome to the devShell!"
    '';
    };
};

}
