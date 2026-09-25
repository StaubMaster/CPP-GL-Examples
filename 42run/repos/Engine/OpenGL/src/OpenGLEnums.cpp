#include "OpenGLEnums.hpp"

#include <iostream>



std::ostream & GL::operator<<(std::ostream & s, Error val)
{
	switch (val)
	{
		case Error::NoError: s << "NoError"; break;
		case Error::InvalidEnum: s << "InvalidEnum"; break;
		case Error::InvalidValue: s << "InvalidValue"; break;
		case Error::InvalidOperation: s << "InvalidOperation"; break;
		case Error::InvalidFramebufferOperation: s << "InvalidFramebufferOperation"; break;
		case Error::OutOfMemory: s << "OutOfMemory"; break;
		case Error::StackUnderflow: s << "StackUnderflow"; break;
		case Error::StackOverflow: s << "StackOverflow"; break;
		default: s << "Error: " << ((unsigned int)val); break;
	}
	return s;
}

std::ostream & GL::operator<<(std::ostream & s, ParameterName val)
{
	switch (val)
	{
		case ParameterName::AliasedLineWidthRange: s << "AliasedLineWidthRange"; break;
		case ParameterName::ArrayBufferBinding: s << "ArrayBufferBinding"; break;
		case ParameterName::Blend: s << "Blend"; break;
		case ParameterName::BlendColor: s << "BlendColor"; break;
		case ParameterName::BlendDstAlpha: s << "BlendDstAlpha"; break;
		case ParameterName::BlendDstRgb: s << "BlendDstRgb"; break;
		case ParameterName::BlendEquationRgb: s << "BlendEquationRgb"; break;
		case ParameterName::BlendEquationAlpha: s << "BlendEquationAlpha"; break;
		case ParameterName::BlendSrcAlpha: s << "BlendSrcAlpha"; break;
		case ParameterName::BlendSrcRgb: s << "BlendSrcRgb"; break;
		case ParameterName::ColorClearValue: s << "ColorClearValue"; break;
		case ParameterName::ColorLogicOp: s << "ColorLogicOp"; break;
		case ParameterName::ColorWritemask: s << "ColorWritemask"; break;
		case ParameterName::CompressedTextureFormats: s << "CompressedTextureFormats"; break;
		case ParameterName::MaxComputeShaderStorageBlocks: s << "MaxComputeShaderStorageBlocks"; break;
		case ParameterName::MaxCombinedShaderStorageBlocks: s << "MaxCombinedShaderStorageBlocks"; break;
		case ParameterName::MaxComputeUniformBlocks: s << "MaxComputeUniformBlocks"; break;
		case ParameterName::MaxComputeTextureImageUnits: s << "MaxComputeTextureImageUnits"; break;
		case ParameterName::MaxComputeUniformComponents: s << "MaxComputeUniformComponents"; break;
		case ParameterName::MaxComputeAtomicCounters: s << "MaxComputeAtomicCounters"; break;
		case ParameterName::MaxComputeAtomicCounterBuffers: s << "MaxComputeAtomicCounterBuffers"; break;
		case ParameterName::MaxCombinedComputeUniformComponents: s << "MaxCombinedComputeUniformComponents"; break;
		case ParameterName::MaxComputeWorkGroupInvocations: s << "MaxComputeWorkGroupInvocations"; break;
		case ParameterName::MaxComputeWorkGroupCount: s << "MaxComputeWorkGroupCount"; break;
		case ParameterName::MaxComputeWorkGroupSize: s << "MaxComputeWorkGroupSize"; break;
		case ParameterName::DispatchIndirectBufferBinding: s << "DispatchIndirectBufferBinding"; break;
		case ParameterName::MaxDebugGroupStackDepth: s << "MaxDebugGroupStackDepth"; break;
		case ParameterName::DebugGroupStackDepth: s << "DebugGroupStackDepth"; break;
		case ParameterName::ContextFlags: s << "ContextFlags"; break;
		case ParameterName::CullFace: s << "CullFace"; break;
		case ParameterName::CullFaceMode: s << "CullFaceMode"; break;
		case ParameterName::CurrentProgram: s << "CurrentProgram"; break;
		case ParameterName::DepthClearValue: s << "DepthClearValue"; break;
		case ParameterName::DepthFunc: s << "DepthFunc"; break;
		case ParameterName::DepthRange: s << "DepthRange"; break;
		case ParameterName::DepthTest: s << "DepthTest"; break;
		case ParameterName::DepthWritemask: s << "DepthWritemask"; break;
		case ParameterName::Dither: s << "Dither"; break;
		case ParameterName::Doublebuffer: s << "Doublebuffer"; break;
		case ParameterName::DrawBuffer: s << "DrawBuffer"; break;
		case ParameterName::DrawBuffer0: s << "DrawBuffer0"; break;
		case ParameterName::DrawBuffer1: s << "DrawBuffer1"; break;
		case ParameterName::DrawBuffer2: s << "DrawBuffer2"; break;
		case ParameterName::DrawBuffer3: s << "DrawBuffer3"; break;
		case ParameterName::DrawBuffer4: s << "DrawBuffer4"; break;
		case ParameterName::DrawBuffer5: s << "DrawBuffer5"; break;
		case ParameterName::DrawBuffer6: s << "DrawBuffer6"; break;
		case ParameterName::DrawBuffer7: s << "DrawBuffer7"; break;
		case ParameterName::DrawBuffer8: s << "DrawBuffer8"; break;
		case ParameterName::DrawBuffer9: s << "DrawBuffer9"; break;
		case ParameterName::DrawBuffer10: s << "DrawBuffer10"; break;
		case ParameterName::DrawBuffer11: s << "DrawBuffer11"; break;
		case ParameterName::DrawBuffer12: s << "DrawBuffer12"; break;
		case ParameterName::DrawBuffer13: s << "DrawBuffer13"; break;
		case ParameterName::DrawBuffer14: s << "DrawBuffer14"; break;
		case ParameterName::DrawBuffer15: s << "DrawBuffer15"; break;
		case ParameterName::DrawFramebufferBinding: s << "DrawFramebufferBinding"; break;
		case ParameterName::ReadFramebufferBinding: s << "ReadFramebufferBinding"; break;
		case ParameterName::ElementArrayBufferBinding: s << "ElementArrayBufferBinding"; break;
		case ParameterName::FragmentShaderDerivativeHint: s << "FragmentShaderDerivativeHint"; break;
		case ParameterName::ImplementationColorReadFormat: s << "ImplementationColorReadFormat"; break;
		case ParameterName::ImplementationColorReadType: s << "ImplementationColorReadType"; break;
		case ParameterName::LineSmooth: s << "LineSmooth"; break;
		case ParameterName::LineSmoothHint: s << "LineSmoothHint"; break;
		case ParameterName::LineWidth: s << "LineWidth"; break;
		case ParameterName::LayerProvokingVertex: s << "LayerProvokingVertex"; break;
		case ParameterName::LogicOpMode: s << "LogicOpMode"; break;
		case ParameterName::MajorVersion: s << "MajorVersion"; break;
		case ParameterName::Max3dTextureSize: s << "Max3dTextureSize"; break;
		case ParameterName::MaxArrayTextureLayers: s << "MaxArrayTextureLayers"; break;
		case ParameterName::MaxClipDistances: s << "MaxClipDistances"; break;
		case ParameterName::MaxColorTextureSamples: s << "MaxColorTextureSamples"; break;
		case ParameterName::MaxCombinedAtomicCounters: s << "MaxCombinedAtomicCounters"; break;
		case ParameterName::MaxCombinedFragmentUniformComponents: s << "MaxCombinedFragmentUniformComponents"; break;
		case ParameterName::MaxCombinedGeometryUniformComponents: s << "MaxCombinedGeometryUniformComponents"; break;
		case ParameterName::MaxCombinedTextureImageUnits: s << "MaxCombinedTextureImageUnits"; break;
		case ParameterName::MaxCombinedUniformBlocks: s << "MaxCombinedUniformBlocks"; break;
		case ParameterName::MaxCombinedVertexUniformComponents: s << "MaxCombinedVertexUniformComponents"; break;
		case ParameterName::MaxCubeMapTextureSize: s << "MaxCubeMapTextureSize"; break;
		case ParameterName::MaxDepthTextureSamples: s << "MaxDepthTextureSamples"; break;
		case ParameterName::MaxDrawBuffers: s << "MaxDrawBuffers"; break;
		case ParameterName::MaxDualSourceDrawBuffers: s << "MaxDualSourceDrawBuffers"; break;
		case ParameterName::MaxElementsIndices: s << "MaxElementsIndices"; break;
		case ParameterName::MaxElementsVertices: s << "MaxElementsVertices"; break;
		case ParameterName::MaxFragmentAtomicCounters: s << "MaxFragmentAtomicCounters"; break;
		case ParameterName::MaxFragmentShaderStorageBlocks: s << "MaxFragmentShaderStorageBlocks"; break;
		case ParameterName::MaxFragmentInputComponents: s << "MaxFragmentInputComponents"; break;
		case ParameterName::MaxFragmentUniformComponents: s << "MaxFragmentUniformComponents"; break;
		case ParameterName::MaxFragmentUniformVectors: s << "MaxFragmentUniformVectors"; break;
		case ParameterName::MaxFragmentUniformBlocks: s << "MaxFragmentUniformBlocks"; break;
		case ParameterName::MaxFramebufferWidth: s << "MaxFramebufferWidth"; break;
		case ParameterName::MaxFramebufferHeight: s << "MaxFramebufferHeight"; break;
		case ParameterName::MaxFramebufferLayers: s << "MaxFramebufferLayers"; break;
		case ParameterName::MaxFramebufferSamples: s << "MaxFramebufferSamples"; break;
		case ParameterName::MaxGeometryAtomicCounters: s << "MaxGeometryAtomicCounters"; break;
		case ParameterName::MaxGeometryShaderStorageBlocks: s << "MaxGeometryShaderStorageBlocks"; break;
		case ParameterName::MaxGeometryInputComponents: s << "MaxGeometryInputComponents"; break;
		case ParameterName::MaxGeometryOutputComponents: s << "MaxGeometryOutputComponents"; break;
		case ParameterName::MaxGeometryTextureImageUnits: s << "MaxGeometryTextureImageUnits"; break;
		case ParameterName::MaxGeometryUniformBlocks: s << "MaxGeometryUniformBlocks"; break;
		case ParameterName::MaxGeometryUniformComponents: s << "MaxGeometryUniformComponents"; break;
		case ParameterName::MaxIntegerSamples: s << "MaxIntegerSamples"; break;
		case ParameterName::MinMapBufferAlignment: s << "MinMapBufferAlignment"; break;
		case ParameterName::MaxLabelLength: s << "MaxLabelLength"; break;
		case ParameterName::MaxProgramTexelOffset: s << "MaxProgramTexelOffset"; break;
		case ParameterName::MinProgramTexelOffset: s << "MinProgramTexelOffset"; break;
		case ParameterName::MaxRectangleTextureSize: s << "MaxRectangleTextureSize"; break;
		case ParameterName::MaxRenderbufferSize: s << "MaxRenderbufferSize"; break;
		case ParameterName::MaxSampleMaskWords: s << "MaxSampleMaskWords"; break;
		case ParameterName::MaxServerWaitTimeout: s << "MaxServerWaitTimeout"; break;
		case ParameterName::MaxShaderStorageBufferBindings: s << "MaxShaderStorageBufferBindings"; break;
		case ParameterName::MaxTessControlAtomicCounters: s << "MaxTessControlAtomicCounters"; break;
		case ParameterName::MaxTessEvaluationAtomicCounters: s << "MaxTessEvaluationAtomicCounters"; break;
		case ParameterName::MaxTessControlShaderStorageBlocks: s << "MaxTessControlShaderStorageBlocks"; break;
		case ParameterName::MaxTessEvaluationShaderStorageBlocks: s << "MaxTessEvaluationShaderStorageBlocks:"; break;
		case ParameterName::MaxTextureBufferSize: s << "MaxTextureBufferSize"; break;
		case ParameterName::MaxTextureImageUnits: s << "MaxTextureImageUnits"; break;
		case ParameterName::MaxTextureLodBias: s << "MaxTextureLodBias"; break;
		case ParameterName::MaxTextureSize: s << "MaxTextureSize"; break;
		case ParameterName::MaxUniformBufferBindings: s << "MaxUniformBufferBindings"; break;
		case ParameterName::MaxUniformBlockSize: s << "MaxUniformBlockSize"; break;
		case ParameterName::MaxUniformLocations: s << "MaxUniformLocations"; break;
		//case ParameterName::MaxVaryingComponents: s << "MaxVaryingComponents"; break;
		//case ParameterName::MaxVaryingComponents: s << "MaxVaryingComponents/MaxVaryingFloats"; break;
		case ParameterName::MaxVaryingVectors: s << "MaxVaryingVectors"; break;
		//case ParameterName::MaxVaryingFloats: s << "MaxVaryingFloats"; break; //
		case ParameterName::MaxVertexAtomicCounters: s << "MaxVertexAtomicCounters"; break;
		case ParameterName::MaxVertexAttribs: s << "MaxVertexAttribs"; break;
		case ParameterName::MaxVertexShaderStorageBlocks: s << "MaxVertexShaderStorageBlocks"; break;
		case ParameterName::MaxVertexTextureImageUnits: s << "MaxVertexTextureImageUnits"; break;
		case ParameterName::MaxVertexUniformComponents: s << "MaxVertexUniformComponents"; break;
		case ParameterName::MaxVertexUniformVectors: s << "MaxVertexUniformVectors"; break;
		case ParameterName::MaxVertexOutputComponents: s << "MaxVertexOutputComponents"; break;
		case ParameterName::MaxVertexUniformBlocks: s << "MaxVertexUniformBlocks"; break;
		case ParameterName::MaxViewportDims: s << "MaxViewportDims"; break;
		case ParameterName::MaxViewports: s << "MaxViewports"; break;
		case ParameterName::MinorVersion: s << "MinorVersion"; break;
		case ParameterName::NumCompressedTextureFormats: s << "NumCompressedTextureFormats"; break;
		case ParameterName::NumExtensions: s << "NumExtensions"; break;
		case ParameterName::NumProgramBinaryFormats: s << "NumProgramBinaryFormats"; break;
		case ParameterName::NumShaderBinaryFormats: s << "NumShaderBinaryFormats"; break;
		case ParameterName::PackAlignment: s << "PackAlignment"; break;
		case ParameterName::PackImageHeight: s << "PackImageHeight"; break;
		case ParameterName::PackLsbFirst: s << "PackLsbFirst"; break;
		case ParameterName::PackRowLength: s << "PackRowLength"; break;
		case ParameterName::PackSkipImages: s << "PackSkipImages"; break;
		case ParameterName::PackSkipPixels: s << "PackSkipPixels"; break;
		case ParameterName::PackSkipRows: s << "PackSkipRows"; break;
		case ParameterName::PackSwapBytes: s << "PackSwapBytes"; break;
		case ParameterName::PixelPackBufferBinding: s << "PixelPackBufferBinding"; break;
		case ParameterName::PixelUnpackBufferBinding: s << "PixelUnpackBufferBinding"; break;
		case ParameterName::PointFadeThresholdSize: s << "PointFadeThresholdSize"; break;
		case ParameterName::PrimitiveRestartIndex: s << "PrimitiveRestartIndex"; break;
		case ParameterName::ProgramBinaryFormats: s << "ProgramBinaryFormats"; break;
		case ParameterName::ProgramPipelineBinding: s << "ProgramPipelineBinding"; break;
		case ParameterName::ProgramPointSize: s << "ProgramPointSize"; break;
		case ParameterName::ProvokingVertex: s << "ProvokingVertex"; break;
		case ParameterName::PointSize: s << "PointSize"; break;
		case ParameterName::PointSizeGranularity: s << "PointSizeGranularity"; break;
		case ParameterName::PointSizeRange: s << "PointSizeRange"; break;
		case ParameterName::PolygonOffsetFactor: s << "PolygonOffsetFactor"; break;
		case ParameterName::PolygonOffsetUnits: s << "PolygonOffsetUnits"; break;
		case ParameterName::PolygonOffsetClamp: s << "PolygonOffsetClamp"; break;
		case ParameterName::PolygonOffsetFill: s << "PolygonOffsetFill"; break;
		case ParameterName::PolygonOffsetLine: s << "PolygonOffsetLine"; break;
		case ParameterName::PolygonOffsetPoint: s << "PolygonOffsetPoint"; break;
		case ParameterName::PolygonSmooth: s << "PolygonSmooth"; break;
		case ParameterName::PolygonSmoothHint: s << "PolygonSmoothHint"; break;
		case ParameterName::ReadBuffer: s << "ReadBuffer"; break;
		case ParameterName::RenderbufferBinding: s << "RenderbufferBinding"; break;
		case ParameterName::SampleBuffers: s << "SampleBuffers"; break;
		case ParameterName::SampleCoverageValue: s << "SampleCoverageValue"; break;
		case ParameterName::SampleCoverageInvert: s << "SampleCoverageInvert"; break;
		case ParameterName::SampleMaskValue: s << "SampleMaskValue"; break;
		case ParameterName::SamplerBinding: s << "SamplerBinding"; break;
		case ParameterName::Samples: s << "Samples"; break;
		case ParameterName::ScissorBox: s << "ScissorBox"; break;
		case ParameterName::ScissorTest: s << "ScissorTest"; break;
		case ParameterName::ShaderCompiler: s << "ShaderCompiler"; break;
		case ParameterName::ShaderStorageBufferBinding: s << "ShaderStorageBufferBinding"; break;
		case ParameterName::ShaderStorageBufferOffsetAlignment: s << "ShaderStorageBufferOffsetAlignment"; break;
		case ParameterName::ShaderStorageBufferStart: s << "ShaderStorageBufferStart"; break;
		case ParameterName::ShaderStorageBufferSize: s << "ShaderStorageBufferSize"; break;
		case ParameterName::SmoothLineWidthRange: s << "SmoothLineWidthRange"; break;
		case ParameterName::SmoothLineWidthGranularity: s << "SmoothLineWidthGranularity"; break;
		case ParameterName::StencilBackFail: s << "StencilBackFail"; break;
		case ParameterName::StencilBackFunc: s << "StencilBackFunc"; break;
		case ParameterName::StencilBackPassDepthFail: s << "StencilBackPassDepthFail"; break;
		case ParameterName::StencilBackPassDepthPass: s << "StencilBackPassDepthPass"; break;
		case ParameterName::StencilBackRef: s << "StencilBackRef"; break;
		case ParameterName::StencilBackValueMask: s << "StencilBackValueMask"; break;
		case ParameterName::StencilBackWritemask: s << "StencilBackWritemask"; break;
		case ParameterName::StencilClearValue: s << "StencilClearValue"; break;
		case ParameterName::StencilFail: s << "StencilFail"; break;
		case ParameterName::StencilFunc: s << "StencilFunc"; break;
		case ParameterName::StencilPassDepthFail: s << "StencilPassDepthFail"; break;
		case ParameterName::StencilPassDepthPass: s << "StencilPassDepthPass"; break;
		case ParameterName::StencilRef: s << "StencilRef"; break;
		case ParameterName::StencilTest: s << "StencilTest"; break;
		case ParameterName::StencilValueMask: s << "StencilValueMask"; break;
		case ParameterName::StencilWritemask: s << "StencilWritemask"; break;
		case ParameterName::Stereo: s << "Stereo"; break;
		case ParameterName::SubpixelBits: s << "SubpixelBits"; break;
		case ParameterName::TextureBinding1D: s << "TextureBinding1D"; break;
		case ParameterName::TextureBinding1DArray: s << "TextureBinding1DArray"; break;
		case ParameterName::TextureBinding2D: s << "TextureBinding2D"; break;
		case ParameterName::TextureBinding2DArray: s << "TextureBinding2DArray"; break;
		case ParameterName::TextureBinding2DMultisample: s << "TextureBinding2DMultisample"; break;
		case ParameterName::TextureBinding2DMultisampleArray: s << "TextureBinding2DMultisampleArray"; break;
		case ParameterName::TextureBinding3D: s << "TextureBinding3D"; break;
		case ParameterName::TextureBindingBuffer: s << "TextureBindingBuffer"; break;
		case ParameterName::TextureBindingCubeMap: s << "TextureBindingCubeMap"; break;
		case ParameterName::TextureBindingRectangle: s << "TextureBindingRectangle"; break;
		case ParameterName::TextureCompressionHint: s << "TextureCompressionHint"; break;
		case ParameterName::TextureBufferOffsetAlignment: s << "TextureBufferOffsetAlignment"; break;
		case ParameterName::Timestamp: s << "Timestamp"; break;
		case ParameterName::TransformFeedbackBufferBinding: s << "TransformFeedbackBufferBinding"; break;
		case ParameterName::TransformFeedbackBufferStart: s << "TransformFeedbackBufferStart"; break;
		case ParameterName::TransformFeedbackBufferSize: s << "TransformFeedbackBufferSize"; break;
		case ParameterName::UniformBufferBinding: s << "UniformBufferBinding"; break;
		case ParameterName::UniformBufferOffsetAlignment: s << "UniformBufferOffsetAlignment"; break;
		case ParameterName::UniformBufferSize: s << "UniformBufferSize"; break;
		case ParameterName::UniformBufferStart: s << "UniformBufferStart"; break;
		case ParameterName::UnpackAlignment: s << "UnpackAlignment"; break;
		case ParameterName::UnpackImageHeight: s << "UnpackImageHeight"; break;
		case ParameterName::UnpackLsbFirst: s << "UnpackLsbFirst"; break;
		case ParameterName::UnpackRowLength: s << "UnpackRowLength"; break;
		case ParameterName::UnpackSkipImages: s << "UnpackSkipImages"; break;
		case ParameterName::UnpackSkipPixels: s << "UnpackSkipPixels"; break;
		case ParameterName::UnpackSkipRows: s << "UnpackSkipRows"; break;
		case ParameterName::UnpackSwapBytes: s << "UnpackSwapBytes"; break;
		case ParameterName::VertexArrayBinding: s << "VertexArrayBinding"; break;
		case ParameterName::VertexBindingDivisor: s << "VertexBindingDivisor"; break;
		case ParameterName::VertexBindingOffset: s << "VertexBindingOffset"; break;
		case ParameterName::VertexBindingStride: s << "VertexBindingStride"; break;
		case ParameterName::VertexBindingBuffer: s << "VertexBindingBuffer"; break;
		case ParameterName::MaxVertexAttribRelativeOffset: s << "MaxVertexAttribRelativeOffset"; break;
		case ParameterName::MaxVertexAttribBindings: s << "MaxVertexAttribBindings"; break;
		case ParameterName::Viewport: s << "Viewport"; break;
		case ParameterName::ViewportBoundsRange: s << "ViewportBoundsRange"; break;
		case ParameterName::ViewportIndexProvokingVertex: s << "ViewportIndexProvokingVertex"; break;
		case ParameterName::ViewportSubpixelBits: s << "ViewportSubpixelBits"; break;
		case ParameterName::MaxElementIndex: s << "MaxElementIndex"; break;
		default: s << "ParameterName: " << ((unsigned int)val); break;
	}
	return s;
}

