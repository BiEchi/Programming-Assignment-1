#include "Person.hpp"
#include "HashMap.hpp"
/**
 * @brief Compare the distance of two people, decide whether the distance is
 * within the threshold.
 *
 * @param address the address of the person to be compared with the fixed point
 * person, where address is int arrary of length two. The first component is x
 * coordinate, the second component is y coordinate.
 * @param center the address of the fixed point person.
 * @param threshold corresponds to "theta" in the documentation
 * @return true if the distance is less or equal than the threshold, false
 * otherwise.
 */
 #include <unordered_map>
    using namespace std;
    int nodeNum = 1;
    int node1[] = {0, 1};
    int node2[] = {1, 2};
    int node3[] = {1, 3};
    int node4[] = {2, 5};
    int node5[] = {3, 7};
    int node6[] = {0, 9};
    int node7[] = {10, 0};
    int node8[] = {1, 12};

    unordered_map<int, int*> forwardtable{{1, node1}, {2, node2}, {3, node3},
                                          {4, node4}, {5, node5}, {6, node6},
                                          {7, node7}, {8, node8}};

    int threshold = 1;
bool withInThreshold(int *address, int *center, int threshold) {
  double compare_x, compare_y, center_x, center_y;
  double distanceS;
  compare_x = address[0];
  compare_y = address[1];
  center_x = center[0];
  center_y = center[1];
  distanceS = (compare_x - center_x) * (compare_x - center_x) +
              (compare_y - center_y) * (compare_y - center_y);
  return distanceS <= threshold * threshold ? true : false;
}

int *center = forwardtable.at(nodeNum);
void query(HashMap addressIndex) {
  vector<int> nodeWithInThreshold1;
  vector<int> nodeWithInThreshold2;
  vector<int> nodeWithInThreshold3;
  for (int i = 1; i <= 8; i++) {
    int *address = forwardtable.at(i);
    if (withInThreshold(address, center, threshold)) {
      nodeWithInThreshold1.push_back(i);
    }
  }
  for (int i = 1; i <= 8; i++) {
    int *address = forwardtable.at(i);
    if (withInThreshold(address, center, threshold * 2)) {
      nodeWithInThreshold2.push_back(i);
    }
  }
  for (int i = 1; i <= 8; i++) {
    int *address = forwardtable.at(i);
    if (withInThreshold(address, center, threshold * 3)) {
      nodeWithInThreshold3.push_back(i);
    }
  }
  vector<Person *> personList;
  float treatmentType1 = 0;
  float treatmentType2 = 0;
  float treatmentType3 = 0;
  for (vector<int>::iterator iter = nodeWithInThreshold1.begin();
       iter != nodeWithInThreshold1.end(); iter++) {
    int temp = *iter;
    personList = addressIndex.query(temp);
    for (auto iter = personList.begin(); iter != personList.end(); iter++) {
      if ((*iter)->getTreatmentType() == '1') {
        treatmentType1++;
      } else if ((*iter)->getTreatmentType() == '2') {
        treatmentType2++;
      } else {
        treatmentType3++;
      }
    }

    cout << "The percentage of patients of emergency cure with the first threshold is "
         << treatmentType1 / (treatmentType1 + treatmentType2 + treatmentType3)
         << endl;
    cout << "The percentage of patients in hospital bed with the first threshold is "
         << treatmentType2 / (treatmentType1 + treatmentType2 + treatmentType3)
         << endl;
    cout << "The percentage of patients under vaccination with the first threshold is "
         << treatmentType3 / (treatmentType1 + treatmentType2 + treatmentType3)
         << endl;
  }
    treatmentType1 = 0;
    treatmentType2 = 0;
    treatmentType3 = 0;
    for (auto iter = nodeWithInThreshold2.begin();
       iter != nodeWithInThreshold2.end(); iter++) {
    personList = addressIndex.query(*iter);
    for (auto iter = personList.begin(); iter != personList.end(); iter++) {
      if ((*iter)->getTreatmentType() == '1') {
        treatmentType1++;
      } else if ((*iter)->getTreatmentType() == '2') {
        treatmentType2++;
      } else {
        treatmentType3++;
      }
    }

    cout << "The percentage of patients of emergency cure with the first threshold is "
         << treatmentType1 / (treatmentType1 + treatmentType2 + treatmentType3)
         << endl;
    cout << "The percentage of patients in hospital bed with the first threshold is "
         << treatmentType2 / (treatmentType1 + treatmentType2 + treatmentType3)
         << endl;
    cout << "The percentage of patients under vaccination with the first threshold is "
         << treatmentType3 / (treatmentType1 + treatmentType2 + treatmentType3)
         << endl;
  }
    treatmentType1 = 0;
    treatmentType2 = 0;
    treatmentType3 = 0;
  for (auto iter = nodeWithInThreshold3.begin();
       iter != nodeWithInThreshold3.end(); iter++) {
    personList = addressIndex.query(*iter);
    for (auto iter = personList.begin(); iter != personList.end(); iter++) {
      if ((*iter)->getTreatmentType() == '1') {
        treatmentType1++;
      } else if ((*iter)->getTreatmentType() == '2') {
        treatmentType2++;
      } else {
        treatmentType3++;
      }
    }

    cout << "The percentage of patients of emergency cure with the first threshold is "
         << treatmentType1 / (treatmentType1 + treatmentType2 + treatmentType3)
         << endl;
    cout << "The percentage of patients in hospital bed with the first threshold is "
         << treatmentType2 / (treatmentType1 + treatmentType2 + treatmentType3)
         << endl;
    cout << "The percentage of patients under vaccination with the first threshold is "
         << treatmentType3 / (treatmentType1 + treatmentType2 + treatmentType3)
         << endl;
  }
}
