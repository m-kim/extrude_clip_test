add_executable(extrude_clip_test
	main.cxx
	)
set_target_properties(extrude_clip_test PROPERTIES CXX_STANDARD 14)
target_link_libraries(extrude_clip_test
vtkm_cont
vtkm_filter
	)
set_target_properties(extrude_clip_test PROPERTIES CXX_STANDARD 14)
