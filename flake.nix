{
  description = "NSS module to resolve based on currently connected network";
  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          nss-hosts-netdependent =
            nixpkgs.legacyPackages.${system}.stdenv.mkDerivation {
              pname = "nss-hosts-netdependent";
              version = "0.0.1";
              src = ./.;
            };
        in
        {
          defaultPackage = nss-hosts-netdependent;
        }
      ) // {
        nixosModule = { config, lib, pkgs, ... }: {
          options.services.nss-hosts-netdependent = {
            enable = lib.mkOption {
              description = "Enable network-dependent hostname resolution";
              type = lib.types.bool;
              default = false;
            };
          };
          config = lib.mkIf config.services.nss-hosts-netdependent.enable {
            system.nssModules = [ self.defaultPackage.${pkgs.system} ];
            system.nssDatabases.hosts = lib.mkOrder 300 ["debug" "netdependent"];
          };
        };
      };
}
