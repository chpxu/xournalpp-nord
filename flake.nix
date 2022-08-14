{
    description = "Xournal++ Flake with Nordic settings and theme.";

    inputs = {
        nixpkgs.url = github:NixOS/nixpkgs/nixos-22.05;
        xournalpp = {
            type = "github";
            owner = "chpxu";
            repo = "xournalpp";
            rev = "11764dcd5ea4948dede9639d843d719e920b6814";
        };
    };

  outputs = { self, nixpkgs, xournalpp }: {
    packages.x86_64-linux.xournalpp =
      # Notice the reference to nixpkgs here.
      with import nixpkgs { system = "x86_64-linux"; };
      stdenv.mkDerivation {
        name = "xournalpp";
        src = xournalpp;
        buildInputs = [
            cmake
            glib
            pkg-config
            gtk3
            gettext
            wrapGAppsHook
            librsvg
            libsndfile
            libxml2
            libzip
            pcre
            poppler
            portaudio
            zlib
        ];
      };
  };
}
