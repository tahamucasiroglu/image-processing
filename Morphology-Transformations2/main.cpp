#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include<locale.h>
#include <string>

#define SINIR 128 //blackorwhite daki siyah beyaz ayrým sýnýrý

using namespace std;
	char temp;
	string img,header,image;
	int w,h;

void resim_oku( char *fileName);
void resim_yaz(char *filename);
void blackOrWite();
void dilation();
void erosion();
void acma();
void kapama();
void erosion2();
void erosion3();
void dilation2();
void dilation3();


void test(int sayi){
	cout<<"Test"<<sayi<<endl;
}



int main(){
	setlocale(LC_ALL, "Turkish");
	char* resim1="img1.bmp", *resim2="img2.bmp",*kaydet="sonuc.bmp";
		
	resim_oku("img1.bmp");
 	blackOrWite();//siyah beyaz yapýlan yer
 	dilation();//dilation iþleminin uygulandýðý yer 3x3 matris ile
 	erosion();//erosion iþleminin uygulandýðý yer 3x3 matris ile
 	acma();// önce erosion sonra dilation uygulanan yer
 	kapama();//acma nýn tersi
	erosion2();// 3x3 matrisin köþeleri çýkartýlarak yapýlan iþlem
	erosion3();//3x3 matrisin köþeleri ile uygulanan iþlem
	dilation2();//3x3 ün köþeleri çýkartýlarak yapýlan iþlem
	dilation3();//3x3 ün köþeleri ile yapýlan iþlem
		
	
	
	return 0;
}


void resim_oku( char *fileName)
{
 fstream resim(fileName,fstream::in|fstream::binary);
 if(!resim.is_open()){
 	cout<<"resim açýlamadý"<<endl;
 	return;
 }
 while(!resim.eof()){
 	resim.get(temp);
 	img+=(int)temp;
 	
 }
 resim.close();
 if(img[0]!='B'&&img[1]!='M'){
 	cout<<"Bu BMP dosyasý deðil"<<endl;
 	exit(1);
 }
 for(int i=0;i<54;i++){
 	header[i]=img[i];
 }
 w=header[18];
 h=header[22];
 w<0 ? w+=256: w=w;
 h<0 ? h+=256: h=h;
 resim.close();
}

void blackOrWite(){
	
	for(int i=54;i<img.length();i++){
		image+=img[i];
	}
	int dosya[image.length()];
	for(int i=0;i<image.length();i++){
		dosya[i]=(int)image[i];
		if(dosya[i]<0){
			dosya[i]+=256;
		}
	}
	for(int i=0;i<image.length();i++){
		if(dosya[i]<SINIR){
			dosya[i]=0;
		}else{
			dosya[i]=255;
		}
	}
	img.clear();
	for(int i=0;i<54;i++){
		img+=header[i];
	}
	for(int i=0;i<image.length();i++){
		img+=dosya[i];
	}
	resim_yaz("blackorwhite.bmp");
	
}

void dilation(){
	
	string baslik,temp;
	for(int i=0;i<img.length();i++){
		temp+=img[i];
	}
	
	
	int matris[h][w],tempmatris[h][w];
	int counter=img.length()-(w*h);
	for(int i=0;i<counter;i++){
		baslik+=img[i];
	}
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			matris[i][j]=img[counter];
			tempmatris[i][j]=img[counter];
			counter++;
			
			if(matris[i][j]<0){
				matris[i][j]+=256;
				tempmatris[i][j]+=256;
			}
		}
	}
	counter=img.length()-(w*h);
	
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(tempmatris[i-1][j-1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i-1][j]==255){
				matris[i][j]=255;
			}else if(tempmatris[i][j-1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i+1][j+1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i][j+1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i+1][j]==255){
				matris[i][j]=255;
			}else if(tempmatris[i+1][j-1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i-1][j+1]==255){
				matris[i][j]=255;
			}
		}
	}
	img.clear();
	
	for(int i=0;i<counter;i++){
		img+=baslik[i];
	}
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
		img+=matris[i][j];
		}
	}
	resim_yaz("dilation.bmp");
	img.clear();
	
	for(int i=0;i<temp.length();i++){
		img+=temp[i];
	}
	
	temp.clear();
	
	
	
}

