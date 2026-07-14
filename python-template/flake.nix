{

description = "Pythong Development Shell";

inputs.nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";

outputs =
{ self, nixpkgs }:
let
    system = "x86_64-linux";
    run = pkgs.writeShellScriptBin "run" "python3 src/main.py";

    pkgs = import nixpkgs { inherit system; };
in
{

    devShells.x86_64-linux.default = pkgs.mkShell {
        buildInputs = with pkgs; [
            python3
            run
        ];
        shellHook = ''
            echo "Welcome to the devShell!"
        '';
    };
};

}