GL::ClearMask GL::operator|(ClearMask v0, ClearMask v1) { return (ClearMask)((unsigned int)v0 | (unsigned int)v1); }



std::ostream & GL::operator<<(std::ostream & s, Comparison val)
{
	switch (val)
	{
		case Comparison::Never: s << "Never"; break;
		case Comparison::Less: s << "Less"; break;
		case Comparison::Equal: s << "Equal"; break;
		case Comparison::Lequal: s << "Lequal"; break;
		case Comparison::Greater: s << "Greater"; break;
		case Comparison::Notequal: s << "Notequal"; break;
		case Comparison::Gequal: s << "Gequal"; break;
		case Comparison::Always: s << "Always"; break;
		default: s << "Comparison: " << ((unsigned int)val); break;
	}
	return s;
}



std::ostream & GL::operator<<(std::ostream & s, Side val)
{
	switch (val)
	{
		case Side::Front: s << "Front"; break;
		case Side::Back: s << "Back"; break;
		case Side::FrontAndBack: s << "FrontAndBack"; break;
		default: s << "Side: " << ((unsigned int)val); break;
	}
	return s;
}
std::ostream & GL::operator<<(std::ostream & s, FrontSide val)
{
	switch (val)
	{
		case FrontSide::Cw: s << "Cw"; break;
		case FrontSide::Ccw: s << "Ccw"; break;
		default: s << "FrontSide: " << ((unsigned int)val); break;
	}
	return s;
}



