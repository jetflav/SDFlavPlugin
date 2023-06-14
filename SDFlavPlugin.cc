// -*- C++ -*-
#include "SDFlavPlugin.hh"
#include "FlavInfo.hh"
#include <istream>


using fastjet::contrib::FlavInfo;
using fastjet::contrib::FlavHistory;

void SDFlavourCalc::operator()(fastjet::PseudoJet& jet) {
  fastjet::ClusterSequence cs(jet.constituents(), m_plugin);
  std::vector<fastjet::PseudoJet> sdjets = m_sd(cs.exclusive_jets_up_to(1));
  if(sdjets.size() != 1) jet.set_user_info(new FlavHistory(FlavInfo()));
  std::vector<fastjet::PseudoJet> sdj = sdjets[0].constituents();
  FlavInfo flavj = FlavHistory::current_flavour_of(sdj[0]);
  for(size_t i=1; i < sdj.size(); i++){
    flavj = flavj+FlavHistory::current_flavour_of(sdj[i]);
  }
  // if(jet.constituents().size() != sdj.size()) {
  //   std::cout<<jet.constituents().size()<<" "<<sdj.size()<<"\n";
  //   for(auto p: jet.constituents()) std::cout<<FlavHistory::current_flavour_of(p).description()<<"\n";
  //   std::cout<<"---------\n";
  //   for(auto p: sdj) std::cout<<FlavHistory::current_flavour_of(p).description()<<"\n";
  //   std::cout<<"**********\n";
  // }
  jet.set_user_info(new FlavHistory(flavj));
}


void SDFlavourCalc::operator()(std::vector<fastjet::PseudoJet>& jets) {
  for(fastjet::PseudoJet& jet: jets) {
    operator()(jet);
  }
}
