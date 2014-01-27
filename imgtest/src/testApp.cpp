#include "testApp.h"
//int n,p,flag;
int p,q,flag;
int a;
int r;
float b;
int f,o;
long int sum,im,jm,w;
//long int im,in,jm,jk,e,f,g;
//int n;
int cx,col,h;
long int xPos,yPos;
ofColor bgrey;
//video
//int bann=0;

//indiamap
//int d[7];            //distance
int i,j;
int t[8]={0,0,0,0,0,0,0,0};
int s[9]={0,0,0,0,0,0,0,0,0};
long int x1St[8] = {206,137,361,215,245,170,424,190};
long int x2St[8] = {232,240,407,263,317,234,501,200};
long int y1St[8] = {93,122,230,384,306,254,151,387};
long int y2St[8] = {116,195,280,456,374,324,255,453};
//int mint[7] = {43,72,57,63,45,50,70};
//--------------------------------------------------------------
void testApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);

	// enable depth->video image calibration
	kinect.setRegistration(true);

	kinect.init(true);
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
	//indiamap
	//Sound loading
	state1.loadSound("thunukthunuk.wav");
	state2.loadSound("rangeelomharodholna.wav");
	state3.loadSound("amijetomar.wav");
	state4.loadSound("tnmankatha.wav");
	state5.loadSound("Ap.wav");
	state6.loadSound("dhagala.wav");
	//state7.loadSound("percussion.wav");
	state8.loadSound("neram-pista.wav");
	//state9.loadSound();
	//Sound setvolume
    state1.setVolume(1.0f);
	state2.setVolume(1.0f);
	state3.setVolume(1.0f);
	state4.setVolume(1.0f);
    state5.setVolume(1.0f);
	state6.setVolume(1.0f);
	state7.setVolume(1.0f);
	state8.setVolume(1.0f);
	//state9.setVolume(1.0f);
        //loading image
        image.loadImage("main.png");
        image1.loadImage("pun1.jpg");
        image2.loadImage("raj2.jpg");
        image3.loadImage("wb3.jpg");
        image4.loadImage("tn4.jpg");
        image5.loadImage("ap5.jpg");
        image6.loadImage("maha6.jpg");
        //image6.loadImage("main.jpg");
        image7.loadImage("7sis7.jpg");
        image8.loadImage("kerala8.jpg");
        //image9.loadImage("kar9.jpg");
        //conversion to Kinect coordinates
       /* for(i=0;i<7;i++)
            {
                x1St[i] = ((x1St[i] - 32 )*5)/8;
                y1St[i] = (y1St[i]*5)/8;
                //mint[i] = (mint[i] * 5)/8;
                x2St[i] = ((x2St[i] - 32 )*5)/8;
                y2St[i] = (y2St[i]*5)/8;
            }*/
            //video loading
            india.loadMovie("India.mp4");
            //india.play();

            bgrey.r = 79;
            bgrey.g = 81;
            bgrey.b = 76;
            bgrey.setHsb(59.5,4.25,22.667);

	//kinect.init(true); // shows infrared instead of RGB video image
	//kinect.init(false, false); // disable video image (faster fps)

	//kinect.open();		// opens first available kinect
	//kinect.open(1);	// open a kinect by id, starting with 0 (sorted by serial # lexicographically))
	//kinect.open("A00362A08602047A");	// open a kinect using it's unique serial #
