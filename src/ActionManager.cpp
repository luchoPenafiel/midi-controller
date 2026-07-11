#include "ActionManager.h"

ActionManager::ActionManager()
{
  for (uint8_t i = 0; i < MAX_BUTTONS; i++)
  {
    _actions[i] = nullptr;
  }
}

void ActionManager::assignAction(uint8_t buttonIndex, Action *action)
{
  if (buttonIndex >= MAX_BUTTONS)
    return;

  _actions[buttonIndex] = action;
}

void ActionManager::execute(uint8_t buttonIndex)
{
  if (buttonIndex >= MAX_BUTTONS)
    return;

  if (_actions[buttonIndex] != nullptr)
  {
    _actions[buttonIndex]->execute();
  }
}