file(REMOVE_RECURSE
  "libopenGPMP.a"
  "libopenGPMP.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX Fortran)
  include(CMakeFiles/openGPMP.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
