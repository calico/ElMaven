#ifndef FRAGMENT_H
#define FRAGMENT_H
#include <vector>
#include <string>
#include <map>

class Scan;

using std::vector;
using std::string;
using std::map;

struct FragmentationMatchScore {

    double fractionMatched;
    double ppmError;
    double mzFragError;
    double mergedScore;
    double hypergeomScore;
    double mvhScore;
    double dotProduct;
    double weightedDotProduct;
    double spearmanRankCorrelation;
    double ticMatched;
    double numMatches;

    static vector<string> getScoringAlgorithmNames() {
        vector<string> names;
        names.push_back("HyperGeomScore");
        names.push_back("MVH");
        names.push_back("DotProduct");
        names.push_back("WeightedDotProduct");
        names.push_back("SpearmanRank");
        names.push_back("TICMatched");
        names.push_back("NumMatches");
        return names;
    }

    double getScoreByName(string scoringAlgorithm) {
        if (scoringAlgorithm == "HyperGeomScore")
            return hypergeomScore;
        else if (scoringAlgorithm == "MVH")
            return mvhScore;
        else if (scoringAlgorithm == "DotProduct")
            return dotProduct;
        else if (scoringAlgorithm == "SpearmanRank")
            return spearmanRankCorrelation;
        else if (scoringAlgorithm == "TICMatched")
            return ticMatched;
        else if (scoringAlgorithm == "WeightedDotProduct")
            return weightedDotProduct;
        else if (scoringAlgorithm == "NumMatches")
            return numMatches;
        else return hypergeomScore;

    }

    FragmentationMatchScore() {
        fractionMatched = 0;
        spearmanRankCorrelation = 0;
        ticMatched = 0;
        numMatches = 0;
        ppmError = 1000;
        mzFragError = 1000;
        mergedScore = 0;
        dotProduct = 0;
        weightedDotProduct = 0;
        hypergeomScore = 0;
        mvhScore = 0;
    }

    FragmentationMatchScore& operator=(const FragmentationMatchScore& b) {
        fractionMatched = b.fractionMatched;
        spearmanRankCorrelation = b.spearmanRankCorrelation;
        ticMatched = b.ticMatched;
        numMatches = b.numMatches;
        ppmError = b.ppmError;
        mzFragError = b.mzFragError;
        mergedScore = b.mergedScore;
        dotProduct = b.dotProduct;
        weightedDotProduct = b.weightedDotProduct;
        hypergeomScore = b.hypergeomScore;
        mvhScore = b.mvhScore;
        return *this;
    }
};

class Fragment { 

    public: 
        Fragment();
        
        Fragment(Scan* scan,
                 float minFractionalIntensity,
                 float minSigNoiseRatio,
                 int maxFragmentSize);

        Fragment(Fragment* other);

        Fragment& operator=(const Fragment& f);

        ~Fragment();

        double precursorMz;				//parent
        int polarity;					//scan polarity 	+1 or -1
        vector<float> mzValues;				//mz values
        vector<float> intensityValues;		//intensity values
        vector<Fragment*> brothers;		//pointers to similar fragments 
        string sampleName;				//name of Sample
        int scanNum;					//scan Number
        float rt;						//retention time of parent scan
        float collisionEnergy;
        int precursorCharge;	
        float purity;

        Fragment* consensus; //consensus pattern build on brothers
        vector<int> obscount; // vector size =  mzValues vector size, with counts of number of times mz was observed
        map<int,string> annotations; //mz value annotations.. assume that values are sorted by mz

        void appendBrothers(Fragment* other);

        void printMzList();

        int findClosestHighestIntensityPos(float mz, float tolr);

        static vector<int> compareRanks(Fragment* a, Fragment* b, float productAmuToll);

        void addBrotherFragment(Fragment* b);

        /**
         * @brief create a consensus spectra for all brother fragments
         * @details go through all brother fragments and create a spectra where 
         * a new m/z is added if it does not fall within the PPM tolerance range of existing m/zs.
         * intensity for every m/z is calculated as the sum of intensities in that m/z bracket
         * averaged over the number of brother fragments and further normalized against the highest intensity.
         */
        void buildConsensus(float productPpmTolr);

        float consensusRt();

        float consensusPurity();

        vector<int> intensityOrderDesc();

        vector<int> mzSortIncreasing();

        void sortByIntensity();

        void sortByMz();

        void buildConsensusAvg();

        double totalIntensity();

        vector<float> asDenseVector(float mzmin, float mzmax, int nbins = 2000);

        double logNchooseK(int N, int k);

        double spearmanRankCorrelation(const vector<int>& X);

        double ticMatched(const vector<int>& X);

        double mzErr(const vector<int>& X, Fragment* other);

        double dotProduct(Fragment* other);

        double hyperGeometricScore(int k, int m, int n, int N = 100000);

        /**
         * Multivariate hypergeometric distribution
         */
        double MVH(const vector<int>& X, Fragment* other);

        double mzWeightedDotProduct(const vector<int>& X, Fragment* other);

        FragmentationMatchScore scoreMatch(Fragment* other, float productPpmTolr);

        inline unsigned int nobs() { return mzValues.size(); }

        static bool compPrecursorMz(const Fragment* a, const Fragment* b);
        bool operator<(const Fragment* b) const;
        bool operator==(const Fragment* b) const;
};

#endif
