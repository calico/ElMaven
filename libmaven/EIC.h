/**
 * @class EIC
 * @ingroup libmaven
 * @brief Wrapper class for a eic.
 * @author Sabu George
 */
#ifndef MZEIC_H
#define MZEIC_H
 #include <mzSample.h>
 
class Peak;
class PeakGroup;
class mzSample;
class mzPoint;
class Scan;

class EIC {

    public:
        /// A constructor
        /**
        *
        *
        */
        EIC();

        /// A destructor
        /**
        *
        *
        */
        ~EIC();

        /// An enum
        /**
        * 
        */
        enum SmootherType { GAUSSIAN=0, AVG=1, SAVGOL=2 };

        vector <int> scannum;
        vector <float> rt;
        vector <float> mz;
        vector <float> intensity;
        vector <Peak>  peaks;
        string sampleName;

        /** pointer to originating sample */
        mzSample* sample;

        /**  color of the eic line, [r,g,b, alpha] */
        float color[4];

        /**  pointer to smoothed intentsity array */
        float *spline;

        /** pointer to baseline array */
        float *baseline;

        /** maxItensity in eics */
        float maxIntensity;

        /**      sum of all intensities in EIC */
        float totalIntensity;

        /** number of observatiosn above baseline. */
        int   eic_noNoiseObs;

        float mzmin;
        float mzmax;
        float rtmin;
        float rtmax;

        /**
        * [addPeak ]
        * @method addPeak
        * @param  peakPos []
        * @return []
        */
        Peak* addPeak(int peakPos);

        /**
        * [delete Peak]
        * @method deletePeak
        * @param  i          [peak position]
        */
        void deletePeak(unsigned int i);

        /**
        * [get Peak Positions]
        * @method getPeakPositions
        * @param  smoothWindow     [smoothing Window]
        */
        void getPeakPositions(int smoothWindow);

        /**
        * [get Peak Details]
        * @method getPeakDetails
        * @param  peak           [peak]
        */
        void getPeakDetails(Peak& peak);

        /**
        * [get Peak Width]
        * @method getPeakWidth
        * @param  peak         [peak]
        */
        void getPeakWidth(Peak& peak);

        /**
        * [compute BaseLine]
        * @method computeBaseLine
        * @param  smoothingWindow [smoothing Window]
        * @param  dropTopX        [drop top X percent]
        */
        void computeBaseLine(int smoothingWindow, int dropTopX);

        /**
        * [compute Spline]
        * @method computeSpline
        * @param  smoothWindow  [smoothing Window]
        */
        void computeSpline(int smoothWindow);

        /**
        * [find Peak Bounds]
        * @method findPeakBounds
        * @param  peak           [peak]
        */
        void findPeakBounds(Peak& peak);

        /**
        * [get Peak Statistics]
        * @method getPeakStatistics
        */
        void getPeakStatistics();

        void findPeaks();

        /**
        * [check Gaussian Fit]
        * @method checkGaussianFit
        * @param  peak             [peak]
        */
        void checkGaussianFit(Peak& peak);


        vector<mzPoint> getIntensityVector(Peak& peak);

        /**
        * [summary]
        * @method summary
        */
        void summary();

        /**
        * [set Smoother Type]
        * @method setSmootherType
        * @param  x               [Smoother type]
        */
        void setSmootherType(EIC::SmootherType x) { smootherType=x; }

        /**
        * [set Baseline Smoothing Window]
        * @method setBaselineSmoothingWindow
        * @param  x                          [baseline Smoothing Window]
        */
        void setBaselineSmoothingWindow(int x) { baselineSmoothingWindow=x;}

        /**
        * [setBaselineDropTopX ]
        * @method setBaselineDropTopX
        * @param  x                   []
        */
        void setBaselineDropTopX(int x) { baselineDropTopX=x; }

        bool makeEICSlice(mzSample* sample, float mzmin,float mzmax, float rtmin, float rtmax, int mslevel);

        void getRTMinMaxPerScan();

        void normalizeIntensityPerScan(float scale);

        /**
        * [size ]
        * @method size
        * @return []
        */
        inline unsigned int size() { return intensity.size();}

        /**
        * [getSample ]
        * @method getSample
        * @return []
        */
        inline mzSample* getSample() { return sample; }


        static vector<PeakGroup> groupPeaks(vector<EIC*>&eics, int smoothingWindow, float maxRtDiff);
        /**
        * [eicMerge ]
        * @method eicMerge
        * @param  eics     []
        * @return []
        */
        static EIC* eicMerge(const vector<EIC*>& eics);

        /**
        * [remove Low Rank Groups ]
        * @method removeLowRankGroups
        * @param  groups              [vector of peak groups]
        * @param  rankLimit           [group rank limit ]
        */
        static void removeLowRankGroups(vector<PeakGroup>&groups, unsigned int rankLimit );

        /**
        * [compare Max Intensity]
        * @method compMaxIntensity
        * @param  a                [EIC a]
        * @param  b                [EIC b]
        * @return [true or false]
        */
        static bool compMaxIntensity(EIC* a, EIC* b ) { return a->maxIntensity > b->maxIntensity; }

    private:
        SmootherType smootherType;

                        /** baseline smoothin window */
        int baselineSmoothingWindow;

                        /** fraction of point to remove when computing baseline */
        int baselineDropTopX;

};
#endif //MZEIC_H
