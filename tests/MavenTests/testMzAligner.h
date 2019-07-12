#ifndef TESTMZALIGNER_H
#define TESTMZALIGNER_H
#include <QtTest>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class TestMzAligner : public QObject {
    Q_OBJECT

    public:
        TestMzAligner();

    private Q_SLOTS:
        // functions executed by QtTest before and after test suite
        void initTestCase();
        void cleanupTestCase();

        // functions executed by QtTest before and after each test
        void init();
        void cleanup();

        // test functions - all functions prefixed with "test" will be ran as tests
        // this is automatically detected thanks to Qt's meta-information about QObjects
        void testDoAlignment();
        void testSaveFit();

        /**
         * @brief Tests the functionality of OBI-WARP
         * @details Calculates the rt difference between peaks of reference Sample and the rest
         * of the samples. The test cases passes if the rt difference between peaks decreases after alignment
         */
        void testObiWarp();

};

#endif // TESTMZALIGNER_H
