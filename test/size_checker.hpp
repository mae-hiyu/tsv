/*!
  \file size_check.hpp
  \author zin
  */

#ifndef _REFLECT_SIZE_CHECK_HPP_
#define _REFLECT_SIZE_CHECK_HPP_

namespace test {

//! Print size of all classes
void printClassSize();

//! Print size of basic types 
void printBasicTypeSize();

//! Print size of camera classes
void printCameraClassSize();

//! Print size of data classes
void printDataClassSize();

//! Print size of data structure classes
void printDataStructureClassSize();

//! Print size of geometry classes
void printGeometryClassSize();

//! Print size of material classes
void printMaterialClassSize();

//! Print size of OpenCL classes
void printOpenCLClassSize();

//! Print size of renderer classes
void printRendererClassSize();

//! Print size of sampling classes
void printSamplingClassSize();

//! Print size of tonemapping classes
void printTonemappingClassSize();

} // namespace test

#endif // _REFLECT_SIZE_CHECK_HPP_
