#  DON'T EDIT THIS FILE.
#  THIS IS GENERATED BY "Configuration/configure_BuildRule.py".


OBJECTS := \
$(OUTDIR)/./Renderer/EnsembleAverageBuffer.o \
$(OUTDIR)/./Renderer/HAVSVolumeRenderer.o \
$(OUTDIR)/./Renderer/ParticleBasedRenderer.o \
$(OUTDIR)/./Renderer/ParticleVolumeRenderer.o \
$(OUTDIR)/./Renderer/PointRenderer.o \
$(OUTDIR)/./Renderer/PolygonRenderer.o \
$(OUTDIR)/./Renderer/PreIntegrationTable.o \
$(OUTDIR)/./Renderer/ProjectedTetrahedraTable.o \
$(OUTDIR)/./Renderer/RayCastingRenderer.o \
$(OUTDIR)/./Renderer/StochasticLineEngine.o \
$(OUTDIR)/./Renderer/StochasticLineRenderer.o \
$(OUTDIR)/./Renderer/StochasticMultivariateTetrahedraEngine.o \
$(OUTDIR)/./Renderer/StochasticMultivariateTetrahedraRenderer.o \
$(OUTDIR)/./Renderer/StochasticPointEngine.o \
$(OUTDIR)/./Renderer/StochasticPointRenderer.o \
$(OUTDIR)/./Renderer/StochasticPolygonEngine.o \
$(OUTDIR)/./Renderer/StochasticPolygonRenderer.o \
$(OUTDIR)/./Renderer/StochasticRendererBase.o \
$(OUTDIR)/./Renderer/StochasticRenderingCompositor.o \
$(OUTDIR)/./Renderer/StochasticRenderingEngine.o \
$(OUTDIR)/./Renderer/StochasticTetrahedraEngine.o \
$(OUTDIR)/./Renderer/StochasticTetrahedraRenderer.o \
$(OUTDIR)/./Viewer/BufferObject.o \
$(OUTDIR)/./Viewer/FragmentShader.o \
$(OUTDIR)/./Viewer/FrameBufferObject.o \
$(OUTDIR)/./Viewer/GeometryShader.o \
$(OUTDIR)/./Viewer/IndexBufferObject.o \
$(OUTDIR)/./Viewer/PixelBufferObject.o \
$(OUTDIR)/./Viewer/ProgramObject.o \
$(OUTDIR)/./Viewer/RenderBuffer.o \
$(OUTDIR)/./Viewer/ShaderObject.o \
$(OUTDIR)/./Viewer/ShaderSource.o \
$(OUTDIR)/./Viewer/Texture3D.o \
$(OUTDIR)/./Viewer/TextureRectangle.o \
$(OUTDIR)/./Viewer/VertexBufferObject.o \
$(OUTDIR)/./Viewer/VertexShader.o \



$(OUTDIR)/./Viewer/%.o: ./Viewer/%.cpp ./Viewer/%.h
	$(MKDIR) $(OUTDIR)/./Viewer
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Renderer/%.o: ./Renderer/%.cpp ./Renderer/%.h
	$(MKDIR) $(OUTDIR)/./Renderer
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<


install::
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLEW/.
	$(INSTALL) ./*.h $(INSTALL_DIR)/include/SupportGLEW/.
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLEW/./Renderer
	$(INSTALL) ./Renderer/*.h $(INSTALL_DIR)/include/SupportGLEW/./Renderer
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLEW/./Renderer/HAVSVolumeRenderer
	$(INSTALL) ./Renderer/HAVSVolumeRenderer/*.h $(INSTALL_DIR)/include/SupportGLEW/./Renderer/HAVSVolumeRenderer
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLEW/./Renderer/ParticleVolumeRenderer
	$(INSTALL) ./Renderer/ParticleVolumeRenderer/*.h $(INSTALL_DIR)/include/SupportGLEW/./Renderer/ParticleVolumeRenderer
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLEW/./Renderer/PointRenderer
	$(INSTALL) ./Renderer/PointRenderer/*.h $(INSTALL_DIR)/include/SupportGLEW/./Renderer/PointRenderer
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLEW/./Renderer/PolygonRenderer
	$(INSTALL) ./Renderer/PolygonRenderer/*.h $(INSTALL_DIR)/include/SupportGLEW/./Renderer/PolygonRenderer
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLEW/./Renderer/RayCastingRenderer
	$(INSTALL) ./Renderer/RayCastingRenderer/*.h $(INSTALL_DIR)/include/SupportGLEW/./Renderer/RayCastingRenderer
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLEW/./Renderer/Shader
	$(INSTALL) ./Renderer/Shader/*.h $(INSTALL_DIR)/include/SupportGLEW/./Renderer/Shader
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLEW/./Renderer/StochasticRenderingEngine
	$(INSTALL) ./Renderer/StochasticRenderingEngine/*.h $(INSTALL_DIR)/include/SupportGLEW/./Renderer/StochasticRenderingEngine
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLEW/./Viewer
	$(INSTALL) ./Viewer/*.h $(INSTALL_DIR)/include/SupportGLEW/./Viewer