void erosion(){
string baslik,temp;
	for(int i=0;i<img.length();i++){
		temp+=img[i];
	}
	

	
	
	int matris[h][w],tempmatris[h][w];
	int counter=img.length()-(w*h);
	for(int i=0;i<counter;i++){
		baslik+=img[i];
	}

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			matris[i][j]=img[counter];
			tempmatris[i][j]=img[counter];
			counter++;
			
			if(matris[i][j]<0){
				matris[i][j]+=256;
				tempmatris[i][j]+=256;
			}
		}
	}
	counter=img.length()-(w*h);
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(tempmatris[i-1][j-1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i-1][j]==0){
				matris[i][j]=0;
			}else if(tempmatris[i][j-1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i+1][j+1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i][j+1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i+1][j]==0){
				matris[i][j]=0;
			}else if(tempmatris[i+1][j-1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i-1][j+1]==0){
				matris[i][j]=0;
			}
		}
	}
	img.clear();

	for(int i=0;i<counter;i++){
		img+=baslik[i];
	}
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
		img+=matris[i][j];
		}
	}
	resim_yaz("erosion.bmp");
	img.clear();

	for(int i=0;i<temp.length();i++){
		img+=temp[i];
	}
	
	temp.clear();
	
}

void acma(){
		string baslik,temp;
	for(int i=0;i<img.length();i++){
		temp+=img[i];
	}
	

	
	
	int matris[h][w],tempmatris[h][w];
	int counter=img.length()-(w*h);
	for(int i=0;i<counter;i++){
		baslik+=img[i];
	}

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			matris[i][j]=img[counter];
			tempmatris[i][j]=img[counter];
			counter++;
			
			if(matris[i][j]<0){
				matris[i][j]+=256;
				tempmatris[i][j]+=256;
			}
		}
	}
	counter=img.length()-(w*h);
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(tempmatris[i-1][j-1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i-1][j]==0){
				matris[i][j]=0;
			}else if(tempmatris[i][j-1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i+1][j+1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i][j+1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i+1][j]==0){
				matris[i][j]=0;
			}else if(tempmatris[i+1][j-1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i-1][j+1]==0){
				matris[i][j]=0;
			}
		}
	}
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			tempmatris[i][j]=matris[i][j];		
		}
	}
	
	
		for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(tempmatris[i-1][j-1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i-1][j]==255){
				matris[i][j]=255;
			}else if(tempmatris[i][j-1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i+1][j+1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i][j+1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i+1][j]==255){
				matris[i][j]=255;
			}else if(tempmatris[i+1][j-1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i-1][j+1]==255){
				matris[i][j]=255;
			}
		}
	}
	
	
	
	
	
	img.clear();

	for(int i=0;i<counter;i++){
		img+=baslik[i];
	}
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
		img+=matris[i][j];
		}
	}
	resim_yaz("acma.bmp");
	img.clear();

	for(int i=0;i<temp.length();i++){
		img+=temp[i];
	}
	
	temp.clear();
	
}
void kapama(){
			string baslik,temp;
	for(int i=0;i<img.length();i++){
		temp+=img[i];
	}
	

	
	
	int matris[h][w],tempmatris[h][w];
	int counter=img.length()-(w*h);
	for(int i=0;i<counter;i++){
		baslik+=img[i];
	}

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			matris[i][j]=img[counter];
			tempmatris[i][j]=img[counter];
			counter++;
			
			if(matris[i][j]<0){
				matris[i][j]+=256;
				tempmatris[i][j]+=256;
			}
		}
	}
	counter=img.length()-(w*h);
	
		for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(tempmatris[i-1][j-1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i-1][j]==255){
				matris[i][j]=255;
			}else if(tempmatris[i][j-1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i+1][j+1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i][j+1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i+1][j]==255){
				matris[i][j]=255;
			}else if(tempmatris[i+1][j-1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i-1][j+1]==255){
				matris[i][j]=255;
			}
		}
	}
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			tempmatris[i][j]=matris[i][j];		
		}
	}
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(tempmatris[i-1][j-1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i-1][j]==0){
				matris[i][j]=0;
			}else if(tempmatris[i][j-1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i+1][j+1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i][j+1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i+1][j]==0){
				matris[i][j]=0;
			}else if(tempmatris[i+1][j-1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i-1][j+1]==0){
				matris[i][j]=0;
			}
		}
	}
	
	
	
	
	
	
	img.clear();

	for(int i=0;i<counter;i++){
		img+=baslik[i];
	}
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
		img+=matris[i][j];
		}
	}
	resim_yaz("kapama.bmp");
	img.clear();

	for(int i=0;i<temp.length();i++){
		img+=temp[i];
	}
	
	temp.clear();
	
}

