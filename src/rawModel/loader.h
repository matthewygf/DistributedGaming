#ifndef LOADER_H
#define LOADER_H
#include "rawModel.h"
#include <vector>

using namespace std;
class Loader
{
  public:
        RawModel loadToVao(vector<float>& positions);
        int createVAO();
        void storeData(int attributeNum, vector<float>& data);
        void unbindVAO();
        void cleanUp();

  private:
      vector <int> vaos ;
      vector <int> vbos ;     
  
};

#endif
