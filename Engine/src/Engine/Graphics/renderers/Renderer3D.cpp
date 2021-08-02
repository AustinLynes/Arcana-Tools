#include "Renderer3D.h"
#include <glm/gtc/matrix_transform.hpp>
namespace ArcanaTools {

#define MAX_QUADS 10'000
	//Skybox Renderer3D::m_skybox;
	struct RenderBatch2D {
		static const uint32_t MaxQuadCount = MAX_QUADS;
		static const uint32_t MaxVertexCount = MaxQuadCount * 4;
		static const uint32_t MaxIndexCount = MaxQuadCount * 6;
		static const uint32_t MaxTextureSlots = 32;

		VertexArray* QuadVertexArray;
		VertexBuffer* QuadVertexBuffer;

		std::unordered_map<const char*, Shader*> TextureShaders;
		Texture2D* WhiteTexture = nullptr;

		uint32_t QuadIndexCount = 0;
		Vertex2D* bufferBase = nullptr;
		Vertex2D* bufferPtr = nullptr;

		uint32_t PointLightCount = 0;
		uint32_t SpotLightCount = 0;

		std::array<Texture2D*, MaxTextureSlots> textureSlots;
		uint32_t textureSlotIndex = 1;// 0 --> white texture

		Renderer3D::Stats stats = {};

		glm::vec4 QuadVertexPositions[4];

		friend std::ostream& operator<<(std::ostream& _os, RenderBatch2D& _batch) {
			_os << std::endl
				<< "Batch Info {" << std::endl
				<< "\t" << "Max Quad Count: " << _batch.MaxQuadCount << std::endl
				<< "\t" << "Max Vertex Count: " << _batch.MaxVertexCount << std::endl
				<< "\t" << "Max Index Count: " << _batch.MaxIndexCount << std::endl
				<< "\t" << "Max Texture Slot Count: " << _batch.MaxTextureSlots << std::endl;

			uint32_t v_count = 4;
			for (size_t i = 0; i < _batch.stats.QuadCount * v_count; i++)
			{
				_os << "\t" << "Buffer Base Ptr: " << _batch.bufferBase[i] << std::endl;

			}

			_os << "\t" << "Buffer Ptr: " << *_batch.bufferPtr << std::endl
				<< "}" << std::endl;
			return _os;
		}
	};

