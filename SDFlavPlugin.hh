#ifndef SDFLAV_DEF
#define SDFLAV_DEF
#include "fastjet/contrib/SoftDrop.hh"
#include "fastjet/JadePlugin.hh"
#include "fastjet/contrib/Recluster.hh"


class SDFlavourCalc {
public:

  /// Constructor
  SDFlavourCalc(const double beta = 2,
                const double zcut = 0.1,
                const double R = 0.4) {

    m_sd = {beta, zcut,
            fastjet::contrib::RecursiveSymmetryCutBase::SymmetryMeasure::scalar_z,
            R,
            std::numeric_limits<double>::infinity(),
            fastjet::contrib::RecursiveSymmetryCutBase::RecursionChoice::larger_pt,
            0};

    m_plugin = new fastjet::JadePlugin();
    fastjet::Recluster recluster = {fastjet::JetDefinition(m_plugin)};
    m_sd.set_reclustering(true,&recluster);

  }

  fastjet::contrib::SoftDrop m_sd = {0,0,1};
  fastjet::JetDefinition::Plugin * m_plugin;

  void operator()(std::vector<fastjet::PseudoJet>& jets);

};


#endif
