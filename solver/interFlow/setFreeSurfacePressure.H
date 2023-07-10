
word freeSurfaceFieldName = args.get<word>("freeSurfaceField");

const volScalarField& freeSurfaceVolFraction = 
    mesh.lookupObject<volScalarField>(freeSurfaceFieldName); 
const double epsilon = 1e-08; 

//const auto& own = mesh.owner(); 
//const auto& nei = mesh.neighbour(); 
//DynamicList<label> freeSurfaceCells;
//forAll(own, faceI)
//{
    //if (freeSurfaceVolFraction[own[faceI]] > (1 - epsilon))
    //{
        //freeSurfaceCells.append(own[faceI]);
    //}
    //if (freeSurfaceVolFraction[nei[faceI]] > (1 - epsilon))
    //{
        //freeSurfaceCells.append(nei[faceI]);
    //}
//}

marker = alpha1;
marker = fvc::average(fvc::interpolate(marker));
marker = fvc::average(fvc::interpolate(marker));
marker = fvc::average(fvc::interpolate(marker));

DynamicList<label> freeSurfaceCells;
forAll(marker, cellI)
{
    if ((1 - marker[cellI]) > (1 - epsilon))
    {
        freeSurfaceCells.append(cellI);
    }
}
p_rghEqn.setValues(freeSurfaceCells, 0.);
