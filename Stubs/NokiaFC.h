#ifndef NOKIAFC_H
#define NOKIAFC_H

#define R_FC_ERROR_MSG 0

class FirstCheck
{
  public:
    inline FirstCheck() {};
    static inline void DoFirstCheckL(const TLitC8<7> &, TPtr16) {}
};

#endif /* NOKIAFC_H */
