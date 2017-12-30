#include "clickable.h"

#include "inputmanager.h"

Clickable::Clickable()
{
  SetClickable(true);
}

Clickable::~Clickable()
{
  SetClickable(false);
}

void Clickable::ToLocal(double mouseX, double mouseY, double& outLocalX, double& outLocalY) const
{
  outLocalX = mouseX - m_ClickableArea.x1;
  outLocalY = mouseY - m_ClickableArea.y1;
}

void Clickable::SetClickableArea(const Rect& area)
{
  m_ClickableArea = area;
}

void Clickable::SetClickable(bool isClickable)
{
  if(isClickable == m_IsClickable) return;

  m_IsClickable = isClickable;

  if(gInputManager)
  {
    if(!isClickable)
      gInputManager->UnregisterClickable(this);
    else
      gInputManager->RegisterClickable(this);
  }
}