std::ostream & GL::operator<<(std::ostream & s, ShaderType val)
{
	switch (val)
	{
		case ShaderType::ComputeShader: s << "ComputeShader"; break;
		case ShaderType::VertexShader: s << "VertexShader"; break;
		case ShaderType::TessControlShader: s << "TessControlShader"; break;
		case ShaderType::TessEvaluationShade: s << "TessEvaluationShade"; break;
		case ShaderType::GeometryShader: s << "GeometryShader"; break;
		case ShaderType::FragmentShader: s << "FragmentShader"; break;
		default: s << "ShaderType: " << ((unsigned int)val); break;
	}
	return s;
}
std::ostream & GL::operator<<(std::ostream & s, ShaderParameterName val)
{
	switch (val)
	{
		case ShaderParameterName::ShaderType: s << "ShaderType"; break;
		case ShaderParameterName::DeleteStatus: s << "DeleteStatus"; break;
		case ShaderParameterName::CompileStatus: s << "CompileStatus"; break;
		case ShaderParameterName::InfoLogLength: s << "InfoLogLength"; break;
		case ShaderParameterName::ShaderSourceLength: s << "ShaderSourceLength"; break;
		default: s << "ShaderParameterName: " << ((unsigned int)val); break;
	}
	return s;
}
std::ostream & GL::operator<<(std::ostream & s, ShaderProgramParameterName val)
{
	switch (val)
	{
		case ShaderProgramParameterName::DeleteStatus: s << "DeleteStatus"; break;
		case ShaderProgramParameterName::LinkStatus: s << "LinkStatus"; break;
		case ShaderProgramParameterName::ValidateStatus: s << "ValidateStatus"; break;
		case ShaderProgramParameterName::InfoLogLength: s << "InfoLogLength"; break;
		case ShaderProgramParameterName::AttachedShaders: s << "AttachedShaders"; break;
		case ShaderProgramParameterName::ActiveAtomicCounterBuffers: s << "ActiveAtomicCounterBuffers"; break;
		case ShaderProgramParameterName::ActiveAttributes: s << "ActiveAttributes"; break;
		case ShaderProgramParameterName::ActiveAttributeMaxLength: s << "ActiveAttributeMaxLength"; break;
		case ShaderProgramParameterName::ActiveUniforms: s << "ActiveUniforms"; break;
		case ShaderProgramParameterName::ActiveUniformBlocks: s << "ActiveUniformBlocks"; break;
		case ShaderProgramParameterName::ActiveUniformBlockMaxNameLength: s << "ActiveUniformBlockMaxNameLength"; break;
		case ShaderProgramParameterName::ActiveUniformMaxLength: s << "ActiveUniformMaxLength"; break;
		case ShaderProgramParameterName::ComputeWorkGroupSize: s << "ComputeWorkGroupSize"; break;
		case ShaderProgramParameterName::ProgramBinaryLength: s << "ProgramBinaryLength"; break;
		case ShaderProgramParameterName::TransformFeedbackBufferMode: s << "TransformFeedbackBufferMode"; break;
		case ShaderProgramParameterName::TransformFeedbackVaryings: s << "TransformFeedbackVaryings"; break;
		case ShaderProgramParameterName::TransformFeedbackVaryingMaxLength: s << "TransformFeedbackVaryingMaxLength"; break;
		case ShaderProgramParameterName::GeometryVerticesOut: s << "GeometryVerticesOut"; break;
		case ShaderProgramParameterName::GeometryInputType: s << "GeometryInputType"; break;
		case ShaderProgramParameterName::GeometryOutputType: s << "GeometryOutputType"; break;
		default: s << "ShaderProgramParameterName: " << ((unsigned int)val); break;
	}
	return s;
}



