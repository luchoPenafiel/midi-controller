#ifndef ACTION_H
#define ACTION_H

class Action
{
public:
  virtual ~Action() = default;
  virtual void execute() = 0;
};

#endif