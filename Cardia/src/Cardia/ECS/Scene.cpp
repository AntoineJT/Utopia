#include "cdpch.hpp"
#include "Cardia/ECS/Scene.hpp"
#include "Cardia/ECS/Entity.hpp"
#include "Cardia/ECS/Components.hpp"
#include "Cardia/Renderer/Renderer2D.hpp"
#include "Cardia/Renderer/Camera.hpp"


namespace Cardia
{
	Scene::Scene(std::string name)
		: m_Name(std::move(name))
	{

	}

	Entity Scene::createEntity(const std::string& name)
	{
		Entity entity = {m_Registry.create(), this};
		entity.addComponent<Component::Transform>();
		entity.addComponent<Component::Name>(name.empty() ? "Default Entity" : name);
		return entity;
	}

	void Scene::destroyEntity(entt::entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::onUpdate(DeltaTime deltaTime, const glm::vec2& viewport)
	{

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

		mainCamera->setViewportSize(viewport.x, viewport.y);

		Renderer2D::beginScene(*mainCamera, mainCameraTransform);

		const auto view = m_Registry.view<Component::Transform, Component::SpriteRenderer>();
		for (const auto entity : view)
		{
			auto [transform, spriteRenderer] = view.get<Component::Transform, Component::SpriteRenderer>(entity);
			Renderer2D::drawRect(transform.getTransform(), spriteRenderer.texture.get(), spriteRenderer.color, spriteRenderer.tillingFactor, spriteRenderer.zIndex);
		}

		Renderer2D::endScene();
	}

	void Scene::onUpdateEditor(DeltaTime deltaTime, Camera& editorCamera)
	{
		Renderer2D::beginScene(editorCamera, editorCamera.getPosition());

		const auto view = m_Registry.view<Component::Transform, Component::SpriteRenderer>();
		for (const auto entity : view)
		{
			auto [transform, spriteRenderer] = view.get<Component::Transform, Component::SpriteRenderer>(entity);
			Renderer2D::drawRect(transform.getTransform(), spriteRenderer.texture.get(), spriteRenderer.color, spriteRenderer.tillingFactor, spriteRenderer.zIndex);
		}

		Renderer2D::endScene();
	}

	void Scene::clear()
	{
		m_Registry.clear();
	}
}
