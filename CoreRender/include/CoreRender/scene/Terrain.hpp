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

#ifndef _CORERENDER_SCENE_TERRAIN_HPP_INCLUDED_
#define _CORERENDER_SCENE_TERRAIN_HPP_INCLUDED_

#include "../res/Resource.hpp"
#include "../math/Vector3.hpp"
#include "../math/Vector2.hpp"
#include "../render/Texture.hpp"
#include "../render/VertexBuffer.hpp"
#include "../render/IndexBuffer.hpp"
#include "../render/FrameData.hpp"
#include "../render/Material.hpp"
#include "../render/VertexLayout.hpp"

namespace cr
{
namespace scene
{
	class TerrainMaterial;

	class Terrain : public res::Resource
	{
		public:
			Terrain(cr::res::ResourceManager* rmgr, const std::string& name);
			virtual ~Terrain();

			void render(render::RenderQueue &queue,
			            math::Matrix4 transmat,
			            math::Vector3F camerapos);

			void set(unsigned int sizex,
			         unsigned int sizez,
			         unsigned int patchsize = 33,
			         float *displacement = 0);

			void setDisplacement(unsigned int x,
			                     unsigned int z,
			                     math::Vector3F displacement);
			void setDisplacement(unsigned int x,
			                     unsigned int z,
			                     float height);
			math::Vector3F getDisplacement(int x, int z);

			/**
			 * Discards the displacement data in RAM and only keeps the copy in
			 * VRAM. If you call this, following calls to setDisplacement()
			 * and getDisplacement() will not work properly.
			 */
			void discardDisplacementData();

			math::Vector2I getSize()
			{
				return math::Vector2I(sizex, sizez);
			}

			void setMaterial(render::Material::Ptr material)
			{
				this->material = material;
				material->addTexture("displacementMap", displacementmap);
			}

			virtual bool load();

			virtual bool waitForLoading(bool recursive,
			                            bool highpriority = false);

			virtual const char *getType()
			{
				return "Terrain";
			}

			typedef core::SharedPointer<Terrain> Ptr;
		private:
			void updateNormals(unsigned int x,
			                   unsigned int z,
			                   unsigned int sizex,
			                   unsigned int sizez);
			void updateGeometry(unsigned int patchsize);

			void renderPatch(render::RenderQueue &queue,
			                 math::Matrix4 transmat,
			                 unsigned int lod,
			                 float *offsetscale,
			                 render::CustomUniform &texcoordscale);
			void renderRecursively(render::RenderQueue &queue,
			                       math::Matrix4 transmat,
			                       unsigned int maxdepth,
			                       math::Vector3F camerapos,
			                       float *offsetscale,
			                       render::CustomUniform &texcoordscale);

			render::Material::Ptr material;

			float *displacement;
			float *normals;
			unsigned int sizex;
			unsigned int sizez;
			unsigned int patchsize;

			struct Patch
			{
				unsigned int patchsize;
				unsigned int indextype;
				unsigned int indexoffset;
				unsigned int vertexoffset;
				unsigned int indexcount;
			};
			std::vector<Patch> patches;
			render::VertexBuffer::Ptr vertices;
			render::IndexBuffer::Ptr indices;
			render::VertexLayout::Ptr layout;

			render::Texture::Ptr displacementmap;
			render::Texture::Ptr normalmap;

			tbb::mutex mutex;
	};
}
}

#endif