/*!
  \file size_check.cpp
  \author zin
  */

// Standard C++ library
#include <cstddef>
// Reflect
#include "CameraModel/camera_model.hpp"
#include "CameraModel/film.hpp"
#include "CameraModel/pinhole_camera.hpp"
//#include "CameraModel/thin_lens_camera.hpp"
//#include "Data/intersection_point.hpp"
//#include "Data/light_source_reference.hpp"
//#include "Data/object.hpp"
//#include "Data/photon_cache.hpp"
//#include "Data/ray.hpp"
//#include "Data/wavelength_samples.hpp"
//#include "DataStructure/aabb.hpp"
//#include "DataStructure/bvh_node.hpp"
//#include "Geometry/flat_mesh.hpp"
//#include "Geometry/geometry.hpp"
//#include "Geometry/normal_smoothed_mesh.hpp"
//#include "Geometry/plane.hpp"
//#include "Geometry/smoothed_mesh.hpp"
//#include "Geometry/sphere.hpp"
//#include "Material/shader_model.hpp"
//#include "Material/value_weight.hpp"
//#include "Material/weight.hpp"
//#include "Material/SurfaceScattering/Bxdf/lambert_brdf.hpp"
//#include "Material/SurfaceScattering/Bxdf/ggx_conductor_brdf.hpp"
//#include "Material/Emitter/non_directional_light.hpp"
//#include "RendererBase/renderer_system.hpp"
//#include "Sampling/sampled_spectra.hpp"
//#include "Sampling/sampled_wavelengths.hpp"
//#include "Tonemapping/tonemapping_method.hpp"
//#include "Utility/size.hpp"

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

/*!
  \details
  No detailed.
  */
int main()
{
  std::cout << "Class name, Member name, Size, Alignment" << std::endl;
  printBasicTypeSize();
  std::cout << std::endl;
  printCameraClassSize();
//  std::cout << std::endl;
//  printDataClassSize();
//  std::cout << std::endl;
//  printDataStructureClassSize();
//  std::cout << std::endl;
//  printGeometryClassSize();
//  std::cout << std::endl;
//  printMaterialClassSize();
//  std::cout << std::endl;
//  printOpenCLClassSize();
//  std::cout << std::endl;
//  printRendererClassSize();
//  std::cout << std::endl;
//  printSamplingClassSize();
//  std::cout << std::endl;
//  printTonemappingClassSize();
//  std::cout << std::endl;
}

/*!
  \details
  No detailed.
  */
void printBasicTypeSize()
{
  std::cout << "## Basic types" << std::endl;

  PRINT_TYPE_DATA(bool);
  PRINT_TYPE_DATA(char);
  PRINT_TYPE_DATA(int);
  PRINT_TYPE_DATA(long);
  PRINT_TYPE_DATA(long long);
  PRINT_TYPE_DATA(std::size_t);
  PRINT_TYPE_DATA(float);
  PRINT_TYPE_DATA(double);
  PRINT_TYPE_DATA(long double);
  PRINT_TYPE_DATA(void*);
}

/*!
  \details
  No detailed.
  */
void printCameraClassSize()
{
  using namespace reflect;
  std::cout << "## Camera classes" << std::endl;

  PRINT_CLASS_DATA(Film);
  PRINT_CLASS_DATA(CameraModel);
  PRINT_CLASS_DATA(PinholeCamera);
//  PRINT_CLASS_DATA(ThinLensCamera);
}

