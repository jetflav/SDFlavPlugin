#ifndef TRANSFORMFLAV_DEF
#define TRANSFORMFLAV_DEF
#include "fastjet/tools/Transformer.hh"
#include <memory>

class TransformedFlavourCalc {
public:

  /// Constructor
  TransformedFlavourCalc(fastjet::Transformer* transform) : p_transform(transform) {}

  std::unique_ptr<fastjet::Transformer> p_transform;

  void operator()(fastjet::PseudoJet& jet);
  void operator()(std::vector<fastjet::PseudoJet>& jets);
};


#endif
