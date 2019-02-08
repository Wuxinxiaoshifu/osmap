/*
 * dummymap.h
 *
 *  Created on: 17 nov. 2018
 *      Author: alejandro
 */

#ifndef DUMMYMAP_H_
#define DUMMYMAP_H_

#include <set>
#include <map>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

namespace ORB_SLAM2{

class KeyFrame;

class MapPoint{
public:
  static unsigned int nNextId;
  unsigned int mnId;
  bool mbBad = false;
  Mat mWorldPos;
  float mnVisible;
  float mnFound;
  Mat mDescriptor;

  KeyFrame *mpRefKF;
  std::map<KeyFrame*,size_t> mObservations;
  void AddObservation(KeyFrame*, int){}
  void SetBadFlag(){}
  void UpdateNormalAndDepth(){}
};

class KeyFrame{
public:
  static unsigned int nNextId;
  unsigned int mnId;
  bool mbBad = false;
  double mTimeStamp = 0;
  Mat mTcw;
  Mat mK;
  Mat mDescriptors;
  unsigned int N;
  vector<KeyPoint> mvKeysUn;
  vector<MapPoint*> mvpMapPoints;
  set<KeyFrame*> mspLoopEdges;

  bool mbNotErase;
  const int mnMinX=0, mnMinY=0, mnMaxX=2, mnMaxY=2, mnGridCols=1, mnGridRows=1;
  const float mfGridElementWidthInv=.5, mfGridElementHeightInv=.5;
  KeyFrame *mpParent = NULL;
  vector<vector<vector<size_t> > > mGrid;
  std::map<KeyFrame*, int> mConnectedKeyFrameWeights;
  vector<KeyFrame*> mvpOrderedConnectedKeyFrames;
  void ComputeBoW(){}
  void SetPose(Mat){}
  void UpdateConnections(){}
  void SetBadFlag(){}
  void ChangeParent(KeyFrame *pKF){}
};


class Map{
public:
  set<MapPoint*> mspMapPoints;
  set<KeyFrame*> mspKeyFrames;
  vector<KeyFrame*> mvpKeyFrameOrigins;
  long unsigned int mnMaxKFid;
};

class KeyFrameDatabase{
public:
	void add(KeyFrame *pKF){}
	void clear(){}
};


class Tracker{
public:
	Frame mCurrentFrame;
};

class System{
public:
	Map *mpMap;
	KeyFrameDatabase *mpKeyFrameDatabase;
	Tracker *mpTracker;
};

}	// namespace ORB_SLAM2

#endif /* DUMMYMAP_H_ */