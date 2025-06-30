Info<< "Reading field T\n" << endl;

volScalarField T
(
    IOobject
    (
        "T",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


Info<< "Reading diffusivity DT\n" << endl;

volScalarField DT
(
    IOobject
    (
        "DT",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimViscosity, Zero)
);

//if (!DT.headerOk())
//{
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
    DT = dimensionedScalar("DT", dimViscosity, transportProperties);
    dimensionedScalar T0("T0", dimTemperature, transportProperties);
    dimensionedScalar TL("TL", dimTemperature, transportProperties);
    dimensionedScalar L("L", dimLength, transportProperties);
//}

volVectorField coords ("coords", mesh.C());
volScalarField T_anal ("T_anal", ((TL-T0)/L)*coords.component(0) + T0);

T_anal.write();

#include "createFvOptions.H"
