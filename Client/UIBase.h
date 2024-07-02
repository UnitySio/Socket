#pragma once
#include "Math/Vector2.h"
#include <memory>
#include <vector>
#include "Math/Color.h"
#include "Level/World.h"

class WindowsWindow;

class UIBase
{
public:
	UIBase();
	virtual ~UIBase() = default;

	void SetParent(UIBase* parent);
	void SetSize(const Math::Vector2& value);
	void SetPosition(const Math::Vector2& pos);

protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) abstract;


	Math::Vector2 position_;
	Math::Vector2 rectsize_;
	Math::Color color_;
	float stroke_;
	float rotation_;
	UIBase* parent_;
	std::vector<UIBase*> children_;

private:
	friend class Renderer;
	friend class UIManager;
	friend class StringComponent;
};