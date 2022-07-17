#pragma once
#include <string>
#include <string_view>
#include <iostream>
#include <functional>

/*
    Create a mediator and have each object in the system to refer to him
    Mediator engages in a bidirectional communication with  its connected components
    Mediator has function the components can call
    Components  have functions  the mediator can call
*/

struct EventData
{
    virtual void Print() const = 0;
};

using EventCallbackFn = std::function<void(EventData&)>;

struct PlayerScoredData : EventData
{
    std::string mPlayerName;
    int mGoalsScored;
    PlayerScoredData(const std::string_view& playerName, const int goals)
        : mPlayerName(playerName)
        , mGoalsScored(goals)
    {}

    void Print() const override
    {
        std::cout << mPlayerName << " has scored " << mGoalsScored << '\n';
    }
};

struct Game
{
    std::vector<EventCallbackFn> mCallbacks;

    void AddCallback(const EventCallbackFn& func)
    {
        mCallbacks.emplace_back(func);
    }

    template<typename T>
    void ProcessEvent(const T& e)
    {
        e->Print();
        for (auto& func : mCallbacks)
        {
            func(*e);
        }
    }
};

struct Player
{
    std::string mPlayerName;
    int mGoals = 0;
    Game& mGame;

    Player(const std::string_view& name, Game& game)
        : mPlayerName(name)
        , mGame(game)
    {}

    void Score()
    {
        mGoals++;
        PlayerScoredData ps{mPlayerName, mGoals};
        mGame.ProcessEvent(&ps);
    }
};

struct Coach
{
    EventCallbackFn mEventCallback;
    
    Game& mGame;
    Coach(Game& game)
        : mGame(game)
    {
        mEventCallback = [this](auto&& e){ return this->OnEvent(std::forward<decltype(e)>(e)); };
        mGame.AddCallback(mEventCallback);
    }

    void OnEvent(EventData& e)
    {
        std::cout << "Yeah!\n";
    }
};

