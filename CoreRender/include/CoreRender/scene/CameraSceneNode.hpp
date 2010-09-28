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

#ifndef _CORERENDER_SCENE_CAMERASCENENODE_HPP_INCLUDED_
#define _CORERENDER_SCENE_CAMERASCENENODE_HPP_INCLUDED_

#include "SceneNode.hpp"
#include "CoreRender/render/Pipeline.hpp"

namespace cr
{
namespace scene
{
	class CameraSceneNode : public SceneNode
	{
		public:
			CameraSceneNode(render::Pipeline::Ptr pipeline);
			virtual ~CameraSceneNode();

			void setOrtho(float left,
			              float right,
			              float bottom,
			              float top,
			              float near,
			              float far);
			void setPerspective(float left,
			                    float right,
			                    float bottom,
			                    float top,
			                    float near,
			                    float far);
			void setPerspectiveFOV(float fov,
			                       float aspectratio,
			                       float near,
			                       float far);

			render::Pipeline::Ptr getPipeline();

			typedef core::SharedPointer<CameraSceneNode> Ptr;
		private:
			virtual void onUpdate(bool abstranschanged);

			render::Pipeline::Ptr pipeline;

			bool projmatdirty;
			math::Matrix4 projmat;
	};
}
}

#endif