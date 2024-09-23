#pragma once
#include <memory>
#include <string>
#include <vector>

class Actor;
enum class EndPlayReason : MathTypes::uint64;

class Level
{
public:
    Level(const std::wstring& kName);
    virtual ~Level() = default;

    virtual void Load() = 0;
    
    virtual void Unload(EndPlayReason type);
    virtual void InitializeActors();
    virtual void PhysicsTick(float delta_time);
    virtual void Tick(float delta_time);
    virtual void PostTick(float delta_time);
    virtual void Render(float alpha);

    inline const std::wstring& GetName() const { return name_; }

    inline bool HasBegunPlay() const { return has_begun_play_; }

protected:
    template<std::derived_from<Actor> T>
    T* AddActor(const std::wstring& kName);

    bool has_begun_play_;

private:
    friend class World;
    
    std::wstring name_;

    std::vector<std::shared_ptr<Actor>> actors_;
};

template <std::derived_from<Actor> T>
T* Level::AddActor(const std::wstring& kName)
{
    std::shared_ptr<Actor> actor = std::make_shared<T>(kName);
    actors_.push_back(actor);

    return static_cast<T*>(actor.get());
}