/*
//	#endif

	colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);

	nearThreshold = 195;
	farThreshold = 185;
	//bThreshWithOpenCV = true;

	ofSetFrameRate(30);

	// zero the tilt on startup
	//angle = 0;
	//kinect.setCameraTiltAngle(angle);
*/
            //font
           // font.loadFont("5thagent.ttf",5);
          /*  //spotlight
            ofEnableDepthTest();
            spotLight.setDiffuseColor( ofColor(255.f, 0.f, 0.f));
            spotLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
            // size of the cone of emitted light, angle between light axis and side of cone //
            // angle range between 0 - 90 in degrees //
            spotLight.setSpotlightCutOff( 50 );

            // rate of falloff, illumitation decreases as the angle from the cone axis increases //
            // range 0 - 128, zero is even illumination, 128 is max falloff //
            spotLight.setSpotConcentration( 45 );
            bSpotLight=true;*/

            o=0;
            r=0;
}
//--------------------------------------------------------------
void testApp::update(){
	ofBackground(76,76,76);

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
		contourFinder.findContours(grayImage, 100, (kinect.width*kinect.height)/2, 50, false);
		}
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

	//Region generation and Key selection for Kinect
        //Indiamap
	//finding distance from each state
	/*        f=0;
		for(i=0;i<7;i++)
		{
		        d[i] =  ofDist( xPos, yPos,  xSt[i],  ySt[i] );

		}

	//finding minimum.
        int smallest=d[0];
        int j=0;
                for (i=0;i<7;i++)
                {
                        if (d[i]<=smallest)
                        {
                                smallest=d[i];


                        }
                }

                for (i=0;i<7;i++)
                {
                        if (d[i]==smallest)
                        {
                                j=i;
                                break;

                        }
                }
                int u=mint[j];
                if (u > smallest)
                {
                        f=j+1;
                }
*/
        if(o!=1)
        {
        for(i=0;i<8;i++)
        {
                if (xPos>x1St[i] && xPos<x2St[i])
                {
                        if(yPos>y1St[i] && yPos<y2St[i])
                        {
                                f=i+1;
                                s[i+1]=1;
                                break;
                        }
                }
        }
        }
        //spotlight
        //cos(ofGetElapsedTimef()) * RAD_TO_DEG
        //spotLight.setOrientation( ofVec3f( 0, 5, 0) );
        //spotLight.setPosition( xPos, yPos, 0);
	// update the sound playing system:
	ofSoundUpdate();
        cout<<f<<endl;
        if(s[f]==1)
        {
	switch(f)
	{
	        case 1:
	               {
	                        state1.play();
	                        state2.stop();
	                        state3.stop();
	                        state4.stop();
	                        state5.stop();
	                        state6.stop();
	                        //state7.stop();
	                        state8.stop();
	                        t[f-1]++;
	                        //spotlight
	                        //spotLight.setPosition( 370, 160, 200);
	                        break;
	               }
	        case 2:
	                {
	                        state2.play();
	                        state1.stop();
	                        state3.stop();
	                        state4.stop();
	                        state5.stop();
	                        state6.stop();
	                       // state7.stop();
	                        state8.stop();
	                        t[f-1]++;
	                        //spotLight.setPosition( 310, 280, 200);
	                        break;
	                }
	        case 3:
	                {
	                        state3.play();
	                        state1.stop();
	                        state2.stop();
	                        state4.stop();
	                        state5.stop();
	                        state6.stop();
	                        //state7.stop();
	                        state8.stop();
	                        t[f-1]++;
	                        //spotLight.setPosition( 660, 360, 200);
	                        break;
	                }
	        case 4:
	                {
	                        state4.play();
	                        state1.stop();
	                        state3.stop();
	                        state2.stop();
	                        state5.stop();
	                        state6.stop();
	                        //state7.stop();
	                        state8.stop();
	                        t[f-1]++;
	                        //spotLight.setPosition( 380, 690, 200);
	                        break;
	                 }
	        case 5:
	                {
	                        state5.play();
	                        state1.stop();
	                        state3.stop();
	                        state4.stop();
	                        state2.stop();
	                        state6.stop();
	                        //state7.stop();
	                        state8.stop();
	                        t[f-1]++;
	                        //spotLight.setPosition( 430, 530, 200);
	                        break;
	                }
	        case 6:
	                   {
	                        state6.play();
	                        state1.stop();
	                        state3.stop();
	                        state4.stop();
	                        state5.stop();
	                        state2.stop();
	                        //state7.stop();
	                        state8.stop();
	                        t[f-1]++;
	                        //spotLight.setPosition( 330, 450, 200);
	                        break;
	                    }
	        case 7:
	                {
	                        //state7.stop();
	                        state1.stop();
	                        state3.stop();
	                        state4.stop();
	                        state5.stop();
	                        state6.stop();
	                        state2.stop();
	                        state8.stop();
	                        t[f-1]++;
	                        //spotLight.setPosition( 810, 290, 200);
	                        break;
	                 }
	        case 8:
	                {
	                        state8.play();
	                        state1.stop();
	                        state3.stop();
	                        state4.stop();
	                        state5.stop();
	                        state6.stop();
	                        state2.stop();
	                        //state7.stop();
	                        t[f-1]++;
	                       //spotLight.setPosition( 320, 665, 200);
	                        break;
	                 }
	}
	}
	s[f]++;

	india.update();

                if(t[0]>=1 && t[1]>=1 && t[2]>=1 && t[3]>=1 && t[4]>=1 && t[5]>=1 && t[6]>=1 && t[7]>=1 && r==0)
                {
                                ofBackground(255);
                                o=1;
                                r=1;
                                r++;
                                state1.stop();
	                        state3.stop();
	                        state4.stop();
	                        state5.stop();
	                        state6.stop();
	                        state2.stop();
	                        //state7.stop();
	                        state8.stop();
	                         india.play();
	         }

}

