#ifndef SDFLAV_DEF
#define SDFLAV_DEF
#include "fastjet/contrib/SoftDrop.hh"
#include "fastjet/JadePlugin.hh"
#include "fastjet/contrib/Recluster.hh"
#include <memory>

class SDFlavourCalc {
public:

  /// Constructor
  SDFlavourCalc(const double beta = 2,
                const double zcut = 0.1,
                const double R = 0.4) : p_sd(new fastjet::contrib::SoftDrop(beta, zcut,
                                                                            fastjet::contrib::RecursiveSymmetryCutBase::SymmetryMeasure::scalar_z,
                                                                            R,
                                                                            std::numeric_limits<double>::infinity(),
                                                                            fastjet::contrib::RecursiveSymmetryCutBase::RecursionChoice::larger_pt,
                                                                            0)),
                                        p_plugin(new fastjet::JadePlugin()),
                                        p_recluster(new fastjet::Recluster(fastjet::JetDefinition(p_plugin.get()))){
    p_sd->set_reclustering(true,p_recluster.get());
  }

  std::unique_ptr<fastjet::contrib::SoftDrop> p_sd;
  std::unique_ptr<fastjet::JetDefinition::Plugin> p_plugin;
  std::unique_ptr<fastjet::Recluster> p_recluster;

  void operator()(fastjet::PseudoJet& jet);
  void operator()(std::vector<fastjet::PseudoJet>& jets);

};


#endif
