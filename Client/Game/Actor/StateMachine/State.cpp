#include "pch.h"
#include "State.h"

State::State(Actor* owner, StateMachine* state_machine) :
    owner_(owner),
    state_machine_(state_machine)
{
}
