/*
Copyright (C) 2010, Mathias Gottschlag

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _CORERENDER_RENDER_TEXTURE_HPP_INCLUDED_
#define _CORERENDER_RENDER_TEXTURE_HPP_INCLUDED_

#include "RenderResource.hpp"

#include <tbb/spin_mutex.h>

namespace cr
{
namespace render
{
	class RenderCaps;

	struct TextureFormat
	{
		enum List
		{
			Invalid,
			RGBA8,
			RGBA16F,
			RGBA32F,
			RG8,
			RG16,
			RG32,
			RG16F,
			RG32F,
			RGB_DXT1,
			RGBA_DXT1,
			RGBA_DXT3,
			RGBA_DXT5,
			Depth24Stencil8,
			Depth16,
			Depth24
		};

		static bool supported(RenderCaps *caps,
		                      List internalformat,
		                      List format = Invalid);
	};
	struct TextureType
	{
		enum List
		{
			Texture1D,
			Texture2D,
			Texture3D,
			TextureCube
		};
	};

	class Texture : public RenderResource
	{
		public:
			Texture(Renderer *renderer,
			        res::ResourceManager *rmgr,
			        const std::string &name,
			        TextureType::List type);
			virtual ~Texture();

			int getHandle()
			{
				return handle;
			}
			TextureType::List getTextureType()
			{
				return type;
			}

			typedef core::SharedPointer<Texture> Ptr;
		protected:
			int handle;
			TextureType::List type;
	};
}
}

#endif