///*!
//  \details
//  No detailed.
//  */
//void printDataClassSize()
//{
//  using namespace reflect;
//  std::cout << "## Data classes" << std::endl;
//
//  PRINT_CLASS_DATA(IntersectionPoint);
//  PRINT_CLASS_DATA(LightSourceReference);
//  PRINT_CLASS_DATA(Object);
//  PRINT_CLASS_DATA(PhotonCache);
//  PRINT_CLASS_DATA(Ray);
//  PRINT_CLASS_DATA(WavelengthSamples);
//}
//
///*!
//  \details
//  No detailed.
//  */
//void printDataStructureClassSize()
//{
//  using namespace reflect;
//  std::cout << "## DataStructure classes" << std::endl;
//
//  PRINT_CLASS_DATA(Aabb);
//  PRINT_CLASS_DATA(BvhNode);
//}
//
///*!
//  \details
//  No detailed.
//  */
//void printGeometryClassSize()
//{
//  using namespace reflect;
//  std::cout << "## Geometry classes" << std::endl;
//
//  PRINT_CLASS_DATA(Geometry);
//  PRINT_CLASS_DATA(Plane);
//  PRINT_CLASS_DATA(Sphere);
//  PRINT_CLASS_DATA(TriangleMesh);
//  PRINT_CLASS_DATA(FlatMesh);
//  PRINT_CLASS_DATA(NormalSmoothedMesh);
//  PRINT_CLASS_DATA(SmoothedMesh);
//}
//
///*!
//  \details
//  No detailed.
//  */
//void printMaterialClassSize()
//{
//  using namespace reflect;
//  std::cout << "## Material classes" << std::endl;
//
//  PRINT_CLASS_DATA(ShaderModel);
//  PRINT_CLASS_DATA(LambertBrdf);
//  PRINT_CLASS_DATA(GgxConductorBrdf);
//  PRINT_CLASS_DATA(NonDirectionalLight);
//}
//
///*!
//  \details
//  No detailed.
//  */
//void printOpenCLClassSize()
//{
//#ifdef REFLECT_OPENCL
//  using namespace reflect;
//  std::cout << "## OpenCL classes" << std::endl;
//
//  PRINT_TYPE_DATA(cl_char);
//  PRINT_TYPE_DATA(cl_uchar);
//  PRINT_TYPE_DATA(cl_short);
//  PRINT_TYPE_DATA(cl_ushort);
//  PRINT_TYPE_DATA(cl_int);
//  PRINT_TYPE_DATA(cl_uint);
//  PRINT_TYPE_DATA(cl_long);
//  PRINT_TYPE_DATA(cl_ulong);
//  PRINT_TYPE_DATA(cl_half);
//  PRINT_TYPE_DATA(cl_float);
//  PRINT_TYPE_DATA(cl_double);
//  PRINT_TYPE_DATA(cl_float3);
//
//  std::cout << std::endl;
//  PRINT_CL_DATA(ClSpectralDistribution);
//  PRINT_CLASS_DATA(ClSpectraImage);
//  PRINT_CL_DATA(ClLightSourceReference);
//  PRINT_CL_DATA(ClObject);
//  PRINT_CL_DATA(ClAabb);
//  PRINT_CL_DATA(ClBvhNode);
//  PRINT_CL_DATA(ClEmitterModel);
//  PRINT_CL_DATA(ClSurfaceScatteringModel);
//  PRINT_CL_DATA(ClWeight);
//  PRINT_CLASS_DATA(ClPathTracing);
//  PRINT_CL_DATA(ClXorshiftState);
//  PRINT_CL_DATA(ClXsaddState);
//#endif // REFLECT_OPENCL
//}
//
///*!
//  \details
//  No detailed.
//  */
//void printRendererClassSize()
//{
//  using namespace reflect;
//  std::cout << "## Renderer classes" << std::endl;
//
//  PRINT_CLASS_DATA(RendererSystem);
//}
//
///*!
//  \details
//  No detailed.
//  */
//void printSamplingClassSize()
//{
//  using namespace reflect;
//  std::cout << "## Sampling classes" << std::endl;
//
//  PRINT_CLASS_DATA(SampledSpectra);
//  PRINT_CLASS_DATA(SampledWavelengths);
//}
//
///*!
//  \details
//  No detailed.
//  */
//void printTonemappingClassSize()
//{
//  using namespace reflect;
//  std::cout << "## Tonemapping classes" << std::endl;
//
//  PRINT_CLASS_DATA(TonemappingMethod);
//}
