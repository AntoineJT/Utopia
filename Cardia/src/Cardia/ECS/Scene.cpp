#include "cdpch.hpp"
#include "Cardia/ECS/Scene.hpp"
#include "Cardia/ECS/Entity.hpp"
#include "Cardia/ECS/Components.hpp"
#include "Cardia/Renderer/Renderer2D.hpp"
#include "Cardia/Renderer/Camera.hpp"
#include "Cardia/Scripting/ScriptEngine.hpp"


namespace Cardia
{

	Scene::Scene(std::string name)
		: m_Name(std::move(name))
	{
		std::string shaderName = "basic";
		m_BasicShader = ShaderManager::get(shaderName);

		if (!m_BasicShader)
		{
			// TODO: Temporary, should change when Materials get implemented
			const auto shaderPath = "resources/shaders/" + shaderName;
			m_BasicShader = ShaderManager::load(shaderName, {shaderPath + ".vert", shaderPath + ".frag"});
		}
		uint32_t whiteColor = 0xffffffff;
		m_WhiteTexture = Texture2D::create(1, 1, &whiteColor);
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = {m_Registry.create(), this};
		entity.addComponent<Component::Transform>();
		entity.addComponent<Component::ID>();
		entity.addComponent<Component::Name>(name.empty() ? "Default Entity" : name);
		return entity;
	}

	Entity Scene::CreateEntityFromId(UUID uuid) {
		Entity entity = {m_Registry.create(), this};
		entity.addComponent<Component::Transform>();
		entity.addComponent<Component::ID>(uuid);
		entity.addComponent<Component::Name>("Default Entity");
		return entity;
	}

	void Scene::DestroyEntity(entt::entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnRuntimeUpdate()
	{
		ScriptEngine::Instance().OnRuntimeUpdate();

		SceneCamera* mainCamera = nullptr;
		glm::mat4 mainCameraTransform;

		{
			const auto viewCamera = m_Registry.view<Component::Transform, Component::Camera>();
			for (const auto entity: viewCamera)
			{
				auto[transform, cam] = viewCamera.get<Component::Transform, Component::Camera>(
					entity);
				if (cam.primary)
				{
					mainCamera = &cam.camera;
					mainCameraTransform = transform.getTransform();
				}
			}
		}

		if (!mainCamera)
		{
			Log::error("Scene hierarchy should have a primary camera. Either create one or set the existing one to primary");
			return;
		}

		Renderer2D::beginScene(*mainCamera, mainCameraTransform);

		const auto view = m_Registry.view<Component::Transform, Component::SpriteRenderer>();
		for (const auto entity : view)
		{
			auto [transform, spriteRenderer] = view.get<Component::Transform, Component::SpriteRenderer>(entity);
			Renderer2D::drawRect(transform.getTransform(), spriteRenderer.texture.get(), spriteRenderer.color, spriteRenderer.tillingFactor, spriteRenderer.zIndex, static_cast<float>(entity));
		}

		const auto lightView = m_Registry.view<Component::Transform, Component::Light>();
		for (const auto entity : lightView)
		{
			auto [transform, light] = lightView.get<Component::Transform, Component::Light>(entity);
			Renderer2D::addLight(transform, light);
		}

		Renderer2D::endScene();

		m_BasicShader->bind();
		m_BasicShader->setInt("u_Texture", 0);
		const auto meshView = m_Registry.view<Component::Transform, Component::MeshRendererC>();
		for (const auto entity : meshView)
		{
			auto [transform, meshRenderer] = meshView.get<Component::Transform, Component::MeshRendererC>(entity);
			m_BasicShader->setMat4("u_Model", transform.getTransform());
			if (meshRenderer.texture)
				meshRenderer.texture->bind(0);
			else
				m_WhiteTexture->bind(0);
			meshRenderer.meshRenderer->Draw();
		}
	}

	void Scene::OnUpdateEditor(Camera& editorCamera, const glm::mat4& editorCameraTransform)
	{
		Renderer2D::beginScene(editorCamera, editorCameraTransform);

		const auto view = m_Registry.view<Component::Transform, Component::SpriteRenderer>();
		for (const auto entity : view)
		{
			auto [transform, spriteRenderer] = view.get<Component::Transform, Component::SpriteRenderer>(entity);
			Renderer2D::drawRect(transform.getTransform(), spriteRenderer.texture.get(), spriteRenderer.color, spriteRenderer.tillingFactor, spriteRenderer.zIndex, static_cast<float>(entity));
		}

		const auto lightView = m_Registry.view<Component::Transform, Component::Light>();
		for (const auto entity : lightView)
		{
			auto [transform, light] = lightView.get<Component::Transform, Component::Light>(entity);
			Renderer2D::addLight(transform, light);
		}

		Renderer2D::endScene();

		m_BasicShader->bind();
		m_BasicShader->setInt("u_Texture", 0);
		const auto meshView = m_Registry.view<Component::Transform, Component::MeshRendererC>();
		for (const auto entity : meshView)
		{
			auto [transform, meshRenderer] = meshView.get<Component::Transform, Component::MeshRendererC>(entity);
			m_BasicShader->setMat4("u_Model", transform.getTransform());
			if (meshRenderer.texture)
				meshRenderer.texture->bind(0);
			else
				m_WhiteTexture->bind(0);
			meshRenderer.meshRenderer->Draw();
		}
	}

	void Scene::OnViewportResize(float width, float height)
	{
		auto view = m_Registry.view<Component::Camera>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<Component::Camera>(entity);
			cameraComponent.camera.SetViewportSize((float) width, (float) height);
		}
	}

	void Scene::clear()
	{
		m_Registry.clear();
	}

	void Scene::OnRuntimeStart()
	{
		ScriptEngine::Instance().OnRuntimeStart(this);
	}

	Entity Scene::GetEntityByUUID(const UUID& uuid)
	{
		auto view = m_Registry.view<Component::ID>();
		Entity result;
		for (auto entity : view)
		{
			auto& idComponent = view.get<Component::ID>(entity);
			if (idComponent.uuid == uuid) {
				result = Entity(entity, this);
			}
		}
		return result;
	}

	void Scene::OnRuntimeStop()
	{
		ScriptEngine::Instance().OnRuntimeEnd();
	}
}
