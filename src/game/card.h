#ifndef CARD_H
#define CARD_H

#include "sprite.h"
#include "cardtypes.h"

class Card : public Sprite
{
public:

  Card(CardType card, Suit suit, CardFace facing = CardFace::FaceUp);
  virtual ~Card() {}

  void SetSuit(Suit newSuit);
  void SetCard(CardType newCard);

  void Flip();
  inline bool IsFaceUp() const { return m_Facing == CardFace::FaceUp; }

private:

  void UpdateTexture();

  Suit m_Suit;
  CardType m_Card;
  CardFace m_Facing;

};

#endif
