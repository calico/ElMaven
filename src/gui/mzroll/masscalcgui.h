#ifndef MASSCALCGUI_H
#define MASSCALCGUI_H

#include "stable.h"
#include "mzMassCalculator.h"
#include "ui_masscalcwidget.h"

class QAction;
class QTextEdit;
class MainWindow;
class MassCalculator;
class Database;
class MassCutoff;
class Compound;
class PeakGroup;

class MassCalcWidget: public QDockWidget,  public Ui_MassCalcWidget {
      Q_OBJECT

public:
      MassCalcWidget(MainWindow* mw);
      ~MassCalcWidget();

protected:
        

public Q_SLOTS: 
 	  void setMass(float mz);
	  void setCharge(float charge);
	  void setMassCutoff(MassCutoff *massCutoff);
      void compute();
	  QSet<Compound*> findMathchingCompounds(float mz, MassCutoff *massCutoff, float charge);
      void setPeakGroup(PeakGroup* grp);
      void setFragmentationScan(Scan* scan);

private Q_SLOTS:
      void _showInfo();
	  void getMatches();
      void showTable();

private:
      MainWindow* _mw;
      MassCalculator mcalc;
	  std::vector< MassCalculator::Match* > matches;
      std::vector<Compound*> sortedcompounds;

	  double _mz;
	  double _charge;
	  MassCutoff* _massCutoff;

      void pubChemLink(QString formula);
      void keggLink(QString formula);
      void setupSortedCompoundsDB();
      
};

#endif
