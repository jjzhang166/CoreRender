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

#ifndef _CORERENDER_RENDER_PIPELINE_HPP_INCLUDED_
#define _CORERENDER_RENDER_PIPELINE_HPP_INCLUDED_

#include "../res/Resource.hpp"
#include "PipelineStage.hpp"
#include "RenderTarget.hpp"

class TiXmlElement;

namespace cr
{
namespace render
{
	class Renderer;

	/**
	 * Class which defines the way a scene is rendered to the screen or to
	 * a texture. A pipeline is composed from multiple pipeline stages which can
	 * be enabled or disabled.
	 */
	class Pipeline : public res::Resource
	{
		public:
			/**
			 * Constructor.
			 */
			Pipeline(res::ResourceManager *rmgr, const std::string &name);
			/**
			 * Destructor.
			 */
			virtual ~Pipeline();

			PipelineStage *addStage(const std::string &name);
			PipelineStage *getStage(const std::string &name);
			PipelineStage *getStage(unsigned int index);
			void removeStage(const std::string &name);
			unsigned int getStageCount();

			void resizeTargets(unsigned int width, unsigned int height);

			FrameBuffer::Ptr getFrameBuffer(const std::string &name);
			Texture::Ptr getTargetTexture(const std::string &name);
			RenderTarget::Ptr getRenderTarget(const std::string &name);

			virtual bool load();

			virtual bool waitForLoading(bool recursive,
			                            bool highpriority = false);

			virtual const char *getType()
			{
				return "Pipeline";
			}

			typedef core::SharedPointer<Pipeline> Ptr;
		private:
			bool loadSetup(TiXmlElement *xml);
			bool loadCommands(TiXmlElement *xml);
			bool loadStage(TiXmlElement *xml, PipelineStage *stage);

			void parseSize(TiXmlElement *xml, float *relsize, int *abssize);

			std::vector<PipelineStage*> stages;

			struct RenderTargetInfo
			{
				std::string name;
				RenderTarget::Ptr target;
			};
			std::vector<RenderTargetInfo> rendertargets;
			struct TargetTextureInfo
			{
				std::string name;
				Texture::Ptr texture;
				float relsize[2];
				int abssize[2];
			};
			std::vector<TargetTextureInfo> targettextures;
			struct FrameBufferInfo
			{
				std::string name;
				FrameBuffer::Ptr fb;
				float relsize[2];
				int abssize[2];
			};
			std::vector<FrameBufferInfo> framebuffers;

			unsigned int targetsize[2];
	};
}
}

#endif
