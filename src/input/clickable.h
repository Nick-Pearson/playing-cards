#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "rect.h"

// mixin class to allow an object to recieve clicks
class Clickable
{
public:
  Clickable();
  virtual ~Clickable();

  // called when the user clicks on this object
  virtual void OnClicked(double mouseX, double mouseY, int button, int action, int mods) = 0;

public:
  void ToLocal(double mouseX, double mouseY, double& outLocalX, double& outLocalY) const;

  //sets the area that can be clicked
  void SetClickableArea(const Rect& area);

  //get the clickable area
  inline Rect GetClickableArea() const { return m_ClickableArea; }

  //set if this object can be clicked on
  void SetClickable(bool isClickable);

private:
  Rect m_ClickableArea;
  bool m_IsClickable = false;
};

#endif
