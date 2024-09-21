/*!
  \file keyword.hpp
  \author takemura
  */

#ifndef _REFLECT_KEYWORD_HPP_
#define _REFLECT_KEYWORD_HPP_

namespace reflect {

namespace keyword {

// General
constexpr char count[] = "Count";
constexpr char enabled[] = "Enabled";
constexpr char name[] = "Name";
constexpr char type[] = "Type";
constexpr char item[] = "Item%1";
constexpr char non_renderable[] = "NonRenderable";
constexpr char renderable[] = "Renderable";
constexpr char default_setting[] = "DefaultSetting";
constexpr char optimization[] = "Optimization";

// Basic settings
// System setting
constexpr char system_group[] = "System";
constexpr char scene_name[] = "SceneName";
constexpr char random_seed[] = "RandomSeed";
constexpr char num_of_threads[] = "NumberOfThreads";
constexpr char ldr_image_format[] = "LdrImageFormat";
constexpr char png_format[] = "PNG";
constexpr char bmp_format[] = "BMP";
constexpr char ppm_format[] = "PPM";
constexpr char spectra_image_saving[] = "SpectraImageSaving";
constexpr char hdr_image_saving[] = "SpectraImageSaving";
constexpr char saving_image_at_power_of_2_of_pass[] = "SavingImageAtPowerOf2OfPass";
constexpr char saving_interval[] = "SavingInterval";
constexpr char termination_pass[] = "TerminationPass";
constexpr char open_cl[] = "OpenCL";
constexpr char open_cl_cpu[] = "OpenCL CPU";
constexpr char open_cl_use_multiple_gpus[] = "OpenCL Use multiple GPUs";
// Color settings
constexpr char color_group[] = "Color";
constexpr char color[] = "Color";
constexpr char color1[] = "Color1";
constexpr char color2[] = "Color2";
constexpr char width[] = "Width";
constexpr char height[] = "Height";
constexpr char rgb_rendering[] = "RgbRendering";
constexpr char standard_observer[] = "StandardObserver";
constexpr char cie2_cmf[] = "CIE 2deg colour-matching functions";
constexpr char cie10_cmf[] = "CIE 10deg colour-matching functions";
constexpr char cie_1931_rgb[] = "CIE 1931 RGB";
constexpr char standard_illuminant[] = "StandardIlluminant";
constexpr char cie_d65[] = "CIE D65";
constexpr char cie_a[] = "CIE A";
constexpr char spectrum_sampling[] = "SpectrumSampling";
constexpr char regular_sampling[] = "Regular sampling";
constexpr char random_sampling[] = "Random sampling";
constexpr char stratified_sampling[] = "Stratified sampling";
constexpr char lights_based_importance_sampling[] = 
    "Lights based importance sampling";
constexpr char materials_based_importance_sampling[] = 
    "Materials based importance sampling";
constexpr char lights_and_materials_plus_based_importance_sampling[] =
    "Lights and materials (+) based importance sampling";
constexpr char lights_and_materials_multi_based_importance_sampling[] =
    "Lights and materials (x) based importance sampling";
constexpr char tristimulus_values_importance_sampling[] = "Tristimulus Values importance sampling";
constexpr char lights_and_tsv_multi_based_importance_sampling[] = "Lights (+) tsv based importance sampling";
constexpr char color_space[] = "ColorSpace";
constexpr char srgb_d65[] = "sRGB (D65)";
constexpr char srgb_d50[] = "sRGB (D50)";
constexpr char adobe_rgb_d65[] = "Adobe RGB (D65)";
constexpr char adobe_rgb_d50[] = "Adobe RGB (D50)";
constexpr char property[] = "Property";
constexpr char rgb[] = "RGB";
constexpr char spectra[] = "Spectra";
constexpr char spectra_file[] = "SpectraFile";
constexpr char gamma[] = "Gamma";
constexpr char tonemapping[] = "Tonemapping";
constexpr char simplified_reinhard[] = "Simplified Reinhard";
// Renderering method settings
constexpr char rendering_method_group[] = "RenderingMethod";
constexpr char rendering_method[] = "RenderingMethod";
constexpr char ray_cast_epsilon[] = "Ray cast epsilon";
constexpr char path_tracing_method[] = "Path tracing";
constexpr char tsv_rendering_method[] = "Tristimulus Values rendering";
constexpr char tsv_light_rendering_method[] = "TSV Light MIS rendering";
constexpr char regularized_path_tracing_method[] = "Regularized path tracing";
// Probabilistic PPM
constexpr char probabilistic_ppm_method[] = "Probabilistic PPM";
constexpr char tsv_probabilistic_ppm_method[] = "TSV Probabilistic PPM";
constexpr char num_of_photons[] = "NumberOfPhotons";
constexpr char initial_radius[] = "InitialRadius";
constexpr char alpha[] = "Alpha";
constexpr char k[] = "K";
constexpr char filter_kernel[] = "FilterKernel";
constexpr char no_kernel[] = "No kernel";
constexpr char cone_kernel[] = "Cone kernel";
constexpr char gauss_kernel[] = "Gauss kernel";
constexpr char perlin_kernel[] = "Perlin kernel";
// Russian roulette
constexpr char russian_roulette[] = "RussianRoulette";
constexpr char reflectance_max[] = "Reflectance (Max)";
constexpr char reflectance_average[] = "Reflectance (Average)";
constexpr char path_length[] = "Path length";
constexpr char path_length_max[] = "PathLengthMax";
// Bvh settings
constexpr char bvh_group[] = "Bvh";
constexpr char binary_radix_bvh[] = "Binary radix bvh";
constexpr char median_split_bvh[] = "Median split bvh";
constexpr char approximate_agglomerative_clustering_bvh[] = 
    "Approximate agglomerative clustering bvh";
constexpr char delta[] = "Delta";
constexpr char epsilon[] = "Epsilon";
// Object data
constexpr char object[] = "Object";
constexpr char visibility[] = "Visibility";
// Camera data
constexpr char camera_object[] = "Camera";
constexpr char camera_model[] = "CameraModel";
constexpr char pinhole_camera[] = "Pinhole camera";
constexpr char angle_of_view[] = "AngleOfView";
constexpr char spectral_response[] = "SpectralResponse";
constexpr char thin_lens_camera[] = "Thin lens camera";
constexpr char aperture[] = "Aperture";
constexpr char focal_distance[] = "FocalDistance";
// Group object data
constexpr char group_object[] = "Group";
// Single object data
constexpr char single_object[] = "Object";
constexpr char is_light_source[] = "IsLightSource";
constexpr char geometry_type[] = "GeometryType";
constexpr char plane_type[] = "Plane";
constexpr char sphere_type[] = "Sphere";
constexpr char polygon_type[] = "Polygon";
constexpr char emitter_index[] = "EmitterIndex";
constexpr char surface_index[] = "SurfaceIndex";
//constexpr char texture_index[] = "TextureIndex";
constexpr char object_file[] = "ObjectFile";
constexpr char enable_smoothing[] = "EnableSmoothing";
constexpr char use_nagata_patch[] = "UseNagataPatch";

// Film
constexpr char image_size[] = "ImageSize";
constexpr char vga_size[] = "VGA (640x480)";
constexpr char svga_size[] = "SVGA (800x600)";
constexpr char qvga_size[] = "Quad VGA (1280x960)";
constexpr char qhd_size[] = "Quarter HD (960x540)";
constexpr char fwxga_size[] = "FWXGA (1280x720)";
constexpr char full_hd_size[] = "Full HD (1920x1080)";
constexpr char wqhd_size[] = "Wide Quad HD (2560x1440)";
constexpr char image_width[] = "ImageWidth";
constexpr char image_height[] = "ImageHeight";
constexpr char jittering[] = "Jittering";
// Transformation data
constexpr char transformation[] = "Transformation";
constexpr char translation[] = "Translation";
constexpr char scaling[] = "Scaling";
constexpr char rotation[] = "Rotation";
constexpr char axis[] = "Axis";
constexpr char x_axis[] = "X axis";
constexpr char y_axis[] = "Y axis";
constexpr char z_axis[] = "Z axis";
constexpr char angle[] = "Angle";
constexpr char angle_unit[] = "AngleUnit";
constexpr char degree_unit[] = "Degree";
constexpr char radian_unit[] = "Radian";
constexpr char x[] = "X";
constexpr char y[] = "Y";
constexpr char z[] = "Z";
// Material
constexpr char material[] = "Material";
constexpr char default_type[] = "Default";
// Emitter Model
constexpr char emitter_model[] = "EmitterModel";
constexpr char radiant_emittance[] = "RadiantEmittance";
constexpr char non_directional_emitter[] = "Non directional emitter";
// Surface Model
constexpr char surface_model[] = "SurfaceModel";
constexpr char smooth_diffuse_surface[] = "Smooth diffuse surface";
constexpr char reflectance[] = "Reflectance";
constexpr char smooth_dielectric_surface[] = "Smooth dielectric surface";
constexpr char schlick_approximation[] = "SchlickApproximation";
constexpr char exterior_refractive_index[] = "ExteriorRefractiveIndex";
constexpr char interior_refractive_index[] = "InteriorRefractiveIndex";
constexpr char smooth_conductor_surface[] = "Smooth conductor surface";
constexpr char interior_extinction[] = "InteriorExtinction";
constexpr char multilayer_thin_film_surface[] = "Multilayer thin film surface";
constexpr char is_conductor[] = "IsConductor";
constexpr char thickness[] = "Thickness";
constexpr char refractive_index[] = "RefractiveIndex";
constexpr char extinction_coefficient[] = "ExtinctionCoefficient";
constexpr char rough_dielectric_surface[] = "Rough dielectric surface";
constexpr char rough_conductor_surface[] = "Rough conductor surface";
constexpr char roughness[] = "Roughness";
constexpr char smooth_plastic_surface[] = "Smooth plastic surface";
// Texture
constexpr char texture[] = "Texture";
constexpr char value_texture[] = "Value texture";
constexpr char unicolor_texture[] = "Unicolor texture";
constexpr char checkerboard_texture[] = "Checkerboard texture";
constexpr char image_texture[] = "Image texture";
constexpr char image_file[] = "ImageFile";
// Weight
constexpr char weight[] = "Weight";
constexpr char value[] = "Value";
constexpr char texture_index[] = "TextureIndex";

} // namespace keyword

} // namespace reflect

#endif // _REFLECT_KEYWORD_HPP_
