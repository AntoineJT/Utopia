#include <Utopia.hpp>

// Needs to build with spdlog to use log system
#define UT_USE_SPDLOG
#include <Utopia/Log.hpp>

class LayerTest : public Utopia::Layer
{
public:
	explicit LayerTest(std::string&& name)
		: Layer(name) {}

	void onUpdate() override
	{
		if(Utopia::Input::isKeyPressed(Utopia::Key::Y))
		{
			Utopia::Log::info("Key Y is pressed");
		}
	}

	void onEvent(Utopia::Event& event) override
	{
		// Utopia::Log::trace(event);
	}
};


class SandBox : public Utopia::Application
{
public:
	SandBox()
	{
		pushLayer(layer.get());
		pushLayer(layer2.get());
		pushOverlay(imGuiLayer.get());
	}

	~SandBox() override = default;

private:
	std::unique_ptr<Utopia::Layer> layer = std::make_unique<LayerTest>("First Layer");
	std::unique_ptr<Utopia::Layer> layer2 = std::make_unique<LayerTest>("Second Layer");
	std::unique_ptr<Utopia::Layer> imGuiLayer = std::make_unique<Utopia::ImGuiLayer>();
};


std::unique_ptr<Utopia::Application> Utopia::CreateApplication()
{
	return std::make_unique<SandBox>();
}
