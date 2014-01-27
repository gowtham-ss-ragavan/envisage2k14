#include "testApp.h"

int frame;
float speed,volume,vf;
int width,height;
/*
Mouse pressed -->(133,148)
Mouse Released -->(210,250)
Mouse pressed -->(218,503)
Mouse Released -->(298,609)
Mouse pressed -->(611,509)
Mouse Released -->(705,615)
Mouse pressed -->(639,116)
Mouse Released -->(732,212)
Mouse pressed -->(829,356)
Mouse Released -->(895,446)
Mouse pressed -->(424,80)
Mouse Released -->(502,168)
Mouse pressed -->(469,539)
Mouse Released -->(540,631)
Mouse pressed -->(78,332)
Mouse Released -->(166,415)
*/
int smaller_x[8] = {133,218,611,639,829,424,469,78};
int larger_x[8] = {210,298,705,732,895,502,540,166};
int smaller_y[8]= {148,503,509,116,356,80,539,332};
int larger_y[8] = {250,609,615,212,446,168,631,415};
int stop_frame[8]={225,248,263,278,293,308,323,338};
int i = 0;
int j =0;

int f;
long int w;
long int xPos,yPos;
//--------------------------------------------------------------
void testApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);

	// enable depth->video image calibration
	kinect.setRegistration(true);

	kinect.init();
	//kinect.init(true); // shows infrared instead of RGB video image
	//kinect.init(false, false); // disable video image (faster fps)

	kinect.open();		// opens first available kinect
	//kinect.open(1);	// open a kinect by id, starting with 0 (sorted by serial # lexicographically))
	//kinect.open("A00362A08602047A");	// open a kinect using it's unique serial #

//	#endif

	colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);

	nearThreshold = 170;
	farThreshold = 160;
	//bThreshWithOpenCV = true;

	ofSetFrameRate(30);

	// zero the tilt on startup
	//angle = 0;
	//kinect.setCameraTiltAngle(angle);


	//Video initialization begins for the starting video
ofBackground(0,0,0);
vidfile.loadMovie("/home/ssgowtham12/text.mp4");
vidfile.play();
width= vidfile.getWidth();
height = vidfile.getHeight();
cout<<width<<' '<<'*'<<' '<<height<<'\n';



for(j=0;j<8;j++)
{
smaller_x[j]= ((smaller_x[j]-32)*5)/8;
}

for(j=0;j<8;j++)
{
larger_x[j]= ((larger_x[j]-32)*5)/8;
}


for(j=0;j<8;j++)
{
smaller_y[j]= (smaller_y[j]*480)/768;
}

for(j=0;j<8;j++)
{
larger_y[j]= (larger_y[j]*480)/768;
}
j=0;

}
//--------------------------------------------------------------
void testApp::update(){
	//ofBackground(100, 100, 100);

	kinect.update();

	// there is a new frame and we are connected
	if(kinect.isFrameNew()) {

		// load grayscale depth image from the kinect source
		grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);

		// we do two thresholds - one for the far plane and one for the near plane
		// we then do a cvAnd to get the pixels which are a union of the two thresholds
		/*if(bThreshWithOpenCV) {
			grayThreshNear = grayImage;
			grayThreshFar = grayImage;
			grayThreshNear.threshold(nearThreshold, true);
			grayThreshFar.threshold(farThreshold);
			cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
		} *///else {

			// or we do it ourselves - show people how they can work with the pixels
			unsigned char * pix = grayImage.getPixels();

			int numPixels = grayImage.getWidth() * grayImage.getHeight();
			for(int i = 0; i < numPixels; i++) {
				if(pix[i] < nearThreshold && pix[i] > farThreshold) {
					pix[i] = 255;
				} else {
					pix[i] = 0;
				}
			}


		// update the cv images
		grayImage.flagImageChanged();

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
	xPos=0;
	yPos=0;

		if (contourFinder.nBlobs)
		{
			//float xPos,yPos;
			for ( w=0; w < contourFinder.nBlobs; w++)	{
				xPos =kinect.width - contourFinder.blobs[w].centroid.x;
				yPos = contourFinder.blobs[w].centroid.y;
				//cout << xPos << endl;
			}
		}

	//Region generation and Key selection for Kinect

	}

	vidfile.update();

frame = vidfile.getCurrentFrame();
speed = vidfile.getSpeed();

}

//--------------------------------------------------------------
void testApp::draw(){

//Starting Video

vidfile.draw(0,0,width,height);
//ofDrawBitmapString("Frame No : "+ofToString(frame),20,600);
//ofDrawBitmapString("Speed : "+ofToString(speed),20,700);
//ofDrawBitmapString(ofToString(width)+ofToString(height),20,750);
/*ofSetColor(255,255,0);
ofRect(191,height-55,vidfile.getPosition()*(width-40),10);
ofSetColor(255);*/

//Check if the correct frame has arrived
if(frame == stop_frame[j]-1)
{
    vidfile.setPaused(true);
}
        /*ofSetColor(0,255,0);
        ofRect(0,0,1366,768);
        ofSetColor(255);*/
		grayImage.draw(824,618,200,150);
		contourFinder.draw(824,618,200,150);
	//cout<< p+1 << endl;

	/*    if(yPos >= height-55 && yPos <= height - 45)
    {
        if(xPos >=191 && xPos <=191+(width - 40))
            {
                vidfile.setPosition(((float)(xPos-191))/(width-40));
            }
    }*/

    if(xPos >= smaller_x[j] && xPos <= larger_x[j])
    {
        if(yPos>=smaller_y[j] && yPos<= larger_y[j])
            {
                vidfile.setPaused(false);
               j++;
            }
    }

	cout << xPos << ',' << yPos << "," << f << endl;
	//cout << sum << endl;*/
	ofSetColor(255,255,0);
	if(xPos!=0 ||yPos!=0)
	{
	ofCircle(((xPos*8)/5)+32,(yPos*768)/480,8);
	}	
	ofSetColor(255);

}
//--------------------------------------------------------------
void testApp::exit() {
	//kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	switch (key) {
		case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;

		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;

        case 'p':
        vidfile.setPaused(!vidfile.isPaused());
        break;
        /*
        case 'w' :
        vf = vf + 0.1;
        vidfile.setVolume(vf*f);
        break;

        case's':
        vf = vf -0.1;
        vidfile.setVolume(vf*f);
        break;
        */
        case 'd':
        vidfile.nextFrame();
       // speed = speed + 0.2*speed;
        //vidfile.setSpeed(speed);
        break;
        case 'a':
        vidfile.previousFrame();
        //speed = speed -0.2*speed;
       // vidfile.setSpeed(speed);
        break;

	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
cout<<"Mouse Released -->"<<'(' <<x<< ','<<y<<')'<<'\n';
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
