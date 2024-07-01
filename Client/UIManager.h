#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>

class UIBase;
class Button;

class UIManager : public Singleton<UIManager>
{
public:
	void Render();
	std::shared_ptr<Button> CreateButton();

private:
	std::vector<std::shared_ptr<UIBase>> renderList_;
};

