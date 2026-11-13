#include "ToggleMacroAction.h"

ToggleMacroAction::ToggleMacroAction()
{
  _enabled = false;

  _onCount = 0;
  _offCount = 0;

  for (uint8_t i = 0; i < MAX_ACTIONS; i++)
  {
    _onActions[i] = nullptr;
    _offActions[i] = nullptr;
  }
}

void ToggleMacroAction::addOnAction(Action *action)
{
  if (_onCount < MAX_ACTIONS)
  {
    _onActions[_onCount++] = action;
  }
}

void ToggleMacroAction::addOffAction(Action *action)
{
  if (_offCount < MAX_ACTIONS)
  {
    _offActions[_offCount++] = action;
  }
}

void ToggleMacroAction::execute()
{
  if (_enabled)
  {
    deactivate();
  }
  else
  {
    activate();
  }
}

void ToggleMacroAction::activate()
{
  if (_enabled)
  {
    return;
  }

  for (uint8_t i = 0; i < _onCount; i++)
  {
    _onActions[i]->execute();
  }

  _enabled = true;
}

void ToggleMacroAction::deactivate()
{
  if (!_enabled)
  {
    return;
  }

  for (uint8_t i = 0; i < _offCount; i++)
  {
    _offActions[i]->execute();
  }

  _enabled = false;
}

bool ToggleMacroAction::isActive() const
{
  return _enabled;
}