std::ostream & GL::operator<<(std::ostream & s, AttributeType val)
{
	switch (val)
	{
		case AttributeType::HalfFloat: s << "HalfFloat"; break;
		case AttributeType::Float: s << "Float"; break;
		case AttributeType::Double: s << "Double"; break;
		case AttributeType::Fixed: s << "Fixed"; break;
		case AttributeType::Int2101010Rev: s << "Int2101010Rev"; break;
		case AttributeType::UnsignedInt2101010Rev: s << "UnsignedInt2101010Rev"; break;
		case AttributeType::UnsignedInt10f11f11fRev: s << "UnsignedInt10f11f11fRev"; break;
		case AttributeType::Byte: s << "Byte"; break;
		case AttributeType::UnsignedByte: s << "UnsignedByte"; break;
		case AttributeType::Short: s << "Short"; break;
		case AttributeType::UnsignedShort: s << "UnsignedShort"; break;
		case AttributeType::Int: s << "Int"; break;
		case AttributeType::UnsignedInt: s << "UnsignedInt"; break;
		default: s << "AttributeType: " << ((unsigned int)val); break;
	}
	return s;
}
std::ostream & GL::operator<<(std::ostream & s, AttributeIntType val)
{
	switch (val)
	{
		case AttributeIntType::Byte: s << "Byte"; break;
		case AttributeIntType::UnsignedByte: s << "UnsignedByte"; break;
		case AttributeIntType::Short: s << "Short"; break;
		case AttributeIntType::UnsignedShort: s << "UnsignedShort"; break;
		case AttributeIntType::Int: s << "Int"; break;
		case AttributeIntType::UnsignedInt: s << "UnsignedInt"; break;
		default: s << "AttributeIntType: " << ((unsigned int)val); break;
	}
	return s;
}



