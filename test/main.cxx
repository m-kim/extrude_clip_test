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

vtkm::cont::DataSet makeDataSet()
{
  std::vector<int> ibuffn, ibuffc;
  std::vector<double> buff;
  vtkm::cont::DataSet ds;

  int newPhi = numPhi/2 + 1;
  coords = vtkm::cont::make_ArrayHandleExtrudeCoords( vtkm::cont::make_ArrayHandle(buff, vtkm::CopyFlag::On), newPhi, false,vtkm::Pi());
  connectivity = vtkm::cont::make_ArrayHandle(ibuffc, vtkm::CopyFlag::On);
  nextNode = vtkm::cont::make_ArrayHandle(ibuffn, vtkm::CopyFlag::On);
  cells = vtkm::cont::make_CellSetExtrude(connectivity, coords, nextNode, false);

  ds.SetCellSet(cells);
  
  ds.AddField(vtkm::cont::make_FieldPoint("pointvar",  output));

  return ds;
}
int main()
{
  auto ret = makeDataSet();

  vtkm::filter::ClipWithField clip;
  clip.SetClipValue(0.1);
  clip.SetActiveField("pointvar");

  auto ds = clip.Execute(ret);
	return 0;
}
