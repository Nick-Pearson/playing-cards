#include "cardstack.h"
#include "logging.h"

#include "card.h"

CardStack::CardStack(const std::vector<CardDef>& inDeck, unsigned int startIndex /*= 0*/, unsigned int count /*= 0*/)
{
  if(count == 0) count = inDeck.size() - startIndex;

  m_Stack.reserve(count);

  for(unsigned int i = 0; i < count; ++i)
  {
    PushCard(inDeck[i]);
  }

  UpdateCardLocations();
  UpdateEmptyCard();
}

CardDef CardStack::PopCard()
{
  if(Size() == 0) return CardDef();

  CardStackItem item = m_Stack.back();

  if(Card* card = item.representation.get())
  {
    card->SetVisible(false);
  }

  m_Stack.pop_back();

  UpdateEmptyCard();
  UpdateClickableArea();

  return item.definition;
}

void CardStack::PopCards(int count, std::vector<CardDef>& outCards)
{
  count = count > Size() ? Size() : count;

  outCards.reserve(outCards.size() + count);

  for(int i = 0; i < count; ++i)
    outCards.push_back(PopCard());
}

void CardStack::PushCard(const CardDef& newCard)
{
  CardStackItem newItem(newCard);

  m_Stack.push_back(newItem);

  CreateRepresentation(Size() - 1);
  UpdateEmptyCard();
  UpdateClickableArea();
}

void CardStack::PushCards(const std::vector<CardDef>& cards)
{
  m_Stack.reserve(Size() + cards.size());

  for(const CardDef& def : cards)
    PushCard(def);
}

void CardStack::SetRootLocation(const glm::vec3& newPosition)
{
  m_Location = newPosition;
  UpdateCardLocations();
  UpdateClickableArea();
}

CardDef CardStack::PeekCard(int index) const
{
  if(!isValidIndex(index)) return CardDef();

  return m_Stack[index].definition;
}

std::shared_ptr<Card> CardStack::GetRepresentation(int index) const
{
  if(!isValidIndex(index)) return nullptr;

  return m_Stack[index].representation;
}

void CardStack::OnClicked(double mouseX, double mouseY, int button, int action, int mods)
{
  if(action != 0) return;

  PopCard();
}

void CardStack::UpdateCardLocations()
{
  for(int i = 0; i < Size(); ++i)
  {
    std::shared_ptr<Card> card = GetRepresentation(i);

    if(!card.get()) continue;

    card->transform.SetPosition(m_Location - ((float)i * StackSpacing));
  }

  if(Card* e_c = empty_card.get())
    e_c->transform.SetPosition(m_Location);
}

void CardStack::UpdateClickableArea()
{
  int offset = Size() - 1;
  SetClickableArea(Rect(
    m_Location.x - 14.0f,
    m_Location.y - 19.0f - (StackSpacing.y * offset),
    (14.0f * 2.0f) + (StackSpacing.x * offset),
    (19.0f * 2.0f) + (StackSpacing.y * offset)
  ));
}

void CardStack::CreateRepresentation(int index)
{
  if(!isValidIndex(index)) return;

  std::shared_ptr<Card> card = GetRepresentation(index);
  if(card.get()) return;

  card = Renderable::CreateRenderable<Card>(m_Stack[index].definition);
  card->transform.SetPosition(m_Location - ((float)index * StackSpacing));

  m_Stack[index].representation = card;
}

void CardStack::UpdateEmptyCard()
{
  if((Size() == 0 && emptyCardVisible) && !empty_card.get())
  {
    empty_card = Renderable::CreateRenderable<Card>(emptycard_def);
    empty_card->transform.SetPosition(m_Location);
  }
  else if ((Size() != 0 || !emptyCardVisible) && empty_card.get())
  {
    empty_card->SetVisible(false);
    empty_card.reset();
  }
}
