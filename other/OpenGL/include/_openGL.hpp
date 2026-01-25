#ifndef  OPEN_GL_HPP
# define OPEN_GL_HPP

# include "openGL.h"

namespace OpenGL
{
	int getInt(unsigned int name);
	int getInt(unsigned int name, unsigned int index);

	void ShowContextInfo();
	void ShowCurrentInfo();

	void ShowGeneralLimits();
	void ShowUniformLimits();
	void ShowTextureLimits();
	void ShowVertexLimits();
	void ShowFragmentLimits();

	void ShowLimits();

	void ShowBufferInfo();

	
};

#endif