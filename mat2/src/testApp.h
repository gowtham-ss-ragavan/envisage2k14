#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
                void exit();
		void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	        ofxCvColorImage colorImg;

	ofxCvGrayscaleImage grayImage; // grayscale depth image
	ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
	ofxCvGrayscaleImage grayThreshFar; // the far thresholded image

	ofxCvContourFinder contourFinder;

	bool bThreshWithOpenCV;
	bool bDrawPointCloud;

	int nearThreshold;
	int farThreshold;

	int angle;

	// used for viewing the point cloud
	ofEasyCam easyCam;
                ofxKinect kinect;
		ofVideoPlayer mat;
		//ofVideoPlayer disco;
		ofTrueTypeFont font;
		ofTrueTypeFont font1;
		ofSoundPlayer envi;
		ofSoundPlayer final;
		ofSoundPlayer matrix;
};