//--------------------------------------------------------------
void testApp::draw(){
        if(o!=1)
        {
            ofSetColor(255,255,255);
            image.draw(0,0);
	//indiamap
      switch(f)
	{
	       case 0:
	                image.draw(0,0);
	                break;
	        case 1: image1.draw(0,0);
	                //font.drawString("Punjab", 490,160);
	                break;
	        case 2: image2.draw(0,0);
	                //font.drawString("Rajasthan",400,280);
	                break;
	        case 3: image3.draw(0,0);
	                //font.drawString("West Bengal", 760, 360);
	                break;
	        case 4: image4.draw(0,0);
	                //font.drawString("Tamil Nadu", 440, 690);
	                break;
	        case 5: image5.draw(0,0);
	                //font.drawString("Andhra Pradesh", 470, 530);
	                break;
	        case 6: image6.draw(0,0);
	                //font.drawString("Maharashtra", 400, 450);
	                break;
	        case 7: image.draw(0,0);
	                //font.drawString("7 Sisters", 900, 290);
	                break;
                case 8: image8.draw(0,0);
	                //font.drawString("7 Sisters", 900, 290);
	                break;
	}

	//spotlight
	 /*       // enable lighting //
                ofEnableLighting();
                // activate the lights //
	        if (bSpotLight) spotLight.enable();
                if(bSpotLight) spotLight.draw();
                if (!bSpotLight) spotLight.disable();
	        ofDisableLighting();
	        ofSetColor(255, 0, 0);
	        ofSetColor( spotLight.getDiffuseColor() );
	        if(bSpotLight) spotLight.draw();
	        ofSetColor(255);*/
               // grayImage.draw(171, 0, 1024, 768);
		//contourFinder.draw(171, 0, 1024, 768);
		ofSetColor(0,255,0);
        ofCircle(1.7*xPos,1.6*yPos,10);
                ofSetColor(255);
                }
    //cout<<xPos<<','<<yPos<<endl;
        if(r==2)
        {
                ofBackground(255);
                india.draw(0,0);

        }
        ofSetColor(0);
ofDrawBitmapString(ofToString(xPos)+ofToString(yPos) ,100,750);
ofSetColor(255);
       // cout<<bann<<endl;
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

//--------------------------------------------------------------
/*void testApp::keyReleased(int key){

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
//
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
/*
ofSetColor(255);

ofDrawBitmapString(ofToString(x)+ofToString(y) ,100,650);
ofSetColor(0);
*/
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
/*void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}*/