std::ostream & GL::operator<<(std::ostream & s, DrawMode val)
{
	switch (val)
	{
		case DrawMode::Points: s << "Points"; break;
		case DrawMode::LineStrip: s << "LineStrip"; break;
		case DrawMode::LineLoop: s << "LineLoop"; break;
		case DrawMode::Lines: s << "Lines"; break;
		case DrawMode::LineStripAdjacency: s << "LineStripAdjacency"; break;
		case DrawMode::LinesAdjacency: s << "LinesAdjacency"; break;
		case DrawMode::TriangleStrip: s << "TriangleStrip"; break;
		case DrawMode::TriangleFan: s << "TriangleFan"; break;
		case DrawMode::Triangles: s << "Triangles"; break;
		case DrawMode::TriangleStripAdjacency: s << "TriangleStripAdjacency"; break;
		case DrawMode::TrianglesAdjacency: s << "TrianglesAdjacency"; break;
		case DrawMode::Patches: s << "Patches"; break;
		default: s << "DrawMode: " << ((unsigned int)val); break;
	}
	return s;
}
std::ostream & GL::operator<<(std::ostream & s, DrawIndexType val)
{
	switch (val)
	{
		case DrawIndexType::UnsignedByte: s << "UnsignedByte"; break;
		case DrawIndexType::UnsignedShort: s << "UnsignedShort"; break;
		case DrawIndexType::UnsignedInt: s << "UnsignedInt"; break;
		default: s << "DrawIndexType: " << ((unsigned int)val); break;
	}
	return s;
}



