# KOmegaSST4MPPICInterFOAM

Makes the `kOmegaSST` RAS model selectable in `MPPICInterFoam` and the solvers
derived from it (for example
[MPPICInterIsoFoam / MPPICInterIsoRDFFoam](https://github.com/LeonLiangZheng/MPPICInterRDFFOAM))
in OpenFOAM v2212 (ESI).

## Why it is needed

`MPPICInterFoam` builds its turbulence models on
`PhaseCompressibleTurbulenceModel<immiscibleIncompressibleTwoPhaseMixture>`.
Its bundled library `compressibleTwoPhaseMixtureTurbulenceModels` registers
only `Stokes`, `kEpsilon`, `kOmega`, `Smagorinsky` and `kEqn` for that type, so
a case with `RAS { model kOmegaSST; }` stops with "Unknown RASModel type
kOmegaSST". This library instantiates `kOmegaSST` for the same type and
registers it, without touching the OpenFOAM installation.

## Build

```bash
source /path/to/OpenFOAM-v2212/etc/bashrc
cd KOmegaSST4MPPICInterFOAM
wclean
wmake libso
```

The library is written to `$FOAM_USER_LIBBIN/libmyKOmegaSST.so`.

## Use

`system/controlDict`

```foam
libs ("libmyKOmegaSST.so");
```

`constant/turbulenceProperties`

```foam
simulationType  RAS;
RAS
{
    model       kOmegaSST;
    turbulence  on;
    printCoeffs on;
}
```

If the run stops asking for `kFinal`, `omegaFinal` or `UFinal`, add those
entries to `fvSolution`: v2212 looks them up in the final PIMPLE iteration.

## License

Built from OpenFOAM's turbulence-model templates, and therefore
GPL-3.0-or-later.
