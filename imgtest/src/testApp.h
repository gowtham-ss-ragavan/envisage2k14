#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

// uncomment this to read from two kinects simultaneously
//#define USE_TWO_KINECTS

class testApp : public ofBaseApp {
public:

	void setup();
	void update();
	void draw();
	void exit();
	//void kinect();
	void drawPointCloud();

	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	ofTrueTypeFont myfont;
	ofxKinect kinect;

#ifdef USE_TWO_KINECTS
	ofxKinect kinect2;
#endif

	ofxCvColorImage colorImg;

	ofxCvGrayscaleImage grayImage; // grayscale depth image
	ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
	ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
        ofxCvGrayscaleImage grayThreshMid;
        
	ofxCvContourFinder contourFinder;
        ofTrueTypeFont font;     //font
	bool bThreshWithOpenCV;
	bool bDrawPointCloud;

	int nearThreshold;
	int farThreshold;
        int midThreshold;
	int angle;

	// used for viewing the point cloud
	ofEasyCam easyCam;
	
	//sound
	        ofSoundPlayer  state1;
		ofSoundPlayer  state2;
		ofSoundPlayer  state3;
		ofSoundPlayer  state4;
		ofSoundPlayer  state5;
		ofSoundPlayer  state6;
		ofSoundPlayer  state7;
		ofSoundPlayer  state8;
	//image
		ofImage  image;
		ofImage  image1;
		ofImage  image2;
		ofImage  image3;
		ofImage  image4;
		ofImage  image5;
		ofImage  image6;
		ofImage  image7;
		ofImage  image8;
	//spotlight
		ofLight pointLight;
	ofLight spotLight;
	ofLight directionalLight;
	
	ofMaterial material;
    ofImage ofLogoImage;
	
	float radius;
	ofVec3f center;
	bool bShiny;
    bool bSmoothLighting;
	bool bPointLight, bSpotLight, bDirLight;
    bool bUseTexture;
    //video
    ofVideoPlayer 		india;
};
