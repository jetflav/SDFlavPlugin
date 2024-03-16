// -*- C++ -*-
#include "TransformedFlavPlugin.hh"
#include "FlavInfo.hh"
#include <istream>


using fastjet::contrib::FlavInfo;
using fastjet::contrib::FlavHistory;

void TransformedFlavourCalc::operator()(fastjet::PseudoJet& jet) {
  fastjet::PseudoJet tjet = p_transform->result(jet);
  std::vector<fastjet::PseudoJet> tj = tjet.constituents();
  FlavInfo flavj = FlavHistory::current_flavour_of(tj[0]);
  for(size_t i=1; i < tj.size(); i++){
    flavj = flavj+FlavHistory::current_flavour_of(tj[i]);
  }
  jet.set_user_info(new FlavHistory(flavj));
}


void TransformedFlavourCalc::operator()(std::vector<fastjet::PseudoJet>& jets) {
  for(fastjet::PseudoJet& jet: jets) {
    operator()(jet);
  }
}
