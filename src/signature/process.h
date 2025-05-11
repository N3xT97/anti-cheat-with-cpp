#ifndef ANTI_CHEAT_SIGNATURE_PROCESS_H
#define ANTI_CHEAT_SIGNATURE_PROCESS_H

#include "signature/interface.h"

namespace signature {
class Process final: public ISignature{
public:
  std::optional<std::string> name;

  void normalize() override;
  SignData extract() const override;
};
}


#endif //ANTI_CHEAT_SIGNATURE_PROCESS_H
