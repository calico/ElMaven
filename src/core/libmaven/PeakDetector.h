#ifndef PEAKDETECTOR_H
#define PEAKDETECTOR_H

#include <qdebug.h>
#include <qstring.h>
#include <qdatetime.h>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>

#include <omp.h>

class Compound;
class EIC;
class MavenParameters;
class mzSample;
class mzSlice;
class PeakGroup;

/**
 * @class PeakDetector
 * @ingroup libmaven
 * @brief all peak detection logic resides here.
 * @author Elucidata
 */
class PeakDetector {
public:
    boost::signals2::signal< void (const std::string&,unsigned int , int ) > boostSignal;

	PeakDetector();
	PeakDetector(MavenParameters* mp);


	//copy constructor	
	PeakDetector(const PeakDetector &obj) {
		mavenParameters = obj.mavenParameters; 
	}
	
	//assignment constructor
	PeakDetector& operator=(const PeakDetector& obj) {
		mavenParameters = obj.mavenParameters;
		return *this;
	}

    
    void sendBoostSignal( const std::string& progressText, unsigned int completed_slices, int total_slices)
    {
    boostSignal(progressText, completed_slices, total_slices);
    }


	void resetProgressBar();

	/**
	 * [get Maven Parameters]
	 * @return [params]
	 */
	MavenParameters* getMavenParameters() {
		return mavenParameters;
	}

	/**
	 * [set Maven Parameters]
	 * @param mp [params]
	 */
	void setMavenParameters(MavenParameters* mp) {
		mavenParameters = mp;
	}

	/**
	 * [align Samples using Aligner class]
	 * @method alignSamples
	 */
    void alignSamples(const int& method);

	/**
	 * [process Slices]
	 * @method processSlices
	 */
	void processSlices(void);
        void pullAllIsotopes();
        /**
	 * [process one Slice]
	 * @method processSlice
	 * @param  slice        [pointer to mzSlice]
	 */
	void processSlice(mzSlice& slice);

	/**
	 * [process Mass Slices]
	 * @method processMassSlices
	 */
	void processMassSlices();

	/**
	 * [process Slices]
	 * @method processSlices
	 * @param  slices        [pointer to vector of pointer to mzSlice]
	 * @param  setName       [name of set]
	 */
        void processSlices(std::vector<mzSlice*>&slices, std::string setName);

	/**
	 * @brief Filter groups on the basis of user-defined parameters
	 * @param peakgroups vector of Peakgroup objects
	 * @param slice mzSlice object bound to PeakGroup
	 * @return filteredGroups Filtered PeakGroups
	 * @see PeakGroup
	 */
        std::vector<PeakGroup*> groupFiltering(std::vector<PeakGroup> &peakgroups, mzSlice* slice);

	/**
	 * @brief compute fragmentation pattern for all groups
	 */
        void computeFragmentationPattern(std::vector<PeakGroup> &peakgroups);

	/**
	 * [process Compounds]
	 * @method processCompounds
	 * @param  set        [vector of pointer to Compound]
	 * @param  setName       [name of set]
	 * @return [vector of pointer to mzSlice]
	 */
        std::vector<mzSlice*> processCompounds(std::vector<Compound*> set, std::string setName);

    static std::vector<EIC*> pullEICs(mzSlice* slice,
                                 std::vector<mzSample*>& samples,
                                 MavenParameters* mp);

        private:

	/**
	 * [check overlap between RT for each group through all the samples; if a certain degree of overlap is present, do not create a new group]
	 * @method addPeakGroup
	 * @param  group        [pointer to PeakGroup]
	 * @return [True if group is added to all groups, else False]
	 */
	MavenParameters* mavenParameters;
	bool zeroStatus;
};

#endif // PEAKDETECTOR_H
