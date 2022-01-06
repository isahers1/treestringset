#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Include the testing-logger library from
// the CS70 system directory in Docker.
#include <cs70/testinglogger.hpp>

#include "treestringset.hpp"

using namespace std;

///////////////////////////////////////////////////////////
//  TESTING
///////////////////////////////////////////////////////////


bool insertTest() {
    TestingLogger log("insert");

    TreeStringSet mySet;

    mySet.insert("Isaac");
    affirm(mySet.size() == 1);

    mySet.insert("Tejus");
    affirm(mySet.exists("Tejus") == true);
    affirm(mySet.size() == 2);

    return log.summarize();
}

bool existsTest() {
    TestingLogger log("exists");

    TreeStringSet mySet;

    affirm(mySet.exists("Isaac") == false);

    mySet.insert("Tejus");
    affirm(mySet.exists("Tejus") == true);

    return log.summarize();
}

bool printTest() {
    TestingLogger log("print");

    TreeStringSet mySet;

    mySet.insert("Tejus");

    stringstream ss;
    ss << mySet;

    string expected = "(-, Tejus, -)";

    affirm(ss.str() == expected);

    return log.summarize();
}


bool beginTest() {
    TestingLogger log("begin");

    TreeStringSet mySet;
    mySet.insert("42");

    TreeStringSet::iterator iter = mySet.begin();

    affirm(iter == mySet.begin());

    return log.summarize();
}

bool endTest() {
    TestingLogger log("end");

    TreeStringSet mySet;
    mySet.insert("42");
    mySet.insert("43");
    mySet.insert("41");

    TreeStringSet::iterator iter = mySet.end();

    affirm(iter == mySet.end());

    return log.summarize();
}

bool starTest() {
    TestingLogger log("star");

    TreeStringSet mySet;
    mySet.insert("42");
    mySet.insert("43");
    mySet.insert("41");

    TreeStringSet::iterator iter = mySet.begin();

    affirm(*iter == "42");

    return log.summarize();
}

bool iteratorEqualsTest() {
    TestingLogger log("iterator equals");

    TreeStringSet mySet;
    mySet.insert("42");
    mySet.insert("43");
    mySet.insert("41");

    TreeStringSet::iterator iterOne = mySet.begin();
    TreeStringSet::iterator iterTwo = mySet.begin();

    affirm(iterOne == iterTwo);

    ++iterOne;

    affirm(!(iterOne == iterTwo));

    return log.summarize();
}

bool iteratorPlusTest() {
    TestingLogger log("iterator plus");

    TreeStringSet mySet;
    mySet.insert("42");
    mySet.insert("43");
    mySet.insert("41");

    TreeStringSet::iterator iter = mySet.begin();

    ++iter;
    affirm(*iter == "41");

    ++iter;
    ++iter;
    affirm(iter == mySet.end());

    return log.summarize();
}

bool treeEqualsTest() {
    TestingLogger log("tree equals");

    TreeStringSet mySetOne;
    TreeStringSet mySetTwo;

    affirm(mySetOne == mySetTwo);
    mySetOne.insert("42");
    mySetOne.insert("43");
    mySetOne.insert("41");

    mySetTwo.insert("41");
    mySetTwo.insert("42");
    mySetTwo.insert("43");

    affirm(mySetOne == mySetTwo);

    mySetOne.insert("44");

    affirm(!(mySetTwo == mySetOne));

    return log.summarize();
}

bool heightTest() {
    TestingLogger log("height");

    TreeStringSet mySet;
    mySet.insert("42");
    mySet.insert("43");
    mySet.insert("41");

    affirm(mySet.height() == 1);

    return log.summarize();
}


bool depthTest() {
    TestingLogger log("depth");

    TreeStringSet mySet;
    affirm(mySet.averageDepth() == 0);
    mySet.insert("42");
    mySet.insert("43");
    mySet.insert("41");

    // affirm(mySet.averageDepth() == 2/3);

    return log.summarize();
}

bool showStatisticsTest() {
    TestingLogger log("print");

    TreeStringSet mySet;
    mySet.insert("42");
    mySet.insert("43");
    mySet.insert("41");
    mySet.insert("40");

    stringstream ss;
    mySet.showStatistics(ss);

    string expected = "4 nodes, height 2, average depth 1\n";

    affirm(ss.str() == expected);

    return log.summarize();
}

/*
 * Test the TreeStringSet
 */
int main(int, char**) {
    TestingLogger alltests("All tests");

    affirm(insertTest());

    affirm(existsTest());

    affirm(beginTest());

    affirm(endTest());

    affirm(starTest());

    affirm(iteratorEqualsTest());

    affirm(iteratorPlusTest());

    affirm(printTest());

    affirm(treeEqualsTest());

    affirm(heightTest());

    affirm(depthTest());

    affirm(showStatisticsTest());

    if (alltests.summarize(true)) {
        return 0;  // Error code of 0 == Success!
    } else {
        return 2;  // Arbitrarily chosen exit code of 2 means tests failed.
    }
}