std::ostream & GL::operator<<(std::ostream & s, BufferTarget val)
{
	switch (val)
	{
		case BufferTarget::ArrayBuffer: s << "ArrayBuffer"; break;
		case BufferTarget::AtomicCounterBuffer: s << "AtomicCounterBuffer"; break;
		case BufferTarget::CopyReadBuffer: s << "CopyReadBuffer"; break;
		case BufferTarget::CopyWriteBuffer: s << "CopyWriteBuffer"; break;
		case BufferTarget::DispatchIndirectBuffer: s << "DispatchIndirectBuffer"; break;
		case BufferTarget::DrawIndirectBuffer: s << "DrawIndirectBuffer"; break;
		case BufferTarget::ElementArrayBuffer: s << "ElementArrayBuffer"; break;
		case BufferTarget::PixelPackBuffer: s << "PixelPackBuffer"; break;
		case BufferTarget::PixelUnpackBuffer: s << "PixelUnpackBuffer"; break;
		case BufferTarget::QueryBuffer: s << "QueryBuffer"; break;
		case BufferTarget::ShaderStorageBuffer: s << "ShaderStorageBuffer"; break;
		case BufferTarget::TextureBuffer: s << "TextureBuffer"; break;
		case BufferTarget::TransformFeedbackBuffer: s << "TransformFeedbackBuffer"; break;
		case BufferTarget::UniformBuffer: s << "UniformBuffer"; break;
		default: s << "BufferTarget: " << ((unsigned int)val); break;
	}
	return s;
}
std::ostream & GL::operator<<(std::ostream & s, BufferDataUsage val)
{
	switch (val)
	{
		case BufferDataUsage::StreamDraw: s << "StreamDraw"; break;
		case BufferDataUsage::StreamRead: s << "StreamRead"; break;
		case BufferDataUsage::StreamCopy: s << "StreamCopy"; break;
		case BufferDataUsage::StaticDraw: s << "StaticDraw"; break;
		case BufferDataUsage::StaticRead: s << "StaticRead"; break;
		case BufferDataUsage::StaticCopy: s << "StaticCopy"; break;
		case BufferDataUsage::DynamicDraw: s << "DynamicDraw"; break;
		case BufferDataUsage::DynamicRead: s << "DynamicRead"; break;
		case BufferDataUsage::DynamicCopy: s << "DynamicCopy"; break;
		default: s << "BufferDataUsage: " << ((unsigned int)val); break;
	}
	return s;
}
std::ostream & GL::operator<<(std::ostream & s, BufferAccess val)
{
	switch (val)
	{
		case BufferAccess::ReadOnly: s << "ReadOnly"; break;
		case BufferAccess::WriteOnly: s << "WriteOnly"; break;
		case BufferAccess::ReadWrite: s << "ReadWrite"; break;
		default: s << "BufferAccess: " << ((unsigned int)val); break;
	}
	return s;
}



