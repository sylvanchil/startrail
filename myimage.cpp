/************************************
*    name: cong qiu                 *
*    email: congq@g.clemson.edu     *
*    date: OCT, 4th, 2015           *
*************************************/

#include"myimage.h"
#include<cstring>

MyImage::MyImage(int wid, int hei, int chan, float* dat):
	width(wid),
	height(hei),
	channels(chan),
	data(new float[width*height*channels])
{
	memcpy(data, dat, width*height*channels*sizeof(float));
	delete dat;
}


MyImage& MyImage::operator=(const MyImage& my)
{
	width= my.width;
	height= my.height;
	channels = my.channels;
	
	delete[] data;
	data = new float[width*height*channels];
	
	memcpy(data, my.data, width*height*channels*sizeof(float));

	

	return *this;

}

MyImage MyImage::to4ChannelsImage(){
	if(channels ==4){
		MyImage img(*this);
		return img;
	}

	float* newData = new float[width*height*4*sizeof(float)];
	for(int y = 0; y!= height; y++){
		for(int x = 0;x != width; x ++){
			for(int c = 0; c != 4; c ++){
				if(c < 3){
					newData[c+x*4+y*width*4] = data[c+x*3+y*width*3];
				}else{
					newData[c+x*4+y*width*4]= 1.0;	
				}
			}
		}
	}
	MyImage img(width, height, 4, newData);
	return img;	
}

MyImage MyImage::over(MyImage& image, int posx, int posy){
	MyImage newImage(image.to4ChannelsImage());

	for(int y = 0; y< height && (y+posy)< newImage.height ; y++){
		for(int x = 0; x< width && (x+posx< newImage.width ); x++){
			for(int c = 0; c< 3; c++){
				newImage.data[c + (x+posx) *4 + (y+posy)*newImage.width*4]=
				newImage.data[c + (x+posx) *4 + (y+posy)*newImage.width*4] * (255-data[3+x*4+y*width*4])/255+data[c+ x*4 + y*width*4]*(data[3+x*4+y*width*4])/255;
				 
			}
		
		}
	}
	return newImage;

}

void MyImage::displayOutput(float* desBuff){
	for(int y = 0; y < height ; y ++){
		for(int x = 0;x < width; x++){
			for(int c = 0; c < channels; c++){
				desBuff[c + x *channels + (height-1-y)*width*channels] = data[c + x *channels + y * width * channels];
			
			}
		}
	}

}


























