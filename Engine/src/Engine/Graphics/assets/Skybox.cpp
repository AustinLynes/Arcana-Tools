#include "Skybox.h"
#include "Engine/Graphics/renderers/Renderer3D.h"

namespace ArcanaTools {
    
    Skybox::Skybox(std::initializer_list<std::string> filepaths)
	{
        
        std::vector<Vertex> skyboxVertices = {
            Vertex{{-1000.0f,  1000.0f, -1000.0f}},  // 7
            Vertex{{-1000.0f, -1000.0f, -1000.0f}},  // 4
            Vertex{{ 1000.0f, -1000.0f, -1000.0f}},  // 5
            Vertex{{ 1000.0f, -1000.0f, -1000.0f}},  // 
            Vertex{{ 1000.0f,  1000.0f, -1000.0f}},
            Vertex{{-1000.0f,  1000.0f, -1000.0f}},

           Vertex{{-1000.0f, -1000.0f,  1000.0f}},
           Vertex{{-1000.0f, -1000.0f, -1000.0f}},
           Vertex{{-1000.0f,  1000.0f, -1000.0f}},
           Vertex{{-1000.0f,  1000.0f, -1000.0f}},
           Vertex{{-1000.0f,  1000.0f,  1000.0f}},
           Vertex{{-1000.0f, -1000.0f,  1000.0f}},

            Vertex{{1000.0f, -1000.0f, -1000.0f}},
            Vertex{{1000.0f, -1000.0f,  1000.0f}},
            Vertex{{1000.0f,  1000.0f,  1000.0f}},
            Vertex{{1000.0f,  1000.0f,  1000.0f}},
            Vertex{{1000.0f,  1000.0f, -1000.0f}},
            Vertex{{1000.0f, -1000.0f, -1000.0f}},

           Vertex{{-1000.0f, -1000.0f,  1000.0f}},
           Vertex{{-1000.0f,  1000.0f,  1000.0f}},
           Vertex{{ 1000.0f,  1000.0f,  1000.0f}},
           Vertex{{ 1000.0f,  1000.0f,  1000.0f}},
           Vertex{{ 1000.0f, -1000.0f,  1000.0f}},
           Vertex{{-1000.0f, -1000.0f,  1000.0f}},

            Vertex{{-1000.0f,  1000.0f, -1000.0f}},
            Vertex{{ 1000.0f,  1000.0f, -1000.0f}},
            Vertex{{ 1000.0f,  1000.0f,  1000.0f}},
            Vertex{{ 1000.0f,  1000.0f,  1000.0f}},
            Vertex{{-1000.0f,  1000.0f,  1000.0f}},
            Vertex{{-1000.0f,  1000.0f, -1000.0f}},

            Vertex{{-1000.0f, -1000.0f, -1000.0f}},
            Vertex{{-1000.0f, -1000.0f,  1000.0f}},
            Vertex{{ 1000.0f, -1000.0f, -1000.0f}},
            Vertex{{ 1000.0f, -1000.0f, -1000.0f}},
            Vertex{{-1000.0f, -1000.0f,  1000.0f}},
            Vertex{{ 1000.0f, -1000.0f,  1000.0f}} 
        };
        m_count = skyboxVertices.size();

		VertexBuffer* pVBO = VertexBuffer::Create(skyboxVertices.data(), m_count * sizeof(Vertex));
        
        BufferLayout layout = { {ShaderDataType::Float3, "v_position"} };

        pVBO->SetLayout(layout);

		m_VAO = VertexArray::Create();
		m_VAO->Bind();
		m_VAO->AddVertexBuffer(pVBO);
        m_shader = Shader::Create("skybox", "Resources/shaders/Cubemap/shader.vert", "Resources/shaders/Cubemap/shader.frag");

        m_cubemap = Cubemap::Create(filepaths);

        glm::mat4 captureViews[] =
        {
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
        };
        m_irredecentMap = m_cubemap;

        m_shader->SetInt("cubemap_env", m_cubemap->GetID(0));
        m_shader->SetInt("cubemap_ref", m_cubemap->GetID(1));

	}
	Skybox::~Skybox()
	{
	}
	void Skybox::Draw()
	{
        m_shader->Bind();
        m_cubemap->Bind();
        m_VAO->Bind();
        RenderCommand::DrawArrays(m_count);
      //  m_VAO->Unbind();
       // m_cubemap->Unbind();
        m_shader->Unbind();
	}
    Skybox* Skybox::Create(std::initializer_list<std::string> filepaths)
    {
        return new Skybox(filepaths);
    }
}