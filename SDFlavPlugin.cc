// -*- C++ -*-
#include "SDFlavPlugin.hh"
#include "FlavInfo.hh"

using fastjet::contrib::FlavInfo;

void SDFlavourCalc::operator()(fastjet::PseudoJet& j) {
  fastjet::ClusterSequence cs(j.constituents(), m_plugin);
  std::vector<fastjet::PseudoJet> sdj = m_sd(cs.exclusive_jets_up_to(1));

  FlavInfo flavj = sdj[0].user_info<FlavInfo>();
  for(size_t i=1; i < sdj.size(); i++){
    flavj = flavj+sdj[i].user_info<FlavInfo>();
  }
  j.set_user_info(new FlavInfo(flavj));
}


void SDFlavourCalc::operator()(std::vector<fastjet::PseudoJet>& jets) {
  for(fastjet::PseudoJet& j: jets) {
    operator()(j);
  }
}