void erosion2(){
	string baslik,temp;
	for(int i=0;i<img.length();i++){
		temp+=img[i];
	}
	
	int matris[h][w],tempmatris[h][w];
	int counter=img.length()-(w*h);
	for(int i=0;i<counter;i++){
		baslik+=img[i];
	}

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			matris[i][j]=img[counter];
			tempmatris[i][j]=img[counter];
			counter++;
			
			if(matris[i][j]<0){
				matris[i][j]+=256;
				tempmatris[i][j]+=256;
			}
		}
	}
	counter=img.length()-(w*h);
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(tempmatris[i-1][j]==0){
				matris[i][j]=0;
			}else if(tempmatris[i][j-1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i][j+1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i+1][j]==0){
				matris[i][j]=0;
			}
		}
	}
	img.clear();

	for(int i=0;i<counter;i++){
		img+=baslik[i];
	}
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
		img+=matris[i][j];
		}
	}
	resim_yaz("erosion_2.bmp");
	img.clear();

	for(int i=0;i<temp.length();i++){
		img+=temp[i];
	}
	
	temp.clear();
}

void erosion3(){
string baslik,temp;
	for(int i=0;i<img.length();i++){
		temp+=img[i];
	}
	

	
	
	int matris[h][w],tempmatris[h][w];
	int counter=img.length()-(w*h);
	for(int i=0;i<counter;i++){
		baslik+=img[i];
	}

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			matris[i][j]=img[counter];
			tempmatris[i][j]=img[counter];
			counter++;
			
			if(matris[i][j]<0){
				matris[i][j]+=256;
				tempmatris[i][j]+=256;
			}
		}
	}
	counter=img.length()-(w*h);
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(tempmatris[i-1][j-1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i+1][j+1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i+1][j-1]==0){
				matris[i][j]=0;
			}else if(tempmatris[i-1][j+1]==0){
				matris[i][j]=0;
			}
		}
	}
	img.clear();

	for(int i=0;i<counter;i++){
		img+=baslik[i];
	}
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
		img+=matris[i][j];
		}
	}
	resim_yaz("erosion_3.bmp");
	img.clear();

	for(int i=0;i<temp.length();i++){
		img+=temp[i];
	}
	
	temp.clear();
	
}


void dilation2(){
	
	string baslik,temp;
	for(int i=0;i<img.length();i++){
		temp+=img[i];
	}
	
	
	int matris[h][w],tempmatris[h][w];
	int counter=img.length()-(w*h);
	for(int i=0;i<counter;i++){
		baslik+=img[i];
	}
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			matris[i][j]=img[counter];
			tempmatris[i][j]=img[counter];
			counter++;
			
			if(matris[i][j]<0){
				matris[i][j]+=256;
				tempmatris[i][j]+=256;
			}
		}
	}
	counter=img.length()-(w*h);
	
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			 if(tempmatris[i-1][j]==255){
				matris[i][j]=255;
			}else if(tempmatris[i][j-1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i][j+1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i+1][j]==255){
				matris[i][j]=255;
			}
		}
	}
	img.clear();
	
	for(int i=0;i<counter;i++){
		img+=baslik[i];
	}
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
		img+=matris[i][j];
		}
	}
	resim_yaz("dilation_2.bmp");
	img.clear();
	
	for(int i=0;i<temp.length();i++){
		img+=temp[i];
	}
	
	temp.clear();
	
}


void dilation3(){
	
	string baslik,temp;
	for(int i=0;i<img.length();i++){
		temp+=img[i];
	}
	
	
	int matris[h][w],tempmatris[h][w];
	int counter=img.length()-(w*h);
	for(int i=0;i<counter;i++){
		baslik+=img[i];
	}
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			matris[i][j]=img[counter];
			tempmatris[i][j]=img[counter];
			counter++;
			
			if(matris[i][j]<0){
				matris[i][j]+=256;
				tempmatris[i][j]+=256;
			}
		}
	}
	counter=img.length()-(w*h);
	
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(tempmatris[i-1][j-1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i+1][j+1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i+1][j-1]==255){
				matris[i][j]=255;
			}else if(tempmatris[i-1][j+1]==255){
				matris[i][j]=255;
			}
		}
	}
	img.clear();
	
	for(int i=0;i<counter;i++){
		img+=baslik[i];
	}
	
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
		img+=matris[i][j];
		}
	}
	resim_yaz("dilation3.bmp");
	img.clear();
	
	for(int i=0;i<temp.length();i++){
		img+=temp[i];
	}
	
	temp.clear();
	
	
	
}





void resim_yaz(char *filename){
	fstream cikti(filename,fstream::out|fstream::binary);
	cikti<<img;
	cikti.close();
}

