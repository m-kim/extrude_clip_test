#include <vtkm/cont/ArrayHandleExtrudeCoords.h>
#include <vtkm/cont/CellSetExtrude.h>
#include <vtkm/cont/ArrayHandle.h>
#include <vtkm/cont/DataSet.h>
#include <vtkm/filter/ClipWithField.h>

vtkm::cont::CellSetExtrude cells;
vtkm::cont::ArrayHandleExtrudeCoords<double> coords;
vtkm::cont::ArrayHandle<vtkm::Int32> connectivity, nextNode;
vtkm::cont::ArrayHandle<double> output;

int numPhi = 8;

std::vector<double> buff = {0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 1.0f }; 
std::vector<int> ibuffc = {0, 2, 1};
std::vector<int> ibuffn = {0, 1, 2};



int main()
{
  vtkm::cont::DataSet ds;

  coords = vtkm::cont::make_ArrayHandleExtrudeCoords( vtkm::cont::make_ArrayHandle(buff, vtkm::CopyFlag::On), numPhi, true,vtkm::TwoPi());

  output.Allocate(coords.GetPortalConstControl().GetNumberOfValues());

  for (int i=0; i<coords.GetPortalConstControl().GetNumberOfValues(); i++){
    std::cout << i << " " << coords.GetPortalConstControl().Get(i) << std::endl;
    output.GetPortalControl().Set(i, 1.0);
      //static_cast<float>(i)/static_cast<float>(coords.GetPortalConstControl().GetNumberOfValues()));
  }
  connectivity = vtkm::cont::make_ArrayHandle(ibuffc, vtkm::CopyFlag::On);
  nextNode = vtkm::cont::make_ArrayHandle(ibuffn, vtkm::CopyFlag::On);
  cells = vtkm::cont::make_CellSetExtrude(connectivity, coords, nextNode, false);
  std::cout << "# cells: " << cells.GetNumberOfCells() << std::endl;
  std::cout << "# faces: " << cells.GetNumberOfFaces() << std::endl;

  ds.AddCoordinateSystem(vtkm::cont::CoordinateSystem("coords", coords));
  ds.SetCellSet(cells);
  

  ds.AddField(vtkm::cont::make_FieldPoint("pointvar",  output));

  vtkm::filter::ClipWithField clip;
  clip.SetClipValue(0.9);
  clip.SetActiveField("pointvar");

  auto ret = clip.Execute(ds);
 auto clipped_cs = ds.GetCellSet();
  std::cout << "# cells: " << clipped_cs.GetNumberOfCells() << std::endl;
  std::cout << "# faces: " << clipped_cs.GetNumberOfFaces() << std::endl;
}
