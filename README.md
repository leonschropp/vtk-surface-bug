# vtk-surface-bug
In the [documentation vtkUnstructuredGridGeometryFilter]() it says that the filter provides the following functionality:

> Geometry is obtained as follows: all 0D, 1D, and 2D cells are extracted. All 2D faces that are used by only one 3D cell (i.e., boundary faces) are extracted.

However, when I extract the surface of a simple `vtkUnstructuredGrid` modelling a **Bipyramid** in `test_extract_surface.cpp`, then the `vtkUnstructuredGrid` obtained as Output of this filter has 10 cells instead of 8 cells. This means that the base plate where the two pyramids are glued together is **falsly regarded as surface cell** and **counted twice**. 

This is verified by the output of the Test `test_extract_surface.cpp` which you can find at the latest run of the github workflow of this repository. 

Running `test_extract_surface` also produces two VTU files `bipyramid.vtu` and `surface.vtu` containing the `vtkUnstructuredGrid` produces in this Test. I provided them in this repository. You can open these files with [Paraview](https://www.paraview.org/) in order to check that these `UnstructuredGrids` look just as expected.

Note that this github workflow uses the latest version of VTK i.e. the master! 
