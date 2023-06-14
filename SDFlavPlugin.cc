// -*- C++ -*-
#include "fastjet/contrib/SoftDrop.hh"
#include "fastjet/JadePlugin.hh"
#include "fastjet/contrib/Recluster.hh"
#include "FlavInfo.hh"

using fastjet::contrib::FlavInfo;

class SDFlavourCalc{
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

  void operator()(std::vector<fastjet::PseudoJet>& jets) {
    for(fastjet::PseudoJet& j: jets) {
      fastjet::ClusterSequence cs(j.constituents(), m_plugin);
      std::vector<fastjet::PseudoJet> sdj = m_sd(cs.exclusive_jets_up_to(1));

      FlavInfo flavj = sdj[0].user_info<FlavInfo>();
      for(size_t i=1; i < sdj.size(); i++){
        flavj = flavj+sdj[i].user_info<FlavInfo>();
      }
      j.set_user_info(new FlavInfo(flavj));
    }
  }

};




