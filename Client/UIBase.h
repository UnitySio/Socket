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
	enum class AnchorType
	{
		LeftTop,
		CenterTop,
		RightTop,
		CenterLeft,
		Center,
		CenterRight,
		LeftBottom,
		CenterBottom,
		RightBottom,
		None,
	};
	UIBase();
	virtual ~UIBase() = default;

	void SetParent(UIBase* parent);
	void SetSize(const Math::Vector2& value);
	void SetPosition(const Math::Vector2& pos);
	const Math::Vector2 GetPosition();
	void SetAnchorType(const AnchorType& type);
	virtual void SetEnable(const bool& flag);
	const bool& IsEnalbed() { return isEnabled_; }
	void SetVisibility(const bool& flag);
	const bool& IsVisible() { return isVisible_; }

protected:
	using Super = UIBase;
	void SetOffset(const Math::Vector2& pos);

	virtual void Tick();
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow());
	void RefreshAnchorPos();

	Math::Vector2 position_;
	Math::Vector2 parentRectsize_;
	Math::Vector2 rectsize_;
	Math::Vector2 anchor_;
	Math::Vector2 offset_;
	Math::Color color_;
	float stroke_;
	float rotation_;
	UIBase* parent_;
	std::vector<UIBase*> children_;
	AnchorType anchorType_;
	bool isEnabled_;
	bool isVisible_;

private:
	friend class Renderer;
	friend class Canvas;
	friend class StringComponent;
};