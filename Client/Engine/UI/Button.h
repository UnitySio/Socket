#pragma once
#include "UIBase.h"
#include <memory>

class BoxComponent;
class StringComponent;
class BitmapComponent;
class TextBlock;
class Image;

class Button : public UIBase
{
public:
	Button();
	std::shared_ptr<TextBlock>& GetTextComponent() { return string_; }
	std::shared_ptr<Image>& GetImageComponent() { return image_; }
	void SetText(const std::wstring& kString);
	void SetBoxSize(const Math::Vector2& kSize);
	void SetFill(const bool& kFlag);
	void SetBoxColor(const Math::Color& kColor);
	void SetTextColor(const Math::Color& kColor);
	virtual void SetEnable(const bool& kFlag) override;
	const bool& OnMouse();
	void SetImage(const std::wstring& kFileName);
	void RemoveImage();

protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) override;
	virtual void Tick() override;

private:
	std::shared_ptr<Image> image_;
	std::shared_ptr<BoxComponent> box_;
	std::shared_ptr<TextBlock> string_;
	bool isImage_;
};