std::ostream & GL::operator<<(std::ostream & s, PixelDataType val)
{
	switch (val)
	{
		case PixelDataType::UnsignedByte: s << "UnsignedByte"; break;
		case PixelDataType::Byte: s << "Byte"; break;
		case PixelDataType::UnsignedShort: s << "UnsignedShort"; break;
		case PixelDataType::Short: s << "Short"; break;
		case PixelDataType::UnsignedInt: s << "UnsignedInt"; break;
		case PixelDataType::Int: s << "Int"; break;
		case PixelDataType::HalfFloat: s << "HalfFloat"; break;
		case PixelDataType::Float: s << "Float"; break;
		case PixelDataType::UnsignedByte332: s << "UnsignedByte332"; break;
		case PixelDataType::UnsignedByte233Rev: s << "UnsignedByte233Rev"; break;
		case PixelDataType::UnsignedShort565: s << "UnsignedShort565"; break;
		case PixelDataType::UnsignedShort565Rev: s << "UnsignedShort565Rev"; break;
		case PixelDataType::UnsignedShort4444: s << "UnsignedShort4444"; break;
		case PixelDataType::UnsignedShort4444Rev: s << "UnsignedShort4444Rev"; break;
		case PixelDataType::UnsignedShort5551: s << "UnsignedShort5551"; break;
		case PixelDataType::UnsignedShort1555Rev: s << "UnsignedShort1555Rev"; break;
		case PixelDataType::UnsignedInt8888: s << "UnsignedInt8888"; break;
		case PixelDataType::UnsignedInt8888Rev: s << "UnsignedInt8888Rev"; break;
		case PixelDataType::UnsignedInt1010102: s << "UnsignedInt1010102"; break;
		case PixelDataType::UnsignedInt2101010Rev: s << "UnsignedInt2101010Rev"; break;
		default: s << "PixelDataType: " << ((unsigned int)val); break;
	}
	return s;
}
std::ostream & GL::operator<<(std::ostream & s, PixelDataFormat val)
{
	switch (val)
	{
		case PixelDataFormat::Red: s << "Red"; break;
		case PixelDataFormat::Rg: s << "Rg"; break;
		case PixelDataFormat::Rgb: s << "Rgb"; break;
		case PixelDataFormat::Bgr: s << "Bgr"; break;
		case PixelDataFormat::Rgba: s << "Rgba"; break;
		case PixelDataFormat::Bgra: s << "Bgra"; break;
		case PixelDataFormat::RedInteger: s << "RedInteger"; break;
		case PixelDataFormat::RgInteger: s << "RgInteger"; break;
		case PixelDataFormat::RgbInteger: s << "RgbInteger"; break;
		case PixelDataFormat::BgrInteger: s << "BgrInteger"; break;
		case PixelDataFormat::RgbaInteger: s << "RgbaInteger"; break;
		case PixelDataFormat::BgraInteger: s << "BgraInteger"; break;
		case PixelDataFormat::StencilIndex: s << "StencilIndex"; break;
		case PixelDataFormat::DepthComponent: s << "DepthComponent"; break;
		case PixelDataFormat::DepthStencil: s << "DepthStencil"; break;
		default: s << "PixelDataFormat: " << ((unsigned int)val); break;
	}
	return s;
}
std::ostream & GL::operator<<(std::ostream & s, InternalFormat val)
{
	switch (val)
	{
		case InternalFormat::DepthComponent: s << "DepthComponent"; break;
		case InternalFormat::DepthStencil: s << "DepthStencil"; break;
		case InternalFormat::Red: s << "Red"; break;
		case InternalFormat::Rg: s << "Rg"; break;
		case InternalFormat::Rgb: s << "Rgb"; break;
		case InternalFormat::Rgba: s << "Rgba"; break;
		case InternalFormat::R8: s << "R8"; break;
		case InternalFormat::R8Snorm: s << "R8Snorm"; break;
		case InternalFormat::R16: s << "R16"; break;
		case InternalFormat::R16Snorm: s << "R16Snorm"; break;
		case InternalFormat::Rg8: s << "Rg8"; break;
		case InternalFormat::Rg8Snorm: s << "Rg8Snorm"; break;
		case InternalFormat::Rg16: s << "Rg16"; break;
		case InternalFormat::Rg16Snorm: s << "Rg16Snorm"; break;
		case InternalFormat::R3G3B2: s << "R3G3B2"; break;
		case InternalFormat::Rgb4: s << "Rgb4"; break;
		case InternalFormat::Rgb5: s << "Rgb5"; break;
		case InternalFormat::Rgb8: s << "Rgb8"; break;
		case InternalFormat::Rgb8Snorm: s << "Rgb8Snorm"; break;
		case InternalFormat::Rgb10: s << "Rgb10"; break;
		case InternalFormat::Rgb12: s << "Rgb12"; break;
		case InternalFormat::Rgb16Snorm: s << "Rgb16Snorm"; break;
		case InternalFormat::Rgba2: s << "Rgba2"; break;
		case InternalFormat::Rgba4: s << "Rgba4"; break;
		case InternalFormat::Rgb5A1: s << "Rgb5A1"; break;
		case InternalFormat::Rgba8: s << "Rgba8"; break;
		case InternalFormat::Rgba8Snorm: s << "Rgba8Snorm"; break;
		case InternalFormat::Rgb10A2: s << "Rgb10A2"; break;
		case InternalFormat::Rgb10A2ui: s << "Rgb10A2ui"; break;
		case InternalFormat::Rgba12: s << "Rgba12"; break;
		case InternalFormat::Rgba16: s << "Rgba16"; break;
		case InternalFormat::Srgb8: s << "Srgb8"; break;
		case InternalFormat::Srgb8Alpha8: s << "Srgb8Alpha8"; break;
		case InternalFormat::R16f: s << "R16f"; break;
		case InternalFormat::Rg16f: s << "Rg16f"; break;
		case InternalFormat::Rgb16f: s << "Rgb16f"; break;
		case InternalFormat::Rgba16f: s << "Rgba16f"; break;
		case InternalFormat::R32f: s << "R32f"; break;
		case InternalFormat::Rg32f: s << "Rg32f"; break;
		case InternalFormat::Rgb32f: s << "Rgb32f"; break;
		case InternalFormat::Rgba32f: s << "Rgba32f"; break;
		case InternalFormat::R11fG11fB10f: s << "R11fG11fB10f"; break;
		case InternalFormat::Rgb9E5: s << "Rgb9E5"; break;
		case InternalFormat::R8i: s << "R8i"; break;
		case InternalFormat::R8ui: s << "R8ui"; break;
		case InternalFormat::R16i: s << "R16i"; break;
		case InternalFormat::R16ui: s << "R16ui"; break;
		case InternalFormat::R32i: s << "R32i"; break;
		case InternalFormat::R32ui: s << "R32ui"; break;
		case InternalFormat::Rg8i: s << "Rg8i"; break;
		case InternalFormat::Rg8ui: s << "Rg8ui"; break;
		case InternalFormat::Rg16i: s << "Rg16i"; break;
		case InternalFormat::Rg16ui: s << "Rg16ui"; break;
		case InternalFormat::Rg32i: s << "Rg32i"; break;
		case InternalFormat::Rg32ui: s << "Rg32ui"; break;
		case InternalFormat::Rgb8i: s << "Rgb8i"; break;
		case InternalFormat::Rgb8ui: s << "Rgb8ui"; break;
		case InternalFormat::Rgb16i: s << "Rgb16i"; break;
		case InternalFormat::Rgb16ui: s << "Rgb16ui"; break;
		case InternalFormat::Rgb32i: s << "Rgb32i"; break;
		case InternalFormat::Rgb32ui: s << "Rgb32ui"; break;
		case InternalFormat::Rgba8i: s << "Rgba8i"; break;
		case InternalFormat::Rgba8ui: s << "Rgba8ui"; break;
		case InternalFormat::Rgba16i: s << "Rgba16i"; break;
		case InternalFormat::Rgba16ui: s << "Rgba16ui"; break;
		case InternalFormat::Rgba32i: s << "Rgba32i"; break;
		case InternalFormat::Rgba32ui: s << "Rgba32ui"; break;
		case InternalFormat::CompressedRed: s << "CompressedRed"; break;
		case InternalFormat::CompressedRg: s << "CompressedRg"; break;
		case InternalFormat::CompressedRgb: s << "CompressedRgb"; break;
		case InternalFormat::CompressedRgba: s << "CompressedRgba"; break;
		case InternalFormat::CompressedSrgb: s << "CompressedSrgb"; break;
		case InternalFormat::CompressedSrgbAlpha: s << "CompressedSrgbAlpha"; break;
		case InternalFormat::CompressedRedRgtc1: s << "CompressedRedRgtc1"; break;
		case InternalFormat::CompressedSignedRedRgtc1: s << "CompressedSignedRedRgtc1"; break;
		case InternalFormat::CompressedRgRgtc2: s << "CompressedRgRgtc2"; break;
		case InternalFormat::CompressedSignedRgRgtc2: s << "CompressedSignedRgRgtc2"; break;
		case InternalFormat::CompressedRgbaBptcUnorm: s << "CompressedRgbaBptcUnorm"; break;
		case InternalFormat::CompressedSrgbAlphaBptcUnorm: s << "CompressedSrgbAlphaBptcUnorm"; break;
		case InternalFormat::CompressedRgbBptcSignedFloat: s << "CompressedRgbBptcSignedFloat"; break;
		case InternalFormat::CompressedRgbBptcUnsignedFloat: s << "CompressedRgbBptcUnsignedFloat"; break;
		default: s << "InternalFormat: " << ((unsigned int)val); break;
	}
	return s;
}



