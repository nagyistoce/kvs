# Kyoto Visualization System #
Kyoto Visualization System (KVS) is a multi-platform, open-source C++ library for developing scientific visualization applications. KVS provides various classes and interfaces , such as isosurace extraction, streamlines and volume rendering, to visualize medical data obtained by computerized tomography or magnetic resonance imaging, numerical data from computational fluid dynamics and so on.

![https://lh5.googleusercontent.com/_X4cB5gzzR7o/TdaQc1hbCJI/AAAAAAAAADc/vulb1R7QNb0/s800/KVSTopImages.png](https://lh5.googleusercontent.com/_X4cB5gzzR7o/TdaQc1hbCJI/AAAAAAAAADc/vulb1R7QNb0/s800/KVSTopImages.png)

## Online Document ##
  * Getting started with KVS : [Japanese](KVS_top_jp.md) | [English](KVS_top.md)
  * Programming guide : [Japanese](programming_guide_ja.md) | English
  * Transition guide (1.x to 2.x) : [Japanese](transition_guide_1_to_2_jp.md) | English

## Downloads ##
  * Version 2.4.0 : [source](https://docs.google.com/uc?authuser=0&id=0B99geOORHe59VlFESTA3bWlocDg&export=download) | [document](https://docs.google.com/uc?authuser=0&id=0B99geOORHe59dTRkM0YwWTg5QmM&export=download)
  * Version 2.3.0 : [source](https://docs.google.com/uc?authuser=0&id=0B99geOORHe59WExIbWxkSURLYkE&export=download) | [document](https://docs.google.com/uc?authuser=0&id=0B99geOORHe59NVNfR25QcjNKNkE&export=download)


---

## Changes ##
**Version 2.4.0 Released** (2014-10-10)
  * Add new classes and functions
    * `kvs::PrismaticCell`
    * `kvs::CellTree`
    * `kvs::CellLocator`
    * `kvs::CellAdjacencyGraphLocator`
    * `kvs::CellTreeLocator`
    * `kvs::OpenGL::SetPolygonMode`
    * `kvs::OpenGL::SetColorMaterial`
  * Add new methods
    * `kvs::RGBColor::toVec3`
    * `kvs::RGBAColor::toVec4`
    * `kvs::LineObject::setLineTypeToStrip`
    * `kvs::LineObject::setLineTypeToUniline`
    * `kvs::LineObject::setLineTypeToPolyline`
    * `kvs::LineObject::setLineTypeToSegment`
    * `kvs::LineObject::setColorTypeToVertex`
    * `kvs::LineObject::setColorTypeToLine`
    * `kvs::PolygonObject::setPolygonTypeToTriangle`
    * `kvs::PolygonObject::setPolygonTypeToQuadrangle`
    * `kvs::PolygonObject::setColorTypeToVertex`
    * `kvs::PolygonObject::setColorTypeToPolygon`
    * `kvs::PolygonObject::setNormalTypeToVertex`
    * `kvs::PolygonObject::setNormalTypeToPolygon`
    * `kvs::StructuredVolumeObject::setGridTypeToUniform`
    * `kvs::StructuredVolumeObject::setGridTypeToRectilinear`
    * `kvs::StructuredVolumeObject::setGridTypeToCurvilinear`
    * `kvs::StructuredVolumeObject::setLabel`
    * `kvs::StructuredVolumeObject::setUnit`
    * `kvs::StructuredVolumeObject::label`
    * `kvs::StructuredVolumeObject::unit`
    * `kvs::UnstructuredVolumeObject::setCellTypeToTetrahedra`
    * `kvs::UnstructuredVolumeObject::setCellTypeToHexahedra`
    * `kvs::UnstructuredVolumeObject::setCellTypeToQuadraticTetrahedra`
    * `kvs::UnstructuredVolumeObject::setCellTypeToQuadraticHexahedra`
    * `kvs::UnstructuredVolumeObject::setCellTypeToPyramid`
    * `kvs::UnstructuredVolumeObject::setCellTypeToPoint`
    * `kvs::UnstructuredVolumeObject::setCellTypeToPrism`
    * `kvs::UnstructuredVolumeObject::setLabel`
    * `kvs::UnstructuredVolumeObject::setUnit`
    * `kvs::UnstructuredVolumeObject::label`
    * `kvs::UnstructuredVolumeObject::unit`
    * `kvs::ImageObject::pixelType`
    * `kvs::ColorMap::colorSpace`
    * `kvs::ColorMap::setColorSpace`
    * `kvs::ColorMap::setColorSpaceToRGB`
    * `kvs::ColorMap::setColorSpaceToHSV`
    * `kvs::ColorMap::addPoint (for HSV color value)`
    * `kvs::UnstructuredVolumeObject::numberOfCellNodes`
    * `kvs::Camera::setProjectionTypeToPerspective`
    * `kvs::Camera::setProjectionTypeToOrthogonal`
    * `kvs::Camera::setProjectionTypeToFrustum`
    * `kvs::glut::Screen::setControlTargetToObject`
    * `kvs::glut::Screen::setControlTargetToCamera`
    * `kvs::glut::Screen::setControlTargetToLight`
    * `kvs::qt::Screen::setControlTargetToObject`
    * `kvs::qt::Screen::setControlTargetToCamera`
    * `kvs::qt::Screen::setControlTargetToLight`
    * `kvs::Scene::numberOfObjects`
    * `kvs::Scene::hasObjects`
    * `kvs::Scene::hasObject`
    * `kvs::Scene::object`
    * `kvs::Scene::renderer`
  * Add new typedef
    * `kvs::Vec2ui (same as kvs::Vector2ui)`
    * `kvs::Vec2d (same as kvs::Vector2d)`
    * `kvs::Vec3d (same as kvs::Vector3d)`
    * `kvs::Vec4ui (same as kvs::Vector4ui)`
    * `kvs::Vec4d (same as kvs::Vector4d)`
    * `kvs::Mat2d (same as kvs::Matrix22d)`
    * `kvs::Mat3d (same as kvs::Matrix33d)`
    * `kvs::Mat4d (same as kvs::Matrix44d)`
  * Add new cell type
    * `kvs::UnstructuredVolumeObject::CellType::Prism`
  * New support
    * `kvs::ExternalFaces supports “Rectilinear"`
    * `kvs::GlyphBase supports “Rectilinear”`
  * Deprecated methods
    * `kvs::ImageObject::type (use kvs::ImageObject::pixelType)`
    * `kvs::ObjectBase::externalPosition (use kvs::ObjectBase::externalCenter)`
  * Fixed problems
    * `kvs::glsl::ParticleBasedRenderer (PBR_zooming.vert, PBR_zooming.frag)`
    * `kvs::SphereGlyph`
    * `kvs::QuadraticTetrahedralCell`
  * Removed method
    * `kvs::VolumeObjectBase::gridType (use kvs::StructuredVolumeObject::gridType)`
    * `kvs::VolumeObjectBase::cellType (use kvs::UnstructuredVolumeObject::cellType)`
  * Removed enum type
    * `kvs::VolumeObjectBase::GridType::Irregular`
    * `kvs::VolumeObjectBase::GridType (use kvs::StructuredVolumeObject::GridType)`
    * `kvs::VolumeObjectBase::CellType (use kvs::UnstructuredVolumeObject::CellType)`
  * Removed template
    * `kvs::ExporterBase`
    * `kvs::CellBase`
    * `kvs::TetrahedralCell`
    * `kvs::HexahedralCell`
    * `kvs::QuadraticTetrahedralCell`
    * `kvs::QuadraticHexahedralCell`
    * `kvs::PyramidalCell`
    * `kvs::PrismaticCell`
  * Supported new attributes in KVSML
    * Endianness can be specified by ‘endian’ (“big” or “little”) in `<DataArray>`.
    * Label of the value can be specified by ‘label’ in `<Value>`.
    * Unit of the value can be specified by ‘unit’ in `<Value>`.
  * Add new example
    * `Example/SupportQt/MainWindow`

**Version 2.3.0 Released** (2014-04-30)
  * Add new classes
    * `kvs::OpenGL::WithPushedClientAttrib`
  * Add new methods
    * `kvs::RendererManager::rendererID`
    * `kvs::Scene::enableObjectOperation`
    * `kvs::Scene::disableObjectOperation`
    * `kvs::Scene::isEnabledObjectOperation`
    * `kvs::Scene::setEnabledObjectOperation`
    * `kvs::Scene::updateGLModelingMatrix`
    * `kvs::Scene::updateGLViewingMatrix`
    * `kvs::Scene::updateGLProjectionMatrix`
    * `kvs::Scene::updateGLLightParameter`
    * `kvs::Scene::isEnabledCollisionDetection`
    * `kvs::Scene::setEnabledCollisionDetection`
    * `kvs::StochasticRenderingCompositor::timer`
    * `kvs::Quaternion::conjugated`
    * `kvs::glut::OrientationAxis::isEnabledAntiAliasing`
    * `kvs::glut::OrientationAxis::setEnabledAntiAliasing`
  * Add new functions
    * `kvs::OpenGL::SetLight`
    * `kvs::OpenGL::PushClientAttrib`
    * `kvs::OpenGL::PopClientAttrib`
    * `kvs::Quaternion::Zero`
    * `kvs::Quaternion::Identity`
  * Fixed problems
    * `kvs::StructuredVolumeImporter`
  * Deprecated methods
    * `kvs::ObjectManager::setActiveObjectID (use kvs::ObjectManager::setActiveObject)`
    * `kvs::IDManager::operator [] (use kvs::IDManager::id)`
    * `kvs::Quaternion::rotate (use kvs::Quaternion::Rotate)`
    * `kvs::Quaternion::rotationQuaternion (use kvs::Quaternion::RotationQuaternion)`
    * `kvs::Quaternion::linearInterpolation (use kvs::Quaternion::LinearInterpolation)`
    * `kvs::Quaternion::sphericalLinearInterpolation (use kvs::Quaternion::SphericalLinearInterpolation)`
    * `kvs::Quaternion::sphericalCubicInterpolation (use kvs::Quaternion::SphericalCubicInterpolation)`
    * `kvs::Quaternion::splineInterpolation (use kvs::Quaternion::SplineInterpolation)`
    * `kvs::Quaternion::spline (use kvs::Quaternion::Spline)`
    * `kvs::Stl::ntriangles (use kvs::Stl::numberOfTriangles)`
  * Removed class
    * `kvs::ObjectManager::enableAllMove`
    * `kvs::ObjectManager::disableAllMove`
    * `kvs::ObjectManager::isEnableAllMove`
    * `kvs::Scene::enableAllMove`
    * `kvs::Scene::disableAllMove`
    * `kvs::Scene::isEnabledAllMove`
  * Removed method
    * `kvs::ObjectBase::enableCollision`
    * `kvs::ObjectBase::disableCollision`
    * `kvs::ObjectBase::canCollision`
    * `kvs::ObjectBase::positionInDevice`
    * `kvs::ObjectBase::positionInWorld`
    * `kvs::ObjectBase::positionInExternal (use kvs::ObjectBase::externalPosition)`
    * `kvs::ObjectBase::transform`
    * `kvs::ObjectBase::collision`
    * `kvs::ObjectManager::detectCollision`
    * `kvs::ObjectManager::positionInDevice`
    * `kvs::PipelineModule::object`
  * Removed macro
    * `kvsClassName`
    * `kvsModuleName (use kvsModule)`

**Version 2.2.0 Released** (2014-01-14)
  * Add new classes
    * `kvs::ValueTable`
    * `kvs::AnyValueTable`
    * `kvs::KMeans`
    * `kvs::FastKMeans`
    * `kvs::AdaptiveKMeans`
    * `kvs::KMeansClustering`
    * `kvs::PreIntegrationTable3D`
    * `kvs::Program`
    * `kvs::Noncopyable`
    * `kvs::cuda::DriverAPI::Context`
    * `kvs::cuda::DriverAPI::Device`
    * `kvs::cuda::DriverAPI::ErrorString`
    * `kvs::cuda::DriverAPI::Initialization`
    * `kvs::cuda::RuntimeAPI::Device`
    * `kvs::cuda::RuntimeAPI::Initialization`
  * Add new methods
    * `kvs::Scene::registerObject`
    * `kvs::Scene::removeObject`
    * `kvs::Scene::replaceObject`
    * `kvs::Scene::replaceRenderer`
    * `kvs::ObjectManager::numberOfObjects`
    * `kvs::TransferFunction::table`
  * Add new functions
    * `kvs::Math::Fract`
    * `kvs::Math::Mod`
    * `kvs::Math::Mix`
    * `kvs::Math::Step`
  * Fixed problems
    * `kvs::AVSUcd`
    * `kvs::ShaderSource`
    * `kvs::StochasticRenderingCompositor`
    * `kvs::glsl::RayCastingRenderer (RC_ray_caster.frag)`
    * `kvs::KVSMLObjectUnstructuredVolume`
    * `kvs::StochasticUniformGridRenderer`
    * `kvs::glsl::ParticleBasedRenderer`
  * Deprecated methods
    * `kvs::ObjectManager::nobjects`
    * `kvs::RendererManager::nrenderers`
    * `kvs::StochasticRenderingCompositor::isEnabledShading`
    * `kvs::StochasticRenderingCompositor::setEnabledShading`
    * `kvs::StochasticRenderingCompositor::enableShading`
    * `kvs::StochasticRenderingCompositor::disableShading`

**Version 2.1.0 Released** (2013-06-05)
  * Added some new functions and classes.
    * `kvs::ScreenCaptureEvent`
    * `kvs::TargetChangeEvent`
  * Added some new functions and classes.
    * `kvs::OpenGL::Flush`
    * `kvs::OpenGL::Finish`
    * `kvs::OpenGL::Clear`
    * `kvs::OpenGL::SetColorMask`
    * `kvs::OpenGL::SetDepthMask`
    * `kvs::OpenGL::SetDepthFunc`
    * `kvs::OpenGL::SetBlendFunc`
    * `kvs::OpenGL::SetShadeModel`
    * `kvs::OpenGL::SetMatrixMode`
    * `kvs::OpenGL::SetCullFace`
    * `kvs::OpenGL::SetReadBuffer`
    * `kvs::OpenGL::SetDrawBuffer`
    * `kvs::OpenGL::SetDrawBuffers`
    * `kvs::OpenGL::SetRasterPos`
    * `kvs::OpenGL::SetViewport`
    * `kvs::OpenGL::SetOrtho`
    * `kvs::OpenGL::SetPerspective`
    * `kvs::OpenGL::SetFrustum`
    * `kvs::OpenGL::ReadPixels`
    * `kvs::OpenGL::DrawPixels`
    * `kvs::OpenGL::GetModelViewMatrix`
    * `kvs::OpenGL::GetModelViewMatrix`
    * `kvs::OpenGL::GetProjectionMatrix`
    * `kvs::OpenGL::GetProjectionMatrix`
    * `kvs::OpenGL::GetViewport`
    * `kvs::OpenGL::modelViewMatrix`
    * `kvs::OpenGL::projectionMatrix`
    * `kvs::OpenGL::viewport`
    * `kvs::OpenGL::LoadIdentity`
    * `kvs::OpenGL::LoadMatrix`
    * `kvs::OpenGL::LoadMatrix`
    * `kvs::OpenGL::MultMatrix`
    * `kvs::OpenGL::MultMatrix`
    * `kvs::OpenGL::Rotate`
    * `kvs::OpenGL::Scale`
    * `kvs::OpenGL::Translate`
    * `kvs::OpenGL::PushMatrix`
    * `kvs::OpenGL::PopMatrix`
    * `kvs::OpenGL::PushAttrib`
    * `kvs::OpenGL::PopAttrib`
    * `kvs::OpenGL::WithPushedMatrix`
    * `kvs::OpenGL::WithPushedAttrib`
    * `kvs::OpenGL::WithEnabled`
    * `kvs::OpenGL::WithDisabled`
  * Added some new methods.
    * `kvs::FrameBuffer::readPixels`
    * `kvs::FrameBuffer::drawPixels`
  * Added some new static methods.
    * `kvs::Texture::Bind`
    * `kvs::Texture::Unbind`
    * `kvs::Texture::SelectActiveUnit`
    * `kvs::Texture::SetEnv`
  * Added some new methods and classes.
    * `kvs::ProgramObject::Binder`
    * `kvs::ProgramObject::detach`
    * `kvs::ProgramObject::release`
    * `kvs::ProgramObject::build`
    * `kvs::ProgramObject::isCreated`
    * `kvs::ProgramObject::isValid`
    * `kvs::ProgramObject::isBound`
    * `kvs::ProgramObject::isLinked`
    * `kvs::ProgramObject::setUniform`
    * `kvs::ProgramObject::setGeometryInputType`
    * `kvs::ProgramObject::setGeometryOutputType`
    * `kvs::ProgramObject::setGeometryOutputVertices`
  * Added some new methods.
    * `kvs::ShaderObject::isCreated`
    * `kvs::ShaderObject::isValid`
    * `kvs::ShaderObject::isCompiled`
  * Deprecated some methods and functions.
    * `kvs::OpenGL::ActivateTextureUnit`
    * `kvs::ProgramObject::clear`
    * `kvs::ProgramObject::setUnifromValuei`
    * `kvs::ProgramObject::setUnifromValuef`
    * `kvs::ShaderObject::clear`
    * `kvs::ShaderObject::create( shader_source )`
    * `kvs::FrameBuffer::read`
    * `kvs::FrameBuffer::draw`
    * `kvs::RayCastngRenderer::enableCoarseRendering`
    * `kvs::RayCastngRenderer::disableCoarseRendering`
  * Improved implementations.
    * `kvs::glsl::ku::ParticleBasedRenderer`
    * `kvs::StochasticPointRenderer`
    * `kvs::StochasticLineRenderer`
    * `kvs::StochasticPolygonRenderer`
    * `kvs::StochasticUniformGridRenderer`
    * `kvs::StochasticTetrahedraRenderer`
    * `kvs::StochasticMultivariateTetrahedraRenderer`
    * `kvs::StochasticMultipleTetrahedraRenderer`
    * `kvs::StochasticRenderingCompositor`
    * `kvs::StochasticMultipleTetrahedraCompositor`
    * `kvs::StochasticRendererBase`
    * `kvs::StochasticRenderingEngine`
    * `kvs::EnsembleAverageBuffer`
  * Removed classes.
    * `kvs::StochasticPointEngine`
    * `kvs::StochasticLineEngine`
    * `kvs::StochasticPolygonEngine`
    * `kvs::StochasticUniformGridEngine`
    * `kvs::StochasticTetrahedraEngine`
    * `kvs::StochasticMultivariateTetrahedraEngine`
    * `kvs::StochasitcMultipleTetrahedraEngine`

**Version 2.0.1 Released** (2013-04-17)
  * Fixed some bugs
    * `kvs::HAVSVolumeRenderer`

**Version 2.0.0 Released** (2013-04-15)
  * Improved the inner structure of the screen class.
  * Removed SupportSAGE, SupportOpenCABIN, and SupportGLEW.
  * Fixed some bugs.
  * Detailed information [here](transition_guide_1_to_2_jp.md) (sorry, Japanese only).

**Version 1.3.0 Released** (2012-06-09)
  * Added some new methods.
    * kvs::AnyValueArray
    * kvs::ValueArray
    * kvs::Vector2
    * kvs::Vector3
    * kvs::Vector4
  * Fixed some bugs
    * kvs::ValueArray
  * Some modifications for the version of KVS (2.0)

**Version 1.2.0 Released** (2012-04-08)
  * Added some new classes.
    * kvs::Gis
    * kvs::SharedPointer
    * kvs::WeekPointer
    * kvs::glew::HAVSVolumeRenderer
    * kvs::glew::PreIntegrationTable
    * kvs::glew::StochasticPointRenderer
    * kvs::glew::StochasticLineRenderer
    * kvs::glew::StochasticPolygonRenderer
    * kvs::glew::StochasticTetrahedraRenderer
    * kvs::glew::StochasticPointEngine
    * kvs::glew::StochasticLineEngine
    * kvs::glew::StochasticPolygonEngine
    * kvs::glew::StochasticTetrahedraEngine
    * kvs::glew::StochasticRenderingCompositor
    * kvs::glew::StochasticMultivariateTetrahedraRenderer
    * kvs::glew::StochasticMultipleTetrahedraRenderer
    * kvs::glew::StochasticMultipleTetrahedraEngine
    * kvs::glew::StochasticMultipleTetrahedraCompositor
  * Fixed some bugs in the following classes
    * kvs::Streamlines
    * kvs::GlyphBase
    * kvs::rits::ParticleBaseRenderer

**Version 1.1.1 Released** (2011-12-09)
  * Fixed some bugs in the following classes
    * kvs::GrADS
    * kvs::grads::XYZDef
    * kvs::grads::TDef
    * kvs::grads::DataDescriptorFile
  * Prevented an error message for Mac OS X Lion
    * kvs::glew::ParticleVolumeRenderer
  * Prevented an error message for Linux
    * kvs::IDManager
  * kvsmake: Supported resource files for qmake

**Version 1.1.0 Released** (2011-08-10)
  * Added some new classes.
    * kvs::TableObject
    * kvs::TableImporter
    * kvs::KVSMLObjectTable
    * kvs::ParallelCoordinatesRenderer
    * kvs::ScatterPlotRenderer
    * kvs::ScatterPlotMatrixRenderer
    * kvs::glut::ParallelAxisRenderer
    * kvs::glut::Axis2DRenderer
    * kvs::glut::Axis2DMatrixRenderer
    * kvs::RGBFormulae
    * kvs::GrADS
    * kvs::FrontFlow
    * kvs::FrontSTR
  * Added new attributes, label, min\_value and max\_value to Value tag of KVSML format.
    * kvs::KVSMLObjectStructuredVolume
    * kvs::KVSMLObjectUnstructuredVolume
    * kvs::ValueTag
    * kvs::StructuredVolumeImporter
    * kvs::UnstructuredVolumeImporter
    * kvs::VolumeObjectBase
  * Fixed some bugs in the following classes
    * kvs::SphereGlyph
    * kvs::TableImporter
    * kvs::Csv

**Version 1.0.3 Released** (2011-06-18)
  * Fixed some bugs in the following classes
    * kvs::EigenDecomposer
    * kvs::CellBase (transformGlobalToLocal)
  * Changed the array related class to use the string
    * kvs::AnyValue
    * kvs::AnyValueArray
    * kvs::ValueArray

**Version 1.0.2 Released** (2011-05-31)
  * Fixed some bugs in the following classes
    * kvs::KVSMLObjectImage
    * kvs::KVSMLObjectStructuredVolume
    * kvs::KVSMLObjectUnstructuredVolume
    * kvs::KVSMLTransferFunction
  * Enabled multiple registration of the same object to the screen class
    * kvs::Screen
  * kvsmake: Improved compatibility of 'vc' option with VC10

**Version 1.0.1 Released** (2011-01-15)
  * Fixed some bugs in the following classes
    * kvs::ColorMap
    * kvs::OpacityMap
    * kvs::TrilinearInterpolator
    * kvs::AVSUcd
    * kvs::Stl
  * Prevented some warning messages
    * kvs::tiff::Entry
    * kvs::ValueArray
    * kvs::PipelineModule
  * Changed the properties of the member variables in the following class
    * kvs::ParticleVolumeRenderer
  * kvsmake: Improved compatibility of 'vc' option with VC10

**Version 1.0.0 Released** (2010-10-17)
  * Initial release