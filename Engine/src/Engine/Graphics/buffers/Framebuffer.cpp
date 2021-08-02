#include "Framebuffer.h"
#include "Engine/Graphics/renderers/Renderer3D.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace ArcanaTools {

    Framebuffer* Framebuffer::Create(const FrameBufferSpecification& specs)
    {
        switch (Renderer3D::GetAPI()) {
        case RenderAPI::API::OPENGL:
            return new OpenGLFramebuffer(specs);

        }
        return nullptr;
    }
}
