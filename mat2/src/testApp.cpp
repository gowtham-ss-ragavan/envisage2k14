#include "testApp.h"
int f,a,w,d;
long int e,g;
int b[8]={0,0,0,0,0,0,0,0};
long int xPos,yPos;
float z;
//int cr,cg,cb;
//--------------------------------------------------------------
void testApp::setup(){

       // ofSetVerticalSync(true);
        font.loadFont("Dystopian Future.ttf", 100);
        font1.loadFont("Dystopian Future.ttf", 150);
        //matrix.loadSound("prom.wav");
        envi.loadSound("metal_stamp.mp3");
        final.loadSound("mob.wav");
        //matrix.setLoop(false);
        final.setLoop(false);
        envi.setMultiPlay(false);
        final.setMultiPlay(false);
        mat.loadMovie("matrix.mp4");
       // disco.loadMovie("disco.mp4");
	mat.play();

	/*if(e==1)
                {
                  mat.closeMovie();
                disco.play();
                 //disco.update();
                }
	*/
	//if(e==1)
	//disco.play();

	ofSetLogLevel(OF_LOG_VERBOSE);

	// enable depth->video image calibration
	kinect.setRegistration(true);

	kinect.init(true);
	//kinect.init(true); // shows infrared instead of RGB video image
	//kinect.init(false, false); // disable video image (faster fps)

	kinect.open();		// opens first available kinect
	//kinect.open(1);	// open a kinect by id, starting with 0 (sorted by serial # lexicographically))
	//kinect.open("A00362A08602047A");	// open a kinect using it's unique serial #
     //   kinect.mirror();
//	#endif

	colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);

	nearThreshold = 170;
	farThreshold = 160;
	//bThreshWithOpenCV = true;

	ofSetFrameRate(30);
	//h=0;

	// zero the tilt on startup
	//angle = 0;
	//kinect.setCameraTiltAngle(angle);
//	cr=250;
//	cg=0;
//	cb=50;
}

//--------------------------------------------------------------
void testApp::update(){

        mat.update();
        //disco.update();
        kinect.update();
        ofSoundUpdate();

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
                        // pix = flipImage(pix, 640, 480, 3);
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
		contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 100, false);

	xPos=0;
	yPos=0;

		if (contourFinder.nBlobs)
		{
			//float xPos,yPos;
			for ( w=0; w < contourFinder.nBlobs; w++)	{
				xPos = kinect.width-contourFinder.blobs[w].centroid.x;
				yPos = contourFinder.blobs[w].centroid.y;
				//cout << xPos << endl;
			}
		}
}
        z=kinect.getDistanceAt(xPos,yPos);
                //Kinect mapping

                f=0;
                a=0;
                while(a<600)
		{

			//cout<<f<<'\n'<<endl;
			if(xPos>a && xPos<a+75)
			{
			       b[f]=1;
				break;
			}
			if( f==7)
			{
		        f++;
			}
			f++;
	      		a+=75;
		}

		if(b[0]==1 && b[1]==1 && b[2]==1 && b[3]==1 && b[4]==1 && b[5]==1 && b[6]==1 && b[7]==1)
		{
                            // if(xPos>500 && xPos<600)
                          //   {
                             //   if(yPos>350 && yPos<480)
                               //   {
                                        e++;
                                        g=1;

                                        for(d=0;d<8;d++)
                                        {
                                                b[d]=0;
                                        }
                                        //cr-=10;
                                        //cg+=20;
                                        //cb+=5;

                                       /* if(xPos>500 && xPos<600)
                                        {
                                                if(yPos>350 && yPos<480)
                                                       h++;
                                        }*/
                               //   }
                          //  }
                }


        }

//-------------------------------------------------------------
void testApp::draw(){

        mat.draw(0,0);
        // myfont.drawString("VIRTUAL PIANO", cx,45);
        //if(h==1)
        //matrix.play();

       if(b[0]==1)
       {        ofSetColor(0,0,0);
                ofRect(0,0,128,768);
                ofSetColor(255);
                font.drawString("E",40,350);

       }
        if(b[1]==1)
       {        ofSetColor(0,0,0);
                ofRect(128,0,128,768);
                ofSetColor(255);
                font.drawString("N",158,350);
       }
        if(b[2]==1)
       {        ofSetColor(0,0,0);
                ofRect(256,0,128,768);
                ofSetColor(255);
                font.drawString("V",286,350);
               // envi.play();
       }
        if(b[3]==1)
       {        ofSetColor(0,0,0);
                ofRect(384,0,128,768);
                ofSetColor(255);
                font.drawString("I",424,350);
               // envi.play();
       }
        if(b[4]==1)
       {        ofSetColor(0,0,0);
                ofRect(512,0,128,768);
                ofSetColor(255);
                font.drawString("S",542,350);
               // envi.play();
       }
        if(b[5]==1)
       {        ofSetColor(0,0,0);
                ofRect(640,0,128,768);
                ofSetColor(255);
                font.drawString("A",670,350);
               // envi.play();
       }
        if(b[6]==1)
       {        ofSetColor(0,0,0);
                ofRect(768,0,128,768);
                ofSetColor(255);
                font.drawString("G",798,350);
               // envi.play();
       }
        if(b[7]==1)
       {        ofSetColor(0,0,0);
                ofRect(896,0,1,768);
                ofSetColor(255);
                font.drawString("E",926,350);
               // envi.play();
       }
        if(g!=1)
        {
       switch(f)
       {
                case 0: envi.play();break;
                case 1: envi.play();break;
                case 2: envi.play();break;
                case 3: envi.play();break;
                case 4: envi.play();break;
                case 5: envi.play();break;
                case 6: envi.play();break;
                case 7: envi.play();break;
       }
       }
                if(g==1)
                {
                        //disco.draw(0,0,1366,768);
                       /* switch(h)
                        {
                                case 1: ofSetColor(255);
                                        ofRect(0,0,1366,768);
                                        ofSetColor(0);
                                         break;

                                case 2: ofSetColor(0,100,150);
                                        ofRect(0,0,1366,768);
                                        ofSetColor(0);
                                         break;

                                case 3: ofSetColor(210,24,50);
                                        ofRect(0,0,1366,768);
                                        ofSetColor(0);
                                         break;

                                case 4: ofSetColor(12,205,30);
                                        ofRect(0,0,1366,768);
                                        ofSetColor(0);
                                         break;

                                case 5: ofSetColor(30,70,210);
                                        ofRect(0,0,1366,768);
                                        ofSetColor(0);
                                         break;

                                default: ofSetColor(255);
                                        ofRect(0,0,1366,768);
                                        ofSetColor(0);
                                        break;

                          } */

                          ofSetColor(255);
                                        ofRect(0,0,1366,768);
                                        ofSetColor(0);
                         font1.drawString("ENVISAGE",30,350);


                        envi.stop();
                        envi.unloadSound();
                        //matrix.stop();
                        //matrix.unloadSound();
                        //final.play();
                        //ofSetColor(255);


                }
                if(e==1)
                {
                final.play();
                e++;
                }
        //grayImage.draw(0,0,1366,768);
        //contourFinder.draw(0,0,1366,768);
        ofSetColor(255);
        ofCircle((1.7)*xPos,(1.6)*yPos,10);
        ofSetColor(255);
        cout<< xPos << ',' << yPos << ',' << z << endl;
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
	}
}
/*
//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}
*/
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
/*
//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}*/
