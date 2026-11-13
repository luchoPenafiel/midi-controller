#ifndef ACTION_H
#define ACTION_H

class Action
{
public:
  virtual ~Action() = default;
  virtual void execute() = 0;

  virtual void activate() = 0;
  virtual void deactivate() = 0;
  virtual bool isActive() const = 0;
};

#endif