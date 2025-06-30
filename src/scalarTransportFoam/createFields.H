volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field F\n" << endl;

volScalarField F
(
    IOobject
    (
        "F",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volVectorField coords("coords", mesh.C());

forAll(F, faceI)
{
    if (sqr(coords[faceI].component(0) - 0.5) + sqr(coords[faceI].component(2) - 0.5) < 0.0625)
    {

        F[faceI] = 1;
    }

    else
    {

        F[faceI] = 0;
    }
}


volScalarField G
(
    IOobject
    (
        "G",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


Info<< "Reading transportProperties\n" << endl;

IOdictionary transportProperties
(
    IOobject
    (
        "transportProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);


Info<< "Reading diffusivity DT\n" << endl;

dimensionedScalar DT("DT", dimViscosity, transportProperties);
dimensionedScalar c("c", dimVelocity, transportProperties);

#include "createPhi.H"

#include "createFvOptions.H"