std::ostream & GL::operator<<(std::ostream & s, TextureTarget val)
{
	switch (val)
	{
		case TextureTarget::Texture1D: s << "Texture1D"; break;
		case TextureTarget::Texture2D: s << "Texture2D"; break;
		case TextureTarget::Texture3D: s << "Texture3D"; break;
		case TextureTarget::Texture1DArray: s << "Texture1DArray"; break;
		case TextureTarget::Texture2DArray: s << "Texture2DArray"; break;
		case TextureTarget::TextureRectangle: s << "TextureRectangle"; break;
		case TextureTarget::TextureCubeMap: s << "TextureCubeMap"; break;
		case TextureTarget::TextureCubeMapArray: s << "TextureCubeMapArray"; break;
		case TextureTarget::TextureBuffer: s << "TextureBuffer"; break;
		case TextureTarget::Texture2DMultisample: s << "Texture2DMultisample"; break;
		case TextureTarget::Texture2DMultisampleArray: s << "Texture2DMultisampleArray"; break;
		default: s << "TextureTarget: " << ((unsigned int)val); break;
	}
	return s;
}
std::ostream & GL::operator<<(std::ostream & s, TextureParameterName val)
{
	switch (val)
	{
		case TextureParameterName::DepthStencilTextureMode: s << "DepthStencilTextureMode"; break;
		case TextureParameterName::TextureBaseLevel: s << "TextureBaseLevel"; break;
		case TextureParameterName::TextureCompareFunc: s << "TextureCompareFunc"; break;
		case TextureParameterName::TextureCompareMode: s << "TextureCompareMode"; break;
		case TextureParameterName::TextureLodBias: s << "TextureLodBias"; break;
		case TextureParameterName::TextureMinFilter: s << "TextureMinFilter"; break;
		case TextureParameterName::TextureMagFilter: s << "TextureMagFilter"; break;
		case TextureParameterName::TextureMinLod: s << "TextureMinLod"; break;
		case TextureParameterName::TextureMaxLod: s << "TextureMaxLod"; break;
		case TextureParameterName::TextureMaxLevel: s << "TextureMaxLevel"; break;
		case TextureParameterName::TextureSwizzleR: s << "TextureSwizzleR"; break;
		case TextureParameterName::TextureSwizzleG: s << "TextureSwizzleG"; break;
		case TextureParameterName::TextureSwizzleB: s << "TextureSwizzleB"; break;
		case TextureParameterName::TextureSwizzleA: s << "TextureSwizzleA"; break;
		case TextureParameterName::TextureWrapS: s << "TextureWrapS"; break;
		case TextureParameterName::TextureWrapT: s << "TextureWrapT"; break;
		case TextureParameterName::TextureWrapR: s << "TextureWrapR"; break;
		default: s << "TextureParameterName: " << ((unsigned int)val); break;
	}
	return s;
}



std::ostream & GL::operator<<(std::ostream & s, FrameBufferTarget val)
{
	switch (val)
	{
		case FrameBufferTarget::DrawFramebuffer: s << "DrawFramebuffer"; break;
		case FrameBufferTarget::ReadFramebuffer: s << "ReadFramebuffer"; break;
		case FrameBufferTarget::Framebuffer: s << "Framebuffer"; break;
		default: s << "FrameBufferTarget: " << ((unsigned int)val); break;
	}
	return s;
}
