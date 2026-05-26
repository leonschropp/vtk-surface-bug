#include <iostream>
#include <vtkCell.h>
#include <vtkCellData.h>
#include <vtkPoints.h>
#include <vtkPyramid.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridGeometryFilter.h>
#include <vtkXMLUnstructuredGridWriter.h>

vtkSmartPointer<vtkUnstructuredGrid>
vtk_surface(vtkSmartPointer<vtkUnstructuredGrid> grid) {
  vtkSmartPointer<vtkUnstructuredGridGeometryFilter> surface_filter =
      vtkSmartPointer<vtkUnstructuredGridGeometryFilter>::New();
  surface_filter->PassThroughPointIdsOn();
  surface_filter->PassThroughCellIdsOn();
  surface_filter->SetInputData(grid);
  surface_filter->Update();
  vtkSmartPointer<vtkUnstructuredGrid> surface =
      vtkSmartPointer<vtkUnstructuredGrid>::New();
  surface->DeepCopy(surface_filter->GetOutput());
  return surface;
}

vtkSmartPointer<vtkUnstructuredGrid> double_pyramid() {
  vtkNew<vtkPoints> points;
  float p0[3] = {1.0, 1.0, 0.0};
  float p1[3] = {-1.0, 1.0, 0.0};
  float p2[3] = {-1.0, -1.0, 0.0};
  float p3[3] = {1.0, -1.0, 0.0};
  float p4[3] = {0.0, 0.0, 1.0};
  float p5[3] = {0.0, 0.0, -1.0};

  points->InsertNextPoint(p0);
  points->InsertNextPoint(p1);
  points->InsertNextPoint(p2);
  points->InsertNextPoint(p3);
  points->InsertNextPoint(p4);
  points->InsertNextPoint(p5);

  vtkNew<vtkPyramid> up;
  for (int i = 0; i < 5; ++i) {
    up->GetPointIds()->SetId(i, i);
  }

  vtkNew<vtkPyramid> down;
  for (int i = 0; i < 4; ++i) {
    down->GetPointIds()->SetId(i, i);
  }
  down->GetPointIds()->SetId(4, 5);

  vtkSmartPointer<vtkUnstructuredGrid> ug =
      vtkSmartPointer<vtkUnstructuredGrid>::New();
  ug->SetPoints(points);
  ug->InsertNextCell(up->GetCellType(), up->GetPointIds());
  ug->InsertNextCell(down->GetCellType(), down->GetPointIds());
  return ug;
}

int main() {
  vtkSmartPointer<vtkUnstructuredGrid> bipyramid = double_pyramid();

  std::cout << "Test extracting the Surface of Bipyramid" << std::endl;
  std::cout << "===========================================" << std::endl;

  std::cout << "Bipyramid has " << bipyramid->GetNumberOfPoints()
            << "points and " << bipyramid->GetNumberOfCells() << " cells."
            << std::endl;
  vtkSmartPointer<vtkIdList> points = vtkSmartPointer<vtkIdList>::New();
  for (int i = 0; i < 4; ++i) {
    points->InsertNextId(i);
  }
  vtkSmartPointer<vtkIdList> neighbors = vtkSmartPointer<vtkIdList>::New();
  bipyramid->GetCellNeighbors(0, points, neighbors);
  std::cout << "The neighbor of cell in Bipyramid is " << neighbors->GetId(0)
            << std::endl;

  std::cout << "Hence, it is recognised that the two pyramid cells share the "
               "same base plate"
            << std::endl
            << std::endl;

  std::cout << "Start extracting the surface of Bipyramid" << std::endl;
  vtkSmartPointer<vtkUnstructuredGrid> surface = vtk_surface(bipyramid);

  std::cout << "Successfully extracted the surface of Bipyramid." << std::endl
            << std::endl;
  std::cout << "Expected number of nodes on surface: 6" << std::endl;
  std::cout << "Actual number of nodes on surface: "
            << surface->GetNumberOfPoints() << std::endl
            << std::endl;

  std::cout << "Expected number of cells in surface: 8" << std::endl;
  std::cout << "Actual number of cells in surface: "
            << surface->GetNumberOfCells() << std::endl
            << std::endl;

  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
      vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName("bipyramid.vtu");
  writer->SetInputData(bipyramid);
  writer->Write();

  writer->SetFileName("surface.vtu");
  writer->SetInputData(surface);
  writer->Write();

  std::cout << "Written UnstructuredGrid representing Bipyramid into file "
               "'bipyramid.vtu'."
            << std::endl;
  std::cout << "Written UnstructuredGrid representing surface into file "
               "'surface.vtu'."
            << std::endl;

  std::cout << "Open these file with Paraview to check that UnstructuredGrids "
               "have correct form."
            << std::endl;
  return 0;
}
