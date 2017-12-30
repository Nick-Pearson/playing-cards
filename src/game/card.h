#ifndef CARD_H
#define CARD_H

#include "sprite.h"
#include "cardtypes.h"

class Card : public Sprite
{
public:

  Card() {}
  Card(CardDef definiton);

  Card(const Card* other);

  virtual ~Card() {}

  void SetSuit(Suit newSuit);
  void SetCard(CardType newCard);

  void Flip();
  inline bool IsFaceUp() const { return m_Definition.facing == CardFace::FaceUp; }

private:

  void UpdateTexture();

  CardDef m_Definition;

};

#endif
