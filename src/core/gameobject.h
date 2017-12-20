#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
  //called when this object is created
  virtual void OnCreated() {}

  //called every frame
  virtual void Update(float deltaSeconds) {}

  //called when this object is destroyed
  virtual void OnDestroyed() {}
};

#endif