	static RenderBatch2D s_batch;
	// TEMPORARY
	void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data) {
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
		std::stringstream  ss;
		ss << "-------------------------------------------------------- DEBUG MESSAGE ---------------" << std::endl;
		ss << "GL_ERROR ID: " << id << std::endl;
		ss << "GL_ERROR MESSAGE: " << msg << std::endl;
		ss << "Source: ";
		switch (source) {
		case GL_DEBUG_SOURCE_API: ss << "API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: ss << "WINDOW SYSTEM"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: ss << "SHADER COMPILER"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY: ss << "THIRD PARTY"; break;
		case GL_DEBUG_SOURCE_APPLICATION: ss << "APPLICATION"; break;
		case GL_DEBUG_SOURCE_OTHER: ss << "OTHER"; break;
		}
		ss << std::endl;
		ss << "TYPE: ";
		switch (type) {
		case GL_DEBUG_TYPE_ERROR: ss << "ERROR"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: ss << "DEPRICATED BEHAVIOR"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: ss << "UNDEFINED BEHAVIOR"; break;
		case GL_DEBUG_TYPE_PORTABILITY: ss << "PORTABILITY"; break;
		case GL_DEBUG_TYPE_PERFORMANCE: ss << "PERFORMANCE"; break;
		case GL_DEBUG_TYPE_MARKER: ss << "MARKER"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP: ss << "PUSH GROUP"; break;
		case GL_DEBUG_TYPE_POP_GROUP: ss << "POP GROUP"; break;
		case GL_DEBUG_TYPE_OTHER: ss << "OTHER"; break;
		}
		ss << std::endl;
		ss << "SEVERITY: ";
		switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH: ss << "HIGH";  break;
		case GL_DEBUG_SEVERITY_MEDIUM: ss << "MEDIUM";  break;
		case GL_DEBUG_SEVERITY_LOW: ss << "LOW"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: ss << "NOTIFICATION";  break;
		}
		ss << std::endl;

		std::cout << ss.str() << std::endl;

	}


	void Renderer3D::DecrementTextureIndex() {
		s_batch.textureSlotIndex = 1;
	}

	void Renderer3D::Init()
	{
		// TEMPORARY 
		int flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(GLDebugMessageCallback, NULL);
		}



		s_batch.QuadVertexArray = VertexArray::Create();

		s_batch.QuadVertexBuffer = VertexBuffer::Create(s_batch.MaxVertexCount * sizeof(Vertex2D));
		s_batch.QuadVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "v_position"},
			{ShaderDataType::Float4, "v_color"},
			{ShaderDataType::Float2, "v_uv"},
			{ShaderDataType::Float, "v_texID"},
			{ShaderDataType::Float, "v_tilingFactor"},
			{ShaderDataType::Int, "v_entityID"},
			});
		s_batch.QuadVertexArray->AddVertexBuffer(s_batch.QuadVertexBuffer);

		s_batch.bufferBase = new Vertex2D[s_batch.MaxVertexCount];

		uint32_t* indices = new uint32_t[s_batch.MaxIndexCount];
		uint32_t offset = 0;
		for (size_t i = 0; i < s_batch.MaxIndexCount; i += 6)
		{
			// triangle 1
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			// triangle 2
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		IndexBuffer* indexBuffer = IndexBuffer::Create(indices, s_batch.MaxIndexCount);
		s_batch.QuadVertexArray->SetIndexBuffer(indexBuffer);
		delete[] indices;

		s_batch.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t texData = 0xffffffff;
		s_batch.WhiteTexture->SetData(&texData, sizeof(uint32_t));

		int32_t samplers[s_batch.MaxTextureSlots];

		for (uint32_t i = 0; i < s_batch.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}

		s_batch.TextureShaders["Basic_3D"] = Shader::Create("basic_3D", "Resources/shaders/basic_2D/shader.vert", "Resources/shaders/basic_2D/shader.frag");
		s_batch.TextureShaders["Phong_3D"] = Shader::Create("phong_3D", "Resources/shaders/basic_phong/shader.vert", "Resources/shaders/basic_phong/shader.frag");
		s_batch.TextureShaders["Light"] = Shader::Create("Light", "Resources/shaders/light/shader.vert", "Resources/shaders/light/shader.frag");

		s_batch.textureSlots[0] = s_batch.WhiteTexture;

		s_batch.QuadVertexPositions[0] = { -1.0f, -1.0f, 0.0f, 1.0f };
		s_batch.QuadVertexPositions[1] = { 1.0f, -1.0f, 0.0f, 1.0f };
		s_batch.QuadVertexPositions[2] = { 1.0f,  1.0f, 0.0f, 1.0f };
		s_batch.QuadVertexPositions[3] = { -1.0f,  1.0f, 0.0f, 1.0f };

	}

	void Renderer3D::Shutdown()
	{
		/*for (auto buffer : m_FrameBuffers)
		{
			auto buf = buffer.second;
			buf->Delete();

		}*/
		delete[] s_batch.bufferBase;
	}

	void Renderer3D::BeginScene(Entity* pCameraEntity)
	{

		// bind the view projection 

		auto cameraComp = pCameraEntity->GetComponent<Components::PerspectiveCamera>();
		auto cameraController = pCameraEntity->GetComponent<Components::CameraController>();
		auto transformComponent = pCameraEntity->GetComponent<Components::Transform>();

		glm::mat4 view = cameraController.GetViewMatrix(transformComponent.GetPosition());
		glm::mat4 projection = cameraComp.GetInstance()->GetProjectionMatrix();

		glm::mat4 view_projection = projection * view;

		s_batch.TextureShaders["Basic_3D"]->Bind();
		s_batch.TextureShaders["Basic_3D"]->SetMat4("un_ViewProjection", view_projection);


		s_batch.TextureShaders["Light"]->Bind();
		s_batch.TextureShaders["Light"]->SetMat4("un_ViewProjection", view_projection);

		s_batch.TextureShaders["Phong_3D"]->Bind();
		s_batch.TextureShaders["Phong_3D"]->SetMat4("un_ViewProjection", view_projection);
		
		s_batch.TextureShaders["Phong_3D"]->SetFloat3("un_cameraPosition", transformComponent.GetPosition());
		


		//s_batch.TextureShaders["Phong_3D"]->SetInt("un_shadowMap", 8);


		StartBatch();
	}
	void Renderer3D::EndScene()
	{
		Flush();
	}

	void Renderer3D::StartBatch()
	{
		s_batch.QuadIndexCount = 0;
		s_batch.bufferPtr = s_batch.bufferBase;

		s_batch.textureSlotIndex = 1;

		s_batch.PointLightCount = 0;
		s_batch.SpotLightCount = 0;
	}

	void Renderer3D::Flush()
	{

		if (s_batch.QuadIndexCount == 0)
			return; // nothing to draw


		uint32_t batch_size = (uint32_t)((uint8_t*)s_batch.bufferPtr - (uint8_t*)s_batch.bufferBase);

		s_batch.QuadVertexBuffer->SetData(s_batch.bufferBase, batch_size);

		s_batch.TextureShaders["Basic_3D"]->Bind();	

		for (uint32_t i = 0; i < s_batch.textureSlotIndex; i++) {
			if (s_batch.textureSlots[i] == nullptr)
				s_batch.textureSlots[i] = s_batch.WhiteTexture;
			s_batch.textureSlots[i]->Bind(i);
		}

		RenderCommand::DrawIndexed(s_batch.QuadVertexArray, s_batch.QuadIndexCount);

		s_batch.stats.DrawCount++;

	}

	void Renderer3D::NewBatch()
	{
		Flush();
		StartBatch();
	}

	void Renderer3D::DrawQuad(const glm::mat4& transform, Components::SpriteRenderer& spriteRenderer, int entityID)
	{

		constexpr size_t quadVertCount = 4;

		constexpr glm::vec2 uvs[] = {
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f}
		};
		

		float tilingFactor = 1.0f;

		if (s_batch.QuadIndexCount >= RenderBatch2D::MaxIndexCount)
			NewBatch();

		float textureIndex = 0.0f;

		for (uint32_t i = 1; i < s_batch.textureSlotIndex; i++)
		{
			if (*s_batch.textureSlots[i] == *spriteRenderer.texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (s_batch.textureSlotIndex >= RenderBatch2D::MaxTextureSlots)
				NewBatch();

			textureIndex = (float)s_batch.textureSlotIndex;

			s_batch.textureSlots[s_batch.textureSlotIndex] = spriteRenderer.texture;

			s_batch.textureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertCount; i++)
		{
			s_batch.bufferPtr->Position = transform * s_batch.QuadVertexPositions[i];
			s_batch.bufferPtr->Color = spriteRenderer.TintColor;
			s_batch.bufferPtr->UV = uvs[i];
			s_batch.bufferPtr->texID = textureIndex;
			s_batch.bufferPtr->tileFactor = tilingFactor;
			s_batch.bufferPtr->entityID = entityID;
			s_batch.bufferPtr++;
		}

		s_batch.QuadIndexCount += 6;
		s_batch.stats.QuadCount++;
	}

	void Renderer3D::BindPointLight(Components::PointLight light, Components::Transform transform)
	{
		s_batch.TextureShaders["Phong_3D"]->Bind();
		
		std::string cur_light = "un_pointLights[" + std::to_string(light.GetID()) + "].";
		
		s_batch.TextureShaders["Phong_3D"]->SetFloat3(cur_light + "position", transform.GetPosition());

		s_batch.TextureShaders["Phong_3D"]->SetFloat3(cur_light + "ambient", light.Albedo);

		s_batch.TextureShaders["Phong_3D"]->SetFloat(cur_light + "radius", light.Radius);

		
		


		++s_batch.PointLightCount;

	}
	void Renderer3D::BindDirectionalLight(Components::DirectionalLight light)
	{



		s_batch.TextureShaders["Phong_3D"]->SetFloat3("un_dirLight.direction", light.Direction);

		s_batch.TextureShaders["Phong_3D"]->SetFloat3("un_dirLight.ambient", light.Albedo);
		s_batch.TextureShaders["Phong_3D"]->SetFloat3("un_dirLight.diffuse", light.Diffuse);
		s_batch.TextureShaders["Phong_3D"]->SetFloat3("un_dirLight.specular", light.Specular);

	}
	void Renderer3D::BindSpotLight(Components::SpotLight light, Components::Transform transform)
	{

		s_batch.TextureShaders["Phong_3D"]->SetFloat3("position", transform.GetPosition());
		s_batch.TextureShaders["Phong_3D"]->SetFloat3("direction", light.Direction);
		
		s_batch.TextureShaders["Phong_3D"]->SetFloat3("ambient", light.Albedo);
		s_batch.TextureShaders["Phong_3D"]->SetFloat3("diffuse", light.Diffuse);
		s_batch.TextureShaders["Phong_3D"]->SetFloat3("specular", light.Specular);

		s_batch.TextureShaders["Phong_3D"]->SetFloat("cutOff", 1.0f);
		s_batch.TextureShaders["Phong_3D"]->SetFloat("outerCutOff", 10.0f);

		s_batch.TextureShaders["Phong_3D"]->SetFloat("constant", 0.1f);
		s_batch.TextureShaders["Phong_3D"]->SetFloat("linear", 0.5f);
		s_batch.TextureShaders["Phong_3D"]->SetFloat("quadratic", 0.2f);



	}

	void Renderer3D::BindMaterial(Components::Material& material)
	{
		s_batch.TextureShaders["Phong_3D"]->Bind();
		s_batch.TextureShaders["Phong_3D"]->SetFloat3("un_material.albedo", material.Albedo);
		s_batch.TextureShaders["Phong_3D"]->SetFloat("un_material.metallic", material.Metallic);
		s_batch.TextureShaders["Phong_3D"]->SetFloat("un_material.roughness", material.Roughness);
		s_batch.TextureShaders["Phong_3D"]->SetFloat("un_material.ao", material.AmbientOccolusion);

	}

	void Renderer3D::DrawLightModel(Components::MeshRenderer& meshRenderer, Components::Transform transform, Components::PointLight light, int entityID)
	{
		
		Model* model = meshRenderer.GetModel();

		//s_batch.TextureShaders["Depth"]->SetMat4("un_lightSpaceMatrix", lightSpaceMatrix);
		s_batch.TextureShaders["Light"]->Bind();
		s_batch.TextureShaders["Light"]->SetFloat3("un_lightColor", light.Albedo);


		std::vector<Mesh> meshes = model->GetMeshes();

		for (size_t i = 0; i < meshes.size(); i++)
		{
			// Initialize matrices
			//glm::mat4 trans = glm::mat4(1.0f);
			//glm::mat4 rot = glm::mat4(1.0f);
			//glm::mat4 sca = glm::mat4(1.0f);

			//// Transform the matrices to their correct form
			//trans = glm::translate(trans, transform.GetPosition());
			//sca = glm::scale(sca, transform.GetScale());

			//{
			//	s_batch.TextureShaders["Phong_3D"]->Bind();
			//	meshes[i].GetVertexArrayObject()->Bind();
			//	uint32_t diff_count = 0;
			//	uint32_t spec_count = 0;

			//	for (unsigned int j = 0; j < meshes[i].GetTextures().size(); j++)
			//	{
			//		std::string num;
			//		std::string type = meshes[i].GetTextures()[j]->GetType();
			//		if (type == "diffuse") {
			//			num = std::to_string(diff_count++);
			//		}
			//		else if (type == "specular") {
			//			num = std::to_string(spec_count++);
			//		}

			//		meshes[i].GetTextures()[j]->Bind();
			//		meshes[i].GetTextures()[j]->AssignTextureUnit(s_batch.TextureShaders["Phong_3D"], (type + num).c_str(), i);

				//}



				//s_batch.TextureShaders["Phong_3D"]->SetMat4("un_model", transform.GetTransform());
				//s_batch.TextureShaders["Phong_3D"]->SetMat4("un_rotation", transform.GetRotationMatrix());
				//s_batch.TextureShaders["Phong_3D"]->SetMat4("un_scale", transform.GetScaleMatrix());

				//s_batch.TextureShaders["Phong_3D"]->SetInt("un_entityID", entityID);

				//s_batch.TextureShaders["Phong_3D"]->SetInt("un_pointLightIndex", s_batch.PointLightCount);


				s_batch.TextureShaders["Light"]->SetMat4("un_model", transform.GetTransform());
				s_batch.TextureShaders["Light"]->SetInt("un_entityID", entityID);
				s_batch.TextureShaders["Light"]->Bind();

				//std::cout << "Point Light Index: \t" << s_batch.PointLightCount << std::endl;

				RenderCommand::DrawIndexed(meshes[i].GetVertexArrayObject(), meshes[i].GetVertexArrayObject()->GetIndexBuffer()->GetCount());
			}

		}


	void Renderer3D::DrawModel(Components::MeshRenderer& meshRenderer, Components::Transform transform, int entityID)
	{

		Model* model = meshRenderer.GetModel();

		std::vector<Mesh> meshes = model->GetMeshes();
	
		for (size_t i = 0; i < meshes.size(); i++)
		{
			// Initialize matrices
			glm::mat4 trans = glm::mat4(1.0f);
			glm::mat4 rot = glm::mat4(1.0f);
			glm::mat4 sca = glm::mat4(1.0f);
		
			// Transform the matrices to their correct form
			trans = glm::translate(trans, transform.GetPosition());
			sca = glm::scale(sca, transform.GetScale());

			{
				meshes[i].GetVertexArrayObject()->Bind();
				uint32_t diff_count = 0;
				uint32_t spec_count = 0;

				for (unsigned int j = 0; j < meshes[i].GetTextures().size(); j++)
				{
					std::string num;
					std::string type = meshes[i].GetTextures()[j]->GetType();
					if (type == "diffuse") {
						num = std::to_string(diff_count++);	
					}
					else if (type == "specular") {
						num = std::to_string(spec_count++);
					}

					meshes[i].GetTextures()[j]->Bind();
					meshes[i].GetTextures()[j]->AssignTextureUnit(s_batch.TextureShaders["Phong_3D"], (type + num).c_str(), i);
					
				}



				s_batch.TextureShaders["Phong_3D"]->SetMat4("un_model", transform.GetTransform());
				s_batch.TextureShaders["Phong_3D"]->SetMat4("un_rotation", transform.GetRotationMatrix());
				s_batch.TextureShaders["Phong_3D"]->SetMat4("un_scale", transform.GetScaleMatrix());

				s_batch.TextureShaders["Phong_3D"]->SetInt("un_entityID", entityID);

				s_batch.TextureShaders["Phong_3D"]->SetInt("un_pointLightIndex", s_batch.PointLightCount);
				

				/*s_batch.TextureShaders["Light"]->Bind();
				s_batch.TextureShaders["Light"]->SetMat4("un_model", transform.GetTransform());*/

				//std::cout << "Point Light Index: \t" << s_batch.PointLightCount << std::endl;
				s_batch.TextureShaders["Phong_3D"]->Bind();

				RenderCommand::DrawIndexed(meshes[i].GetVertexArrayObject(), meshes[i].GetVertexArrayObject()->GetIndexBuffer()->GetCount());
				//s_batch.TextureShaders["Light"]->Bind();

				//RenderCommand::DrawIndexed(meshes[i].GetVertexArrayObject(), meshes[i].GetVertexArrayObject()->GetIndexBuffer()->GetCount());

			}

		}
	
	
	}

	void Renderer3D::OnWindowResize(float width, float height)
	{
		RenderCommand::SetViewport(width, height);
	}

	void Renderer3D::BindLightShader()
	{
		s_batch.TextureShaders["Light"]->Bind();
	}

	void Renderer3D::BindMaterialShader()
	{
		s_batch.TextureShaders["Phong_3D"]->Bind();
	}

	const Renderer3D::Stats& Renderer3D::GetStats()
	{
		return s_batch.stats;
	}

	void Renderer3D::ResetStats()
	{
		memset(&s_batch.stats, 0, sizeof(Stats));
	}

}
