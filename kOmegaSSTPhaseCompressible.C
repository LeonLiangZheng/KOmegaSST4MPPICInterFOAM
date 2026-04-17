/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
Description
    Instantiation of kOmegaSST turbulence model for
    PhaseCompressibleTurbulenceModel<immiscibleIncompressibleTwoPhaseMixture>.

    Usage: add  libs ("libmyPhaseCompressibleKOmegaSST.so");
           to system/controlDict
\*---------------------------------------------------------------------------*/

// --- Core turbulence framework ---
#include "PhaseCompressibleTurbulenceModel.H"
#include "immiscibleIncompressibleTwoPhaseMixture.H"

// --- Required by defineTurbulenceModelTypes macro ---
#include "laminarModel.H"
#include "RASModel.H"
#include "LESModel.H"

// --- Required by kOmegaSSTBase.C template instantiation ---
//     (fvc::grad, fvm::ddt, fvm::div, fvm::laplacian, solve, etc.)
#include "fvc.H"
#include "fvm.H"
#include "fvMatrices.H"
#include "bound.H"
#include "fvOptions.H"

// --- Registration machinery ---
#include "addToRunTimeSelectionTable.H"
#include "makeTurbulenceModel.H"


// -- 1. Recreate the type aliases (no ODR conflict) ----------------------
defineTurbulenceModelTypes
(
    volScalarField,
    volScalarField,
    compressibleTurbulenceModel,
    PhaseCompressibleTurbulenceModel,
    immiscibleIncompressibleTwoPhaseMixture
);


// -- 2. Instantiate kOmegaSST and register it ----------------------------
#include "kOmegaSST.H"
makeTemplatedTurbulenceModel
(
    immiscibleIncompressibleTwoPhaseMixturePhaseCompressibleTurbulenceModel,
    RAS,
    kOmegaSST
);


// ************************************************************************* //