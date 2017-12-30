#ifndef CARDTYPES_H
#define CARDTYPES_H

enum Suit
{
  S_None,

  S_Clubs,
  S_Hearts,
  S_Spades,
  S_Diamonds
};

enum CardType
{
  C_None,
  Joker,

  Ace,
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King
};

enum CardFace
{
  FaceUp,
  FaceDown
};

struct CardDef
{
  CardDef(Suit inSuit = Suit::S_Clubs, CardType inCardType = CardType::C_None, CardFace inFacing = CardFace::FaceDown) :
  suit(inSuit), cardType(inCardType), facing(inFacing)
  {}

  Suit suit;
  CardType cardType;
  CardFace facing;
};

#endif
