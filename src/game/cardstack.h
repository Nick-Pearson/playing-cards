#ifndef CARDSTACK_H
#define CARDSTACK_H

#include "cardtypes.h"
#include "clickable.h"

#include <glm.hpp>

#include <vector>
#include <memory>

class Card;

//wrapper class for managing a 'stack' of cards, can be drived to include game rules such as when a card can be dropped onto a card stack
class CardStack : public Clickable
{
public:

  CardStack() : CardStack(std::vector<CardDef>()) {}

  //add the range of cards (count of 0 indicates all cards beyond start index)
  CardStack(const std::vector<CardDef>& inDeck, unsigned int startIndex = 0, unsigned int count = 0);

  // Remove from the end of the stack
  CardDef   PopCard();
  void      PopCards(int count, std::vector<CardDef>& outCards);

  //add to end of stack
  void      PushCard(const CardDef& newCard);
  void      PushCards(const std::vector<CardDef>& cards);

  // set the location for the base of the card stack
  virtual void SetRootLocation(const glm::vec3& newPosition);

  // see the deifnition of the card at index, returns none if out of range
  CardDef   PeekCard(int index) const;

  // get the renderer representation of the card at index (can be nullptr)
  std::shared_ptr<Card> GetRepresentation(int index) const;

  // returns the number of cards
  inline int Size() const { return m_Stack.size(); }

  // is this a valid index into the stack
  inline bool isValidIndex(int index) const { return index >= 0 && index < Size(); }

  void SetEmptyCardVisible(bool visible) { emptyCardVisible = visible; UpdateEmptyCard(); }

  glm::vec3 StackSpacing = glm::vec3(0.0f, 6.0f, 0.0f);
  CardDef emptycard_def = CardDef(Suit::S_None, CardType::C_None, CardFace::FaceUp);

public:
  // Clickable Interface
  virtual void OnClicked(double mouseX, double mouseY, int button, int action, int mods) override;

protected:
  void UpdateCardLocations();
  void UpdateClickableArea();
  void CreateRepresentation(int index);

  struct CardStackItem
  {
  public:
    CardStackItem(const CardDef& def) : definition(def)
    {}

    CardDef definition;
    std::shared_ptr<Card> representation;
  };

  std::vector<CardStackItem> m_Stack;

  //renderable to show a stack when empty
  bool emptyCardVisible = true;
  std::shared_ptr<Card> empty_card;

  void UpdateEmptyCard();

  glm::vec3 m_Location;
};

#endif
